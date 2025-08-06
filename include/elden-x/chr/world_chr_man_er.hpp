#pragma once

#include "chr_debug_reload.hpp"
#include "chrset.hpp"
#include "player.hpp"

#include "../singletons.hpp"

namespace er {
namespace CS {

class WorldChrMan : public FD4::FD4Singleton<WorldChrMan, FD4::singleton_index::WorldChrMan> {
public:
    virtual ~WorldChrMan() = default;

    struct chr_reload_list_item {};

    uint8_t unk8[0x10ed8];
    CS::ChrSet<PlayerIns> player_chr_set;
    CS::ChrSet<PlayerIns> ghost_chr_set;
    CS::ChrSet<ChrIns> spirit_ash_chr_set;
    CS::ChrSet<ChrIns> debug_chr_set;
    uint8_t unk11040[0xd4c8];
    CS::PlayerIns *main_player;
    uint8_t unk1e510[0x150];
    chr_debug_reload debug_reload;
    uint8_t unk1e680[0xd60];
};

static_assert(0x10ee0 == __builtin_offsetof(WorldChrMan, player_chr_set));
static_assert(0x10f38 == __builtin_offsetof(WorldChrMan, ghost_chr_set));
static_assert(0x10f90 == __builtin_offsetof(WorldChrMan, spirit_ash_chr_set));
static_assert(0x10fe8 == __builtin_offsetof(WorldChrMan, debug_chr_set));
static_assert(0x1e508 == __builtin_offsetof(WorldChrMan, main_player));
static_assert(0x1e660 == __builtin_offsetof(WorldChrMan, debug_reload));
static_assert(0x1f3e0 == sizeof(WorldChrMan));
}
}
