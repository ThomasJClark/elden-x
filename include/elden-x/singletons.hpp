#pragma once

#include <array>

namespace er {
namespace FD4 {

enum class singleton_index : unsigned int {
#define SINGLETON(name) name,
#include "singletons.inl"
#undef SINGLETON

    count
};

void find_singletons();

namespace impl {
extern std::array<void **, static_cast<unsigned int>(singleton_index::count)> singleton_addresses;
};

template <class T>
inline T *&get_singleton_instance(singleton_index index) {
    return *reinterpret_cast<T **>(impl::singleton_addresses[static_cast<size_t>(index)]);
}

class FD4RuntimeClass;

template <class T, singleton_index index>
class FD4Singleton {
public:
    inline static T *&instance() { return get_singleton_instance<T>(index); }
};

}
}
