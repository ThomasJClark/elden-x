#pragma once

#include <type_traits>

/**
 * DL2 allocator classes adapted from work by Dasaav for libER
 *
 * https://github.com/Dasaav-dsv/libER/blob/d8ae5c92719adca4344d8d902b63286b807f562b/include/memory/from_allocator.hpp#L72
 * https://github.com/Dasaav-dsv/libER/blob/d8ae5c92719adca4344d8d902b63286b807f562b/source/memory/from_allocator.cpp#L34
 */

namespace er {
namespace DLKR {

/**
 * Base virtual class for fromsoft allocators
 */
class DLAllocator {
public:
    virtual ~DLAllocator() = default;
    virtual int get_allocator_id() = 0;
    virtual int _unk0x10() { return -1; }
    virtual int &get_heap_flags(int &flags) = 0;
    virtual size_t get_heap_capacity() = 0;
    virtual size_t get_heap_size() = 0;
    virtual size_t get_heap_backing_capacity() = 0;
    virtual size_t get_heap_allocation_count() = 0;
    virtual size_t msize(void *p) = 0;
    virtual void *allocate(size_t cb) = 0;
    virtual void *allocate_aligned(size_t cb, size_t alignment) = 0;
    virtual void *reallocate(void *p, size_t cb) = 0;
    virtual void *reallocate_aligned(void *p, size_t cb, size_t alignment) = 0;
    virtual void deallocate(void *p) = 0;
    virtual void _unk0x70() {}
    virtual void *allocate2(size_t cb) { return this->allocate(cb); }
    virtual void *allocate2_aligned(size_t cb, size_t alignment) {
        return this->allocate_aligned(cb, alignment);
    }
    virtual void *reallocate2(void *p, size_t cb) { return this->reallocate(p, cb); }
    virtual void *reallocate2_aligned(void *p, size_t cb, size_t alignment) {
        return this->reallocate_aligned(p, cb, alignment);
    }
    virtual void deallocate2(void *p) { this->deallocate(p); }
    virtual bool _unk0xA0() { return false; }
    virtual bool check_owned(void *p) = 0;
    virtual bool _unk0xB0(std::nullptr_t) { return false; }
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void *get_block(void *p) = 0;
};

}
}
