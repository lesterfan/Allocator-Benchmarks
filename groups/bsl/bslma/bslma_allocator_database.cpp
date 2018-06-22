#include <bslma_allocator_database.h>
#include <bslma_default.h>

#include <string>
#include <deque>
#include <ostream>
#include <vector>
#include <map>

#include <iostream>

namespace BloombergLP {

    namespace bslma {

        std::string* getMemoryString();

        // ---------------------------------- AllocatorDatabaseBuffer -----------------------------------------

        template <class T>
        class AllocatorDatabaseBuffer
        {
        public:
            unsigned d_capacity;
            bool d_full;

            std::deque<T> d_deque;

            AllocatorDatabaseBuffer();
            void setCapacity(unsigned capacity);

            void push_back(T input);
            void remove(T input);

            template <class U>
            friend std::ostream& operator<<(std::ostream& os, const AllocatorDatabaseBuffer<U>& circBuff);
        };

        template<class T>
        inline AllocatorDatabaseBuffer<T>::AllocatorDatabaseBuffer() {
            d_capacity = 0;
            d_full = false;
        }

        template<class T>
        inline void AllocatorDatabaseBuffer<T>::setCapacity(unsigned capacity) {
            d_capacity = capacity;
        }

        template<class T>
        inline void AllocatorDatabaseBuffer<T>::push_back(T input) {
            if (d_full) d_deque.pop_front();
            d_deque.push_back(input);
            if (d_deque.size() >= d_capacity) d_full = true;
        }

        template<class T>
        inline void AllocatorDatabaseBuffer<T>::remove(T input) {
            for (auto it = d_deque.begin(); it != d_deque.end(); ++it) {
                if (*it == input) {
                    d_deque.erase(it);
                    d_full = false;
                    break;
                }
            }
        }

        template <class T>
        inline std::ostream& operator<<(std::ostream& os, const AllocatorDatabaseBuffer<T>& circBuff) {
            for (auto it = circBuff.d_deque.rbegin(); it != circBuff.d_deque.rend(); ++it) {
                os << *it << " ";
            }
            return os;
        }


        // ---------------------------------- AllocatorDatabaseTreeNode -----------------------------------------

        class AllocatorDatabaseTreeNode {

        public:
            const void* d_low;
            const void* d_high;
            bool d_flag;
            AllocatorDatabaseBuffer<AllocatorDatabaseTreeNode*> d_lastAccessedChildren;
            void* d_allocator;
            AllocatorDatabaseTreeNode* d_parent;
            std::map<const void*, AllocatorDatabaseTreeNode*> d_children;


            AllocatorDatabaseTreeNode(void* allocator, const void* low, const void* high, int dLen = ALLOCATOR_DATABASE_MAX_CACHE);
            ~AllocatorDatabaseTreeNode();

            int checkContains(const void* newLow, const void* newHigh);
            AllocatorDatabaseTreeNode* getContainingChild(const void* newLow, const void* newHigh);

            void addChild(AllocatorDatabaseTreeNode* child);
            void removeChild(AllocatorDatabaseTreeNode* child);

            friend std::ostream& operator<<(std::ostream& os, const AllocatorDatabaseTreeNode& node);
        };


        // ------------------------------------- AllocatorDatabase_Impl ----------------------------------------------

        // Follows the singleton design pattern.
        class AllocatorDatabase_Impl
        {
            
        public:

            AllocatorDatabase_Impl(const void* low = reinterpret_cast<const void*>(0), const void* high = reinterpret_cast<const void*>(ALLOCATOR_DATABASE_MAX_MEMORY));
            ~AllocatorDatabase_Impl();

            AllocatorDatabaseTreeNode * d_root;

            // void* d_global_allocator;
            bool d_debug;

            AllocatorDatabaseTreeNode* getLowestNode(AllocatorDatabaseTreeNode* ptr, const void* newLow, const void* newHigh);
            int addNode(void* newAllocator, const void* newLow, const void* newHigh);
            int deleteSequence(const void* address);
            void* findAllocator(const void* address);
        };


