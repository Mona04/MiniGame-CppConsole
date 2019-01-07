#include "stdafx.h"
#include "Sound.h"

Sound_Set::Sound_Set()
{
	volume = 0.5f;
	isPlaying = 0;

	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, "..\\sound\\Colorful_Night.mp3",
		FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateSound(g_System, "..\\sound\\jump.mp3",
		FMOD_DEFAULT, 0, &g_Sound[1]);
	FMOD_System_CreateSound(g_System, "..\\sound\\dash.mp3",
		FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "..\\sound\\skill.mp3",
		FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "..\\sound\\point.mp3",
		FMOD_DEFAULT, 0, &g_Sound[4]);
	FMOD_System_CreateSound(g_System, "..\\sound\\thorn.mp3",
		FMOD_DEFAULT, 0, &g_Sound[5]);
	FMOD_System_CreateSound(g_System, "..\\sound\\falling_map.mp3",
		FMOD_DEFAULT, 0, &g_Sound[6]);
	FMOD_System_CreateSound(g_System, "..\\sound\\fail.mp3",
		FMOD_DEFAULT, 0, &g_Sound[7]);
	FMOD_System_CreateSound(g_System, "..\\sound\\clear.mp3",
		FMOD_DEFAULT, 0, &g_Sound[8]);
}

Sound_Set::~Sound_Set()
{
	for(int i = 0 ; i < 8 ; i++)	
		FMOD_Sound_Release(g_Sound[i]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void Sound_Set::On(int var)
{
	FMOD_Channel_IsPlaying(channel[var], &isPlaying);
	if(!isPlaying)
		FMOD_System_PlaySound(g_System, g_Sound[var], NULL, 0, &channel[var]);
}

void Sound_Set::Off(int var)
{
	FMOD_Channel_Stop(channel[var]);
}

void Sound_Set::Update()
{
	if(!g_System)
		FMOD_System_Update(g_System);
}