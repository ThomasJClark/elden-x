#pragma once

namespace from
{
namespace CS
{

class EquipMagicData;
class EquipItemData;

class ChrAsm
{
  public:
    virtual ~ChrAsm() = default;

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

    unsigned char unk8[0x1c];
    gear_type<unsigned int> gear_gaitem_ids;
    gear_type<int> gear_ids;
};

class EquipInventoryData
{
  public:
    virtual ~EquipInventoryData() = default;

    unsigned char unk8[0xa0];
};

class EquipGameData
{
  public:
    unsigned char unk0[0x6c];
    CS::ChrAsm chr_asm;
    unsigned char unk148[0x18];
    CS::EquipInventoryData equip_inventory_data;
    CS::EquipMagicData *equip_magic_data;
    CS::EquipItemData *equip_item_data;
    unsigned char unk218[0x218];
};

class PlayerGameData
{
  public:
    unsigned char unk0[0x9c];
    wchar_t *name;
    unsigned char unka8[0x20c];
    CS::EquipGameData equip_game_data;
    unsigned char unk6e8[0x360];
};

}
}
