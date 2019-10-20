#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "Definitions.h"

USING_NS_CC;

int h = 0;
Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

Scene* GameOver::createScene(int highscore)
{
	h = highscore;

	auto scene = Scene::create();
	auto layer = GameOver::create();

	scene->addChild(layer);

    return scene;
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);

	std::string str = StringUtils::format("SCORE: %d", h);

	auto highscore = cocos2d::Label::createWithSystemFont(str, "Arial", 32);
	highscore->setPosition(Point(visibleSize.width / 10 + 100, visibleSize.height / 2 + 600));
	highscore->setColor(Color3B::BLACK);
	this->addChild(highscore);

	MenuManager();

    return true;
}

void GameOver::MenuManager()
{
	auto *title = Label::createWithSystemFont("GAME OVER", "Arial", 48);
	title->setColor(Color3B::BLACK);
	auto menuTitle = MenuItemLabel::create(title);
	menuTitle->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 200));

	auto menuItem1 = MenuItemImage::create(REPLAY_BUTTON, REPLAY_BUTTON, CC_CALLBACK_1(GameOver::goToMainScene, this));
	menuItem1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 50));
	auto menuItem2 = MenuItemImage::create(EXIT_BUTTON, EXIT_BUTTON, CC_CALLBACK_1(GameOver::Exit, this));
	menuItem2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 150));

	auto menu = Menu::create(menuTitle, menuItem1, menuItem2, NULL);
	this->addChild(menu);
}

void GameOver::goToMainScene(Ref *pSender)
{
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0, scene));
	cleanup();
}

void GameOver::Exit(Ref *pSender)
{
	exit(0);
}