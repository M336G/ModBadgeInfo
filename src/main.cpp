#include <Geode/modify/ProfilePage.hpp>

class $modify(ModBadgeInfoProfilePage, ProfilePage) {
	struct Fields {
		int m_modState;
		cocos2d::CCSprite* m_modBadgeSprite = nullptr;
		bool m_isRobTop = false;
	};
	void loadPageFromUserInfo(GJUserScore* p0) {
  		ProfilePage::loadPageFromUserInfo(p0);

		auto menu = static_cast<cocos2d::CCMenu*>(this->getChildByIDRecursive("username-menu"));

  		if (auto modBadge = static_cast<cocos2d::CCSprite*>(menu->getChildByID("mod-badge"))) {
			m_fields->m_modState = p0->m_modBadge;
			
			if (p0->m_accountID == 71) m_fields->m_isRobTop = true; // RobTop

			switch(m_fields->m_modState) {
				case 1:
					m_fields->m_modBadgeSprite = cocos2d::CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
					break;
				case 2:
					m_fields->m_modBadgeSprite = cocos2d::CCSprite::createWithSpriteFrameName("modBadge_02_001.png");
					break;
				case 3:
					m_fields->m_modBadgeSprite = cocos2d::CCSprite::createWithSpriteFrameName("modBadge_03_001.png");
					break;
			}

			if (m_fields->m_modBadgeSprite) { // Check if it's not nullptr
    			auto modBadgeBtn = CCMenuItemSpriteExtra::create(
        			m_fields->m_modBadgeSprite,
					this,
					menu_selector(ModBadgeInfoProfilePage::onModBadgeBtn)
    			);

				modBadgeBtn->setPosition(modBadge->getPosition());
				modBadgeBtn->setID("mod-badge-btn"_spr);
				menu->addChild(modBadgeBtn);

				// Make the base non-clickable badge invisible without removing it from its parent to avoid breaking dependencies
				modBadge->setVisible(false);
			}
		}
	};
	void onModBadgeBtn(CCObject*) {
		if (m_fields->m_isRobTop) {
			FLAlertLayer::create(
				"RobTop!", 
				"This is <cb>RobTop</c>, the owner of <cy>Geometry Dash</c>. They can do <co>anything they want</c>!", 
				"OK"
			)->show();
			return;
		}
		switch(m_fields->m_modState) {
			case 1:
				FLAlertLayer::create(
					"Moderator!", 
					"This user is a <cy>Geometry Dash</c> <cg>Moderator</c>! They can <co>suggest levels</c> to <cb>RobTop</c>.", 
					"OK"
				)->show();
				break;
			case 2:
				FLAlertLayer::create(
					"Elder Moderator!", 
					"This user is a <cy>Geometry Dash</c> <cr>Elder Moderator</c>! They can <co>moderate comments</c>, <co>whitelist Newgrounds artists</c>, <co>unlock updates for old rated levels</c>, and <co>suggest levels</c> to <cb>RobTop</c>.", 
					"OK"
				)->show();
				break;
			case 3:
				FLAlertLayer::create(
					"Leaderboard Moderator!", 
					"This user is a <cy>Geometry Dash</c> <cj>Leaderboard Moderator</c>! They moderate the <co>Top 100 Leaderboard</c>, the <co>Global Leaderboard</c> and the <co>level-specific leaderboards</c>.", 
					"OK"
				)->show();
				break;
		}
	}
};
