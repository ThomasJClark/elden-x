#pragma once

namespace er {

// If the SteamWorks SDK is included, use the actual Steam ID structure. Otherwise, use a 64
// bit integer.
#ifdef CSTEAMID_DEFINED
using steam_id_type = CSteamID;
#else
using steam_id_type = unsigned long long;
#endif

}