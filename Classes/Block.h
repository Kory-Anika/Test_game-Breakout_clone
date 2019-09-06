#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MenuScene);

	void MenuManager();
	void goToMainScene(Ref *pSender);
	void Exit(Ref *pSender);
};

#endif // __MENUSCENE_H__
