#include "ModHelper.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

std::unordered_map<std::string, std::string> const ModHelper::badgeDescriptions = {
    { "robtop", "This is <cb>RobTop</c>, the owner and creator of <cy>Geometry Dash</c>. They can do <co>anything they want</c>!" },
    { "leaderboard-moderator", "This user is a <cy>Geometry Dash</c> <cj>Leaderboard Moderator</c>! They moderate the <co>Top 100 Leaderboard</c>, the <co>Global Leaderboard</c> and <co>level-specific leaderboards</c>." },
    { "elder-moderator", "This user is a <cy>Geometry Dash</c> <cr>Elder Moderator</c>! They can <co>moderate comments</c>, <co>whitelist Newgrounds artists</c>, <co>unlock updates for old rated levels</c>, and <co>suggest levels</c> to <cb>RobTop</c>." },
    { "moderator", "This user is a <cy>Geometry Dash</c> <cg>Moderator</c>! They can <co>suggest levels</c> to <cb>RobTop</c>." }
};

bool ModHelper::isBadgifyLoaded() {
    static bool isBadgifyLoaded = Loader::get()->isModLoaded("alphalaneous.badgify");
    return isBadgifyLoaded;
}

void ModHelper::showModBadgeAlert(int modState, bool isRobTop) {
    std::string name;
    std::string description;

    if (isRobTop) {
        name = "RobTop!";
        description = badgeDescriptions.at("robtop");
    } else {
        switch (modState) {
            case 1:
                name = "Moderator!";
                description = badgeDescriptions.at("moderator");
                break;
            case 2:
                name = "Elder Moderator!";
                description = badgeDescriptions.at("elder-moderator");
                break;
            case 3:
                name = "Leaderboard Moderator!";
                description = badgeDescriptions.at("leaderboard-moderator");
                break;
            default:
                return;
        }
    }

    FLAlertLayer::create(
        name.c_str(),
        description.c_str(),
        "OK"
    )->show();
}