#include <Geode/Geode.hpp>
#include <alphalaneous.badgify/include/Badgify.hpp>
#include "ModHelper.hpp"

$on_mod(Loaded) {
    if (!ModHelper::isBadgifyLoaded())
        return;

    alpha::badgify::setDescription("alphalaneous.badgify/moderator", ModHelper::badgeDescriptions.at("moderator"));
    alpha::badgify::setDescription("alphalaneous.badgify/elder-moderator", ModHelper::badgeDescriptions.at("elder-moderator"));
    alpha::badgify::setDescription("alphalaneous.badgify/leaderboard-moderator", ModHelper::badgeDescriptions.at("leaderboard-moderator"));
}