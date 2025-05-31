#pragma once

#include "../stl.hpp"

#include <array>

namespace er {
namespace CS {

class ChrIns;

class CSChrModuleBase {
public:
    virtual ~CSChrModuleBase() = default;

    CS::ChrIns *owner;
};

class CSChrDataModule : public CSChrModuleBase {
public:
    unsigned char unk10[0x128];
    int hp;
    int hp_max;
    int hp_max_uncapped;
    int hp_base;
    int fp;
    int fp_max;
    int fp_base;
    int stamina;
    int stamina_max;
    int stamina_base;
    float recoverable_hp_left1;
    float recoverable_hp_left2;
    float recoverable_hp_time;
    unsigned char unk16c[0xbc];
    wchar_t *chr_name;
    unsigned char unk230[0x50];
};

static_assert(0x138 == __builtin_offsetof(CSChrDataModule, hp));
static_assert(0x13c == __builtin_offsetof(CSChrDataModule, hp_max));
static_assert(0x140 == __builtin_offsetof(CSChrDataModule, hp_max_uncapped));
static_assert(0x144 == __builtin_offsetof(CSChrDataModule, hp_base));
static_assert(0x148 == __builtin_offsetof(CSChrDataModule, fp));
static_assert(0x14c == __builtin_offsetof(CSChrDataModule, fp_max));
static_assert(0x150 == __builtin_offsetof(CSChrDataModule, fp_base));
static_assert(0x154 == __builtin_offsetof(CSChrDataModule, stamina));
static_assert(0x158 == __builtin_offsetof(CSChrDataModule, stamina_max));
static_assert(0x15c == __builtin_offsetof(CSChrDataModule, stamina_base));
static_assert(0x160 == __builtin_offsetof(CSChrDataModule, recoverable_hp_left1));
static_assert(0x164 == __builtin_offsetof(CSChrDataModule, recoverable_hp_left2));
static_assert(0x168 == __builtin_offsetof(CSChrDataModule, recoverable_hp_time));
static_assert(0x16c == __builtin_offsetof(CSChrDataModule, unk16c));
static_assert(0x228 == __builtin_offsetof(CSChrDataModule, chr_name));
static_assert(0x230 == __builtin_offsetof(CSChrDataModule, unk230));
static_assert(0x280 == sizeof(CSChrDataModule));

class CSChrModelParamModifierModule : public CSChrModuleBase {
public:
    struct modifier_value {
        int material_id;
        float value1;  // Red
        float value2;  // Green
        float value3;  // Blue
        float value4;  // Alpha
        float value5;  // Intensity
    };
    static_assert(sizeof(modifier_value) == 0x18);

    struct modifier {
        bool unk0{false};
        unsigned int unk4{0};
        int unk8{-1};
        int unkc{-1};
        unsigned long long unk10{0};
        unsigned int unk18{0};
        unsigned int unk1c{0};
        const wchar_t *name;
        modifier_value unk28;
        modifier_value value;
        modifier_value unk58;
        unsigned int unk70{0};
        unsigned int unk74{0};
        unsigned int unk78{0};
        unsigned int unk7c{0};
        unsigned int unk80{0};
        unsigned int unk84{0};
        modifier_value unk88;
        modifier_value unka0;
        unsigned int unkb8{0};
        unsigned int unkbc{0};
        unsigned int unkc0{0};
        unsigned int unkc4{0};
        unsigned int unkc8{0};
        float unkcc{1.0f};
        unsigned int unkd0{1};
        unsigned int unkd4{1};
    };
    static_assert(0x0 == __builtin_offsetof(modifier, unk0));
    static_assert(0x4 == __builtin_offsetof(modifier, unk4));
    static_assert(0x8 == __builtin_offsetof(modifier, unk8));
    static_assert(0xc == __builtin_offsetof(modifier, unkc));
    static_assert(0x10 == __builtin_offsetof(modifier, unk10));
    static_assert(0x18 == __builtin_offsetof(modifier, unk18));
    static_assert(0x1c == __builtin_offsetof(modifier, unk1c));
    static_assert(0x20 == __builtin_offsetof(modifier, name));
    static_assert(0x28 == __builtin_offsetof(modifier, unk28));
    static_assert(0x40 == __builtin_offsetof(modifier, value));
    static_assert(0x58 == __builtin_offsetof(modifier, unk58));
    static_assert(0x70 == __builtin_offsetof(modifier, unk70));
    static_assert(0x74 == __builtin_offsetof(modifier, unk74));
    static_assert(0x78 == __builtin_offsetof(modifier, unk78));
    static_assert(0x7c == __builtin_offsetof(modifier, unk7c));
    static_assert(0x80 == __builtin_offsetof(modifier, unk80));
    static_assert(0x84 == __builtin_offsetof(modifier, unk84));
    static_assert(0x88 == __builtin_offsetof(modifier, unk88));
    static_assert(0xa0 == __builtin_offsetof(modifier, unka0));
    static_assert(0xb8 == __builtin_offsetof(modifier, unkb8));
    static_assert(0xbc == __builtin_offsetof(modifier, unkbc));
    static_assert(0xc0 == __builtin_offsetof(modifier, unkc0));
    static_assert(0xc4 == __builtin_offsetof(modifier, unkc4));
    static_assert(0xc8 == __builtin_offsetof(modifier, unkc8));
    static_assert(0xcc == __builtin_offsetof(modifier, unkcc));
    static_assert(0xd0 == __builtin_offsetof(modifier, unkd0));
    static_assert(0xd4 == __builtin_offsetof(modifier, unkd4));
    static_assert(0xd8 == sizeof(modifier));

    er::vector<modifier> modifiers;
};

class CSChrVfxModule : public CSChrModuleBase {
public:
    struct vfx_entry {
        int material_ex_id;
        int sp_effect_vfx_id;
        int sp_effect_vfx_id2;
    };

    std::array<vfx_entry, 4> vfx;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
};

struct chrmodules {
    CS::CSChrDataModule *data_module;
    void *unk8[22];
    CS::CSChrVfxModule *vfx_module;
    void *unkc0[2];
    CS::CSChrModelParamModifierModule *model_param_modifier_module;
};

}
}
