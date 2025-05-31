#pragma once

#include "chr_nr.hpp"
#include "chrset.hpp"

#include "../singletons.hpp"

namespace er {
namespace CS {

// Nightreign has PlayerIns but it's significantly different - use the base class for now
typedef ChrIns PlayerIns;

class WorldChrMan : public FD4::FD4Singleton<WorldChrMan, FD4::singleton_index::WorldChrMan> {
public:
    virtual ~WorldChrMan() = default;

    unsigned char unk8[0x9a38];
    CS::ChrSet<PlayerIns> player_chr_set;
    CS::ChrSet<PlayerIns> ghost_chr_set;
    CS::ChrSet<ChrIns> spirit_ash_chr_set;
    CS::ChrSet<ChrIns> debug_chr_set;
    unsigned char unk9ba0[0xd948];
    CS::PlayerIns *main_player;
};

static_assert(0x9a40 == __builtin_offsetof(WorldChrMan, player_chr_set));
static_assert(0x9a98 == __builtin_offsetof(WorldChrMan, ghost_chr_set));
static_assert(0x9af0 == __builtin_offsetof(WorldChrMan, spirit_ash_chr_set));
static_assert(0x9b48 == __builtin_offsetof(WorldChrMan, debug_chr_set));
static_assert(0x174E8 == __builtin_offsetof(WorldChrMan, main_player));

}
}
