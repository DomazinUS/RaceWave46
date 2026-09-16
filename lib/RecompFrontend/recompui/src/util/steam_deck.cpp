#include "steam_deck.h"

#include <fstream>

namespace recompui {
    bool is_steam_deck() {
    #ifdef __gnu_linux__
        static bool checked = false;
        static bool detected = false;
        if (!checked) {
            // Check if the board vendor is Valve.
            std::ifstream board_vendor_file("/sys/devices/virtual/dmi/id/board_vendor");
            std::string line;
            if (std::getline(board_vendor_file, line).good() && line == "Valve") {
                detected = true;
            }
            else {
                // Check if the SteamDeck variable is set to 1.
                const char* steam_deck_env = getenv("SteamDeck");
                if (steam_deck_env != nullptr && std::string{steam_deck_env} == "1") {
                    detected = true;
                }
            }

            checked = true;
        }

        return detected;
    #else
        return false;
    #endif
    }
}