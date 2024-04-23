#include <iostream>
#include <vector>
#include <random>
#include "SFML/Audio.hpp"
#include "particle/particle_sounds.h"

std::vector<sf::SoundBuffer> SoundEngine::waterSounds;
std::vector<sf::Sound> SoundEngine::sounds;
std::random_device SoundEngine::rd;
std::mt19937 SoundEngine::gen(SoundEngine::rd());

void SoundEngine::init()
{
	sf::SoundBuffer waterSound;
	if (!waterSound.loadFromFile("data\\sounds\\water.ogg"))
	{
		// error
	}
	waterSounds.push_back(waterSound);
}
void SoundEngine::playSound(SoundType soundType)
{
	switch (soundType)
	{
	case SoundType::WaterDrip:
		if (!waterSounds.empty())
		{
			std::uniform_int_distribution<int> dist(0, waterSounds.size() - 1);
			sf::Sound sound;
			sound.setBuffer(waterSounds[dist(gen)]);
			sounds.push_back(sound);
			sounds.back().play();
		}
		break;
	}
}

void SoundEngine::purgeSounds()
{
	// remove sounds that have finished playing
	sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
		[](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
		sounds.end());
}