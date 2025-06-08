#pragma once

#include "popup_menu.hpp"

#include "../singletons.hpp"
#include "../stl.hpp"

namespace er {
namespace CS {

class MenuUnionJob;

enum class menu_flag : unsigned short {
    sparring = 200,
    unk201 = 201,
    unk202 = 202,
    expeditions = 203,
    expeditions_target = 204,
    expeditions_matchmaking_settings = 205,
    character_selection = 207,
    relic_rites = 208,
    unk215 = 215,
    sparring_settings = 216,
    sparring_character = 217,
    sparring_equipment = 218,
    sparring_equipment_armaments = 219,
    sparring_equipment_skill_sorc_incan = 220,
    sparring_equipment_consumables = 221,
    sparring_equipment_handbook = 222,
    unk223 = 223,
    small_jar_bazaar = 228,
    relic_search = 221,
    unk234 = 234,
    unk300 = 300,
    equipment_menu = 301,
    status_menu = 302,
    status_menu_effect_details = 303,
    system_menu = 304,
    system_menu_brightness = 305,
    advanced_graphics_settings = 307,
    unk308 = 308,
    map_menu = 309,
    unk311 = 311,
    select_equip_slot = 312,
    shop = 313,
    reinforce = 314,
    dormant_power = 317,
    talk_list = 400,
    yes_no_lightbox = 401,
    unk406 = 406,
    tutorial_lightbox = 410,
    settings_dialog = 411,
    relic_search_filter = 221,
    relic_search_sort = 221,
    unk500 = 500,
    unk501 = 501,
    unk502 = 502,
    unk503 = 503,
    unk504 = 504,
    unk505 = 505,
    unk506 = 506,
    unk507 = 507,
    unk508 = 508,
    unk509 = 509,
    pick_up_item = 510,
    unk511 = 511,
    tutorial_toast = 512,
    unk600 = 600,
    unk601 = 601,
    unk602 = 602,
    unk604 = 604,
    unk606 = 606,
    unk607 = 607,
    text_input = 1000,
    system_menu_controls = 1001,
};

enum class menu_flag_state : unsigned char {
    off = 0,
    on = 1,
    unk3 = 3,
    unk7 = 7,
};

class CSMenuMan : public FD4::FD4Singleton<CSMenuMan, FD4::singleton_index::CSMenuMan> {
public:
    virtual ~CSMenuMan() = default;

    unsigned char unk8[0x78];
    CSPopupMenu *popup_menu;
    MenuUnionJob *menu_union_job;
    unsigned char unk90[0x20];
    er::map<menu_flag, menu_flag_state> flags;
};

}
}
