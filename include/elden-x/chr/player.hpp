#pragma once

#include "../steam_id.hpp"
#include "chr.hpp"

namespace er
{

namespace CS
{

class EquipMagicData;
class EquipItemData;

class ChrAsm
{
  public:
    enum class arm_style_type : unsigned int
    {
        one_hand = 1,
        two_hand_left = 2,
        two_hand_right = 3,
    };

    template <typename T> struct gear_type
    {
        T left_weapon_id1;
        T right_weapon_id1;
        T left_weapon_id2;
        T right_weapon_id2;
        T left_weapon_id3;
        T right_weapon_id3;
        T arrow_id1;
        T bolt_id1;
        T arrow_id2;
        T bolt_id2;
        T unused1;
        T unused2;
        T head_protector_id;
        T chest_protector_id;
        T arms_protector_id;
        T legs_protector_id;
        T unused3;
        T accessory_id1;
        T accessory_id2;
        T accessory_id3;
        T accessory_id4;
        T unused4;
    };

    int unk0;
    int unk4;
    arm_style_type arm_style;
    int left_weapon_index;
    int right_weapon_index;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    gear_type<unsigned int> gear_gaitem_ids;
    gear_type<int> gear_param_ids;
    int unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    int unke4;
};
static_assert(0x0 == __builtin_offsetof(ChrAsm, unk0));
static_assert(0x4 == __builtin_offsetof(ChrAsm, unk4));
static_assert(0xc == __builtin_offsetof(ChrAsm, left_weapon_index));
static_assert(0x10 == __builtin_offsetof(ChrAsm, right_weapon_index));
static_assert(0x14 == __builtin_offsetof(ChrAsm, unk14));
static_assert(0x18 == __builtin_offsetof(ChrAsm, unk18));
static_assert(0x1c == __builtin_offsetof(ChrAsm, unk1c));
static_assert(0x20 == __builtin_offsetof(ChrAsm, unk20));
static_assert(0x24 == __builtin_offsetof(ChrAsm, gear_gaitem_ids));
static_assert(0x7c == __builtin_offsetof(ChrAsm, gear_param_ids));
static_assert(0xd4 == __builtin_offsetof(ChrAsm, unkd4));
static_assert(0xd8 == __builtin_offsetof(ChrAsm, unkd8));
static_assert(0xdc == __builtin_offsetof(ChrAsm, unkdc));
static_assert(0xe0 == __builtin_offsetof(ChrAsm, unke0));
static_assert(0xe4 == __builtin_offsetof(ChrAsm, unke4));
static_assert(0xe8 == sizeof(ChrAsm));

class EquipInventoryData
{
  public:
    virtual ~EquipInventoryData() = default;

    unsigned char unk8[0x120];
};

static_assert(0x128 == sizeof(EquipInventoryData));

class EquipGameData
{
  public:
    virtual ~EquipGameData() = default;

    unsigned char unk8[0x64];
    CS::ChrAsm chr_asm;
    CS::EquipInventoryData equip_inventory_data;
    CS::EquipMagicData *equip_magic_data;
    CS::EquipItemData *equip_item_data;
    unsigned char unk290[0x21c];
};

static_assert(0x8 == __builtin_offsetof(EquipGameData, unk8));
static_assert(0x6c == __builtin_offsetof(EquipGameData, chr_asm));
static_assert(0x158 == __builtin_offsetof(EquipGameData, equip_inventory_data));
static_assert(0x280 == __builtin_offsetof(EquipGameData, equip_magic_data));
static_assert(0x288 == __builtin_offsetof(EquipGameData, equip_item_data));
static_assert(0x290 == __builtin_offsetof(EquipGameData, unk290));
static_assert(0x4b0 == sizeof(EquipGameData));

class PlayerGameData
{
  public:
    struct attributes_st
    {
        int vigor;
        int mind;
        int endurance;
        int strength;
        int dexterity;
        int intelligence;
        int faith;
        int arcane;
    };

