#include "Ball.h"
#include "Definitions.h"

USING_NS_CC;
using namespace cocos2d;

Ball::Ball()
{

}

Ball::~Ball()
{

}

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

	this->setPosition(Point(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
	this->setTag(0);

	auto ball_body = PhysicsBody::createBox(this->getContentSize());
	ball_body->setDynamic(true);
	this->setPhysicsBody(ball_body);
}