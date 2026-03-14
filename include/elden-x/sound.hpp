#pragma once

#include "singletons.hpp"

namespace er {
namespace CS {

struct cs_sound_flags {
private:
    uint8_t unk0[0x4];

public:
    bool is_in_combat;

private:
    uint8_t unk5[0x1653];
};

class CSSound : public FD4::FD4Singleton<CSSound, FD4::singleton_index::CSSound> {
public:
    virtual ~CSSound() = default;

private:
    uint8_t unk8[0x320];

public:
    cs_sound_flags *flags;
};

}
}
