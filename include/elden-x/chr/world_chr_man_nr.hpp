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
    uint8_t unk174f0[0xb8];
    chr_debug_reload debug_reload;
    uint8_t unk175c8[0xa8];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task1;
    uint8_t unk176a0[0x28];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task2;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task3;
    uint8_t unk17728[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task4;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task5;
    uint8_t unk177a8[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task6;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task7;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task8;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task9;
    uint8_t unk17888[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task10;
    uint8_t unk178d8[0x100];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task11;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task12;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task13;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task14;
    uint8_t unk17a98[0x20];
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task15;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task16;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task17;
    er::CS::CSEzUpdateTask<er::CS::WorldChrMan> update_task18;
};

static_assert(0x9a40 == __builtin_offsetof(WorldChrMan, player_chr_set));
static_assert(0x9a98 == __builtin_offsetof(WorldChrMan, ghost_chr_set));
static_assert(0x9af0 == __builtin_offsetof(WorldChrMan, spirit_ash_chr_set));
static_assert(0x9b48 == __builtin_offsetof(WorldChrMan, debug_chr_set));
static_assert(0x174E8 == __builtin_offsetof(WorldChrMan, main_player));
static_assert(0x175a8 == __builtin_offsetof(WorldChrMan, debug_reload));
static_assert(0x17670 == __builtin_offsetof(WorldChrMan, update_task1));
static_assert(0x176c8 == __builtin_offsetof(WorldChrMan, update_task2));
static_assert(0x176f8 == __builtin_offsetof(WorldChrMan, update_task3));
static_assert(0x17748 == __builtin_offsetof(WorldChrMan, update_task4));
static_assert(0x17778 == __builtin_offsetof(WorldChrMan, update_task5));
static_assert(0x177c8 == __builtin_offsetof(WorldChrMan, update_task6));
static_assert(0x177f8 == __builtin_offsetof(WorldChrMan, update_task7));
static_assert(0x17828 == __builtin_offsetof(WorldChrMan, update_task8));
static_assert(0x17858 == __builtin_offsetof(WorldChrMan, update_task9));
static_assert(0x178a8 == __builtin_offsetof(WorldChrMan, update_task10));
static_assert(0x179d8 == __builtin_offsetof(WorldChrMan, update_task11));
static_assert(0x17a08 == __builtin_offsetof(WorldChrMan, update_task12));
static_assert(0x17a38 == __builtin_offsetof(WorldChrMan, update_task13));
static_assert(0x17a68 == __builtin_offsetof(WorldChrMan, update_task14));
static_assert(0x17ab8 == __builtin_offsetof(WorldChrMan, update_task15));
static_assert(0x17ae8 == __builtin_offsetof(WorldChrMan, update_task16));
static_assert(0x17b18 == __builtin_offsetof(WorldChrMan, update_task17));
static_assert(0x17b48 == __builtin_offsetof(WorldChrMan, update_task18));

}
}
