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

namespace from
{
namespace param
{

/**
 * @brief An interface to a param table of one of the predefined types.
 *
 * @tparam ParamType one of the predefined param types
 */
template <typename ParamType> class param_table
{
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
     *     from::param::EquipParamAccessory[5020]; @endcode
     *
     * @param row The row id.
     * @return std::pair<paramdef_type&, bool>
     */
    std::pair<paramdef_type &, bool> operator[](row_index_type row) const noexcept
    {
        iterator first = this->begin();
        iterator last = this->end();
        iterator found = std::lower_bound(
            first, last, row, [](const auto &cmp, const auto &row) { return cmp.first < row; });
        if (found == last || (*found).first != row)
        {
            if (!this->dummy_param)
            {
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
    iterator begin() noexcept
    {
        auto solo_param_repository = CS::SoloParamRepository::instance();
        if (!solo_param_repository)
            return iterator{};

        auto file = solo_param_repository->get_param_file(index);
        if (!file)
            return iterator{};

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
    iterator end() noexcept
    {
        auto solo_param_repository = CS::SoloParamRepository::instance();
        if (!solo_param_repository)
            return iterator{};

        auto file = solo_param_repository->get_param_file(index);
        if (!file)
            return iterator{};

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
    const_iterator begin() const noexcept
    {
        return const_cast<param_table *>(this)->begin();
    }

    /**
     * @brief Get the iterator after the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_iterator an iterator past the end of the param table or a
     * default constructed iterator
     */
    const_iterator end() const noexcept
    {
        return const_cast<param_table *>(this)->end();
    }

    /**
     * @brief Get the const iterator to the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_iterator an iterator to the first param row or a
     * default constructed iterator
     */
    const_iterator cbegin() const noexcept
    {
        return this->begin();
    }

    /**
     * @brief Get the const iterator after the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const iterator an iterator past the end of the param table or a
     * default constructed iterator
     */
    const_iterator cend() const noexcept
    {
        return this->end();
    }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    reverse_iterator rbegin() noexcept
    {
        return this->end();
    }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return reverse_iterator an iterator before the start of the param table
     * or a default constructed iterator
     */
    reverse_iterator rend() noexcept
    {
        return this->begin();
    }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    const_reverse_iterator rbegin() const noexcept
    {
        return this->end();
    }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator before the start of the param
     * table or a default constructed iterator
     */
    const_reverse_iterator rend() const noexcept
    {
        return this->begin();
    }

    /**
     * @brief Get the reverse iterator to the last param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator to the last param row or a
     * default constructed iterator
     */
    const_reverse_iterator crbegin() const noexcept
    {
        return this->end();
    }

    /**
     * @brief Get the reverse iterator before the first param row in the table.
     *
     * If the table has not been yet initialized, returns a default
     * constructed iterator.
     *
     * @return const_reverse_iterator an iterator before the start of the param
     * table or a default constructed iterator
     */
    const_reverse_iterator crend() const noexcept
    {
        return this->begin();
    }

  private:
    mutable std::unique_ptr<paramdef_type> dummy_param;
};

/**
 * @brief A helper structure with param type data.
 *
 */
template <param_index Index, typename Def> struct param_type
{
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
inline param_table<param_type<param_index::EquipParamWeapon, paramdef::EQUIP_PARAM_WEAPON_ST>> EquipParamWeapon;
inline param_table<param_type<param_index::EquipParamProtector, paramdef::EQUIP_PARAM_PROTECTOR_ST>> EquipParamProtector;
inline param_table<param_type<param_index::EquipParamAccessory, paramdef::EQUIP_PARAM_ACCESSORY_ST>> EquipParamAccessory;
inline param_table<param_type<param_index::EquipParamGoods, paramdef::EQUIP_PARAM_GOODS_ST>> EquipParamGoods;
inline param_table<param_type<param_index::ReinforceParamWeapon, paramdef::REINFORCE_PARAM_WEAPON_ST>> ReinforceParamWeapon;
inline param_table<param_type<param_index::ReinforceParamProtector, paramdef::REINFORCE_PARAM_PROTECTOR_ST>> ReinforceParamProtector;
inline param_table<param_type<param_index::NpcParam, paramdef::NPC_PARAM_ST>> NpcParam;
inline param_table<param_type<param_index::AtkParam_Npc, paramdef::ATK_PARAM_ST>> AtkParam_Npc;
inline param_table<param_type<param_index::AtkParam_Pc, paramdef::ATK_PARAM_ST>> AtkParam_Pc;
inline param_table<param_type<param_index::NpcThinkParam, paramdef::NPC_THINK_PARAM_ST>> NpcThinkParam;
inline param_table<param_type<param_index::Bullet, paramdef::BULLET_PARAM_ST>> Bullet;
inline param_table<param_type<param_index::BulletCreateLimitParam, paramdef::BULLET_CREATE_LIMIT_PARAM_ST>> BulletCreateLimitParam;
inline param_table<param_type<param_index::BehaviorParam, paramdef::BEHAVIOR_PARAM_ST>> BehaviorParam;
inline param_table<param_type<param_index::BehaviorParam_PC, paramdef::BEHAVIOR_PARAM_ST>> BehaviorParam_PC;
inline param_table<param_type<param_index::Magic, paramdef::MAGIC_PARAM_ST>> Magic;
inline param_table<param_type<param_index::SpEffectParam, paramdef::SP_EFFECT_PARAM_ST>> SpEffectParam;
inline param_table<param_type<param_index::SpEffectVfxParam, paramdef::SP_EFFECT_VFX_PARAM_ST>> SpEffectVfxParam;
inline param_table<param_type<param_index::SpEffectSetParam, paramdef::SP_EFFECT_SET_PARAM_ST>> SpEffectSetParam;
inline param_table<param_type<param_index::TalkParam, paramdef::TALK_PARAM_ST>> TalkParam;
inline param_table<param_type<param_index::MenuColorTableParam, paramdef::MENU_PARAM_COLOR_TABLE_ST>> MenuColorTableParam;
inline param_table<param_type<param_index::ItemLotParam_enemy, paramdef::ITEMLOT_PARAM_ST>> ItemLotParam_enemy;
inline param_table<param_type<param_index::ItemLotParam_map, paramdef::ITEMLOT_PARAM_ST>> ItemLotParam_map;
inline param_table<param_type<param_index::MoveParam, paramdef::MOVE_PARAM_ST>> MoveParam;
inline param_table<param_type<param_index::CharaInitParam, paramdef::CHARACTER_INIT_PARAM>> CharaInitParam;
inline param_table<param_type<param_index::EquipMtrlSetParam, paramdef::EQUIP_MTRL_SET_PARAM_ST>> EquipMtrlSetParam;
inline param_table<param_type<param_index::FaceParam, paramdef::FACE_PARAM_ST>> FaceParam;
inline param_table<param_type<param_index::FaceRangeParam, paramdef::FACE_RANGE_PARAM_ST>> FaceRangeParam;
inline param_table<param_type<param_index::ShopLineupParam, paramdef::SHOP_LINEUP_PARAM>> ShopLineupParam;
inline param_table<param_type<param_index::ShopLineupParam_Recipe, paramdef::SHOP_LINEUP_PARAM>> ShopLineupParam_Recipe;
inline param_table<param_type<param_index::GameAreaParam, paramdef::GAME_AREA_PARAM_ST>> GameAreaParam;
inline param_table<param_type<param_index::CalcCorrectGraph, paramdef::CACL_CORRECT_GRAPH_ST>> CalcCorrectGraph;
inline param_table<param_type<param_index::LockCamParam, paramdef::LOCK_CAM_PARAM_ST>> LockCamParam;
inline param_table<param_type<param_index::ObjActParam, paramdef::OBJ_ACT_PARAM_ST>> ObjActParam;
inline param_table<param_type<param_index::HitMtrlParam, paramdef::HIT_MTRL_PARAM_ST>> HitMtrlParam;
inline param_table<param_type<param_index::KnockBackParam, paramdef::KNOCKBACK_PARAM_ST>> KnockBackParam;
inline param_table<param_type<param_index::DecalParam, paramdef::DECAL_PARAM_ST>> DecalParam;
inline param_table<param_type<param_index::ActionButtonParam, paramdef::ACTIONBUTTON_PARAM_ST>> ActionButtonParam;
inline param_table<param_type<param_index::AiSoundParam, paramdef::AI_SOUND_PARAM_ST>> AiSoundParam;
inline param_table<param_type<param_index::PlayRegionParam, paramdef::PLAY_REGION_PARAM_ST>> PlayRegionParam;
inline param_table<param_type<param_index::NetworkAreaParam, paramdef::NETWORK_AREA_PARAM_ST>> NetworkAreaParam;
inline param_table<param_type<param_index::NetworkParam, paramdef::NETWORK_AREA_PARAM_ST>> NetworkParam;
inline param_table<param_type<param_index::NetworkMsgParam, paramdef::NETWORK_MSG_PARAM_ST>> NetworkMsgParam;
inline param_table<param_type<param_index::BudgetParam, paramdef::BUDGET_PARAM_ST>> BudgetParam;
inline param_table<param_type<param_index::BonfireWarpParam, paramdef::BONFIRE_WARP_PARAM_ST>> BonfireWarpParam;
inline param_table<param_type<param_index::BonfireWarpTabParam, paramdef::BONFIRE_WARP_TAB_PARAM_ST>> BonfireWarpTabParam;
inline param_table<param_type<param_index::BonfireWarpSubCategoryParam, paramdef::BONFIRE_WARP_SUB_CATEGORY_PARAM_ST>> BonfireWarpSubCategoryParam;
inline param_table<param_type<param_index::MenuPropertySpecParam, paramdef::MENUPROPERTY_SPEC>> MenuPropertySpecParam;
inline param_table<param_type<param_index::MenuPropertyLayoutParam, paramdef::MENUPROPERTY_LAYOUT>> MenuPropertyLayoutParam;
inline param_table<param_type<param_index::MenuValueTableParam, paramdef::MENU_VALUE_TABLE_SPEC>> MenuValueTableParam;
inline param_table<param_type<param_index::Ceremony, paramdef::CEREMONY_PARAM_ST>> Ceremony;
inline param_table<param_type<param_index::PhantomParam, paramdef::PHANTOM_PARAM_ST>> PhantomParam;
inline param_table<param_type<param_index::CharMakeMenuTopParam, paramdef::CHARMAKEMENUTOP_PARAM_ST>> CharMakeMenuTopParam;
inline param_table<param_type<param_index::CharMakeMenuListItemParam, paramdef::CHARMAKEMENU_LISTITEM_PARAM_ST>> CharMakeMenuListItemParam;
inline param_table<param_type<param_index::HitEffectSfxConceptParam, paramdef::HIT_EFFECT_SFX_CONCEPT_PARAM_ST>> HitEffectSfxConceptParam;
inline param_table<param_type<param_index::HitEffectSfxParam, paramdef::HIT_EFFECT_SFX_PARAM_ST>> HitEffectSfxParam;
inline param_table<param_type<param_index::WepAbsorpPosParam, paramdef::WEP_ABSORP_POS_PARAM_ST>> WepAbsorpPosParam;
inline param_table<param_type<param_index::ToughnessParam, paramdef::TOUGHNESS_PARAM_ST>> ToughnessParam;
inline param_table<param_type<param_index::SeMaterialConvertParam, paramdef::SE_MATERIAL_CONVERT_PARAM_ST>> SeMaterialConvertParam;
inline param_table<param_type<param_index::ThrowDirectionSfxParam, paramdef::THROW_DIRECTION_SFX_PARAM_ST>> ThrowDirectionSfxParam;
inline param_table<param_type<param_index::DirectionCameraParam, paramdef::DIRECTION_CAMERA_PARAM_ST>> DirectionCameraParam;
inline param_table<param_type<param_index::RoleParam, paramdef::ROLE_PARAM_ST>> RoleParam;
inline param_table<param_type<param_index::WaypointParam, paramdef::WAYPOINT_PARAM_ST>> WaypointParam;
inline param_table<param_type<param_index::ThrowParam, paramdef::THROW_PARAM_ST>> ThrowParam;
inline param_table<param_type<param_index::GrassTypeParam, paramdef::GRASS_TYPE_PARAM_ST>> GrassTypeParam;
inline param_table<param_type<param_index::GrassTypeParam_Lv1, paramdef::GRASS_TYPE_PARAM_ST>> GrassTypeParam_Lv1;
inline param_table<param_type<param_index::GrassTypeParam_Lv2, paramdef::GRASS_TYPE_PARAM_ST>> GrassTypeParam_Lv2;
inline param_table<param_type<param_index::GrassLodRangeParam, paramdef::GRASS_LOD_RANGE_PARAM_ST>> GrassLodRangeParam;
inline param_table<param_type<param_index::NpcAiActionParam, paramdef::NPC_AI_ACTION_PARAM_ST>> NpcAiActionParam;
inline param_table<param_type<param_index::PartsDrawParam, paramdef::PARTS_DRAW_PARAM_ST>> PartsDrawParam;
inline param_table<param_type<param_index::AssetEnvironmentGeometryParam, paramdef::ASSET_GEOMETORY_PARAM_ST>> AssetEnvironmentGeometryParam;
inline param_table<param_type<param_index::AssetModelSfxParam, paramdef::ASSET_MODEL_SFX_PARAM_ST>> AssetModelSfxParam;
inline param_table<param_type<param_index::AssetMaterialSfxParam, paramdef::ASSET_MATERIAL_SFX_PARAM_ST>> AssetMaterialSfxParam;
inline param_table<param_type<param_index::AttackElementCorrectParam, paramdef::ATTACK_ELEMENT_CORRECT_PARAM_ST>> AttackElementCorrectParam;
inline param_table<param_type<param_index::FootSfxParam, paramdef::FOOT_SFX_PARAM_ST>> FootSfxParam;
inline param_table<param_type<param_index::MaterialExParam, paramdef::MATERIAL_EX_PARAM_ST>> MaterialExParam;
inline param_table<param_type<param_index::HPEstusFlaskRecoveryParam, paramdef::ESTUS_FLASK_RECOVERY_PARAM_ST>> HPEstusFlaskRecoveryParam;
inline param_table<param_type<param_index::MPEstusFlaskRecoveryParam, paramdef::ESTUS_FLASK_RECOVERY_PARAM_ST>> MPEstusFlaskRecoveryParam;
inline param_table<param_type<param_index::MultiPlayCorrectionParam, paramdef::MULTI_PLAY_CORRECTION_PARAM_ST>> MultiPlayCorrectionParam;
inline param_table<param_type<param_index::MenuOffscrRendParam, paramdef::MENU_OFFSCR_REND_PARAM_ST>> MenuOffscrRendParam;
inline param_table<param_type<param_index::ClearCountCorrectParam, paramdef::CLEAR_COUNT_CORRECT_PARAM_ST>> ClearCountCorrectParam;
inline param_table<param_type<param_index::MapMimicryEstablishmentParam, paramdef::MAP_MIMICRY_ESTABLISHMENT_PARAM_ST>> MapMimicryEstablishmentParam;
inline param_table<param_type<param_index::WetAspectParam, paramdef::WET_ASPECT_PARAM_ST>> WetAspectParam;
inline param_table<param_type<param_index::SwordArtsParam, paramdef::SWORD_ARTS_PARAM_ST>> SwordArtsParam;
inline param_table<param_type<param_index::KnowledgeLoadScreenItemParam, paramdef::KNOWLEDGE_LOADSCREEN_ITEM_PARAM_ST>> KnowledgeLoadScreenItemParam;
inline param_table<param_type<param_index::MultiHPEstusFlaskBonusParam, paramdef::MULTI_ESTUS_FLASK_BONUS_PARAM_ST>> MultiHPEstusFlaskBonusParam;
inline param_table<param_type<param_index::MultiMPEstusFlaskBonusParam, paramdef::MULTI_ESTUS_FLASK_BONUS_PARAM_ST>> MultiMPEstusFlaskBonusParam;
inline param_table<param_type<param_index::MultiSoulBonusRateParam, paramdef::MULTI_SOUL_BONUS_RATE_PARAM_ST>> MultiSoulBonusRateParam;
inline param_table<param_type<param_index::WorldMapPointParam, paramdef::WORLD_MAP_POINT_PARAM_ST>> WorldMapPointParam;
inline param_table<param_type<param_index::WorldMapPieceParam, paramdef::WORLD_MAP_PIECE_PARAM_ST>> WorldMapPieceParam;
inline param_table<param_type<param_index::WorldMapLegacyConvParam, paramdef::WORLD_MAP_LEGACY_CONV_PARAM_ST>> WorldMapLegacyConvParam;
inline param_table<param_type<param_index::WorldMapPlaceNameParam, paramdef::WORLD_MAP_PLACE_NAME_PARAM_ST>> WorldMapPlaceNameParam;
inline param_table<param_type<param_index::ChrModelParam, paramdef::CHR_MODEL_PARAM_ST>> ChrModelParam;
inline param_table<param_type<param_index::LoadBalancerParam, paramdef::LOAD_BALANCER_PARAM_ST>> LoadBalancerParam;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_ps4, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_ps4;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_ps5, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_ps5;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xb1, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_xb1;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xb1x, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_xb1x;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xss, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_xss;
inline param_table<param_type<param_index::LoadBalancerDrawDistScaleParam_xsx, paramdef::LOAD_BALANCER_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerDrawDistScaleParam_xsx;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_win64, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_win64;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_ps4, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_ps4;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_ps5, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_ps5;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xb1, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_xb1;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xb1x, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_xb1x;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xss, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_xss;
inline param_table<param_type<param_index::LoadBalancerNewDrawDistScaleParam_xsx, paramdef::LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST>> LoadBalancerNewDrawDistScaleParam_xsx;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_AttackType, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_AttackType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_DamageAmount, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_DamageAmount;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_DeffensiveMaterial, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_DeffensiveMaterial;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_HitStop, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_HitStop;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_OffensiveMaterial, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_OffensiveMaterial;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_GrassHitType, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_GrassHitType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerShoes, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_PlayerShoes;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerEquipmentTops, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_PlayerEquipmentTops;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerEquipmentBottoms, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_PlayerEquipmentBottoms;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_PlayerVoiceType, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_PlayerVoiceType;
inline param_table<param_type<param_index::WwiseValueToStrParam_Switch_AttackStrength, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_Switch_AttackStrength;
inline param_table<param_type<param_index::WwiseValueToStrParam_EnvPlaceType, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_EnvPlaceType;
inline param_table<param_type<param_index::WeatherParam, paramdef::WEATHER_PARAM_ST>> WeatherParam;
inline param_table<param_type<param_index::WeatherLotParam, paramdef::WEATHER_LOT_PARAM_ST>> WeatherLotParam;
inline param_table<param_type<param_index::WeatherAssetCreateParam, paramdef::WEATHER_ASSET_CREATE_PARAM_ST>> WeatherAssetCreateParam;
inline param_table<param_type<param_index::WeatherAssetReplaceParam, paramdef::WEATHER_ASSET_REPLACE_PARAM_ST>> WeatherAssetReplaceParam;
inline param_table<param_type<param_index::SpeedtreeParam, paramdef::SPEEDTREE_MODEL_PARAM_ST>> SpeedtreeParam;
inline param_table<param_type<param_index::RideParam, paramdef::RIDE_PARAM_ST>> RideParam;
inline param_table<param_type<param_index::SeActivationRangeParam, paramdef::SE_ACTIVATION_RANGE_PARAM_ST>> SeActivationRangeParam;
inline param_table<param_type<param_index::RollingObjLotParam, paramdef::ROLLING_OBJ_LOT_PARAM_ST>> RollingObjLotParam;
inline param_table<param_type<param_index::NpcAiBehaviorProbability, paramdef::NPC_AI_BEHAVIOR_PROBABILITY_PARAM_ST>> NpcAiBehaviorProbability;
inline param_table<param_type<param_index::BuddyParam, paramdef::BUDDY_PARAM_ST>> BuddyParam;
inline param_table<param_type<param_index::GparamRefSettings, paramdef::GPARAM_REF_SETTINGS_PARAM_ST>> GparamRefSettings;
inline param_table<param_type<param_index::RandomAppearParam, paramdef::RANDOM_APPEAR_PARAM_ST>> RandomAppearParam;
inline param_table<param_type<param_index::MapGridCreateHeightLimitInfoParam, paramdef::MAP_GRID_CREATE_HEIGHT_LIMIT_INFO_PARAM_ST>> MapGridCreateHeightLimitInfoParam;
inline param_table<param_type<param_index::EnvObjLotParam, paramdef::ENV_OBJ_LOT_PARAM_ST>> EnvObjLotParam;
inline param_table<param_type<param_index::MapDefaultInfoParam, paramdef::MAP_DEFAULT_INFO_PARAM_ST>> MapDefaultInfoParam;
inline param_table<param_type<param_index::BuddyStoneParam, paramdef::BUDDY_PARAM_ST>> BuddyStoneParam;
inline param_table<param_type<param_index::LegacyDistantViewPartsReplaceParam, paramdef::LEGACY_DISTANT_VIEW_PARTS_REPLACE_PARAM>> LegacyDistantViewPartsReplaceParam;
inline param_table<param_type<param_index::SoundCommonIngameParam, paramdef::SOUND_COMMON_INGAME_PARAM_ST>> SoundCommonIngameParam;
inline param_table<param_type<param_index::SoundAutoEnvSoundGroupParam, paramdef::SOUND_AUTO_ENV_SOUND_GROUP_PARAM_ST>> SoundAutoEnvSoundGroupParam;
inline param_table<param_type<param_index::SoundAutoReverbEvaluationDistParam, paramdef::SOUND_AUTO_REVERB_EVALUATION_DIST_PARAM_ST>> SoundAutoReverbEvaluationDistParam;
inline param_table<param_type<param_index::SoundAutoReverbSelectParam, paramdef::SOUND_AUTO_REVERB_SELECT_PARAM_ST>> SoundAutoReverbSelectParam;
inline param_table<param_type<param_index::EnemyCommonParam, paramdef::ENEMY_COMMON_PARAM_ST>> EnemyCommonParam;
inline param_table<param_type<param_index::GameSystemCommonParam, paramdef::GAME_SYSTEM_COMMON_PARAM_ST>> GameSystemCommonParam;
inline param_table<param_type<param_index::GraphicsCommonParam, paramdef::GRAPHICS_COMMON_PARAM_ST>> GraphicsCommonParam;
inline param_table<param_type<param_index::MenuCommonParam, paramdef::MENU_COMMON_PARAM_ST>> MenuCommonParam;
inline param_table<param_type<param_index::PlayerCommonParam, paramdef::PLAYER_COMMON_PARAM_ST>> PlayerCommonParam;
inline param_table<param_type<param_index::CutsceneGparamWeatherParam, paramdef::CUTSCENE_GPARAM_WEATHER_PARAM_ST>> CutsceneGparamWeatherParam;
inline param_table<param_type<param_index::CutsceneGparamTimeParam, paramdef::CUTSCENE_GPARAM_TIME_PARAM_ST>> CutsceneGparamTimeParam;
inline param_table<param_type<param_index::CutsceneTimezoneConvertParam, paramdef::CUTSCENE_TIMEZONE_CONVERT_PARAM_ST>> CutsceneTimezoneConvertParam;
inline param_table<param_type<param_index::CutsceneWeatherOverrideGparamConvertParam, paramdef::CUTSCENE_WEATHER_OVERRIDE_GPARAM_ID_CONVERT_PARAM_ST>> CutsceneWeatherOverrideGparamConvertParam;
inline param_table<param_type<param_index::SoundCutsceneParam, paramdef::SOUND_CUTSCENE_PARAM_ST>> SoundCutsceneParam;
inline param_table<param_type<param_index::ChrActivateConditionParam, paramdef::CHR_ACTIVATE_CONDITION_PARAM_ST>> ChrActivateConditionParam;
inline param_table<param_type<param_index::CutsceneMapIdParam, paramdef::CUTSCENE_MAP_ID_PARAM_ST>> CutsceneMapIdParam;
inline param_table<param_type<param_index::CutSceneTextureLoadParam, paramdef::CUTSCENE_TEXTURE_LOAD_PARAM_ST>> CutSceneTextureLoadParam;
inline param_table<param_type<param_index::GestureParam, paramdef::GESTURE_PARAM_ST>> GestureParam;
inline param_table<param_type<param_index::EquipParamGem, paramdef::EQUIP_PARAM_GEM_ST>> EquipParamGem;
inline param_table<param_type<param_index::EquipParamCustomWeapon, paramdef::EQUIP_PARAM_CUSTOM_WEAPON_ST>> EquipParamCustomWeapon;
inline param_table<param_type<param_index::GraphicsConfig, paramdef::CS_GRAPHICS_CONFIG_PARAM_ST>> GraphicsConfig;
inline param_table<param_type<param_index::SoundChrPhysicsSeParam, paramdef::SOUND_CHR_PHYSICS_SE_PARAM_ST>> SoundChrPhysicsSeParam;
inline param_table<param_type<param_index::FeTextEffectParam, paramdef::FE_TEXT_EFFECT_PARAM_ST>> FeTextEffectParam;
inline param_table<param_type<param_index::CoolTimeParam, paramdef::COOL_TIME_PARAM_ST>> CoolTimeParam;
inline param_table<param_type<param_index::WhiteSignCoolTimeParam, paramdef::WHITE_SIGN_COOL_TIME_PARAM_ST>> WhiteSignCoolTimeParam;
inline param_table<param_type<param_index::MapPieceTexParam, paramdef::MAP_PIECE_TEX_PARAM_ST>> MapPieceTexParam;
inline param_table<param_type<param_index::MapNameTexParam, paramdef::MAP_NAME_TEX_PARAM_ST>> MapNameTexParam;
inline param_table<param_type<param_index::WeatherLotTexParam, paramdef::WEATHER_LOT_TEX_PARAM_ST>> WeatherLotTexParam;
inline param_table<param_type<param_index::KeyAssignParam_TypeA, paramdef::KEY_ASSIGN_PARAM_ST>> KeyAssignParam_TypeA;
inline param_table<param_type<param_index::KeyAssignParam_TypeB, paramdef::KEY_ASSIGN_PARAM_ST>> KeyAssignParam_TypeB;
inline param_table<param_type<param_index::KeyAssignParam_TypeC, paramdef::KEY_ASSIGN_PARAM_ST>> KeyAssignParam_TypeC;
inline param_table<param_type<param_index::MapGdRegionInfoParam, paramdef::MAP_GD_REGION_ID_PARAM_ST>> MapGdRegionInfoParam;
inline param_table<param_type<param_index::MapGdRegionDrawParam, paramdef::MAP_GD_REGION_DRAW_PARAM>> MapGdRegionDrawParam;
inline param_table<param_type<param_index::KeyAssignMenuItemParam, paramdef::CS_KEY_ASSIGN_MENUITEM_PARAM>> KeyAssignMenuItemParam;
inline param_table<param_type<param_index::SoundAssetSoundObjEnableDistParam, paramdef::SOUND_ASSET_SOUND_OBJ_ENABLE_DIST_PARAM_ST>> SoundAssetSoundObjEnableDistParam;
inline param_table<param_type<param_index::SignPuddleParam, paramdef::SIGN_PUDDLE_PARAM_ST>> SignPuddleParam;
inline param_table<param_type<param_index::AutoCreateEnvSoundParam, paramdef::AUTO_CREATE_ENV_SOUND_PARAM_ST>> AutoCreateEnvSoundParam;
inline param_table<param_type<param_index::WwiseValueToStrParam_BgmBossChrIdConv, paramdef::WWISE_VALUE_TO_STR_CONVERT_PARAM_ST>> WwiseValueToStrParam_BgmBossChrIdConv;
inline param_table<param_type<param_index::ResistCorrectParam, paramdef::RESIST_CORRECT_PARAM_ST>> ResistCorrectParam;
inline param_table<param_type<param_index::PostureControlParam_WepRight, paramdef::POSTURE_CONTROL_PARAM_WEP_RIGHT_ST>> PostureControlParam_WepRight;
inline param_table<param_type<param_index::PostureControlParam_WepLeft, paramdef::POSTURE_CONTROL_PARAM_WEP_LEFT_ST>> PostureControlParam_WepLeft;
inline param_table<param_type<param_index::PostureControlParam_Gender, paramdef::POSTURE_CONTROL_PARAM_GENDER_ST>> PostureControlParam_Gender;
inline param_table<param_type<param_index::PostureControlParam_Pro, paramdef::POSTURE_CONTROL_PARAM_PRO_ST>> PostureControlParam_Pro;
inline param_table<param_type<param_index::RuntimeBoneControlParam, paramdef::RUNTIME_BONE_CONTROL_PARAM_ST>> RuntimeBoneControlParam;
inline param_table<param_type<param_index::TutorialParam, paramdef::TUTORIAL_PARAM_ST>> TutorialParam;
inline param_table<param_type<param_index::BaseChrSelectMenuParam, paramdef::BASECHR_SELECT_MENU_PARAM_ST>> BaseChrSelectMenuParam;
inline param_table<param_type<param_index::MimicryEstablishmentTexParam, paramdef::MIMICRY_ESTABLISHMENT_TEX_PARAM_ST>> MimicryEstablishmentTexParam;
inline param_table<param_type<param_index::SfxBlockResShareParam, paramdef::SFX_BLOCK_RES_SHARE_PARAM>> SfxBlockResShareParam;
inline param_table<param_type<param_index::FinalDamageRateParam, paramdef::FINAL_DAMAGE_RATE_PARAM_ST>> FinalDamageRateParam;
inline param_table<param_type<param_index::HitEffectSeParam, paramdef::HIT_EFFECT_SE_PARAM_ST>> HitEffectSeParam;
inline param_table<param_type<param_index::ChrEquipModelParam, paramdef::CHR_EQUIP_MODEL_PARAM_ST>> ChrEquipModelParam;
inline param_table<param_type<param_index::MapGridCreateHeightDetailLimitInfo, paramdef::MAP_GRID_CREATE_HEIGHT_LIMIT_DETAIL_INFO_PARAM_ST>> MapGridCreateHeightDetailLimitInfo;
inline param_table<param_type<param_index::MapNameTexParam_m61, paramdef::MAP_NAME_TEX_PARAM_ST_DLC02>> MapNameTexParam_m61;
inline param_table<param_type<param_index::MapPieceTexParam_m61, paramdef::MAP_PIECE_TEX_PARAM_ST_DLC02>> MapPieceTexParam_m61;
inline param_table<param_type<param_index::MimicryEstablishmentTexParam_m61, paramdef::MIMICRY_ESTABLISHMENT_TEX_PARAM_ST_DLC02>> MimicryEstablishmentTexParam_m61;
inline param_table<param_type<param_index::SignPuddleSubCategoryParam, paramdef::SIGN_PUDDLE_SUB_CATEGORY_PARAM_ST>> SignPuddleSubCategoryParam;
inline param_table<param_type<param_index::SignPuddleTabParam, paramdef::SIGN_PUDDLE_TAB_PARAM_ST>> SignPuddleTabParam;
inline param_table<param_type<param_index::WeatherLotTexParam_m61, paramdef::WEATHER_LOT_TEX_PARAM_ST_DLC02>> WeatherLotTexParam_m61;
// clang-format on

} // namespace param
} // namespace from
