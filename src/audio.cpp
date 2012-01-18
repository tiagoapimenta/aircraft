#include "audio.h"

Audio::Audio()
{
	if (SDL_Init (SDL_INIT_AUDIO) == -1) throw "Couldn't init audio.";

	if (Mix_OpenAudio (22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) throw "Couldn't open mixer.";

	music = NULL;
}

Audio::~Audio()
{
	stopMusic();

	for (std::map<std::string, Mix_Music*>::iterator it = musics.begin(); it != musics.end(); it++)
	{
		Mix_FreeMusic (it->second);
	}

	for (std::map<std::string, Mix_Chunk*>::iterator it = sounds.begin(); it != sounds.end(); it++)
	{
		Mix_FreeChunk (it->second);
	}

	Mix_CloseAudio();
}

void Audio::playMusic (std::string filename)
{
	stopMusic();

	if (musics.count (filename) > 0)
	{
		music = musics.find (filename)->second;
	}
	else
	{
		music = Mix_LoadMUS (filename.c_str());

		if (music == NULL) throw "Cound't open music.";

		musics.insert (make_pair (filename, music));
	}

	playMusic();
}

bool Audio::isMusicPaused()
{
	return Mix_PausedMusic() == 1;
}

bool Audio::isMusicPlaying()
{
	return Mix_PlayingMusic() != 0;
}

void Audio::playMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic (music, -1) == -1) throw "Couldn't play music.";
	}
	else if (isMusicPaused())
	{
		Mix_ResumeMusic();
	}
}

void Audio::pauseMusic()
{
	Mix_PauseMusic();
}

void Audio::stopMusic()
{
	Mix_HaltMusic();
}

void Audio::playSound (std::string filename)
{
	Mix_Chunk *sound = NULL;

	if (sounds.count (filename) > 0)
	{
		sound = sounds.find (filename)->second;
	}
	else
	{
		sound = Mix_LoadWAV (filename.c_str());

		if (sound == NULL) throw "Cound't open sound.";

		sounds.insert (make_pair (filename, sound));
	}

	Mix_PlayChannel (-1, sound, 0); // TODO: fix it on play explosion several times: if (Mix_PlayChannel (-1, sound, 0) == -1) throw "Couldn't play sound.";
}
