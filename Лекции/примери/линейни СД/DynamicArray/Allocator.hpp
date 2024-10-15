/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for a simple debugging allocator.
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#pragma once

#ifndef _ALLOCATOR_HEADER_INCLUDED__
#define _ALLOCATOR_HEADER_INCLUDED__

#include <iostream>
#include <unordered_map>

namespace fmi::sdp
{

    template<class Type>
    class DebugCountAllocator
    {
    public:
        Type* alloc()
        {
            Type* memory = new Type;
            assert(allocs.count(memory) == 0);
            allocs.insert({ memory, 1 });
            ++total_allocs;
            ++total_mem;

            return memory;
        }

        void free(Type* memory)
        {
            if (checkPth(memory)) {
                size_t blockCnt = allocs[memory];
                if (blockCnt != 1)
                    std::cerr << "Allocated as array, but unproperly freed !\n";
                allocs.erase(memory);
                ++total_frees;
                delete memory;
            }
        }

        Type* allocArr(size_t count)
        {
            if (!count)
                std::cerr << "Allocation of zero sized block!\n";

            Type* memory = new Type[count];
            assert(allocs.count(memory) == 0);
            allocs.insert({ memory, count });
            ++total_allocs;
            total_mem += count;
            return memory;
        }

        void freeArr(Type* memory)
        {
            if (checkPth(memory)) {
                size_t blockCnt = allocs[memory];
                allocs.erase(memory);
                ++total_frees;
                delete[] memory;
            }
        }

        void printStatistics(std::ostream& stream = std::cout)
        {
            stream
                << "#### Debug counting Allocator ####\n"
                << "Total allocations:      " << total_allocs << "\n"
                << "Total deallocations:    " << total_frees << "\n"
                << "Total memory leaks:     " << total_allocs - total_frees << "\n"
                << "Total memory allocated: " << (total_mem * sizeof(Type)) << "\n";

            if (!allocs.empty()) {
                stream << "Memory still in use:\n";
                for (const auto& alloc : allocs) {
                    stream << "Address: " << alloc.first
                        << " " << sizeof(Type) * alloc.second << " bytes\n";
                }
            }
        }

        void swap(DebugCountAllocator<Type>& other)
        {
            std::swap(total_allocs, other.total_allocs);
            std::swap(total_mem, other.total_mem);
            std::swap(total_frees, other.total_frees);
            allocs.swap(other.allocs);
        }

    private:

        bool checkPth(Type* memory)
        {
            if (!memory) {
                std::cerr << "Deallocating nullptr!\n";
                return false;
            }

            if (!allocs.count(memory)) {
                throw "Pointer not allocated or already freed!";
            }
            return true;
        }

        std::unordered_map<const void*, size_t> allocs;
        size_t total_allocs = 0;
        size_t total_mem = 0;
        size_t total_frees = 0;
    };


    template <class Type>
    class DefaultAllocator
    {
    public:
        Type* alloc()
        {
            ++total_allocs;
            return new Type;
        }

        void free(Type* mem)
        {
            if (mem) ++total_frees;
            delete mem;
        }

        Type* allocArr(size_t count)
        {
            ++total_allocs;
            return new Type[count];
        }

        void freeArr(Type* mem)
        {
            if(mem) ++total_frees;
            delete[] mem;
        }

        void printStatistics(std::ostream& stream = std::cout)
        {
            stream
                << "#### Default Allocator ####\n"
                << "Total allocations:   " << total_allocs << "\n"
                << "Total deallocations: " << total_frees << "\n"
                << "Total memory leaks:  " << total_allocs - total_frees << "\n";
        }

        void swap(DefaultAllocator<Type>& other)
        {
            std::swap(total_allocs, other.total_allocs);
            std::swap(total_frees, other.total_frees);
        }
    private:
        size_t total_allocs = 0;
        size_t total_frees = 0;
    };
}

#endif // _ALLOCATOR_HEADER_INCLUDED__
