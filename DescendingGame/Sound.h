#pragma once
#include <fmod.h>
#include <iostream>

class Sound_Set
{
private:
	FMOD_SYSTEM * g_System = nullptr;
	FMOD_SOUND *g_Sound[9];
	FMOD_CHANNEL *channel[9];
	FMOD_BOOL isPlaying[9];
	float volume;
public:
	Sound_Set();
	~Sound_Set();
	void On(int var);
	void Off(int var);
	void Update();
};