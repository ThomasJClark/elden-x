#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include "dl_allocator.hpp"

namespace er {

template <typename T>
using list = std::list<T, DLKR::DLAllocatorAdapter<T>>;

template <typename K, typename V, typename C = std::less<K>>
using map = std::map<K, V, C, DLKR::DLAllocatorAdapter<std::pair<const K, V>>>;

template <typename T>
using vector = std::vector<T, DLKR::DLAllocatorAdapter<T>>;

template <typename C>
using basic_string = std::basic_string<C, std::char_traits<C>, DLKR::DLAllocatorAdapter<C>>;

typedef basic_string<wchar_t> wstring;

}
