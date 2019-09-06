#ifndef __GAMEWIN_H__
#define __GAMEWIN_H__

#include "cocos2d.h"

class GameWin : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int highscore2);

    virtual bool init();
    
    CREATE_FUNC(GameWin);

	void MenuManager2();
	void goToMainScene(Ref *pSender);
	void Exit(Ref *pSender);
};

#endif // __GAMEWIN_H__
