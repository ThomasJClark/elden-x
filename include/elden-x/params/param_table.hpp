/**
 * @file param_table.hpp
 * @brief ELDEN RING param instances
 *
 * Copyright 2024 libER ELDEN RING API library. Modified for use in elden-x.
 *
 */
#pragma once

#include "../paramdef/paramdefs.hpp"
#include "param_defines.hpp"
#include "param_iterator.hpp"
#include "params.hpp"

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace er {
namespace param {

/**
 * @brief An interface to a param table of one of the predefined types.
 *
 * @tparam ParamType one of the predefined param types
 */
template <typename ParamType>
class param_table {
public:
    /**
     * @brief The paramdefs this param type uses.
     *
     */
    using paramdef_type = typename ParamType::paramdef_type;

    /**
     * @brief The param index of this param table.
     *
     */
    static constexpr param_index index = ParamType::index;

    /**
     * @brief Param iterator type.
     *
     */
    using iterator = param_iterator<paramdef_type>;

    /**
     * @brief Reverse order param iterator type.
     *
     */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /**
     * @brief Param const iterator type.
     *
     */
    using const_iterator = param_const_iterator<paramdef_type>;

    /**
     * @brief Reverse order param const iterator type.
     *
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr param_table() = default;

    /**
     * @brief Get a param row from this param table by its row index.
     *
     * Performs a binary search on the param table to find a matching
     * param row index and returns the row on success. If the desired param
     * row does not exist, returns a default-initialized param row instead.
     *
     * The bool in the param row/bool pair indicates whether the row exists.
     *
     * Example:
     * @code{.cpp} auto [row, row_exists] =
     *     er::param::EquipParamAccessory[5020]; @endcode
     *
     * @param row The row id.
     * @return std::pair<paramdef_type&, bool>
     */
    std::pair<paramdef_type &, bool> operator[](row_index_type row) const noexcept {
        iterator first = this->begin();
        iterator last = this->end();
        iterator found = std::lower_bound(
            first, last, row, [](const auto &cmp, const auto &row) { return cmp.first < row; });
        if (found == last || (*found).first != row) {
            if (!this->dummy_param) {
                auto swap = std::make_unique<paramdef_type>();
                std::atomic_thread_fence(std::memory_order_seq_cst);
                this->dummy_param.swap(swap);
                std::atomic_thread_fence(std::memory_order_seq_cst);
            }
            return {*this->dummy_param, false};
        }
        return {(*found).second, true};
    }

    /**
     * @brief Get the iterator to the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return iterator an iterator to the first param row or a
     * default constructed iterator
     */
    iterator begin() noexcept {
        auto solo_param_repository = CS::SoloParamRepository::instance();
        if (!solo_param_repository) return iterator{};

        auto file = solo_param_repository->get_param_file(index);
        if (!file) return iterator{};

        return iterator(*file, 0);
    }

    /**
     * @brief Get the iterator after the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return iterator an iterator past the end of the param table or a
     * default constructed iterator
     */
    iterator end() noexcept {
        auto solo_param_repository = CS::SoloParamRepository::instance();
        if (!solo_param_repository) return iterator{};

        auto file = solo_param_repository->get_param_file(index);
        if (!file) return iterator{};

        return iterator(*file, file->row_count);
    }

    /**
     * @brief Get the iterator to the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_iterator an iterator to the first param row or a
     * default constructed iterator
     */
    const_iterator begin() const noexcept { return const_cast<param_table *>(this)->begin(); }

    /**
     * @brief Get the iterator after the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_iterator an iterator past the end of the param table or a
     * default constructed iterator
     */
    const_iterator end() const noexcept { return const_cast<param_table *>(this)->end(); }

    /**
     * @brief Get the const iterator to the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_iterator an iterator to the first param row or a
     * default constructed iterator
     */
    const_iterator cbegin() const noexcept { return this->begin(); }

    /**
     * @brief Get the const iterator after the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const iterator an iterator past the end of the param table or a
     * default constructed iterator
     */
    const_iterator cend() const noexcept { return this->end(); }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    reverse_iterator rbegin() noexcept { return this->end(); }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return reverse_iterator an iterator before the start of the param table
     * or a default constructed iterator
     */
    reverse_iterator rend() noexcept { return this->begin(); }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    const_reverse_iterator rbegin() const noexcept { return this->end(); }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator before the start of the param
     * table or a default constructed iterator
     */
    const_reverse_iterator rend() const noexcept { return this->begin(); }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    const_reverse_iterator crbegin() const noexcept { return this->end(); }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator before the start of the param
     * table or a default constructed iterator
     */
    const_reverse_iterator crend() const noexcept { return this->begin(); }

private:
    mutable std::unique_ptr<paramdef_type> dummy_param;
};

/**
 * @brief A helper structure with param type data.
 *
 */
template <param_index Index, typename Def>
struct param_type {
    /**
     * @brief The paramdefs this param uses.
     *
     */
    using paramdef_type = Def;

    /**
     * @brief The param index of this param table.
     *
     */
    static constexpr param_index index = Index;
};

// clang-format off
inline param_table<param_type<param_index::EquipParamWeapon, paramdef::equip_param_weapon_st>> EquipParamWeapon;
inline param_table<param_type<param_index::EquipParamProtector, paramdef::equip_param_protector_st>> EquipParamProtector;
inline param_table<param_type<param_index::EquipParamAccessory, paramdef::equip_param_accessory_st>> EquipParamAccessory;
inline param_table<param_type<param_index::EquipParamGoods, paramdef::equip_param_goods_st>> EquipParamGoods;
inline param_table<param_type<param_index::ReinforceParamWeapon, paramdef::reinforce_param_weapon_st>> ReinforceParamWeapon;
inline param_table<param_type<param_index::ReinforceParamProtector, paramdef::reinforce_param_protector_st>> ReinforceParamProtector;
inline param_table<param_type<param_index::NpcParam, paramdef::npc_param_st>> NpcParam;
inline param_table<param_type<param_index::AtkParam_Npc, paramdef::atk_param_st>> AtkParam_Npc;
inline param_table<param_type<param_index::AtkParam_Pc, paramdef::atk_param_st>> AtkParam_Pc;
inline param_table<param_type<param_index::NpcThinkParam, paramdef::npc_think_param_st>> NpcThinkParam;
inline param_table<param_type<param_index::Bullet, paramdef::bullet_param_st>> Bullet;
inline param_table<param_type<param_index::BulletCreateLimitParam, paramdef::bullet_create_limit_param_st>> BulletCreateLimitParam;
inline param_table<param_type<param_index::BehaviorParam, paramdef::behavior_param_st>> BehaviorParam;
inline param_table<param_type<param_index::BehaviorParam_PC, paramdef::behavior_param_st>> BehaviorParam_PC;
inline param_table<param_type<param_index::Magic, paramdef::magic_param_st>> Magic;
inline param_table<param_type<param_index::SpEffectParam, paramdef::sp_effect_param_st>> SpEffectParam;
inline param_table<param_type<param_index::SpEffectVfxParam, paramdef::sp_effect_vfx_param_st>> SpEffectVfxParam;
inline param_table<param_type<param_index::SpEffectSetParam, paramdef::sp_effect_set_param_st>> SpEffectSetParam;
inline param_table<param_type<param_index::TalkParam, paramdef::talk_param_st>> TalkParam;
inline param_table<param_type<param_index::MenuColorTableParam, paramdef::menu_param_color_table_st>> MenuColorTableParam;
inline param_table<param_type<param_index::ItemLotParam_enemy, paramdef::itemlot_param_st>> ItemLotParam_enemy;
inline param_table<param_type<param_index::ItemLotParam_map, paramdef::itemlot_param_st>> ItemLotParam_map;
inline param_table<param_type<param_index::MoveParam, paramdef::move_param_st>> MoveParam;
inline param_table<param_type<param_index::CharaInitParam, paramdef::character_init_param>> CharaInitParam;
inline param_table<param_type<param_index::EquipMtrlSetParam, paramdef::equip_mtrl_set_param_st>> EquipMtrlSetParam;
inline param_table<param_type<param_index::FaceParam, paramdef::face_param_st>> FaceParam;
inline param_table<param_type<param_index::FaceRangeParam, paramdef::face_range_param_st>> FaceRangeParam;
inline param_table<param_type<param_index::ShopLineupParam, paramdef::shop_lineup_param>> ShopLineupParam;
inline param_table<param_type<param_index::ShopLineupParam_Recipe, paramdef::shop_lineup_param>> ShopLineupParam_Recipe;
inline param_table<param_type<param_index::GameAreaParam, paramdef::game_area_param_st>> GameAreaParam;
inline param_table<param_type<param_index::CalcCorrectGraph, paramdef::cacl_correct_graph_st>> CalcCorrectGraph;
inline param_table<param_type<param_index::LockCamParam, paramdef::lock_cam_param_st>> LockCamParam;
inline param_table<param_type<param_index::ObjActParam, paramdef::obj_act_param_st>> ObjActParam;
inline param_table<param_type<param_index::HitMtrlParam, paramdef::hit_mtrl_param_st>> HitMtrlParam;
inline param_table<param_type<param_index::KnockBackParam, paramdef::knockback_param_st>> KnockBackParam;
inline param_table<param_type<param_index::DecalParam, paramdef::decal_param_st>> DecalParam;
inline param_table<param_type<param_index::ActionButtonParam, paramdef::actionbutton_param_st>> ActionButtonParam;
inline param_table<param_type<param_index::AiSoundParam, paramdef::ai_sound_param_st>> AiSoundParam;
inline param_table<param_type<param_index::PlayRegionParam, paramdef::play_region_param_st>> PlayRegionParam;
inline param_table<param_type<param_index::NetworkAreaParam, paramdef::network_area_param_st>> NetworkAreaParam;
inline param_table<param_type<param_index::NetworkParam, paramdef::network_area_param_st>> NetworkParam;
inline param_table<param_type<param_index::NetworkMsgParam, paramdef::network_msg_param_st>> NetworkMsgParam;
inline param_table<param_type<param_index::BudgetParam, paramdef::budget_param_st>> BudgetParam;
inline param_table<param_type<param_index::BonfireWarpParam, paramdef::bonfire_warp_param_st>> BonfireWarpParam;
inline param_table<param_type<param_index::BonfireWarpTabParam, paramdef::bonfire_warp_tab_param_st>> BonfireWarpTabParam;
inline param_table<param_type<param_index::BonfireWarpSubCategoryParam, paramdef::bonfire_warp_sub_category_param_st>> BonfireWarpSubCategoryParam;
inline param_table<param_type<param_index::MenuPropertySpecParam, paramdef::menuproperty_spec>> MenuPropertySpecParam;
inline param_table<param_type<param_index::MenuPropertyLayoutParam, paramdef::menuproperty_layout>> MenuPropertyLayoutParam;
inline param_table<param_type<param_index::MenuValueTableParam, paramdef::menu_value_table_spec>> MenuValueTableParam;
inline param_table<param_type<param_index::Ceremony, paramdef::ceremony_param_st>> Ceremony;
inline param_table<param_type<param_index::PhantomParam, paramdef::phantom_param_st>> PhantomParam;
inline param_table<param_type<param_index::CharMakeMenuTopParam, paramdef::charmakemenutop_param_st>> CharMakeMenuTopParam;
inline param_table<param_type<param_index::CharMakeMenuListItemParam, paramdef::charmakemenu_listitem_param_st>> CharMakeMenuListItemParam;
inline param_table<param_type<param_index::HitEffectSfxConceptParam, paramdef::hit_effect_sfx_concept_param_st>> HitEffectSfxConceptParam;
inline param_table<param_type<param_index::HitEffectSfxParam, paramdef::hit_effect_sfx_param_st>> HitEffectSfxParam;
inline param_table<param_type<param_index::WepAbsorpPosParam, paramdef::wep_absorp_pos_param_st>> WepAbsorpPosParam;
inline param_table<param_type<param_index::ToughnessParam, paramdef::toughness_param_st>> ToughnessParam;
inline param_table<param_type<param_index::SeMaterialConvertParam, paramdef::se_material_convert_param_st>> SeMaterialConvertParam;
inline param_table<param_type<param_index::ThrowDirectionSfxParam, paramdef::throw_direction_sfx_param_st>> ThrowDirectionSfxParam;
inline param_table<param_type<param_index::DirectionCameraParam, paramdef::direction_camera_param_st>> DirectionCameraParam;
inline param_table<param_type<param_index::RoleParam, paramdef::role_param_st>> RoleParam;
inline param_table<param_type<param_index::WaypointParam, paramdef::waypoint_param_st>> WaypointParam;
inline param_table<param_type<param_index::ThrowParam, paramdef::throw_param_st>> ThrowParam;
inline param_table<param_type<param_index::GrassTypeParam, paramdef::grass_type_param_st>> GrassTypeParam;
inline param_table<param_type<param_index::GrassTypeParam_Lv1, paramdef::grass_type_param_st>> GrassTypeParam_Lv1;
inline param_table<param_type<param_index::GrassTypeParam_Lv2, paramdef::grass_type_param_st>> GrassTypeParam_Lv2;
inline param_table<param_type<param_index::GrassLodRangeParam, paramdef::grass_lod_range_param_st>> GrassLodRangeParam;
inline param_table<param_type<param_index::NpcAiActionParam, paramdef::npc_ai_action_param_st>> NpcAiActionParam;
inline param_table<param_type<param_index::PartsDrawParam, paramdef::parts_draw_param_st>> PartsDrawParam;
inline param_table<param_type<param_index::AssetEnvironmentGeometryParam, paramdef::asset_geometory_param_st>> AssetEnvironmentGeometryParam;
inline param_table<param_type<param_index::AssetModelSfxParam, paramdef::asset_model_sfx_param_st>> AssetModelSfxParam;
inline param_table<param_type<param_index::AssetMaterialSfxParam, paramdef::asset_material_sfx_param_st>> AssetMaterialSfxParam;
inline param_table<param_type<param_index::AttackElementCorrectParam, paramdef::attack_element_correct_param_st>> AttackElementCorrectParam;
inline param_table<param_type<param_index::FootSfxParam, paramdef::foot_sfx_param_st>> FootSfxParam;
inline param_table<param_type<param_index::MaterialExParam, paramdef::material_ex_param_st>> MaterialExParam;
inline param_table<param_type<param_index::HPEstusFlaskRecoveryParam, paramdef::estus_flask_recovery_param_st>> HPEstusFlaskRecoveryParam;
inline param_table<param_type<param_index::MPEstusFlaskRecoveryParam, paramdef::estus_flask_recovery_param_st>> MPEstusFlaskRecoveryParam;
inline param_table<param_type<param_index::MultiPlayCorrectionParam, paramdef::multi_play_correction_param_st>> MultiPlayCorrectionParam;
inline param_table<param_type<param_index::MenuOffscrRendParam, paramdef::menu_offscr_rend_param_st>> MenuOffscrRendParam;
inline param_table<param_type<param_index::ClearCountCorrectParam, paramdef::clear_count_correct_param_st>> ClearCountCorrectParam;
inline param_table<param_type<param_index::MapMimicryEstablishmentParam, paramdef::map_mimicry_establishment_param_st>> MapMimicryEstablishmentParam;
inline param_table<param_type<param_index::WetAspectParam, paramdef::wet_aspect_param_st>> WetAspectParam;
inline param_table<param_type<param_index::SwordArtsParam, paramdef::sword_arts_param_st>> SwordArtsParam;
inline param_table<param_type<param_index::KnowledgeLoadScreenItemParam, paramdef::knowledge_loadscreen_item_param_st>> KnowledgeLoadScreenItemParam;
inline param_table<param_type<param_index::MultiHPEstusFlaskBonusParam, paramdef::multi_estus_flask_bonus_param_st>> MultiHPEstusFlaskBonusParam;
inline param_table<param_type<param_index::MultiMPEstusFlaskBonusParam, paramdef::multi_estus_flask_bonus_param_st>> MultiMPEstusFlaskBonusParam;
inline param_table<param_type<param_index::MultiSoulBonusRateParam, paramdef::multi_soul_bonus_rate_param_st>> MultiSoulBonusRateParam;
inline param_table<param_type<param_index::WorldMapPointParam, paramdef::world_map_point_param_st>> WorldMapPointParam;
inline param_table<param_type<param_index::WorldMapPieceParam, paramdef::world_map_piece_param_st>> WorldMapPieceParam;
inline param_table<param_type<param_index::WorldMapLegacyConvParam, paramdef::world_map_legacy_conv_param_st>> WorldMapLegacyConvParam;
inline param_table<param_type<param_index::WorldMapPlaceNameParam, paramdef::world_map_place_name_param_st>> WorldMapPlaceNameParam;
inline param_table<param_type<param_index::ChrModelParam, paramdef::chr_model_param_st>> ChrModelParam;
inline param_table<param_type<param_index::LoadBalancerParam, paramdef::load_balancer_param_st>> LoadBalancerParam;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_ps4, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_ps4;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_ps5, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_ps5;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xb1, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_xb1;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xb1x, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_xb1x;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xss, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_xss;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xsx, paramdef::load_balancer_draw_dist_scale_param_st>> LoadBalancerDrawDistScaleParam_xsx;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_win64, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_win64;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_ps4, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_ps4;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_ps5, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_ps5;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xb1, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_xb1;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xb1x, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_xb1x;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xss, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_xss;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xsx, paramdef::load_balancer_new_draw_dist_scale_param_st>> LoadBalancerNewDrawDistScaleParam_xsx;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_AttackType, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_AttackType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_DamageAmount, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_DamageAmount;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_DeffensiveMaterial, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_DeffensiveMaterial;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_HitStop, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_HitStop;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_OffensiveMaterial, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_OffensiveMaterial;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_GrassHitType, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_GrassHitType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerShoes, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_PlayerShoes;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerEquipmentTops, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_PlayerEquipmentTops;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerEquipmentBottoms, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_PlayerEquipmentBottoms;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerVoiceType, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_PlayerVoiceType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_AttackStrength, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_Switch_AttackStrength;
inline param_table<param_type<param_index::WwiseValueToStrParam_EnvPlaceType, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_EnvPlaceType;
inline param_table<param_type<param_index::WeatherParam, paramdef::weather_param_st>> WeatherParam;
inline param_table<param_type<param_index::WeatherLotParam, paramdef::weather_lot_param_st>> WeatherLotParam;
inline param_table<param_type<param_index::WeatherAssetCreateParam, paramdef::weather_asset_create_param_st>> WeatherAssetCreateParam;
inline param_table<param_type<param_index::WeatherAssetReplaceParam, paramdef::weather_asset_replace_param_st>> WeatherAssetReplaceParam;
inline param_table<param_type<param_index::SpeedtreeParam, paramdef::speedtree_model_param_st>> SpeedtreeParam;
inline param_table<param_type<param_index::RideParam, paramdef::ride_param_st>> RideParam;
inline param_table<param_type<param_index::SeActivationRangeParam, paramdef::se_activation_range_param_st>> SeActivationRangeParam;
inline param_table<param_type<param_index::RollingObjLotParam, paramdef::rolling_obj_lot_param_st>> RollingObjLotParam;
inline param_table<param_type<param_index::NpcAiBehaviorProbability, paramdef::npc_ai_behavior_probability_param_st>> NpcAiBehaviorProbability;
inline param_table<param_type<param_index::BuddyParam, paramdef::buddy_param_st>> BuddyParam;
inline param_table<param_type<param_index::GparamRefSettings, paramdef::gparam_ref_settings_param_st>> GparamRefSettings;
inline param_table<param_type<param_index::RandomAppearParam, paramdef::random_appear_param_st>> RandomAppearParam;
inline param_table<param_type<param_index::MapGridCreateHeightLimitInfoParam, paramdef::map_grid_create_height_limit_info_param_st>> MapGridCreateHeightLimitInfoParam;
inline param_table<param_type<param_index::EnvObjLotParam, paramdef::env_obj_lot_param_st>> EnvObjLotParam;
inline param_table<param_type<param_index::MapDefaultInfoParam, paramdef::map_default_info_param_st>> MapDefaultInfoParam;
inline param_table<param_type<param_index::BuddyStoneParam, paramdef::buddy_param_st>> BuddyStoneParam;
inline param_table<param_type<param_index::LegacyDistantViewPartsReplaceParam, paramdef::legacy_distant_view_parts_replace_param>> LegacyDistantViewPartsReplaceParam;
inline param_table<param_type<param_index::SoundCommonIngameParam, paramdef::sound_common_ingame_param_st>> SoundCommonIngameParam;
inline param_table<param_type<param_index::SoundAutoEnvSoundGroupParam, paramdef::sound_auto_env_sound_group_param_st>> SoundAutoEnvSoundGroupParam;
inline param_table<param_type<param_index::SoundAutoReverbEvaluationDistParam, paramdef::sound_auto_reverb_evaluation_dist_param_st>> SoundAutoReverbEvaluationDistParam;
inline param_table<param_type<param_index::SoundAutoReverbSelectParam, paramdef::sound_auto_reverb_select_param_st>> SoundAutoReverbSelectParam;
inline param_table<param_type<param_index::EnemyCommonParam, paramdef::enemy_common_param_st>> EnemyCommonParam;
inline param_table<param_type<param_index::GameSystemCommonParam, paramdef::game_system_common_param_st>> GameSystemCommonParam;
inline param_table<param_type<param_index::GraphicsCommonParam, paramdef::graphics_common_param_st>> GraphicsCommonParam;
inline param_table<param_type<param_index::MenuCommonParam, paramdef::menu_common_param_st>> MenuCommonParam;
inline param_table<param_type<param_index::PlayerCommonParam, paramdef::player_common_param_st>> PlayerCommonParam;
inline param_table<param_type<param_index::CutsceneGparamWeatherParam, paramdef::cutscene_gparam_weather_param_st>> CutsceneGparamWeatherParam;
inline param_table<param_type<param_index::CutsceneGparamTimeParam, paramdef::cutscene_gparam_time_param_st>> CutsceneGparamTimeParam;
inline param_table<param_type<param_index::CutsceneTimezoneConvertParam, paramdef::cutscene_timezone_convert_param_st>> CutsceneTimezoneConvertParam;
inline param_table<param_type<param_index::CutsceneWeatherOverrideGparamConvertParam, paramdef::cutscene_weather_override_gparam_id_convert_param_st>> CutsceneWeatherOverrideGparamConvertParam;
inline param_table<param_type<param_index::SoundCutsceneParam, paramdef::sound_cutscene_param_st>> SoundCutsceneParam;
inline param_table<param_type<param_index::ChrActivateConditionParam, paramdef::chr_activate_condition_param_st>> ChrActivateConditionParam;
inline param_table<param_type<param_index::CutsceneMapIdParam, paramdef::cutscene_map_id_param_st>> CutsceneMapIdParam;
inline param_table<param_type<param_index::CutSceneTextureLoadParam, paramdef::cutscene_texture_load_param_st>> CutSceneTextureLoadParam;
inline param_table<param_type<param_index::GestureParam, paramdef::gesture_param_st>> GestureParam;
inline param_table<param_type<param_index::EquipParamGem, paramdef::equip_param_gem_st>> EquipParamGem;
inline param_table<param_type<param_index::EquipParamCustomWeapon, paramdef::equip_param_custom_weapon_st>> EquipParamCustomWeapon;
inline param_table<param_type<param_index::GraphicsConfig, paramdef::cs_graphics_config_param_st>> GraphicsConfig;
inline param_table<param_type<param_index::SoundChrPhysicsSeParam, paramdef::sound_chr_physics_se_param_st>> SoundChrPhysicsSeParam;
inline param_table<param_type<param_index::FeTextEffectParam, paramdef::fe_text_effect_param_st>> FeTextEffectParam;
inline param_table<param_type<param_index::CoolTimeParam, paramdef::cool_time_param_st>> CoolTimeParam;
inline param_table<param_type<param_index::WhiteSignCoolTimeParam, paramdef::white_sign_cool_time_param_st>> WhiteSignCoolTimeParam;
inline param_table<param_type<param_index::MapPieceTexParam, paramdef::map_piece_tex_param_st>> MapPieceTexParam;
inline param_table<param_type<param_index::MapNameTexParam, paramdef::map_name_tex_param_st>> MapNameTexParam;
inline param_table<param_type<param_index::WeatherLotTexParam, paramdef::weather_lot_tex_param_st>> WeatherLotTexParam;
inline param_table<param_type<param_index::KeyAssignParam_TypeA, paramdef::key_assign_param_st>> KeyAssignParam_TypeA;
inline param_table<param_type<param_index::KeyAssignParam_TypeB, paramdef::key_assign_param_st>> KeyAssignParam_TypeB;
inline param_table<param_type<param_index::KeyAssignParam_TypeC, paramdef::key_assign_param_st>> KeyAssignParam_TypeC;
inline param_table<param_type<param_index::MapGdRegionInfoParam, paramdef::map_gd_region_id_param_st>> MapGdRegionInfoParam;
inline param_table<param_type<param_index::MapGdRegionDrawParam, paramdef::map_gd_region_draw_param>> MapGdRegionDrawParam;
inline param_table<param_type<param_index::KeyAssignMenuItemParam, paramdef::cs_key_assign_menuitem_param>> KeyAssignMenuItemParam;
inline param_table<param_type<param_index::SoundAssetSoundObjEnableDistParam, paramdef::sound_asset_sound_obj_enable_dist_param_st>> SoundAssetSoundObjEnableDistParam;
inline param_table<param_type<param_index::SignPuddleParam, paramdef::sign_puddle_param_st>> SignPuddleParam;
inline param_table<param_type<param_index::AutoCreateEnvSoundParam, paramdef::auto_create_env_sound_param_st>> AutoCreateEnvSoundParam;
inline param_table<param_type<param_index::WwiseValueToStrParam_BgmBossChrIdConv, paramdef::wwise_value_to_str_convert_param_st>> WwiseValueToStrParam_BgmBossChrIdConv;
inline param_table<param_type<param_index::ResistCorrectParam, paramdef::resist_correct_param_st>> ResistCorrectParam;
inline param_table<param_type<param_index::PostureControlParam_WepRight, paramdef::posture_control_param_wep_right_st>> PostureControlParam_WepRight;
inline param_table<param_type<param_index::PostureControlParam_WepLeft, paramdef::posture_control_param_wep_left_st>> PostureControlParam_WepLeft;
inline param_table<param_type<param_index::PostureControlParam_Gender, paramdef::posture_control_param_gender_st>> PostureControlParam_Gender;
inline param_table<param_type<param_index::PostureControlParam_Pro, paramdef::posture_control_param_pro_st>> PostureControlParam_Pro;
inline param_table<param_type<param_index::RuntimeBoneControlParam, paramdef::runtime_bone_control_param_st>> RuntimeBoneControlParam;
inline param_table<param_type<param_index::TutorialParam, paramdef::tutorial_param_st>> TutorialParam;
inline param_table<param_type<param_index::BaseChrSelectMenuParam, paramdef::basechr_select_menu_param_st>> BaseChrSelectMenuParam;
inline param_table<param_type<param_index::MimicryEstablishmentTexParam, paramdef::mimicry_establishment_tex_param_st>> MimicryEstablishmentTexParam;
inline param_table<param_type<param_index::SfxBlockResShareParam, paramdef::sfx_block_res_share_param>> SfxBlockResShareParam;
inline param_table<param_type<param_index::FinalDamageRateParam, paramdef::final_damage_rate_param_st>> FinalDamageRateParam;
inline param_table<param_type<param_index::HitEffectSeParam, paramdef::hit_effect_se_param_st>> HitEffectSeParam;
inline param_table<param_type<param_index::ChrEquipModelParam, paramdef::chr_equip_model_param_st>> ChrEquipModelParam;
inline param_table<param_type<param_index::MapGridCreateHeightDetailLimitInfo, paramdef::map_grid_create_height_limit_detail_info_param_st>> MapGridCreateHeightDetailLimitInfo;
inline param_table<param_type<param_index::MapNameTexParam_m61, paramdef::map_name_tex_param_st_dlc02>> MapNameTexParam_m61;
inline param_table<param_type<param_index::MapPieceTexParam_m61, paramdef::map_piece_tex_param_st_dlc02>> MapPieceTexParam_m61;
inline param_table<param_type<param_index::MimicryEstablishmentTexParam_m61, paramdef::mimicry_establishment_tex_param_st_dlc02>> MimicryEstablishmentTexParam_m61;
inline param_table<param_type<param_index::SignPuddleSubCategoryParam, paramdef::sign_puddle_sub_category_param_st>> SignPuddleSubCategoryParam;
inline param_table<param_type<param_index::SignPuddleTabParam, paramdef::sign_puddle_tab_param_st>> SignPuddleTabParam;
inline param_table<param_type<param_index::WeatherLotTexParam_m61, paramdef::weather_lot_tex_param_st_dlc02>> WeatherLotTexParam_m61;
// clang-format on

}
}
