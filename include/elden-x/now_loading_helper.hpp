#pragma once

#include "singletons.hpp"

namespace er {
namespace CS {

class CSNowLoadingHelper
    : public FD4::FD4Singleton<CSNowLoadingHelper, FD4::singleton_index::CSNowLoadingHelper> {
public:
    virtual ~CSNowLoadingHelper() = default;

    unsigned char unk8[0xe0];
    float fade_in_opacity;
    bool loaded1;
    bool loaded2;
    unsigned char unkee[0xa];
};

static_assert(0xe8 == __builtin_offsetof(CSNowLoadingHelper, fade_in_opacity));
static_assert(0xec == __builtin_offsetof(CSNowLoadingHelper, loaded1));
static_assert(0xed == __builtin_offsetof(CSNowLoadingHelper, loaded2));
static_assert(0xf8 == sizeof(CSNowLoadingHelper));
}
}
