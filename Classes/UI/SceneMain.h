#ifndef _SCENE_MAIN_H
#define _SCENE_MAIN_H

#include "Renderer/Scene.h"

class SceneMain : public Scene
{
public:
	SceneMain();
	~SceneMain();

public : 

	CREATE_FUNC(SceneMain) ;

	bool init();


private:
	


};

#endif