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

    void *alloc(size_t _s, const char *_f, int _l);
    void _free(void *_memory);
    void report() const;

private:
    Memory_Tracker();
    Memory_Tracker(const Memory_Tracker &mt) = delete;
    Memory_Tracker &operator=(const Memory_Tracker &mt) = delete;

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

