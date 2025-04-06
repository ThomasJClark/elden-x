#pragma once

namespace er {
namespace CS {

enum class ceremony_type : unsigned char { none = 0 };

class GameMan {
public:
    static GameMan *instance();

    unsigned char unk0[0xbc8];
    bool is_in_online_mode;
    unsigned char unkbc9[0x27];
    ceremony_type ceremony_type;
    unsigned char unkbf1[0x28f];
};

static_assert(0x0 == __builtin_offsetof(GameMan, unk0));
static_assert(0xbc8 == __builtin_offsetof(GameMan, is_in_online_mode));
static_assert(0xbc9 == __builtin_offsetof(GameMan, unkbc9));
static_assert(0xbf0 == __builtin_offsetof(GameMan, ceremony_type));
static_assert(0xbf1 == __builtin_offsetof(GameMan, unkbf1));
static_assert(0xe80 == sizeof(GameMan));
}
}
