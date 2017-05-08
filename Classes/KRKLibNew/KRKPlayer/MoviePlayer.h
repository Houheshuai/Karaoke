#ifndef _MOVIEPLAYER_H
#define _MOVIEPLAYER_H

#include "vlc/vlc.h"

class Sprite;
class MoviePlayer
{
public:
	~MoviePlayer();

    static MoviePlayer * GetInstance(void);
	static void destroyInstance(void);

    void play(char *path);
    void stop(void);
    void pause(void);
    void draw(void);
	void setVolume(int vol);

protected:
    MoviePlayer();

private:
	bool init(void);

    libvlc_instance_t *vlc;
    libvlc_media_player_t *vlc_player;

    unsigned int width;
    unsigned int height;

	Sprite				*d_frameSprite;

    static MoviePlayer * _instance;
};


#endif