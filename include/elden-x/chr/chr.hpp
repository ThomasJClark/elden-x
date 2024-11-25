#pragma once

#include "../paramdef/SP_EFFECT_PARAM_ST.hpp"
#include "../stl.hpp"

#include <array>

namespace from
{

namespace CS
{

class ChrIns;

struct SpecialEffectEntryAccumulatorInfo
{
    void *unk0;
    int upper_trigger_count;
    int effect_on_upper_or_higher;
    int lower_trigger_count;
    int effect_on_lower_or_below;
    int unk18;
    unsigned int unk1c;
};

class SpecialEffect
{
  public:
    virtual ~SpecialEffect() = default;

    struct sp_effect_entry;
    struct sp_effect_entry
    {
        paramdef::SP_EFFECT_PARAM_ST *param;
        unsigned int param_id;
        unsigned int unkc;
        CS::SpecialEffectEntryAccumulatorInfo accumulator_info;
        sp_effect_entry *next;
        sp_effect_entry *previous;
        float duration;
        float duration2;
        float total_duration;
        float interval_timer;
        unsigned int unk50[0x28];
    };

    sp_effect_entry *head;
    CS::ChrIns *owner;
    void *unk18;
    unsigned char unk20[0x118];
};
static_assert(0x8 == __builtin_offsetof(SpecialEffect, head));
static_assert(0x10 == __builtin_offsetof(SpecialEffect, owner));
static_assert(0x18 == __builtin_offsetof(SpecialEffect, unk18));
static_assert(0x20 == __builtin_offsetof(SpecialEffect, unk20));
static_assert(0x138 == sizeof(SpecialEffect));

class CSChrModelParamModifierModule
{
    virtual ~CSChrModelParamModifierModule() = default;

  public:
    struct modifier_value
    {
        int material_id;
        float value1; // Red
        float value2; // Green
        float value3; // Blue
        float value4; // Alpha
        float value5; // Intensity
    };
    static_assert(sizeof(modifier_value) == 0x18);

    struct modifier
    {
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

    CS::ChrIns *owner;
    from::vector<modifier> modifiers;
};

class CSChrVfxModule
{
    virtual ~CSChrVfxModule() = default;

  public:
    struct vfx_entry
    {
        int material_ex_id;
        int sp_effect_vfx_id;
        int sp_effect_vfx_id2;
    };

    CS::ChrIns *owner;
    std::array<vfx_entry, 4> vfx;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
};

class ChrIns
{
  public:
    virtual ~ChrIns() = default;

    struct modules_type
    {
        void *unk0[23];
        CS::CSChrVfxModule *vfx_module;
        void *unkc0[2];
        CS::CSChrModelParamModifierModule *model_param_modifier_module;
    };

    unsigned char unk8[0x170];
    CS::SpecialEffect *special_effects;
    unsigned char unk180[0x10];
    modules_type *modules;
    unsigned char unk198[0x3e8];
};

}
}
