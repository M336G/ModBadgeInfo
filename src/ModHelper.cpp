#include "ModHelper.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

std::unordered_map<std::string, std::string> const ModHelper::badgeDescriptions = {
    { "robtop", "This is <cb>RobTop</c>, the <cy>owner & creator of Geometry Dash</c>.\nHe can do <cl>anything he wants</c>!" },
    { "leaderboard-moderator", "This is a <cj>Leaderboard Moderator</c>!\nThey moderate the <cc>Top 1000 whitelist</c>, <cs>Global & level leaderboards</c>, and can <cr>ban players from them</c>. They also have <cr>more power when voting for Demon ratings</c>.\nThis role can <co>only</c> be granted by <cb>RobTop</c>!" },
    { "elder-moderator", "This is an <cr>Elder Moderator</c>!\nThey <cl>suggest levels they find good</c> to <cb>RobTop</c> to be rated, <cr>moderate comments</c>, <cc>whitelist Newgrounds artists</c>, <cf>unlock updates for old rated levels</c>, and more. They have the <cl>same rating power as regular Moderators</c>.\nThis role can <co>only</c> be granted by <cb>RobTop</c>!" },
    { "moderator", "This is a <cs>Moderator</c>!\nThey can <cl>suggest levels they find good</c> to <cb>RobTop</c> to be rated and have <cr>more power when voting for Demon ratings</c>.\nThis role can <co>only</c> be granted by <cb>RobTop</c>!" }
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