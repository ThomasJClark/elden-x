#pragma once

#include "singletons.hpp"
#include "stl.hpp"

namespace er {
namespace CS {

class CSEventFlagMan
    : public FD4::FD4Singleton<CSEventFlagMan, FD4::singleton_index::CSEventFlagMan> {
public:
    enum class block_location_type { index = 1, pointer = 2 };

    struct block_location {
        block_location_type type;

        union {
            int index;
            unsigned char *pointer;
        };
    };

    unsigned char unk8[0x14];
    int flags_per_block;
    int block_size;
    int block_count;
    unsigned char *block_data;
    map<int, block_location> block_locations;
    unsigned char unk48[0x220];

    virtual ~CSEventFlagMan() = default;

    /**
     * @returns true if the given event flag is set on
     */
    bool get_event_flag(int flag_id) {
        int block_id = flag_id / flags_per_block;

        if (auto *data = get_block_data(block_id); data) {
            int index = flag_id - block_id * flags_per_block;
            int byte_index = index / 8;
            int bit_index = 7 - index % 8;
            return (data[byte_index] & (1 << bit_index)) != 0;
        }

        return false;
    }

private:
    unsigned char *get_block_data(int block_id) {
        if (auto block_location_it = block_locations.find(block_id);
            block_location_it != block_locations.end()) {
            if (block_location_it->second.type == block_location_type::index) {
                return &block_data[block_size * block_location_it->second.index];
            } else if (block_location_it->second.type == block_location_type::pointer) {
                return block_location_it->second.pointer;
            }
        }

        return nullptr;
    }
};

static_assert(0x8 == __builtin_offsetof(CSEventFlagMan, unk8));
static_assert(0x1c == __builtin_offsetof(CSEventFlagMan, flags_per_block));
static_assert(0x20 == __builtin_offsetof(CSEventFlagMan, block_size));
static_assert(0x24 == __builtin_offsetof(CSEventFlagMan, block_count));
static_assert(0x28 == __builtin_offsetof(CSEventFlagMan, block_data));
static_assert(0x30 == __builtin_offsetof(CSEventFlagMan, block_locations));

}
}