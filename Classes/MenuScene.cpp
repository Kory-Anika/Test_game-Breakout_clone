#include "MenuScene.h"
#include "MainScene.h"
#include "Definitions.h"

USING_NS_CC;

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
using namespace ui;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();

	scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);

	MenuManager();

    return true;
}

void MenuScene::MenuManager() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto *title = Label::createWithSystemFont("MAIN MENU", "Arial", 48);
	title->setColor(Color3B::BLACK);
	auto menuTitle = MenuItemLabel::create(title);

	auto menuItem1 = MenuItemImage::create(PLAY_BUTTON, PLAY_BUTTON, CC_CALLBACK_1(MenuScene::goToMainScene, this));
	auto menuItem2 = MenuItemImage::create(EXIT_BUTTON, EXIT_BUTTON, CC_CALLBACK_1(MenuScene::Exit, this));

	auto menu = Menu::create(menuTitle, menuItem1, menuItem2, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 9);
	this->addChild(menu);
}

void MenuScene::goToMainScene(Ref *pSender)
{
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0, scene));
	cleanup();
}

void MenuScene::Exit(Ref *pSender)
{
	exit(0);
}