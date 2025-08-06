#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include "dl_allocator.hpp"

namespace er {

namespace impl {
extern er::DLKR::DLAllocator *default_dl_allocator;
}

/**
 * Class meeting the C++ Allocator named requirements, using a DLAllocator as a backend
 *
 * This can be used to refer to STL containers constructed by the game engine in a way that allows
 * resizing/deallocating them in custom code, or to construct new containers that the game engine
 * can resize and deallocate.
 */
template <typename T>
class allocator {
    DLKR::DLAllocator *dl_allocator;

public:
    using value_type = T;
    using size_type = unsigned long long;
    using difference_type = long long;

    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::false_type;

    allocator()
        : dl_allocator(impl::default_dl_allocator) {}

    template <typename U>
    allocator(const allocator<U> &other) noexcept
        : dl_allocator(other.dl_allocator) {}

    T *allocate(size_type count) {
        return reinterpret_cast<T *>(dl_allocator->allocate_aligned(count * sizeof(T), alignof(T)));
    }

    void deallocate(T *p, size_type count = 0) {
        dl_allocator->deallocate(reinterpret_cast<void *>(p));
    }
};

template <typename T1, typename T2>
inline static bool operator==(const allocator<T1> &lhs, const allocator<T2> &rhs) noexcept {
    return &lhs.allocator == &rhs.allocator;
};

template <typename T>
using list = std::list<T, allocator<T>>;

template <typename K, typename V, typename C = std::less<K>>
using map = std::map<K, V, C, allocator<std::pair<const K, V>>>;

template <typename T>
using vector = std::vector<T, allocator<T>>;

template <typename C>
using basic_string = std::basic_string<C, std::char_traits<C>, allocator<C>>;

typedef basic_string<wchar_t> wstring;

}
