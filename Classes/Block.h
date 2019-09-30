#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class Block
{
public:
	Block();
	void Block_Spawn(Layer *layer, int f, int i, Color3B color);

private:
	Sprite *block;
	Vector<Sprite*> blocks;

	Size visible_size;
	Vec2 origin;
};

#endif // __BLOCK_H__
