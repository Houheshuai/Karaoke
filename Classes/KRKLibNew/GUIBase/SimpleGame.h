#ifndef _SIMPLE_GAME_H
#define _SIMPLE_GAME_H
#include <string>

class SimpleGame
{
public:
	SimpleGame();
	virtual ~SimpleGame(){};

	virtual void start(std::string _resFolderPath);
	virtual void restart();
	virtual void stop();

	virtual bool isStopped();
	
	virtual void onKeyDown(int codepoint);
	virtual void onKeyUp(int codepoint);
	virtual void onCharacter(int codepoint);
	virtual void update(float dt);

};



#endif