#pragma once

#include <SDL_mixer.h>
#include<string>
#include<iostream>

#ifndef _AUDIO_PLAYER_H
#define _AUDIO_PLAYER_H
class AudioPlayer
{
private:
	Mix_Chunk* m_audio = nullptr;
	int m_channel = -1;
	
	int m_numberOfLoops = -1; // Assumes infinite if not specified.

public:
	AudioPlayer();
	AudioPlayer(std::string path); // Construct with specified audio track.
	~AudioPlayer();

	// ONLY WORKS FOR WAV!
	// Loads and Binds WAV file to m_audio using the path parameter.
	// If successful returns true. If fails returns false.
	bool LoadFromFile(std::string path);

	// Starts playing currently bound audio track 
	// Looping the amount of times specified by SetLoopAmount() or infinitely if unspecified.
	// Returns error and plays nothing if no audio is bound to the class.
	void Play();

	// Stops any audio currently playing.
	void Pause();

	// Set audio players volume based on parameter.
	void SetVolume(float volume);

	// Set number of times the audio should loop before stopping.
	void SetLoopAmount(int numberOfLoops);

	// Fades audio volume to nothing over specified amount of time.
	void FadeOut(int ms);
};
#endif // _AUDIOPLAYER_H

