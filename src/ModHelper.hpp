#pragma once

class ModHelper {
public:
    static constexpr int robTopAccountID = 71;
    static constexpr int robTopUserID = 16;

    static const std::unordered_map<std::string, std::string> badgeDescriptions;

    static bool isBadgifyLoaded();
    static void showModBadgeAlert(int modState, bool isRobTop);
};