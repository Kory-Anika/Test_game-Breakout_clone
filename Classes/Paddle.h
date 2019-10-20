#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class Paddle : public Sprite
{
public:
	Paddle() {};
	virtual ~Paddle() {};

	static Paddle* create();
	void initOptions();
};

#endif // __PADDLE_H__