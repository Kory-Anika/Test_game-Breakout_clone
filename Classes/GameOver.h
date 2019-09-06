#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int highscore);

    virtual bool init();
    
    CREATE_FUNC(GameOver);

	void MenuManager();
	void goToMainScene(Ref *pSender);
	void Exit(Ref *pSender);
};

#endif // __GAMEOVER_H__
