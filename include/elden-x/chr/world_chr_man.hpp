#pragma once

#include "player.hpp"

namespace from
{
namespace CS
{

class WorldChrManImp
{
  public:
    static WorldChrManImp *instance();

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
