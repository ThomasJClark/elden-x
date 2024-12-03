/**
 * @file param_defines.hpp
 * @brief ELDEN RING param defines and enums
 *
 * Copyright 2024 libER ELDEN RING API library. Modified for use in elden-x.
 *
 */
#pragma once

#include <cstddef>
#include <cstdint>

namespace from
{
namespace param
{
/**
 * @brief Signed 32-bit integers are used to represent param row indices.
 *
 */
using row_index_type = int32_t;

/**
 * @brief The smallest param row index.
 *
 */
inline constexpr row_index_type row_index_min = 0;

/**
 * @brief The biggest param row index.
 *
 * (it is not INT_MAX!)
 *
 */
inline constexpr row_index_type row_index_max = 999'999'999;

/**
 * @brief The index for specifying no param row.
 *
 * This may be used in param cells that refer to other params
 * to specify no reference.
 *
 */
inline constexpr row_index_type row_index_none = -1;

/**
 * @brief An enum of all param tables as they appear in order.
 *
 * Contains every param type used.
 *
 */
enum class param_index : int
{
    EquipParamWeapon,
    EquipParamProtector,
    EquipParamAccessory,
    EquipParamGoods,
    ReinforceParamWeapon,
    ReinforceParamProtector,
    NpcParam,
    AtkParam_Npc,
    AtkParam_Pc,
    NpcThinkParam,
    Bullet,
    BulletCreateLimitParam,
    BehaviorParam,
    BehaviorParam_PC,
    Magic,
    SpEffectParam,
    SpEffectVfxParam,
    SpEffectSetParam,
    TalkParam,
    MenuColorTableParam,
    ItemLotParam_enemy,
    ItemLotParam_map,
    MoveParam,
    CharaInitParam,
    EquipMtrlSetParam,
    FaceParam,
    FaceRangeParam,
    ShopLineupParam,
    ShopLineupParam_Recipe,
    GameAreaParam,
    CalcCorrectGraph,
    LockCamParam,
    ObjActParam,
    HitMtrlParam,
    KnockBackParam,
    DecalParam,
    ActionButtonParam,
    AiSoundParam,
    PlayRegionParam,
    NetworkAreaParam,
    NetworkParam,
    NetworkMsgParam,
    BudgetParam,
    BonfireWarpParam,
    BonfireWarpTabParam,
    BonfireWarpSubCategoryParam,
    MenuPropertySpecParam,
    MenuPropertyLayoutParam,
    MenuValueTableParam,
    Ceremony,
    PhantomParam,
    CharMakeMenuTopParam,
    CharMakeMenuListItemParam,
    HitEffectSfxConceptParam,
    HitEffectSfxParam,
    WepAbsorpPosParam,
    ToughnessParam,
    SeMaterialConvertParam,
    ThrowDirectionSfxParam,
    DirectionCameraParam,
    RoleParam,
    WaypointParam,
    ThrowParam,
    GrassTypeParam,
    GrassTypeParam_Lv1,
    GrassTypeParam_Lv2,
    GrassLodRangeParam,
    NpcAiActionParam,
    PartsDrawParam,
    AssetEnvironmentGeometryParam,
    AssetModelSfxParam,
    AssetMaterialSfxParam,
    AttackElementCorrectParam,
    FootSfxParam,
    MaterialExParam,
    HPEstusFlaskRecoveryParam,
    MPEstusFlaskRecoveryParam,
    MultiPlayCorrectionParam,
    MenuOffscrRendParam,
    ClearCountCorrectParam,
    MapMimicryEstablishmentParam,
    WetAspectParam,
    SwordArtsParam,
    KnowledgeLoadScreenItemParam,
    MultiHPEstusFlaskBonusParam,
    MultiMPEstusFlaskBonusParam,
    MultiSoulBonusRateParam,
    WorldMapPointParam,
    WorldMapPieceParam,
    WorldMapLegacyConvParam,
    WorldMapPlaceNameParam,
    ChrModelParam,
    LoadBalancerParam,
    LoadBalancerDrawDistScaleParam,
    LoadBalancerDrawDistScaleParam_ps4,
    LoadBalancerDrawDistScaleParam_ps5,
    LoadBalancerDrawDistScaleParam_xb1,
    LoadBalancerDrawDistScaleParam_xb1x,
    LoadBalancerDrawDistScaleParam_xss,
    LoadBalancerDrawDistScaleParam_xsx,
    LoadBalancerNewDrawDistScaleParam_win64,
    LoadBalancerNewDrawDistScaleParam_ps4,
    LoadBalancerNewDrawDistScaleParam_ps5,
    LoadBalancerNewDrawDistScaleParam_xb1,
    LoadBalancerNewDrawDistScaleParam_xb1x,
    LoadBalancerNewDrawDistScaleParam_xss,
    LoadBalancerNewDrawDistScaleParam_xsx,
    WwiseValueToStrParam_Switch_AttackType,
    WwiseValueToStrParam_Switch_DamageAmount,
    WwiseValueToStrParam_Switch_DeffensiveMaterial,
    WwiseValueToStrParam_Switch_HitStop,
    WwiseValueToStrParam_Switch_OffensiveMaterial,
    WwiseValueToStrParam_Switch_GrassHitType,
    WwiseValueToStrParam_Switch_PlayerShoes,
    WwiseValueToStrParam_Switch_PlayerEquipmentTops,
    WwiseValueToStrParam_Switch_PlayerEquipmentBottoms,
    WwiseValueToStrParam_Switch_PlayerVoiceType,
    WwiseValueToStrParam_Switch_AttackStrength,
    WwiseValueToStrParam_EnvPlaceType,
    WeatherParam,
    WeatherLotParam,
    WeatherAssetCreateParam,
    WeatherAssetReplaceParam,
    SpeedtreeParam,
    RideParam,
    SeActivationRangeParam,
    RollingObjLotParam,
    NpcAiBehaviorProbability,
    BuddyParam,
    GparamRefSettings,
    RandomAppearParam,
    MapGridCreateHeightLimitInfoParam,
    EnvObjLotParam,
    MapDefaultInfoParam,
    BuddyStoneParam,
    LegacyDistantViewPartsReplaceParam,
    SoundCommonIngameParam,
    SoundAutoEnvSoundGroupParam,
    SoundAutoReverbEvaluationDistParam,
    SoundAutoReverbSelectParam,
    EnemyCommonParam,
    GameSystemCommonParam,
    GraphicsCommonParam,
    MenuCommonParam,
    PlayerCommonParam,
    CutsceneGparamWeatherParam,
    CutsceneGparamTimeParam,
    CutsceneTimezoneConvertParam,
    CutsceneWeatherOverrideGparamConvertParam,
    SoundCutsceneParam,
    ChrActivateConditionParam,
    CutsceneMapIdParam,
    CutSceneTextureLoadParam,
    GestureParam,
    EquipParamGem,
    EquipParamCustomWeapon,
    GraphicsConfig,
    SoundChrPhysicsSeParam,
    FeTextEffectParam,
    CoolTimeParam,
    WhiteSignCoolTimeParam,
    MapPieceTexParam,
    MapNameTexParam,
    WeatherLotTexParam,
    KeyAssignParam_TypeA,
    KeyAssignParam_TypeB,
    KeyAssignParam_TypeC,
    MapGdRegionInfoParam,
    MapGdRegionDrawParam,
    KeyAssignMenuItemParam,
    SoundAssetSoundObjEnableDistParam,
    SignPuddleParam,
    AutoCreateEnvSoundParam,
    WwiseValueToStrParam_BgmBossChrIdConv,
    ResistCorrectParam,
    PostureControlParam_WepRight,
    PostureControlParam_WepLeft,
    PostureControlParam_Gender,
    PostureControlParam_Pro,
    RuntimeBoneControlParam,
    TutorialParam,
    BaseChrSelectMenuParam,
    MimicryEstablishmentTexParam,
    SfxBlockResShareParam,
    FinalDamageRateParam,
    HitEffectSeParam,
    ChrEquipModelParam,
    MapGridCreateHeightDetailLimitInfo,
    MapNameTexParam_m61,
    MapPieceTexParam_m61,
    MimicryEstablishmentTexParam_m61,
    SignPuddleSubCategoryParam,
    SignPuddleTabParam,
    WeatherLotTexParam_m61,
    PARAM_COUNT
};

/**
 * @brief The total number of all defined param tables.
 *
 */
inline constexpr size_t param_count = size_t(param_index::PARAM_COUNT);

} // namespace param
} // namespace from
