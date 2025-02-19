#pragma once

#include <span>

#include "singletons.hpp"

namespace er
{

namespace DLNR3D
{
class ManagerImplSteam;

class Session
{
  public:
    virtual ~Session() = default;

    unsigned char unk8[0x3c0];
    int unk3c8;
    unsigned char unk3cc[0x19c];
};

static_assert(0x568 == sizeof(Session));

class SessionSteam : public Session
{
  public:
    virtual ~SessionSteam() = default;

    unsigned char unk568[0x90];
};

static_assert(0x5f8 == sizeof(SessionSteam));

class SessionManagerSteam
{
  public:
    virtual ~SessionManagerSteam() = default;
    virtual void unkfn1(){};
    virtual void unkfn2(){};
    virtual void end_session(int, int, void *){};
    virtual void kick_out(int, void *, int){};
    virtual void unkfn5(){};
    virtual void end_session2(int){};

    ManagerImplSteam *impl;
    void *unk10;

    /** Plural, but afaict there are always either 0 or 1 sessions */
    SessionSteam **sessions;
    int session_capacity;
    unsigned int session_count;

    unsigned char unk28[0x88];
};

static_assert(0x8 == __builtin_offsetof(SessionManagerSteam, impl));
static_assert(0x18 == __builtin_offsetof(SessionManagerSteam, sessions));
static_assert(0x20 == __builtin_offsetof(SessionManagerSteam, session_capacity));
static_assert(0x24 == __builtin_offsetof(SessionManagerSteam, session_count));
static_assert(0xb0 == sizeof(SessionManagerSteam));

class ManagerImplSteam
{
  public:
    virtual ~ManagerImplSteam() = default;

    unsigned char unk8[0x708];
    SessionManagerSteam session_manager;
    unsigned char unk7c0[0x1e0];
};

static_assert(0x710 == __builtin_offsetof(ManagerImplSteam, session_manager));
}

namespace CS
{
class CSSessionManager
    : public FD4::FD4Singleton<CSSessionManager, FD4::singleton_index::CSSessionManager>
{
  public:
    struct player_entry
    {
        void *unk0;
        void *unk8;
        unsigned long long steam_id;
        unsigned char unk18[0xe8];
    };

    virtual ~CSSessionManager() = default;

    unsigned char unk8[0x58];
    DLNR3D::ManagerImplSteam *impl;
    unsigned char unk68[0x10];
    player_entry *player_entries_begin;
    player_entry *player_entries_end;
    void *unk88;
    player_entry host_player_entry;
    unsigned char unk190[0x1c8];

    std::span<player_entry> player_entries()
    {
        return {player_entries_begin, player_entries_end};
    }

    std::span<DLNR3D::SessionSteam *> sessions()
    {
        return {impl->session_manager.sessions,
                static_cast<size_t>(impl->session_manager.session_count)};
    }

    void end_session(DLNR3D::Session *session, int unk2 = 0, void *unk3 = nullptr)
    {
        impl->session_manager.end_session(session->unk3c8, unk2, unk3);
    }

    void end_session2(DLNR3D::Session *session)
    {
        impl->session_manager.end_session2(session->unk3c8);
    };

    void kick(int unk1, void *unk2, int unk3)
    {
        impl->session_manager.kick_out(unk1, unk2, unk3);
    }
};

typedef CSSessionManager CSSessionManagerImp;

static_assert(0x8 == __builtin_offsetof(CSSessionManager, unk8));
static_assert(0x60 == __builtin_offsetof(CSSessionManager, impl));
static_assert(0x68 == __builtin_offsetof(CSSessionManager, unk68));
static_assert(0x78 == __builtin_offsetof(CSSessionManager, player_entries_begin));
static_assert(0x80 == __builtin_offsetof(CSSessionManager, player_entries_end));
static_assert(0x88 == __builtin_offsetof(CSSessionManager, unk88));
static_assert(0x90 == __builtin_offsetof(CSSessionManager, host_player_entry));
static_assert(0x190 == __builtin_offsetof(CSSessionManager, unk190));
static_assert(0x358 == sizeof(CSSessionManager));
}

}
