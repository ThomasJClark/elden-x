/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct decal_param_st {
    /**
     * @brief Texture ID
     */
    int textureId{-1};

    /**
     * @brief Damipoli ID
     *
     * Damipoly ID of decal generation standard. If specified by TAE, it will be
     * the value of TAE.
     */
    int dmypolyId{-1};

    /**
     * @brief Reference angle offset_up / down [deg]
     */
    float pitchAngle{0.f};

    /**
     * @brief Reference angle offset_left / right [deg]
     */
    float yawAngle{0.f};

    /**
     * @brief Pasting start distance [m]
     */
    float nearDistance{0.f};

    /**
     * @brief Paste end distance [m]
     */
    float farDistance{0.f};

    /**
     * @brief Size at the start distance [m]
     */
    float nearSize{0.f};

    /**
     * @brief Size at the end distance [m]
     */
    float farSize{0.f};

    /**
     * @brief Monitoring special effects ID
     *
     * Monitoring special effect ID. If you enter an arbitrary special effect
     * ID, decals will not be generated unless the special effect is applied.
     */
    int maskSpeffectId{-1};

    unsigned int pad_10 : 4 {0};

    /**
     * @brief Texture replacement by material
     *
     * When it is generated by an attack hit, 1 changes the texture depending on
     * the defense material. New Texture ID = Blood Material ID * 10000000 +
     * Original Texture ID
     */
    unsigned int replaceTextureId_byMaterial : 1 {0};

    /**
     * @brief Damipoli search location
     *
     * Damipoli Search Location 0: Body 1: Left Hand Weapon 2: Right Hand Weapon
     */
    unsigned int dmypolyCategory : 2 {0};

    unsigned int pad_05 : 4 {0};

    /**
     * @brief Deferred
     *
     * Acts as a deferred decal at 1
     */
    unsigned int useDeferredDecal : 1 {1};

    /**
     * @brief paint
     *
     * Acts as a paint decal at 1
     */
    unsigned int usePaintDecal : 1 {1};

    /**
     * @brief Bloody expression
     *
     * Affected by optional bloody expression, ID is +1000 in mild, do not paste
     * if hidden
     */
    unsigned int bloodTypeEnable : 1 {0};

    /**
     * @brief Whether to use normal ingredients
     *
     * 1 if normal component is used (compatible with normal and shinyness
     * texture integration)
     */
    unsigned int bUseNormal : 1 {0};

    unsigned int pad_08 : 1 {0};

    unsigned int pad_09 : 1 {0};

    /**
     * @brief Whether to enable POM
     */
    unsigned int usePom : 1 {0};

    /**
     * @brief Whether to update emissive
     */
    unsigned int useEmissive : 1 {0};

    /**
     * @brief Whether to paste vertically
     */
    unsigned int putVertical : 1 {0};

    /**
     * @brief Random scale minimum [%]
     */
    short randomSizeMin{100};

    /**
     * @brief Random scale maximum [%]
     */
    short randomSizeMax{100};

    /**
     * @brief Random angle_minimum twist [deg]
     */
    float randomRollMin{0.f};

    /**
     * @brief Random angle _ maximum twist [deg]
     */
    float randomRollMax{0.f};

    /**
     * @brief Random angle_minimum top and bottom [deg]
     */
    float randomPitchMin{0.f};

    /**
     * @brief Random angle_maximum value [deg]
     */
    float randomPitchMax{0.f};

    /**
     * @brief Random angle_minimum left and right [deg]
     */
    float randomYawMin{0.f};

    /**
     * @brief Random angle_maximum left and right [deg]
     */
    float randomYawMax{0.f};

    /**
     * @brief POM height scale
     */
    float pomHightScale{1.f};

    /**
     * @brief Minimum number of POM samples
     */
    unsigned char pomSampleMin{8};

    /**
     * @brief Maximum number of POM samples
     */
    unsigned char pomSampleMax{64};

    /**
     * @brief Blend mode
     */
    signed char blendMode{1};

    /**
     * @brief Reference coordinates for skipping decals
     *
     * Reference coordinates that determine the direction in which the decal is
     * flown
     */
    signed char appearDirType{0};

    /**
     * @brief Emissive starting price
     */
    float emissiveValueBegin{1.f};

    /**
     * @brief Emissive end value
     */
    float emissiveValueEnd{1.f};

    /**
     * @brief Emissive update time (seconds)
     *
     * Interpolation time from start value to end value
     */
    float emissiveTime{0.f};

    /**
     * @brief Do you want to interpolate?
     *
     * Do you generate the time when the bar is extended due to the decal
     * generation of TAE?
     */
    bool bIntpEnable{false};

    unsigned char pad_01[3];

    /**
     * @brief Interpolation interval [m]
     *
     * Distance to interpolate decals generated between TAE bars when
     * interpolation is enabled
     */
    float intpIntervalDist{0.1f};

    /**
     * @brief Texture ID at the start of interpolation
     *
     * Texture ID at the start of interpolation (-1 uses the same value as the
     * texture ID)
     */
    int beginIntpTextureId{-1};

    /**
     * @brief Texture ID at the end of interpolation
     *
     * Texture at the end of interpolation Texture ID (-1 uses the same value as
     * the texture ID)
     */
    int endIntpTextureId{-1};

    /**
     * @brief SFX ID issued when the decal is affixed
     *
     * SFXID issued when the decal is affixed (Nothing is issued with -1)
     */
    int appearSfxId{-1};

    /**
     * @brief Offset position of SFX
     *
     * Offset distance of SFX generation position
     */
    float appearSfxOffsetPos{0.f};

    /**
     * @brief Mask texture ID
     *
     * Mask texture ID (see texture ID with -1)
     */
    int maskTextureId{-1};

    /**
     * @brief Albedo texture ID
     *
     * Albedo Texture ID (See Texture ID with -1)
     */
    int diffuseTextureId{-1};

    /**
     * @brief Reflect texture ID
     *
     * Reflectance texture ID (see texture ID with -1)
     */
    int reflecTextureId{-1};

    /**
     * @brief Mask strength
     *
     * Mask strength (currently valid only with deferred decals)
     */
    float maskScale{1.f};

    /**
     * @brief Normal texture ID
     *
     * Normal texture ID (see texture ID with -1)
     */
    int normalTextureId{-1};

    /**
     * @brief Height texture ID
     *
     * Height texture ID (see texture ID with -1)
     */
    int heightTextureId{-1};

    /**
     * @brief Emissive Texture ID
     *
     * Emissive Texture ID (See Texture ID with -1)
     */
    int emissiveTextureId{-1};

    /**
     * @brief Albedo color: R
     */
    unsigned char diffuseColorR{255};

    /**
     * @brief Albedo color: G
     */
    unsigned char diffuseColorG{255};

    /**
     * @brief Albedo color: B
     */
    unsigned char diffuseColorB{255};

    unsigned char pad_03[1];

    /**
     * @brief Reflect color: R
     */
    unsigned char reflecColorR{255};

    /**
     * @brief Reflect color: G
     */
    unsigned char reflecColorG{255};

    /**
     * @brief Reflect color: B
     */
    unsigned char reflecColorB{255};

    /**
     * @brief Is the life effective?
     */
    bool bLifeEnable{false};

    /**
     * @brief The strength of shinyness
     */
    float siniScale{1.f};

    /**
     * @brief Lifespan [seconds]
     *
     * Lifespan [seconds] (Time after decal is applied, fade-in time does not
     * matter)
     */
    float lifeTimeSec{0.f};

    /**
     * @brief Fade out time [seconds]
     */
    float fadeOutTimeSec{0.f};

    /**
     * @brief priority
     *
     * The larger this value, the easier it is to remain (-1 does not disappear)
     */
    short priority{-1};

    /**
     * @brief If there is a decal nearby, will it be thinned out?
     *
     * Whether to thin out if there is a decal nearby
     */
    bool bDistThinOutEnable{false};

    /**
     * @brief Fix random pattern
     *
     * If you select "Yes", one variation number randomly determined for each
     * texture other than 0 will be applied. The number of non-zero variations
     * must be the same.
     */
    bool bAlignedTexRandomVariationEnable{false};

    /**
     * @brief Candidates for thinning within this distance
     *
     * Candidates for thinning if there is a decal within this distance
     */
    float distThinOutCheckDist{0.f};

    /**
     * @brief Candidates for thinning if the difference in direction is within
     * this angle [degrees]
     *
     * Candidates for thinning if the difference in decal direction is within
     * this angle
     */
    float distThinOutCheckAngleDeg{0.f};

    /**
     * @brief If the number of satisfied conditions is more than this number,
     * thin out
     *
     * If the distance and angle are more than this number, thin out
     */
    unsigned char distThinOutMaxNum{1};

    /**
     * @brief How many recent thinnings to check
     *
     * How many recent thinning candidates to check
     */
    unsigned char distThinOutCheckNum{1};

    /**
     * @brief Delay frame until it occurs [frame (30FPS conversion)]
     *
     * After trying to paste the decal, it will actually be pasted after this
     * frame
     */
    short delayAppearFrame{0};

    /**
     * @brief Number of albedo variations
     *
     * Number of random variations of albedo texture (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Diffuse : 4 {0};

    /**
     * @brief Number of mask variations
     *
     * Number of random variations of mask texture (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Mask : 4 {0};

    /**
     * @brief Number of reflection variations
     *
     * Number of random variations of reflex textures (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Reflec : 4 {0};

    unsigned int pad_12 : 4 {0};

    /**
     * @brief Number of normal variations
     *
     * Number of random variations of normal texture (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Normal : 4 {0};

    /**
     * @brief Number of height variations
     *
     * Number of random variations of height texture (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Height : 4 {0};

    /**
     * @brief Number of emissive variations
     *
     * Number of random variations of emissive textures (including 0th, 2 for 2
     * textures)
     */
    unsigned int randVaria_Emissive : 4 {0};

    unsigned int pad_11 : 4 {0};

    /**
     * @brief Fade-in time [seconds]
     */
    float fadeInTimeSec{0.f};

    /**
     * @brief Decimation: Duplicate multiplication value
     *
     * Determine if the decal size is duplicated by multiplying it by this
     * value.
     */
    float thinOutOverlapMultiRadius{0.f};

    /**
     * @brief Decimation: Neighborhood addition distance [m]
     *
     * Judge whether it is a neighborhood within the range of adding this
     * distance [m] to the decal size.
     */
    float thinOutNeighborAddRadius{0.f};

    /**
     * @brief Decimation: Overlapping limit
     *
     * Limit number that can be duplicated
     */
    unsigned int thinOutOverlapLimitNum{0};

    /**
     * @brief Decimation: Neighborhood limit
     *
     * Maximum number of neighbors
     */
    unsigned int thinOutNeighborLimitNum{0};

    /**
     * @brief Thinning mode
     */
    signed char thinOutMode{0};

    /**
     * @brief Emissive color: R
     */
    unsigned char emissiveColorR{255};

    /**
     * @brief Emissive color: G
     */
    unsigned char emissiveColorG{255};

    /**
     * @brief Emissive color: B
     */
    unsigned char emissiveColorB{255};

    /**
     * @brief SFX generation upper limit angle
     */
    float maxDecalSfxCreatableSlopeAngleDeg{-1.f};

    unsigned char pad_02[40];
};

};
};

static_assert(sizeof(er::paramdef::decal_param_st) == 248,
              "DECAL_PARAM_ST paramdef size does not match detected size");
