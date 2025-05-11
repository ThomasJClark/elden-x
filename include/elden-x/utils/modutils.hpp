#pragma once

#include <stdexcept>
#include <vector>

namespace modutils {

void initialize();

#ifdef ER_WITH_HOOKS
void enable_hooks();
#endif

void deinitialize();

struct scanopts {
    typedef std::vector<std::pair<ptrdiff_t, ptrdiff_t>> relative_offsets_type;

    std::string aob;
    void *address;
    ptrdiff_t offset = 0;
    relative_offsets_type relative_offsets = {};
};

namespace impl {
uintptr_t scan_memory(uintptr_t, const std::string &);
uintptr_t apply_offsets(uintptr_t, ptrdiff_t offset, const scanopts::relative_offsets_type &);
uintptr_t scan(const scanopts &opts);

#ifdef ER_WITH_HOOKS
void hook(void *function, void *detour, void **trampoline);
#endif
}

template <typename T>
inline T *scan(const scanopts &opts) {
    return reinterpret_cast<T *>(impl::scan(opts));
}

#ifdef ER_WITH_HOOKS
template <typename F>
inline F *hook(const scanopts &opts, F &detour, F *&trampoline) {
    auto function = scan<F>(opts);
    if (function == nullptr) {
        throw std::runtime_error("Failed to find original function address");
    }
    impl::hook(reinterpret_cast<void *>(function), reinterpret_cast<void *>(&detour),
               reinterpret_cast<void **>(&trampoline));
    return function;
}
#endif

extern bool sus;

};