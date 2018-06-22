#ifndef INCLUDED_BSLMA_ALLOCATOR_DATABASE
#define INCLUDED_BSLMA_ALLOCATOR_DATABASE

#define ALLOCATOR_DATABASE_MAX_CACHE 1
#define ALLOCATOR_DATABASE_MAX_MEMORY 0xffffffffffff

#include <cstddef>

namespace BloombergLP {
    namespace bslma {

        template <class T>
        class AllocatorDatabaseBuffer;

        class AllocatorDatabaseTreeNode;

        class AllocatorDatabase_Impl; 

        class AllocatorDatabase{
        
        private:

            static AllocatorDatabase* d_global_instance;
            AllocatorDatabase(); 

        public:

            AllocatorDatabase_Impl* d_impl;
            bool d_debug;

            static AllocatorDatabase* instance();
    
            // ------------------------------------- Needed functions ----------------------------------------------
            static void* lookup(const void* address, bool debug = false);
            static void add_sequence(const void* address, size_t length, void* allocator, bool debug = false);
            static void delete_sequence(const void* address, bool debug = false);
        };
    }

}


#endif // !INCLUDED_BSLMA_ALLOCATOR_DATABASE
