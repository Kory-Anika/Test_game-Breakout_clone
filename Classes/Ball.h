#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class Ball : public Sprite
{
public:
	Ball();
	virtual ~Ball();

	static Ball* create();
	void initOptions();

private:
};

#endif // __BALL_H__