#pragma once

#include "player.hpp"

#include "../utils/modutils.hpp"

namespace from
{
namespace CS
{

class WorldChrManImp
{
  public:
    static WorldChrManImp *instance()
    {
        return modutils::get_singleton<from::CS::WorldChrManImp>("WorldChrMan");
    }

    struct net_player_type
    {
        CS::PlayerIns *player;
        unsigned char unk[0x8];
    };

    virtual ~WorldChrManImp() = default;

    unsigned char unk8[0x10EF0];
    net_player_type *net_players;
    unsigned char unk10F00[0xd608];
    CS::PlayerIns *main_player;
};

}
}
