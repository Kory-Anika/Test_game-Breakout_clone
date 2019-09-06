#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "Definitions.h"
#include "GameOver.h"
#include "GameWin.h"

USING_NS_CC;

int s = 200;
int count = 0;

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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = MainScene::create();
	layer->SetWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);

	auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgenode = Node::create();
	edgenode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgenode->setPhysicsBody(edgebody);
	this->addChild(edgenode);

	// ball sprite
	{
		auto ball = Sprite::create(BALL);
		ball->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
		ball->setScale(0.2);
		ball->setTag(1);

		auto ballbody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1.03, 0));
		
		ballbody->addMoment(20);
		ballbody->setCollisionBitmask(1);
		ballbody->setContactTestBitmask(true);
		//ballbody->setVelocity(Vect(s, s));
		ballbody->applyForce(Vect(400, 400));
		ballbody->applyImpulse(Vect(600, 600));

		ball->setPhysicsBody(ballbody);
		this->addChild(ball);

		auto action = MoveBy::create(500, Vec2(s, s));
		ball->runAction(action);
	}

	// rect sprite
	{
		auto rect = Sprite::create("CloseNormal.png");
		rect->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 270));
		rect->setScaleX(8);
		rect->setColor(Color3B::BLACK);
		rect->setTag(2);

		auto rectbody = PhysicsBody::createBox(rect->getContentSize(), PhysicsMaterial(0, 1, 0));
		
		rectbody->setCollisionBitmask(2);
		rectbody->setContactTestBitmask(true);
		rectbody->setDynamic(false);
		rectbody->addMoment(10);
		rectbody->applyImpulse(Vect(200, 200));
		
		rect->setPhysicsBody(rectbody);
		this->addChild(rect);

		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

			Vec2 loc = event->getCurrentTarget()->getPosition();
			switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				event->getCurrentTarget()->setPosition(--loc.x - 50, loc.y);
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				event->getCurrentTarget()->setPosition(++loc.x + 50, loc.y);
				break;
			}
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, rect);
	}

	// rect0 sprite
	{
		auto rect0 = Sprite::create(RECT0);
		rect0->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 330));
		rect0->setScaleX(15);
		rect0->setTag(0);

		auto rect0body = PhysicsBody::createBox(rect0->getContentSize(), PhysicsMaterial(0, 1, 0));

		rect0body->setCollisionBitmask(0);
		rect0body->setContactTestBitmask(true);
		rect0body->setDynamic(false);

		rect0->setPhysicsBody(rect0body);
		this->addChild(rect0);
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContact, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// cube array
	{
		Cubes(-60, 0);
		Cubes(-30, 14);
		Cubes(0, 29);
		Cubes(30, 44);
		Cubes(60, 59); 
	}

	UserDefault *def = UserDefault::getInstance();

	//score
	{
		score = 0;
		__String *tempscore = __String::createWithFormat("%i", score);

		scoreLabel = Label::createWithSystemFont(tempscore->getCString(), "Arial", 30);
		scoreLabel->setColor(Color3B::BLACK);
		scoreLabel->setPosition(Point(visibleSize.width / 10 + origin.x, visibleSize.height / 2 + 305));
		this->addChild(scoreLabel, 1000);
	}

    return true;
}

bool MainScene::onContact(cocos2d::PhysicsContact &contact)
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
				scoreLabel->setString(tempscore->getCString());
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
				scoreLabel->setString(tempscore->getCString());
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

void MainScene::Update(float dt)
{
	for (int i = 0; i < cubes.size(); i++)
	{
		auto cube = cubes.at(i);

		cube->setPositionX(cube->getPositionX() - dt * 10);
	}
}