#include <Geode/Geode.hpp>
#include "../ModHelper.hpp"

using namespace geode::prelude;

#include <Geode/modify/ProfilePage.hpp>
class $modify(MyProfilePage, ProfilePage) {
	struct Fields {
		int m_modState;
		bool m_isRobTop = false;
	};

	void loadPageFromUserInfo(GJUserScore *score) {
		ProfilePage::loadPageFromUserInfo(score);

		if (ModHelper::isBadgifyLoaded())
			return;

		// Get the original mod badge
		auto *menu = static_cast<cocos2d::CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));
		if (!menu) return;
		auto *modBadge = static_cast<cocos2d::CCSprite *>(menu->getChildByIDRecursive("mod-badge"));
		if (!modBadge) return;

		// If the badge's already there after a reload, delete it and continue
		if (auto *modBadgeBtnDupe = static_cast<CCMenuItemSpriteExtra *>(menu->getChildByIDRecursive("mod-badge-button"_spr))) {
			modBadgeBtnDupe->removeFromParentAndCleanup(true);
			menu->updateLayout();
		}

		// Change these fields accordingly
		m_fields->m_modState = score->m_modBadge;
		m_fields->m_isRobTop = (score->m_accountID == ModHelper::robTopAccountID && score->m_userID == ModHelper::robTopUserID);

        // Store the original mod badge position and remove it from the menu
        auto modBadgePosition = modBadge->getPosition();
        modBadge->removeFromParent();

		// Create the actual clickable button
		auto *modBadgeBtn = CCMenuItemSpriteExtra::create(
			modBadge,
			this,
			menu_selector(MyProfilePage::onModBadgeBtn)
		);
        modBadgeBtn->setID("mod-badge-button"_spr);
        modBadgeBtn->setPosition(modBadgePosition);
		
		menu->addChild(modBadgeBtn);
	};

	void onModBadgeBtn(CCObject *) {
		ModHelper::showModBadgeAlert(m_fields->m_modState, m_fields->m_isRobTop);
	};
};