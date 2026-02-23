#include <Geode/modify/CommentCell.hpp>
#include "../ModHelper.h"

class $modify(MyCommentCell, CommentCell) {
	struct Fields {
		int m_modState;
		bool m_isRobTop = false;
	};

	void loadFromComment(GJComment *comment) {
		CommentCell::loadFromComment(comment);

		// Get the original mod badge
		auto layer = this->getChildByIndex(1);
		if (!layer) return;
		auto mainMenu = layer->getChildByID("main-menu");
		if (!mainMenu) return;
		auto userMenu = mainMenu->getChildByID("user-menu");
		if (!userMenu) return;
		auto usernameMenu = userMenu->getChildByID("username-menu");
		if (!usernameMenu) return;
		auto modBadge = usernameMenu->getChildByID("mod-badge");
		if (!modBadge) return;

		// Change these fields accordingly
		m_fields->m_modState = comment->m_modBadge;
		m_fields->m_isRobTop = comment->m_accountID == ModHelper::robTopAccountID && comment->m_userID == ModHelper::robTopUserID;

		// Create the new sprite according to the modBadge value we got
		auto modBadgeSpr = ModHelper::createModBadgeSprite(m_fields->m_modState);
		modBadgeSpr->setScale(modBadge->getScale());

		// Create the actual clickable button
		auto modBadgeBtn = CCMenuItemSpriteExtra::create(
			modBadgeSpr,
			this,
			menu_selector(MyCommentCell::onModBadgeBtn)
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