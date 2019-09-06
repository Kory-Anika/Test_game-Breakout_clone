#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

	unsigned int score;
	cocos2d::Label *scoreLabel;

private:
	cocos2d::PhysicsWorld *SceneWorld;
	void SetWorld(cocos2d::PhysicsWorld *MyWorld) { SceneWorld = MyWorld; }
	bool onContact(cocos2d::PhysicsContact &contact);

	std::vector<Sprite*> cubes;
	void Cubes(int f, int t);

	void Update(float dt);
};

#endif // __MAINSCENE_H__
