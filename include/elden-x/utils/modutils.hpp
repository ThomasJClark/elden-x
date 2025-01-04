#pragma once
#define WIN32_LEAN_AND_MEAN

#include <stdexcept>
#include <vector>

namespace modutils
{

void initialize();
void enable_hooks();
void deinitialize();

struct scanopts
{
    typedef std::vector<std::pair<ptrdiff_t, ptrdiff_t>> relative_offsets_type;

    std::string aob;
    void *address;
    ptrdiff_t offset = 0;
    relative_offsets_type relative_offsets = {};
};

namespace impl
{
void *scan(const scanopts &opts);
void hook(void *function, void *detour, void **trampoline);
void *get_singleton_address(const std::string &singleton_name);
}

template <typename T> inline T *get_singleton(const std::string &singleton_name)
{
    return reinterpret_cast<T *>(impl::get_singleton_address(singleton_name));
}

template <typename T> inline T *scan(const scanopts &opts)
{
    return reinterpret_cast<T *>(impl::scan(opts));
}

template <typename F> inline F *hook(const scanopts &opts, F &detour, F *&trampoline)
{
    auto function = scan<F>(opts);
    if (function == nullptr)
    {
        throw std::runtime_error("Failed to find original function address");
    }
    impl::hook(reinterpret_cast<void *>(function), reinterpret_cast<void *>(&detour),
               reinterpret_cast<void **>(&trampoline));
    return function;
}

};