    virtual ~PlayerGameData() = default;

    std::wstring_view name()
    {
        return std::wstring_view{&name_c_str[0]};
    }

    unsigned char unk8[0x8];
    int hp;
    int hp_max;
    int fp;
    int fp_max;
    int stamina;
    int stamina_max;
    unsigned char unk28[0x14];
    attributes_st attributes;
    unsigned char unk5c[0xc];
    int rune_level;
    unsigned char unk6c[0x30];
    wchar_t name_c_str[16];
    unsigned char unkbc[0x26];
    unsigned char max_reinforce_level;
    unsigned char unke3[0x1cd];
    CS::EquipGameData equip_game_data;
    unsigned char unk760[0x408];
};

static_assert(0x8 == __builtin_offsetof(PlayerGameData, unk8));
static_assert(0x10 == __builtin_offsetof(PlayerGameData, hp));
static_assert(0x14 == __builtin_offsetof(PlayerGameData, hp_max));
static_assert(0x18 == __builtin_offsetof(PlayerGameData, fp));
static_assert(0x1c == __builtin_offsetof(PlayerGameData, fp_max));
static_assert(0x20 == __builtin_offsetof(PlayerGameData, stamina));
static_assert(0x24 == __builtin_offsetof(PlayerGameData, stamina_max));
static_assert(0x28 == __builtin_offsetof(PlayerGameData, unk28));
static_assert(0x3c == __builtin_offsetof(PlayerGameData, attributes));
static_assert(0x5c == __builtin_offsetof(PlayerGameData, unk5c));
static_assert(0x68 == __builtin_offsetof(PlayerGameData, rune_level));
static_assert(0x6c == __builtin_offsetof(PlayerGameData, unk6c));
static_assert(0x9c == __builtin_offsetof(PlayerGameData, name_c_str));
static_assert(0xbc == __builtin_offsetof(PlayerGameData, unkbc));
static_assert(0xe2 == __builtin_offsetof(PlayerGameData, max_reinforce_level));
static_assert(0xe3 == __builtin_offsetof(PlayerGameData, unke3));
static_assert(0x2b0 == __builtin_offsetof(PlayerGameData, equip_game_data));
static_assert(0x760 == __builtin_offsetof(PlayerGameData, unk760));
static_assert(0xb68 == sizeof(PlayerGameData));

class PlayerNetworkSession
{
  public:
    virtual ~PlayerNetworkSession() = default;

    steam_id_type steam_id;
};

class PlayerSessionHolder
{
  public:
    virtual ~PlayerSessionHolder() = default;

    void *unk8;
    CS::PlayerNetworkSession *network_session;
    CS::PlayerNetworkSession *network_session2;
    int unk20;
};
static_assert(0x8 == __builtin_offsetof(PlayerSessionHolder, unk8));
static_assert(0x10 == __builtin_offsetof(PlayerSessionHolder, network_session));
static_assert(0x18 == __builtin_offsetof(PlayerSessionHolder, network_session2));
static_assert(0x20 == __builtin_offsetof(PlayerSessionHolder, unk20));
static_assert(0x28 == sizeof(PlayerSessionHolder));

class PlayerIns : public CS::ChrIns
{
  public:
    virtual ~PlayerIns() = default;

    CS::PlayerGameData *game_data;
    unsigned char unk588[0x10];
    CS::PlayerSessionHolder session_holder;
    unsigned char unk5c0[0x180];
};
static_assert(0x580 == __builtin_offsetof(PlayerIns, game_data));
static_assert(0x588 == __builtin_offsetof(PlayerIns, unk588));
static_assert(0x598 == __builtin_offsetof(PlayerIns, session_holder));
static_assert(0x5c0 == __builtin_offsetof(PlayerIns, unk5c0));
static_assert(0x740 == sizeof(PlayerIns));

}
}
