#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

class $modify(EditedMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		CCNode* moreGamesMenu = this->getChildByID("more-games-menu");
		moreGamesMenu->removeAllChildren();
		moreGamesMenu->updateLayout();

		return true;
	}
};
class $modify(EditedLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if(!LevelEditorLayer::init(p0, p1)) {
			return false;
		}
		CCNode* editorButtons = this->getChildByID("EditorUI")->getChildByID("editor-buttons-menu");

		editorButtons->removeChildByID("copy-button");
		editorButtons->removeChildByID("paste-button");
		editorButtons->removeChildByID("go-to-layer-button");
		return true;
	}
};
class $modify(EditedCreatorLayer, CreatorLayer) {
	bool init() {
		if(!CreatorLayer::init()) {
			return false;
		}

		CCNode* creatorButtons = this->getChildByID("creator-buttons-menu");
		
		// sorry no funny dialogue
		creatorButtons->removeChildByID("versus-button");
		creatorButtons->removeChildByID("map-button");
		creatorButtons->removeChildByID("map-packs-button");
		CCMenuItemSpriteExtra* mapPacksButtonOhDearOhGodNo = static_cast<CCMenuItemSpriteExtra*>(creatorButtons->getChildByID("map-packs-button"));
		CCMenuItemSpriteExtra* disguisedMapPack;
		if(Mod::get()->getSavedValue<byte>("map-pack-check", 0) == (byte)0) {
			disguisedMapPack = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_mapPacksBtn_001.png"),
				this,
				menu_selector(EditedCreatorLayer::runAway)
			);
			disguisedMapPack->setUserObject(creatorButtons);
			disguisedMapPack->setPosition(314.6, 65.4);
			disguisedMapPack->setID("this-isnt-what-it-seems-i-promise"_spr);

			disguisedMapPack->getChildByTag(1)->setScale(0.8);
			creatorButtons->addChild(disguisedMapPack);
		}
		
		return true;
	}
	void runAway(CCObject* sender) {
		FLAlertLayer::create("Oh Dear!", "Thought I could get away with this...", "OK")->show();
		CCNode* ctrButtons = static_cast<CCNode*>(static_cast<CCNode*>(sender)->getUserObject());
		ctrButtons->removeChildByID("this-isnt-what-it-seems-i-promise"_spr);
		Mod::get()->setSavedValue<byte>("map-pack-check", 1);
	}
};
class $modify(EditedLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* lvl, bool chllng) {
		if(!LevelInfoLayer::init(lvl, chllng)) {
			return false;
		}
		CCNode* rightSide = this->getChildByID("right-side-menu");

		rightSide->removeChildByID("refresh-button");
		rightSide->removeChildByID("rate-button");
		rightSide->updateLayout();
		return true;
	}
};