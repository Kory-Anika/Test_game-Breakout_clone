#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "Definitions.h"
#include "GameOver.h"
#include "GameWin.h"

USING_NS_CC;

using namespace cocos2d;

int x_movement = 0;
int speed = 400;

Color3B red = Color3B(255, 0, 0);
Color3B green = Color3B(0, 255, 0);
Color3B blue = Color3B(0, 0, 255);

Color3B MyColor;
Color3B MyColors[] = {
	{red},
	{green},
	{blue}
};

Scene* MainScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = MainScene::create();
	layer->SetWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	game_layer = Layer::create();

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);

	//edge_node
	{
		auto edgenode = Node::create();
		edgenode->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
		edgenode->setTag(0);

		auto edge_body = PhysicsBody::createEdgeBox(visible_size, PhysicsMaterial(1.0f, 0.5f, 0.5f), 3);
		edge_body->setDynamic(false);
		edgenode->setPhysicsBody(edge_body);
		
		this->addChild(edgenode); 
	}

	ball = Ball::create();
	game_layer->addChild(ball);

	paddle = Paddle::create();
	game_layer->addChild(paddle);

	// rect0 sprite
	{
		auto rect0 = Sprite::create(RECT0);
		rect0->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y - 330));
		rect0->setScaleX(15);
		rect0->setTag(3);

		auto rect0_body = PhysicsBody::createBox(rect0->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		rect0_body->setDynamic(false);
		rect0_body->setCollisionBitmask(0);
		rect0_body->setContactTestBitmask(true);
		rect0->setPhysicsBody(rect0_body);

		this->addChild(rect0);
	}

	// blocks
	{
		Blocks(-60);
		Blocks(-30);
		Blocks(0);
		Blocks(30);
		Blocks(60);
	}

	// keyboard listener 
	{
		auto keyBoardListener = EventListenerKeyboard::create();
		keyBoardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				x_movement--;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				x_movement++;
				break;
			}
		};
		keyBoardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				x_movement++;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				x_movement--;
				break;
			}
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	}

	// contact listener
	{
		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	}

	this->addChild(game_layer);

	UserDefault *def = UserDefault::getInstance();

	this->scheduleUpdate();
	this->schedule(schedule_selector(MainScene::update_speed), 0.009 * visible_size.width);

	//score label
	{
		score = 0;
		__String *temp_score = __String::createWithFormat("%i", score);

		score_label = Label::createWithSystemFont(temp_score->getCString(), "Arial", 30);
		score_label->setColor(Color3B::BLACK);
		score_label->setPosition(Point(visible_size.width / 10 + origin.x, visible_size.height / 2 + 305));
		this->addChild(score_label, 10);
	}

    return true;
}

bool MainScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 1 && nodeB->getTag() != 0 && nodeB->getTag() != 2 && nodeB->getTag() != 3)
		{
			
			if (nodeB->getColor() == blue)
			{
				nodeB->setColor(red);
			}
			
			else if (nodeB->getColor() == red)
			{
				nodeB->setColor(green);
			}

			else if (nodeB->getColor() == green)
			{
				nodeB->removeFromParentAndCleanup(true);

				score += 10;
				__String *tempscore = __String::createWithFormat("%i", score);
				score_label->setString(tempscore->getCString());
			}
		}
		else if (nodeB->getTag() == 1 && nodeA->getTag() != 0 && nodeA->getTag() != 2 && nodeA->getTag() != 3)
		{
			if (nodeA->getColor() == blue)
			{
				nodeA->setColor(red);
			}

			else if (nodeA->getColor() == red)
			{
				nodeA->setColor(green);
			}

			else if (nodeA->getColor() == green)
			{
				nodeA->removeFromParentAndCleanup(true);

				score += 10;
				__String *tempscore = __String::createWithFormat("%i", score);
				score_label->setString(tempscore->getCString());
			}
		}
	}

	auto nodeC = contact.getShapeA()->getBody()->getNode();
	auto nodeD = contact.getShapeB()->getBody()->getNode();

	if (nodeC && nodeD)
	{
		if ((nodeC->getTag() == 1 && nodeD->getTag() == 3 && nodeD->getTag() != 0 && nodeD->getTag() != 2)
			|| (nodeD->getTag() == 1 && nodeC->getTag() == 3 && nodeC->getTag() != 0 && nodeD->getTag() != 2))
		{
			auto scene = GameOver::createScene(score);
			Director::getInstance()->replaceScene(scene);
			cleanup();
		}
	}

	if (score == 750)
	{
		auto scene2 = GameWin::createScene(score);
		Director::getInstance()->replaceScene(scene2);
		cleanup();
	}

	return true;
}

void MainScene::Blocks(int f)
{
	for (int i = 0; i < 15; i++)
	{
		Color3B MyColor = MyColors[cocos2d::random(0, 2)];

		block.Block_Spawn(this, f, i, MyColor);
	}
}

void MainScene::update(float dt)
{
	float new_pos_x = paddle->getPositionX() + (x_movement * MOVEMENT_SPEED);
	paddle->setPositionX(new_pos_x);

	auto body = ball->getPhysicsBody();
	body->setVelocity(body->getVelocity().getNormalized() * speed);
}

void MainScene::update_speed(float dt)
{
	speed += 5;
	CCLOG("speed: %i", speed);
}