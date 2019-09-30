#include "Block.h"
#include "Definitions.h"

USING_NS_CC;
using namespace cocos2d;

Block::Block()
{

}

void Block::Block_Spawn(Layer * layer, int f, int i, Color3B color)
{
	visible_size = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	block = Sprite::create(BLOCK);
	block->setPosition(Vec2(visible_size.width / 28 + i * 32, visible_size.height / 1.2 + f));
	block->setScale(0.87f);
	block->setColor(color);

	auto block_body = PhysicsBody::createBox(block->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	block_body->setContactTestBitmask(true);
	block_body->setDynamic(false);
	block_body->setCollisionBitmask(i + 3);
	block_body->setContactTestBitmask(true);
	block->setPhysicsBody(block_body);

	layer->addChild(block, i);
	blocks.pushBack(block);
}