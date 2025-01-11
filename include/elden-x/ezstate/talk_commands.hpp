#pragma once

#include "ezstate.hpp"

/**
 * Many of the known commands for ELDEN RING talkscripts, taken for the most part from ESDLang
 */
namespace er
{
namespace talk_command
{

constexpr ezstate::command talk_to_player{.bank = 1, .id = 1};
constexpr ezstate::command remove_my_aggro{.bank = 1, .id = 5};
constexpr ezstate::command force_end_talk{.bank = 1, .id = 8};
constexpr ezstate::command clear_talk_progress_data{.bank = 1, .id = 9};
constexpr ezstate::command show_shop_message{.bank = 1, .id = 10};
constexpr ezstate::command set_event_flag{.bank = 1, .id = 11};
constexpr ezstate::command close_shop_message{.bank = 1, .id = 12};
constexpr ezstate::command open_generic_dialog{.bank = 1, .id = 17};
constexpr ezstate::command force_close_generic_dialog{.bank = 1, .id = 18};
constexpr ezstate::command add_talk_list_data{.bank = 1, .id = 19};
constexpr ezstate::command clear_talk_list_data{.bank = 1, .id = 20};
constexpr ezstate::command open_regular_shop{.bank = 1, .id = 22};
constexpr ezstate::command open_enhance_shop{.bank = 1, .id = 24};
constexpr ezstate::command open_magic_equip{.bank = 1, .id = 28};
constexpr ezstate::command open_repository{.bank = 1, .id = 30};
constexpr ezstate::command open_soul{.bank = 1, .id = 31};
constexpr ezstate::command clear_talk_action_state{.bank = 1, .id = 35};
constexpr ezstate::command set_update_distance{.bank = 1, .id = 38};
constexpr ezstate::command clear_player_damage_info{.bank = 1, .id = 39};
constexpr ezstate::command start_bonfire_anim_loop{.bank = 1, .id = 42};
constexpr ezstate::command end_bonfire_kindle_anim_loop{.bank = 1, .id = 43};
constexpr ezstate::command open_sell_shop{.bank = 1, .id = 46};
constexpr ezstate::command change_player_stat{.bank = 1, .id = 47};
constexpr ezstate::command open_equipment_change_of_purpose_shop{.bank = 1, .id = 48};
constexpr ezstate::command combine_menu_flag_and_event_flag{.bank = 1, .id = 49};
constexpr ezstate::command player_equipment_quantity_change{.bank = 1, .id = 52};
constexpr ezstate::command shuffle_rng_seed{.bank = 1, .id = 57};
constexpr ezstate::command set_rng_seed{.bank = 1, .id = 58};
constexpr ezstate::command replace_tool{.bank = 1, .id = 59};
constexpr ezstate::command give_sp_effect_to_player{.bank = 1, .id = 62};
constexpr ezstate::command force_close_menu{.bank = 1, .id = 67};
constexpr ezstate::command set_talk_time{.bank = 1, .id = 68};
constexpr ezstate::command report_conversation_end_to_havok_behavior{.bank = 1, .id = 71};
constexpr ezstate::command open_conversation_choices_menu{.bank = 1, .id = 76};
constexpr ezstate::command stop_event_anim_without_forcing_conversation_end{.bank = 1, .id = 80};
constexpr ezstate::command open_chara_make_menu{.bank = 1, .id = 81};
constexpr ezstate::command open_choose_quantity_dialog{.bank = 1, .id = 82};
constexpr ezstate::command clear_quantity_value_of_choose_quantity_dialog{.bank = 1, .id = 83};
constexpr ezstate::command set_work_value{.bank = 1, .id = 100};
constexpr ezstate::command update_player_respawn_point{.bank = 1, .id = 101};
constexpr ezstate::command set_message_tag_value{.bank = 1, .id = 102};
constexpr ezstate::command turn_character_to_face_entity{.bank = 1, .id = 103};
constexpr ezstate::command award_item_lot{.bank = 1, .id = 104};
constexpr ezstate::command open_estus_allot_menu{.bank = 1, .id = 105};
constexpr ezstate::command estus_allocation_update{.bank = 1, .id = 108};
constexpr ezstate::command bonfire_activation{.bank = 1, .id = 109};
constexpr ezstate::command open_transposition_shop{.bank = 1, .id = 111};
constexpr ezstate::command reallocate_attributes{.bank = 1, .id = 113};
constexpr ezstate::command request_animation{.bank = 1, .id = 123};
constexpr ezstate::command open_physick_menu{.bank = 1, .id = 130};
constexpr ezstate::command acquire_gesture{.bank = 1, .id = 131};
constexpr ezstate::command open_dragon_communion_shop{.bank = 1, .id = 135};
constexpr ezstate::command open_tailoring_shop{.bank = 1, .id = 142};
constexpr ezstate::command open_ash_of_war_shop{.bank = 1, .id = 143};
constexpr ezstate::command open_puppet_shop{.bank = 1, .id = 144};
constexpr ezstate::command open_dupe_shop{.bank = 1, .id = 146};
constexpr ezstate::command set_event_flag_value{.bank = 1, .id = 147};
constexpr ezstate::command open_champions_equipment_sho{.bank = 1, .id = 148};
constexpr ezstate::command add_talk_list_data_if{.bank = 5, .id = 19};
constexpr ezstate::command add_talk_list_data_alt{.bank = 5, .id = 149};

}
}
