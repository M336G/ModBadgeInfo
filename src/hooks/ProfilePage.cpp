#include <Geode/modify/ProfilePage.hpp>
#include "../ModHelper.h"

class $modify(MyProfilePage, ProfilePage) {
	struct Fields {
		int m_modState;
		bool m_isRobTop = false;
	};

	void loadPageFromUserInfo(GJUserScore *p0) {
		ProfilePage::loadPageFromUserInfo(p0);

		// Get the original mod badge
		auto layer = this->getChildByIndex(0);
		if (!layer) return;
		auto usernameMenu = layer->getChildByID("username-menu");
		if (!usernameMenu) return;
		auto modBadge = usernameMenu->getChildByID("mod-badge");
		if (!modBadge) return;

		// Change these fields accordingly
		m_fields->m_modState = p0->m_modBadge;
		m_fields->m_isRobTop = p0->m_accountID == ModHelper::robTopAccountID && p0->m_userID == ModHelper::robTopUserID;
		
		// Create the new sprite according to the modBadge value we got
		auto modBadgeSpr = ModHelper::createModBadgeSprite(m_fields->m_modState);

		// Create the actual clickable button
		auto modBadgeBtn = CCMenuItemSpriteExtra::create(
			modBadgeSpr,
			this,
			menu_selector(MyProfilePage::onModBadgeBtn)
		);

		modBadgeBtn->setID("mod-badge-button"_spr);
		modBadgeBtn->setPosition(modBadge->getPosition());
		usernameMenu->addChild(modBadgeBtn);

		// Keep the original badge but make it invisible to avoid issues with other
		// mods depending on it
		modBadge->setVisible(false);
	};

	void onModBadgeBtn(CCObject *) {
		ModHelper::showModBadgeAlert(m_fields->m_modState, m_fields->m_isRobTop);
	};
};