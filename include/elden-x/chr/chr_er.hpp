#pragma once

#include "chrmodules.hpp"
#include "chrspeffect.hpp"

namespace er {

namespace CS {

class ChrIns;

struct mapid {
    unsigned char subregion;
    unsigned char region;
    unsigned char block;
    unsigned char area;
};

class ChrIns {
public:
    virtual ~ChrIns() = default;

    unsigned char unk8[0x28];
    mapid current_map;
    mapid previous_map;
    mapid current_map2;
    mapid previous_map2;
    unsigned char unk40[0x138];
    CS::SpecialEffect *special_effects;
    unsigned char unk180[0x10];
    chrmodules *modules;
    unsigned char unk198[0x3e8];
};

static_assert(0x8 == __builtin_offsetof(ChrIns, unk8));
static_assert(0x30 == __builtin_offsetof(ChrIns, current_map));
static_assert(0x34 == __builtin_offsetof(ChrIns, previous_map));
static_assert(0x38 == __builtin_offsetof(ChrIns, current_map2));
static_assert(0x3c == __builtin_offsetof(ChrIns, previous_map2));
static_assert(0x40 == __builtin_offsetof(ChrIns, unk40));
static_assert(0x178 == __builtin_offsetof(ChrIns, special_effects));
static_assert(0x180 == __builtin_offsetof(ChrIns, unk180));
static_assert(0x190 == __builtin_offsetof(ChrIns, modules));
static_assert(0x198 == __builtin_offsetof(ChrIns, unk198));
static_assert(0x580 == sizeof(ChrIns));

}
}
