#include <Geode/Geode.hpp>
#include <dasshu.badgified/include/Badgified.hpp>

#include "ModHelper.hpp"

$on_mod(Loaded) {
    if (!ModHelper::isBadgifiedLoaded())
        return;

    dasshu::badgified::setDescription("dasshu.badgified/moderator", ModHelper::badgeDescriptions.at("moderator"));
    dasshu::badgified::setDescription("dasshu.badgified/elder-moderator", ModHelper::badgeDescriptions.at("elder-moderator"));
    dasshu::badgified::setDescription("dasshu.badgified/leaderboard-moderator", ModHelper::badgeDescriptions.at("leaderboard-moderator"));
}