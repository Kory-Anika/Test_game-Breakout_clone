#include "Paddle.h"
#include "Definitions.h"

USING_NS_CC;
using namespace cocos2d;

Paddle::Paddle()
{

}

Paddle::~Paddle()
{

}

Paddle * Paddle::create()
{
	Paddle* paddle = NULL;
	paddle = new Paddle();

	if (paddle && paddle->initWithFile(PADDLE))
	{
		paddle->initOptions();
	}
	else
	{
		delete paddle;
	}

	return paddle;
}

void Paddle::initOptions()
{
	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 4 + origin.y));
	this->setScaleX(8);
	this->setColor(Color3B::BLACK);
	this->setTag(2);

	auto paddle_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	paddle_body->setDynamic(false);
	paddle_body->setContactTestBitmask(true);
	
	this->setPhysicsBody(paddle_body);
}