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
		auto *layer = this->m_mainLayer;
		auto *menu = static_cast<cocos2d::CCMenu *>(layer->getChildByIDRecursive("username-menu"));
		if (!menu) return;
		auto *modBadge = static_cast<cocos2d::CCSprite *>(menu->getChildByIDRecursive("mod-badge"));
		if (!modBadge) return;

		// If the badge's already there after a reload, delete it and continue
		if (auto *modBadgeBtnDupe = static_cast<CCMenuItemSpriteExtra *>(menu->getChildByIDRecursive("mod-badge-button"_spr))) {
			modBadgeBtnDupe->removeFromParentAndCleanup(true);
			menu->updateLayout();
		}

		// Change these fields accordingly
		m_fields->m_modState = comment->m_modBadge;
		m_fields->m_isRobTop = comment->m_accountID == ModHelper::robTopAccountID && comment->m_userID == ModHelper::robTopUserID;

		// Store the original mod badge position and remove it from the menu
        auto modBadgePosition = modBadge->getPosition();
        modBadge->removeFromParent();

		// Create the actual clickable button
		auto *modBadgeBtn = CCMenuItemSpriteExtra::create(
			modBadge,
			this,
			menu_selector(MyCommentCell::onModBadgeBtn)
		);
        modBadgeBtn->setID("mod-badge-button"_spr);
        modBadgeBtn->setPosition(modBadgePosition);
		
		menu->addChild(modBadgeBtn);
	};

	void onModBadgeBtn(CCObject *) {
		ModHelper::showModBadgeAlert(m_fields->m_modState, m_fields->m_isRobTop);
	};
};