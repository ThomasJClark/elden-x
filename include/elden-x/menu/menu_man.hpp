#pragma once

#include "popup_menu.hpp"

#include "../utils/modutils.hpp"

namespace er
{
namespace CS
{

class CSMenuManImp
{
  public:
    static CSMenuManImp *instance()
    {
        return modutils::get_singleton<er::CS::CSMenuManImp>("CSMenuMan");
    }

    virtual ~CSMenuManImp() = default;

    unsigned char unk8[0x78];

    CS::CSPopupMenu *popup_menu;
};

}
}
