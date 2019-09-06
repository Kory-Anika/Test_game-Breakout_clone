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

	this->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
	this->setScale(0.2f);
	this->setTag(1);

	auto paddle_body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 1.0f));
	paddle_body->setDynamic(true);
	
	Vec2 force = Vec2(100, 100);
	paddle_body->applyImpulse(force, paddle_body->getPositionOffset());
	
	this->setPhysicsBody(paddle_body);
}