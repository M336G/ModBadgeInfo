#pragma once

class ModHelper {
public:
    static const int8_t robTopAccountID = 71;
    static const int8_t robTopUserID = 16;

    static cocos2d::CCSprite *createModBadgeSprite(int modState) {
        switch (modState) {
            case 1:
                return cocos2d::CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
            case 2:
                return cocos2d::CCSprite::createWithSpriteFrameName("modBadge_02_001.png");
            case 3:
                return cocos2d::CCSprite::createWithSpriteFrameName("modBadge_03_001.png");
            default:
                return nullptr;
        }
    }

    static void showModBadgeAlert(int modState, bool isRobTop) {
        if (isRobTop) {
            FLAlertLayer::create(
                "RobTop!",
                "This is <cb>RobTop</c>, the owner and creator of <cy>Geometry Dash</c>. They can do <co>anything they want</c>!",
                "OK")
                ->show();
            return;
        }

        switch (modState) {
            case 1:
                FLAlertLayer::create(
                    "Moderator!",
                    "This user is a <cy>Geometry Dash</c> <cg>Moderator</c>! They can <co>suggest levels</c> to <cb>RobTop</c>.",
                    "OK")
                    ->show();
                break;
            case 2:
                FLAlertLayer::create(
                    "Elder Moderator!",
                    "This user is a <cy>Geometry Dash</c> <cr>Elder Moderator</c>! They can <co>moderate comments</c>, <co>whitelist Newgrounds artists</c>, <co>unlock updates for old rated levels</c>, and <co>suggest levels</c> to <cb>RobTop</c>.",
                    "OK")
                    ->show();
                break;
            case 3:
                FLAlertLayer::create(
                    "Leaderboard Moderator!",
                    "This user is a <cy>Geometry Dash</c> <cj>Leaderboard Moderator</c>! They moderate the <co>Top 100 Leaderboard</c>, the <co>Global Leaderboard</c> and the <co>level-specific leaderboards</c>.",
                    "OK")
                    ->show();
                break;
        }
    }
};