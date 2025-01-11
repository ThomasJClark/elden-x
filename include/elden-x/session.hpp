#pragma once

#include <span>

#include "./utils/modutils.hpp"

namespace er
{
namespace CS
{

class CSSessionManagerImp
{
  public:
    static CSSessionManagerImp *instance()
    {
        return modutils::get_singleton<CSSessionManagerImp>("CSSessionManager");
    }

    struct player_entry
    {
        void *unk0;
        void *unk8;
        unsigned long long steam_id;
        unsigned char unk18[0xe8];
    };

    virtual ~CSSessionManagerImp() = default;

    unsigned char unk8[0x70];
    player_entry *player_entries_begin;
    player_entry *player_entries_end;
    void *unk88;
    player_entry host_player_entry;
    unsigned char unk190[0x1c8];

    std::span<player_entry> player_entries()
    {
        return {player_entries_begin, player_entries_end};
    }
};

static_assert(0x8 == __builtin_offsetof(CSSessionManagerImp, unk8));
static_assert(0x78 == __builtin_offsetof(CSSessionManagerImp, player_entries_begin));
static_assert(0x80 == __builtin_offsetof(CSSessionManagerImp, player_entries_end));
static_assert(0x88 == __builtin_offsetof(CSSessionManagerImp, unk88));
static_assert(0x90 == __builtin_offsetof(CSSessionManagerImp, host_player_entry));
static_assert(0x190 == __builtin_offsetof(CSSessionManagerImp, unk190));
static_assert(0x358 == sizeof(CSSessionManagerImp));
}
}
