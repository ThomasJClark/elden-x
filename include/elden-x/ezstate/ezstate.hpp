#pragma once

#include <span>

namespace from
{
namespace ezstate
{

struct event;
struct state_group;
struct state;
struct transition;

typedef std::span<event> events;
typedef std::span<state> states;
typedef std::span<transition *> transitions;
typedef std::span<unsigned char> expression;
typedef std::span<expression> args;

/**
 * Base class extended by EzState::detail::EzStateMachineImpl
 */
class machine
{
  public:
    virtual ~machine() = default;

    unsigned char unk1[0x20];
    state_group *state_group;
    unsigned char unk2[0x110];
};

/**
 * The possible states in a state machine. This is usually represented by a function in ESDLang.
 */
struct state_group
{
    int id;
    states states;
    state *initial_state;
};

/**
 * A transition from one EzState state to another. The state machine will transition to the first
 * target state whose evaluator bytecode evaluates to true.
 */
struct transition
{
    state *target_state;
    events pass_events;
    transitions sub_transitions;
    expression evaluator;

    inline transition(state *target_state, expression evaluator)
        : target_state(target_state), evaluator(evaluator)
    {
    }
};

/**
 * A command (AKA built-in function called in an EzState state). Most of the known command
 * IDs are available in talk_commands.hpp
 */
struct command
{
    int bank;
    int id;

    bool operator==(command const &other)
    {
        return bank == other.bank && id == other.id;
    }
};

/**
 * An event in a talkscript. This is what's typically represented as a built-in function call in
 * ESDLang, such as "AddTalkListData(1, 12345, -1)"
 */
struct event
{
    command command;
    args args;
};

struct state
{
    /**
     * I think this is only used when reading talkscripts from disk, but I'm not sure
     */
    int id;

    /**
     * Transitions to other states. The first one to evaluate to true will become the new active
     * state
     */
    transitions transitions;

    /**
     * Commands executed when we transition into this state
     */
    events entry_events;

    /**
     * Other commands presumably executed at different times, although I don't see these used often
     */
    events exit_events;
    events while_events;
};

}
}
