#pragma once
#include <iostream>
#include <unordered_map>
#include <mutex>

class Memory_Tracker
{
public:
    static Memory_Tracker &get()
    {
        static Memory_Tracker mt;
        return mt;
    }

    void *alloc(size_t _s, const char *_f, int _l)
    {
        std::cout << "allocating " << std::endl;
        std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
        void *ptr = malloc(_s);
        m_allocs[ptr] = {_s, _f, _l};
        m_total_allocated += _s;
        return ptr;
    }

    void _free(void *_memory)
    {
        std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
        auto it = m_allocs.find(_memory);
        if (it != m_allocs.end())
        {
            m_total_allocated -= it->second.size;
            m_allocs.erase(_memory);
        }
        free(_memory);
    }

    void report() const
    {
        std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
        std::cout << "Current Allocations: " << m_allocs.size() << "\n";
        std::cout << "Total Allocated: " << m_total_allocated << " bytes\n";
    }

private:
    Memory_Tracker() : m_total_allocated(0) {}
    Memory_Tracker(const Memory_Tracker &mt) = delete;
    Memory_Tracker operator=(const Memory_Tracker &mt) = delete;

private:
    struct Allocation_Info
    {
        size_t size;
        const char *file;
        int line;
    };

    std::unordered_map<void *, Allocation_Info> m_allocs;
    mutable std::mutex m_mt_mutex;
    size_t m_total_allocated;
};

// void *operator new(size_t _s, const char *_f, int _l)
// {
//     return Memory_Tracker::get().alloc(_s, _f, _l);
// }

// void* operator new[](size_t size, const char* file, int line)
// {
//     return Memory_Tracker::get().alloc(size, file, line);
// }

// void operator delete(void *ptr)
// {
//     return Memory_Tracker::get()._free(ptr);
// }

// #ifdef new
// #undef new
// #endif

// #ifdef delete 
// #undef delete 
// #endif

// // Macro para redefinir new
// #define new new (__FILE__, __LINE__)
// #define delete delete(void* ptr)