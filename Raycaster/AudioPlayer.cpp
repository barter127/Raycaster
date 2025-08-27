#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	// If no loop or an inappropriate amount is requested loop forever.
	if (m_numberOfLoops <= 0)
	{
		// PlayChannel will loop infinitely if number of loops is -1.
		m_numberOfLoops = -1;
	}

	// Notify of possible misuse of system.
	if (m_numberOfLoops < -1)
	{
		std::cerr << "[?] Unintended. Attempted to loop song negative amount of times." << std::endl;
	}
}

AudioPlayer::AudioPlayer(std::string path)
{
	if (!LoadFromFile(path))
	{
		std::cerr << "[!] Error. Audio couldn't be loaded from path. " << path << std::endl;
	}
}

AudioPlayer::~AudioPlayer()
{
	Mix_FreeChunk(m_audio);
	//
	// delete m_audio;
	m_audio = nullptr;
}

bool AudioPlayer::LoadFromFile(std::string path)
{
	// Set audio using path parameter.
	m_audio = Mix_LoadWAV(path.c_str());

	// Return true if loading was succesful.
	if (m_audio != nullptr)
	{
		return true; // Success!!!
	}
	return false; // Failed.
}

void AudioPlayer::Play()
{
	// Doofus proofing.
	if (m_audio != nullptr)
	{
		m_channel = Mix_PlayChannel(m_channel, m_audio, m_numberOfLoops);
	}
	else
	{
		std::cerr << "[!] Error. Attempted to start audio player with no valid track." << std::endl;
	}
}

void AudioPlayer::PlayOneShot(AudioClip* audio, float volume)
{
	// Set volume based off param.
	SetVolume(volume);

	// Play audio from audio clip. As it's one shot assume no loops.
	m_channel = Mix_PlayChannel(m_channel, audio->GetAudio(), 0);
}

void AudioPlayer::Pause()
{
	Mix_Pause(m_channel);
}

void AudioPlayer::SetVolume(float volume)
{
	Mix_Volume(m_channel, volume);
}

void AudioPlayer::SetLoopAmount(int numberOfLoops)
{
	// Block incorrect use of function.
	if (numberOfLoops < -1)
	{
		std::cerr << "[?] Unintended. Attenpted to set number of loops to a value < -1." << std::endl;
	}
	else // Function used correctly :D
	{
		m_numberOfLoops = numberOfLoops;
	}
}

void AudioPlayer::FadeOut(int ms)
{
	if (Mix_FadeOutChannel(m_channel, ms) <= 0)
	{
		std::cerr << "[?] Unintended. Attempted to FadeOut audio when no audio was playing" << std::endl;
	}
}