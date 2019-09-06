#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class Block
{
public:
	Block();
	void Block_Spawn(Layer *layer);

private:
	Sprite *block;
	Vector<Sprite*> blocks;
};

#endif // __BLOCK_H__
