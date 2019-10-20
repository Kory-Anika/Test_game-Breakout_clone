#include "Ball.h"
#include "Definitions.h"

USING_NS_CC;
using namespace cocos2d;

Ball * Ball::create()
{
	Ball* ball = NULL;
	ball = new Ball();

	if (ball && ball->initWithFile(BALL))
	{
		ball->initOptions();
	}
	else
	{
		delete ball;
	}

	return ball;
}

void Ball::initOptions()
{
	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 4 + origin.y));
	this->setScale(0.2f);
	this->setTag(1);

	auto ball_body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(1.0f, 1.0f, 0.0f));
	ball_body->setDynamic(true);
	ball_body->setCollisionBitmask(1);
	ball_body->setContactTestBitmask(true);

	ball_body->setVelocity(Vec2(300, 300));
	ball_body->applyImpulse(Vec2(600, 600));

	this->setPhysicsBody(ball_body);
}