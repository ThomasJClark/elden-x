#pragma once

#include "chrmodules.hpp"
#include "chrspeffect.hpp"

namespace er {

namespace CS {

class ChrIns {
public:
    virtual ~ChrIns() = default;

    unsigned char unk8[0x188];
    CS::SpecialEffect *special_effects;
    unsigned char unk198[0x20];
    chrmodules *modules;
    unsigned char unk1c0[0x3e0];
};

static_assert(0x8 == __builtin_offsetof(ChrIns, unk8));
static_assert(0x190 == __builtin_offsetof(ChrIns, special_effects));
static_assert(0x198 == __builtin_offsetof(ChrIns, unk198));
static_assert(0x1B8 == __builtin_offsetof(ChrIns, modules));
static_assert(0x1c0 == __builtin_offsetof(ChrIns, unk1c0));
static_assert(0x5a0 == sizeof(ChrIns));

}
}
