#pragma once

#include "../paramdef/sp_effect_param_st.hpp"

namespace er {
namespace CS {

class ChrIns;

struct SpecialEffectEntryAccumulatorInfo {
    void *unk0;
    int upper_trigger_count;
    int effect_on_upper_or_higher;
    int lower_trigger_count;
    int effect_on_lower_or_below;
    int unk18;
    unsigned int unk1c;
};

class SpecialEffect {
public:
    virtual ~SpecialEffect() = default;

    struct sp_effect_entry;
    struct sp_effect_entry {
        paramdef::sp_effect_param_st *param;
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

}
}
