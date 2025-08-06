#include <elden-x/stl.hpp>

/**
 * Custom implementation of DLAllocator. This can be used to construct new STL containers that the
 * game engine can resize and deallocate.
 */
class win32_heap_allocator : public er::DLKR::DLAllocator {
public:
    virtual ~win32_heap_allocator() = default;
    int get_allocator_id() override { return 0x401; }
    int &get_heap_flags(int &flags) override { return flags = 0b11011; }
    size_t get_heap_capacity() override { return std::numeric_limits<size_t>::max(); }
    size_t get_heap_size() override { return 0; }
    size_t get_heap_backing_capacity() override { return std::numeric_limits<size_t>::max(); }
    size_t get_heap_allocation_count() override { return 0; }
    size_t msize(void *p) override { return 0; }
    void *allocate(size_t cb) override { return _aligned_malloc(cb, 0x10); }
    void *allocate_aligned(size_t cb, size_t alignment) override {
        return _aligned_malloc(cb, alignment > 0x10 ? alignment : 0x10);
    }
    void *reallocate(void *p, size_t cb) override { return _aligned_realloc(p, cb, 0x10); }
    void *reallocate_aligned(void *p, size_t cb, size_t alignment) override {
        return _aligned_realloc(p, cb, alignment > 0x10 ? alignment : 0x10);
    }
    void deallocate(void *p) override { return _aligned_free(p); }
    bool check_owned(void *p) override { return false; }
    void lock() override {}
    void unlock() override {}
    void *get_block(void *p) override { return nullptr; }

private:
    er::DLKR::DLAllocator *base = this;
};

static win32_heap_allocator default_dl_allocator_instance;

er::DLKR::DLAllocator *er::impl::default_dl_allocator = &default_dl_allocator_instance;
