#pragma once

#include "menu/menu_man.hpp"
#include "singletons.hpp"

namespace er {
namespace CS {

class GameRend;
class FrontEndView;
class CSFadeScreen;
class FeSystemAnnounceView;
class FeSummonMessageView;
class ClockView;

struct fe_state {
    // Show HP/FP/SP/etc. in the top half of the screen. These might not actually be visible if the
    // HUD is set to hidden or auto
    bool show_player_status : 1;

    // Show weapons/spells/etc. in the bottom half of the screen.
    bool show_equipment : 1;
};

class CSFeMan : public FD4::FD4Singleton<CSFeMan, FD4::singleton_index::CSFeMan> {
public:
    virtual ~CSFeMan() = default;

    void *unk8;
    GameRend *game_rend;
    FrontEndView *front_end_view;
    CSFadeScreen *fade_screen;
    FeSystemAnnounceView *system_accounce_view;
    FeSummonMessageView *summon_message_view;
    ClockView *clock_view;
    unsigned char unk48[0x38];
    fe_state state;
    unsigned char unk79[0x83a7];
};

static_assert(0x8 == __builtin_offsetof(CSFeMan, unk8));
static_assert(0x10 == __builtin_offsetof(CSFeMan, game_rend));
static_assert(0x18 == __builtin_offsetof(CSFeMan, front_end_view));
static_assert(0x20 == __builtin_offsetof(CSFeMan, fade_screen));
static_assert(0x28 == __builtin_offsetof(CSFeMan, system_accounce_view));
static_assert(0x30 == __builtin_offsetof(CSFeMan, summon_message_view));
static_assert(0x38 == __builtin_offsetof(CSFeMan, clock_view));
static_assert(0x78 == __builtin_offsetof(CSFeMan, state));
static_assert(0x8420 == sizeof(CSFeMan));

}
}
