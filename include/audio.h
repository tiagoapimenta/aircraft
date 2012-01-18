#ifndef AUDIO_H
#define AUDIO_H

#include "core.h"

class Audio
{
public:
	Audio();
	~Audio();

	void playMusic (std::string filename);
	bool isMusicPaused();
	bool isMusicPlaying();
	void playMusic();
	void pauseMusic();
	void stopMusic();
	void playSound (std::string filename);

protected:
private:
	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;
	Mix_Music *music;
};

#endif // AUDIO_H
