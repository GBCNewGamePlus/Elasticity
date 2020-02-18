#ifndef __COMPONENT_AUDIO_COMPONENT_H__
#define __COMPONENT_AUDIO_COMPONENT_H__
#include <SFML/Audio.hpp>
#include "../../Base/ActorComponent.h" 


class AudioComponent : public ActorComponent{
protected:
	bool looping;
	std::string fileName;
	float pitch;
	float volume;
	sf::Music music;
public:
	AudioComponent(std::string fN = std::string(""), bool looping = false, float pitch = 1.0f, float volume = 1.0f);
	bool Play();
	bool Stop();
	bool Pause();
	sf::SoundSource::Status GetState();
	float GetPitch();
	void SetPitch(float f);
	float GetVolume();
	void SetVolume(float f);
	bool IsLooping();
	void SetLooping(bool b);
	bool SetFile(std::string s);
	std::string GetFile();
};


#endif