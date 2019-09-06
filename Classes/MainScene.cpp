#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "Definitions.h"
#include "GameOver.h"
#include "GameWin.h"

USING_NS_CC;

using namespace cocos2d;

int s = 200;
int count = 0;
int x_movement = 0;

ccColor3B red = ccColor3B(255, 0, 0);
ccColor3B green = ccColor3B(0, 255, 0);
ccColor3B blue = ccColor3B(0, 0, 255);

ccColor3B MyColor;

ccColor3B MyColors[] = {
	{ red },
	{ green },
	{ blue }
};

Scene* MainScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
		auto edgebody = PhysicsBody::createEdgeBox(visible_size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		auto edgenode = Node::create();
		edgenode->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
		edgenode->setPhysicsBody(edgebody);
		this->addChild(edgenode); 
	}

	// ball sprite
	ball = Ball::create();
	game_layer->addChild(ball);

	paddle = Paddle::create();
	game_layer->addChild(paddle);

	// rect0 sprite
	{
		auto rect0 = Sprite::create(RECT0);
		rect0->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y - 330));
		rect0->setScaleX(15);
		rect0->setTag(0);

		auto rect0body = PhysicsBody::createBox(rect0->getContentSize(), PhysicsMaterial(0, 1, 0));

		rect0body->setCollisionBitmask(0);
		rect0body->setContactTestBitmask(true);
		rect0body->setDynamic(false);

		rect0->setPhysicsBody(rect0body);
		this->addChild(rect0);
	}

	// cube array
	{
		Cubes(-60, 0);
		Cubes(-30, 14);
		Cubes(0, 29);
		Cubes(30, 44);
		Cubes(60, 59);
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
		if (nodeA->getTag() == 1 && nodeB->getTag() != 2 && nodeB->getTag() != 0)
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

				score = score + 10;
				__String *tempscore = __String::createWithFormat("%i", score);
				score_label->setString(tempscore->getCString());
			}

			count = count + 1;
			if (count % 5 == 0)
			{
				s = s + s * 0.1;
			}
		}
		else if (nodeB->getTag() == 1 && nodeA->getTag() != 2 && nodeA->getTag() != 0)
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

				score = score + 10;
				__String *tempscore = __String::createWithFormat("%i", score);
				score_label->setString(tempscore->getCString());
			}

			count = count + 1;
			if (count % 5 == 0)
			{
				s = s + s * 0.1;
			}
		}
	}

	PhysicsBody *c = contact.getShapeA()->getBody();
	PhysicsBody *d = contact.getShapeB()->getBody();

	if ((1 == c->getCollisionBitmask() && 0 == d->getCollisionBitmask()) || (0 == c->getCollisionBitmask() && 1 == d->getCollisionBitmask()))
	{
		auto scene = GameOver::createScene(score);
		Director::getInstance()->replaceScene(scene);
		cleanup();
	}

	if (score == 750)
	{
		auto scene2 = GameWin::createScene(score);
		Director::getInstance()->replaceScene(scene2);
		cleanup();
	}

	return true;
}

void MainScene::Cubes(int f, int t) 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 15; i++)
	{
		ccColor3B MyColor = MyColors[cocos2d::random(0, 2)];

		auto cube = Sprite::create("CloseNormal.png");
		cube->setPosition(Vec2(visibleSize.width / 28 + i * 32, visibleSize.height / 1.2 + f));
		cube->setScale(0.87);
		cube->setColor(MyColor);
		cube->setTag(t + 3);

		auto cubebody = PhysicsBody::createBox(cube->getContentSize(), PhysicsMaterial(0, 1, 0));

		cubebody->setCollisionBitmask(t + 3);
		cubebody->setContactTestBitmask(true);
		cubebody->setDynamic(false);

		cube->setPhysicsBody(cubebody);

		this->addChild(cube, i);
		cubes.push_back(cube);
	}
}

void MainScene::update(float dt)
{
	//for (int i = 0; i < cubes.size(); i++)
	//{
	//	auto cube = cubes.at(i);

	//	cube->setPositionX(cube->getPositionX() - dt * 10);
	//}

	float new_pos_x = paddle->getPositionX() + (x_movement * MOVEMENT_SPEED);
	paddle->setPositionX(new_pos_x);
}