        // --------------------------- AllocatorDatabaseTreeNode -------------------------------------------
        AllocatorDatabaseTreeNode::AllocatorDatabaseTreeNode(void* allocator, const void* low, const void* high, int dLen) {
            d_allocator = allocator;
            d_low = low;
            d_high = high;
            d_flag = false;
            d_lastAccessedChildren.setCapacity(dLen);
            
        }

        AllocatorDatabaseTreeNode::~AllocatorDatabaseTreeNode()
        {
            for (auto it = d_children.begin(); it != d_children.end(); ++it) {
                AllocatorDatabaseTreeNode* child = it->second;
                delete child;
            }
        }

        int AllocatorDatabaseTreeNode::checkContains(const void* newLow, const void* newHigh)
        {
            // The new sequence is contained in this one
            if (d_low <= newLow && newLow <= newHigh && newHigh <= d_high) {
                return 1;
            }

            // This is the case where there is overlap and is therefore invalid.
            else if ((d_low <= newLow && newLow <= d_high && d_high < newHigh) ||
                (newLow < d_low && d_low <= newHigh && newHigh <= d_high) ||
                (newLow < d_low && d_low <= d_high && d_high <= newHigh)) {
                return 2;
            }

            return 0;
        }

        AllocatorDatabaseTreeNode * AllocatorDatabaseTreeNode::getContainingChild(const void* newLow, const void* newHigh)
        {
            // Check cached children (may not be the cleanest code)
            for (auto it = d_lastAccessedChildren.d_deque.rbegin(); it != d_lastAccessedChildren.d_deque.rend(); ++it) {
                int ret = (*it)->checkContains(newLow, newHigh);
                if (ret == 1) {
                    return *it;
                }
                else if (ret == 2) {
                    d_flag = true;
                    return nullptr;
                }
            }

            // Get the only child that might contain the region [newLow, newHigh]
            std::map<const void*, AllocatorDatabaseTreeNode*>::iterator it = d_children.lower_bound(newLow);
            if (it == d_children.end()) {
                if (d_children.size() > 0) --it;
                else {
                    return nullptr;
                }
            }
            else if (it->first != newLow) --it;

            // Check if the containment is valid (if a containment is found)
            if (it != d_children.end()) {
                int ret = it->second->checkContains(newLow, newHigh);
                if (ret == 1) {
                    d_lastAccessedChildren.push_back(it->second);
                    return it->second;
                }
                else if (ret == 2) {
                    d_flag = true;
                    return nullptr;
                }
            }

            return nullptr;
        }

        void AllocatorDatabaseTreeNode::addChild(AllocatorDatabaseTreeNode* child)
        {
            d_children.insert(std::pair<const void*, AllocatorDatabaseTreeNode*>(child->d_low, child));
            child->d_parent = this;
        }

        void AllocatorDatabaseTreeNode::removeChild(AllocatorDatabaseTreeNode* child)
        {
            d_lastAccessedChildren.remove(child);

            std::map<const void*, AllocatorDatabaseTreeNode*>::iterator  it = d_children.find(child->d_low);
            if (it != d_children.end()) {
                d_children.erase(it);
            }

            // Delete the child to avoid a memory leak.
            delete child;
        }

        std::ostream& operator<<(std::ostream& os, const AllocatorDatabaseTreeNode& node)
        {
            os << "Hello, world!";
            return os;
        }


        // --------------------------- AllocatorDatabase_Impl ---------------------------------------------------

        AllocatorDatabase_Impl::AllocatorDatabase_Impl(const void* low, const void* high)
        {
            // Initialize to a pointer of the global allocator
            // d_global_allocator = Default::defaultAllocator();
            d_debug = false;

            void* newName = nullptr;
            d_root = new AllocatorDatabaseTreeNode(newName, low, high);
        }

        AllocatorDatabase_Impl::~AllocatorDatabase_Impl()
        {
            delete d_root;
        }
        AllocatorDatabaseTreeNode * AllocatorDatabase_Impl::getLowestNode(AllocatorDatabaseTreeNode * ptr, const void* newLow, const void* newHigh)
        {
            AllocatorDatabaseTreeNode* nextChild = ptr->getContainingChild(newLow, newHigh);
            if (nextChild != nullptr) {
                return getLowestNode(nextChild, newLow, newHigh);
            }
            if (ptr->d_flag == true) {
                ptr->d_flag = false;
                return nullptr;
            }

            return ptr;
        }

