#include "GameWin.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "Definitions.h"

USING_NS_CC;

int h2 = 0;
Size visibleSize2 = Director::getInstance()->getVisibleSize();
Vec2 origin2 = Director::getInstance()->getVisibleOrigin();

Scene* GameWin::createScene(int highscore)
{
	h2 = highscore;

	auto scene = Scene::create();
	auto layer = GameWin::create();

	scene->addChild(layer);

    return scene;
}

bool GameWin::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);

	std::string str = StringUtils::format("SCORE: %d", h2);

	auto highscore2 = cocos2d::Label::createWithSystemFont(str, "Arial", 32);
	highscore2->setPosition(Point(visibleSize2.width / 10 + 100, visibleSize2.height / 2 + 600));
	highscore2->setColor(Color3B::BLACK);
	this->addChild(highscore2);

	MenuManager2();

    return true;
}

void GameWin::MenuManager2()
{
	auto *title = Label::createWithSystemFont("YOU WON!", "Arial", 48);
	title->setColor(Color3B::BLACK);
	auto menuTitle = MenuItemLabel::create(title);
	menuTitle->setPosition(Point(visibleSize2.width / 2 + origin2.x, visibleSize2.height / 2 + 200));

	auto menuItem1 = MenuItemImage::create(REPLAY_BUTTON, REPLAY_BUTTON, CC_CALLBACK_1(GameWin::goToMainScene, this));
	menuItem1->setPosition(Point(visibleSize2.width / 2 + origin2.x, visibleSize2.height / 2 + 50));
	auto menuItem2 = MenuItemImage::create(EXIT_BUTTON, EXIT_BUTTON, CC_CALLBACK_1(GameWin::Exit, this));
	menuItem2->setPosition(Point(visibleSize2.width / 2 + origin2.x, visibleSize2.height / 2 - 150));

	auto menu = Menu::create(menuTitle, menuItem1, menuItem2, NULL);
	this->addChild(menu);
}

void GameWin::goToMainScene(Ref *pSender)
{
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0, scene));
}

void GameWin::Exit(Ref *pSender)
{
	exit(0);
}