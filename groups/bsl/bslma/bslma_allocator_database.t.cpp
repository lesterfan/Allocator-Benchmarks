#include <iostream>
#include <regex>
#include <assert.h>
#include <unordered_map>

#include "bslma_allocator_database.h"

using namespace BloombergLP::bslma;

void printMemory() {
    int N = 20;
    std::cout << "Starting to print!" << std::endl;
    std::string res = "Current memory : ";
    for (int i = 0; i < (int)N; ++i) {
        res += *static_cast<std::string*>(AllocatorDatabase::lookup(reinterpret_cast<void*>(i)));
        res += " ";
    }
    std::cout << res << std::endl;
    std::cout << std::endl;
}

void IOTest() {
    std::cout << "Entering IO Test" << std::endl;
    printMemory();
    std::unordered_map<std::string, std::string*> memMap;
    while (1) {
        std::cout << "> ";
        std::string inp;
        std::getline(std::cin, inp);
        std::cout << std::endl;

        std::regex addSeqRe("^AllocatorDatabase::add_sequence\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\w+)\\s*\\);$");
        std::smatch addSeqM;

        std::regex deleteSeqRe("^AllocatorDatabase::delete_sequence\\(\\s*(\\d+)\\s*\\);$");
        std::smatch deleteSeqM;

        if (std::regex_search(inp, addSeqM, addSeqRe)) {
            unsigned address = std::stoul(addSeqM[1]);
            unsigned length = std::stoul(addSeqM[2]);

            std::string* allocator;
            if (memMap.find(std::string(addSeqM[3])) == memMap.end()) {
                allocator = new std::string(addSeqM[3]);
                memMap.insert(std::pair<std::string, std::string*>(std::string(addSeqM[3]), allocator));
            }
            else {
                allocator = memMap.find(std::string(addSeqM[3]))->second;
            }

            AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(address), length, allocator);
        }
        else if (std::regex_search(inp, deleteSeqM, deleteSeqRe)) {
            unsigned address = std::stoul(deleteSeqM[1]);

            AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(address));
        }
        else {
            std::cout << "Error: Function not supported!" << std::endl;
        }

    }
}

int main(int argc, char* argv[]) {
    const int                 test = argc > 1 ? atoi(argv[1]) : 0;
    const bool             verbose = argc > 2;
    const bool         veryVerbose = argc > 3;
    const bool     veryVeryVerbose = argc > 4;
    const bool veryVeryVeryVerbose = argc > 5;

    switch (test) {
    case 0:
    case 4: {
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(1), 25, static_cast<void*>(new std::string("A")) );
        break;
    }
    case 3: {
        if (verbose) {
            std::cout << "Test3" << std::endl;
            // std::cout << *getMemoryString() << std::endl;
        }
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(2), 5, static_cast<void*>(new std::string("A")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(8), 2, static_cast<void*>(new std::string("B")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(3), 3, static_cast<void*>(new std::string("C")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(4), 1, static_cast<void*>(new std::string("D")), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(4), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(3), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(2), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(9), veryVerbose);
        if (verbose) std::cout << std::endl;
        break;
    }
    case 2: {
        if (verbose) {
            std::cout << "Test2" << std::endl;
            // std::cout << *getMemoryString() << std::endl;
        }
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(2), 5, static_cast<void*>(new std::string("A")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(2), 5, static_cast<void*>(new std::string("B")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(2), 5, static_cast<void*>(new std::string("C")), veryVerbose);
        AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(2), 5, static_cast<void*>(new std::string("D")), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(4), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(4), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(4), veryVerbose);
        AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(4), veryVerbose);
        if (verbose) std::cout << std::endl;
        break;
    }
    case 1: {
        // Size of the memory
        int N = 20;
        if (verbose) {
            std::cout << "Test1" << std::endl;
            // std::cout << *getMemoryString() << std::endl;
        }
        for (int i = 0; i < (int)N; ++i) {
            char c = 65 + i;
            AllocatorDatabase::add_sequence(reinterpret_cast<const void*>(i), (int)N - i, new std::string(1, c), veryVerbose);
        }
        for (int i = (int)N - 1; i >= 0; --i) {
            AllocatorDatabase::delete_sequence(reinterpret_cast<const void*>(i), veryVerbose);
        }
        if (verbose) std::cout << std::endl;
        break;
    }
    case -1: {
        IOTest();
    }
    };


}
