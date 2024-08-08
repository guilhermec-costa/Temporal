#include "profiling/memory_tracker.hpp"

void *Memory_Tracker::alloc(size_t _s, const char *_f, int _l)
{
    std::cout << "allocating " << _s << " bytes" << std::endl;
    std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
    void *ptr = malloc(_s);
    m_allocs[ptr] = {_s, _f, _l};
    m_total_allocated += _s;
    return ptr;
}

void Memory_Tracker::_free(void *_memory)
{
    std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
    auto it = m_allocs.find(_memory);
    if (it != m_allocs.end())
    {
        m_total_allocated -= it->second.size;
        m_allocs.erase(it);
    }
    free(_memory);
}

void Memory_Tracker::report() const
{
    std::lock_guard<std::mutex> mtx_manager(m_mt_mutex);
    std::cout << "Current Allocations: " << m_allocs.size() << "\n";
    std::cout << "Total Allocated: " << m_total_allocated << " bytes\n";
}

Memory_Tracker::Memory_Tracker() : m_total_allocated(0) {}

// Implementations of the global new/delete operators
#ifdef ENABLE_MEMORY_TRACKING
void *operator new(size_t _s, const char *_f, int _l)
{
    return Memory_Tracker::get().alloc(_s, _f, _l);
}

void *operator new[](size_t size, const char *file, int line)
{
    return Memory_Tracker::get().alloc(size, file, line);
}
#define new new (__FILE__, __LINE__)

void operator delete(void *ptr) noexcept
{
    Memory_Tracker::get()._free(ptr);
}

void operator delete[](void *ptr) noexcept
{
    Memory_Tracker::get()._free(ptr);
}
#endif