        int AllocatorDatabase_Impl::addNode(void* newAllocator, const void* newLow, const void* newHigh)
        {
            AllocatorDatabaseTreeNode* lowestNode = getLowestNode(d_root, newLow, newHigh);

            // If there was an error
            if (lowestNode == nullptr) return 1;
            if (lowestNode->d_allocator == newAllocator) return 1;

            // Last sanity check to make sure its contained
            if (lowestNode->checkContains(newLow, newHigh) != 1) return 1;

            AllocatorDatabaseTreeNode* newNode = new AllocatorDatabaseTreeNode(newAllocator, newLow, newHigh);
            lowestNode->addChild(newNode);

            return 0;
        }

        int AllocatorDatabase_Impl::deleteSequence(const void* address)
        {
            AllocatorDatabaseTreeNode* lowestNode = getLowestNode(d_root, address, address);

            // If there was an error
            if (lowestNode == nullptr) return 1;

            if (lowestNode == d_root) return 1;
            lowestNode->d_parent->removeChild(lowestNode);

            return 0;
        }

        void* AllocatorDatabase_Impl::findAllocator(const void* address)
        {
            AllocatorDatabaseTreeNode* lowestNode = getLowestNode(d_root, address, address);
            if (lowestNode == nullptr) return nullptr;

            return lowestNode->d_allocator;
        }


        // ----------------------------- AllocatorDatabase --------------------------------------

        AllocatorDatabase* AllocatorDatabase::d_global_instance = nullptr;
        AllocatorDatabase::AllocatorDatabase(){
            static AllocatorDatabase_Impl impl;
            d_impl = &impl;
        }

        
        // To follow the singleton design pattern.
        AllocatorDatabase* AllocatorDatabase::instance()
        {
            if (nullptr == d_global_instance) {
                static AllocatorDatabase global_instance;
                d_global_instance = &global_instance;
            }
            return d_global_instance;
        }

        void* AllocatorDatabase::lookup(const void* address, bool debug) {
            void* result = AllocatorDatabase::instance()->d_impl->findAllocator(address);

            if (AllocatorDatabase::instance()->d_impl->d_debug){
                int ret = (result == nullptr);
                std::cout << "Ran : lookup(" << address << "); ret = " << ret << ", result = " << result << std::endl;
            }

            // return result == nullptr ? AllocatorDatabase::instance()->d_impl->d_global_allocator : result;
            return result == nullptr? Default::defaultAllocator() : result;
        }

        std::string* getMemoryString() {
            std::string* res = new std::string("");
            for (int i = 0; i < ALLOCATOR_DATABASE_MAX_MEMORY; ++i) {
                *res += *static_cast<std::string*>(AllocatorDatabase::lookup(reinterpret_cast<void*>(i)));
                *res += " ";
            }
            return res;
        }

        void AllocatorDatabase::add_sequence(const void* address, size_t length, void* allocator, bool debug) {

            // if (allocator == AllocatorDatabase::instance()->d_impl->d_global_allocator) return;
            int ret = AllocatorDatabase::instance()->d_impl->addNode(allocator, address, (char*)address + length - 1);

            if (AllocatorDatabase::instance()->d_debug) {
                std::cout << "Ran : add_sequence(" << address << ", " << length << ", " << allocator << "); ret = " << ret << "\n";
                // std::string* debugPrint = getMemoryString();
                // std::cout << *debugPrint << std::endl;
                // delete debugPrint;
            }
        }

        void AllocatorDatabase::delete_sequence(const void* address, bool debug) {
            int ret = AllocatorDatabase::instance()->d_impl->deleteSequence(address);

            if (AllocatorDatabase::instance()->d_debug) {
                std::cout << "Ran : delete_sequence(" << address << "); ret = " << ret << "\n";
                // std::string* debugPrint = getMemoryString();
                // std::cout << *debugPrint << std::endl;
                // delete debugPrint;
            }
        }
    
    }
}
