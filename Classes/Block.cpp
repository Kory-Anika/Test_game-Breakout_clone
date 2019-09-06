#include "Block.h"
#include "Definitions.h"

USING_NS_CC;
using namespace cocos2d;

Block::Block()
{
	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
}

void Block::Block_Spawn(Layer * layer)
{
	//block = Sprite::create(BLOCK);
	//enemy->setPosition(random_point);
	//enemy->setScale(0.4, 0.4);
	//enemy->setTag(random_tag);

	//auto enemy_body = PhysicsBody::createCircle(100);
	//enemy_body->setContactTestBitmask(0xFFFFFFFF);
	//enemy_body->setDynamic(true);
	//enemy->setPhysicsBody(enemy_body);

	//layer->addChild(enemy, 5);
	//enemies.pushBack(enemy);
}