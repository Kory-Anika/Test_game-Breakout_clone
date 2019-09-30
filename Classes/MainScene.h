#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

using namespace cocos2d;

class MainScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

private:
	PhysicsWorld *SceneWorld;
	void SetWorld(PhysicsWorld *MyWorld) { SceneWorld = MyWorld; };

	Layer *game_layer;
	Ball *ball;
	Paddle *paddle;
	Block block;

	std::vector<Sprite*> cubes;

	unsigned int score;
	Label *score_label;

	bool onContactBegin(PhysicsContact &contact);
	void Blocks(int f);
	void update(float dt);
	void update_speed(float dt);
};

#endif // __MAINSCENE_H__