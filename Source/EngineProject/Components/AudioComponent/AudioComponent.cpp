#include <iostream>
#include "AudioComponent.h"

AudioComponent::AudioComponent(std::string fN, bool l, float p, float v)
{
		fileName = fN;
		looping = l;
		music.setLoop(looping);
		pitch = p;
		music.setPitch(pitch);
		volume = v;
		music.setVolume(volume);
		componentName = "audioComponent";
}

bool AudioComponent::Play()
{

	if (!music.openFromFile(fileName)) { //checking if the file is there
		cout << "File Not Found!";
		return false;
	}
	
	music.play();
	return true;
}

bool AudioComponent::Stop()
{
	music.stop();
	return true;
}

bool AudioComponent::Pause()
{
	music.pause();
	return true;
}

sf::SoundSource::Status AudioComponent::GetState()
{
	return music.getStatus();
}

float AudioComponent::GetPitch()
{
	return pitch;
}

void AudioComponent::SetPitch(float f)
{
	pitch = f;
	music.setPitch(pitch);
}

float AudioComponent::GetVolume()
{
	return volume;
}

void AudioComponent::SetVolume(float f)
{
	volume = f;
	music.setVolume(volume);
}

bool AudioComponent::IsLooping()
{
	return looping;
}

void AudioComponent::SetLooping(bool b)
{
	looping = b;
	music.setLoop(looping);
}

bool AudioComponent::SetFile(std::string s)
{
	music.stop(); //not sure how this will interact when playing, so i'm hard killing the song before swapping files
	fileName = s;
	if (!music.openFromFile(fileName)) {
		cout << "File Not Found!";
		return false;
	}
	return true;
}

std::string AudioComponent::GetFile()
{
	return fileName;
}
