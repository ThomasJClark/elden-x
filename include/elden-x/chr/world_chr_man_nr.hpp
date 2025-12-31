#pragma once

#include "chr_debug_reload.hpp"
#include "chr_nr.hpp"
#include "chrset.hpp"

#include "../singletons.hpp"
#include "../task.hpp"

namespace er {
namespace CS {

// Nightreign has PlayerIns but it's significantly different - use the base class for now
typedef ChrIns PlayerIns;

class WorldChrMan : public FD4::FD4Singleton<WorldChrMan, FD4::singleton_index::WorldChrMan> {
public:
    virtual ~WorldChrMan() = default;

    uint8_t unk8[0x9a38];
    CS::ChrSet<PlayerIns> player_chr_set;
    CS::ChrSet<PlayerIns> ghost_chr_set;
    CS::ChrSet<ChrIns> spirit_ash_chr_set;
    CS::ChrSet<ChrIns> debug_chr_set;
    uint8_t unk9ba0[0xd948];
    CS::PlayerIns *main_player;
    uint8_t unk174f0[0xc8];
    chr_debug_reload debug_reload;
    uint8_t unk175d8[0xa8];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task1;
    uint8_t unk176b0[0x28];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task2;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task3;
    uint8_t unk17738[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task4;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task5;
    uint8_t unk177b8[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task6;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task7;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task8;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task9;
    uint8_t unk17898[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task10;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task11;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task12;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task13;
    uint8_t unk17978[0x70];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task14;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task15;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task16;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task17;
    uint8_t unk17aa8[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task18;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task19;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task20;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task21;
};

static_assert(0x9a40 == __builtin_offsetof(WorldChrMan, player_chr_set));
static_assert(0x9a98 == __builtin_offsetof(WorldChrMan, ghost_chr_set));
static_assert(0x9af0 == __builtin_offsetof(WorldChrMan, spirit_ash_chr_set));
static_assert(0x9b48 == __builtin_offsetof(WorldChrMan, debug_chr_set));
static_assert(0x174E8 == __builtin_offsetof(WorldChrMan, main_player));
static_assert(0x175b8 == __builtin_offsetof(WorldChrMan, debug_reload));
static_assert(0x17680 == __builtin_offsetof(WorldChrMan, update_task1));
static_assert(0x176d8 == __builtin_offsetof(WorldChrMan, update_task2));
static_assert(0x17708 == __builtin_offsetof(WorldChrMan, update_task3));
static_assert(0x17758 == __builtin_offsetof(WorldChrMan, update_task4));
static_assert(0x17788 == __builtin_offsetof(WorldChrMan, update_task5));
static_assert(0x177d8 == __builtin_offsetof(WorldChrMan, update_task6));
static_assert(0x17808 == __builtin_offsetof(WorldChrMan, update_task7));
static_assert(0x17838 == __builtin_offsetof(WorldChrMan, update_task8));
static_assert(0x17868 == __builtin_offsetof(WorldChrMan, update_task9));
static_assert(0x178b8 == __builtin_offsetof(WorldChrMan, update_task10));
static_assert(0x178e8 == __builtin_offsetof(WorldChrMan, update_task11));
static_assert(0x17918 == __builtin_offsetof(WorldChrMan, update_task12));
static_assert(0x17948 == __builtin_offsetof(WorldChrMan, update_task13));
static_assert(0x179e8 == __builtin_offsetof(WorldChrMan, update_task14));
static_assert(0x17a18 == __builtin_offsetof(WorldChrMan, update_task15));
static_assert(0x17a48 == __builtin_offsetof(WorldChrMan, update_task16));
static_assert(0x17a78 == __builtin_offsetof(WorldChrMan, update_task17));
static_assert(0x17ac8 == __builtin_offsetof(WorldChrMan, update_task18));
static_assert(0x17af8 == __builtin_offsetof(WorldChrMan, update_task19));
static_assert(0x17b28 == __builtin_offsetof(WorldChrMan, update_task20));
static_assert(0x17b58 == __builtin_offsetof(WorldChrMan, update_task21));

}
}
