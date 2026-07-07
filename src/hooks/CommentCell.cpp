#include <Geode/Geode.hpp>
#include "../ModHelper.hpp"

using namespace geode::prelude;

#include <Geode/modify/CommentCell.hpp>
class $modify(MyCommentCell, CommentCell) {
	struct Fields {
		int m_modState;
		bool m_isRobTop = false;
	};

	void loadFromComment(GJComment *comment) {
		CommentCell::loadFromComment(comment);

		if (ModHelper::isBadgifyLoaded())
			return;

		// Get the original mod badge
		auto *menu = static_cast<CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));
		if (!menu) return;
		auto *modBadge = static_cast<CCSprite *>(menu->getChildByIDRecursive("mod-badge"));
		if (!modBadge) return;

		// If the badge's already there after a reload, delete it and continue
		if (auto *modBadgeBtnDupe = static_cast<CCMenuItemSpriteExtra *>(menu->getChildByIDRecursive("mod-badge-button"_spr))) {
			modBadgeBtnDupe->removeFromParentAndCleanup(true);
			menu->updateLayout();
		}

		// Change these fields accordingly
		m_fields->m_modState = comment->m_modBadge;
		m_fields->m_isRobTop = (comment->m_accountID == ModHelper::robTopAccountID && comment->m_userID == ModHelper::robTopUserID);

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