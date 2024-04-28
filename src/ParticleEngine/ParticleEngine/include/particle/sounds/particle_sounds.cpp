#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

#include "SFML/Audio.hpp"

#include "particle/particle_sounds.h"

std::vector<sf::SoundBuffer> SoundEngine::liquidDripSounds;
std::vector<sf::SoundBuffer> SoundEngine::bubbleSounds;
std::vector<sf::SoundBuffer> SoundEngine::sizzleSounds;
std::vector<sf::SoundBuffer> SoundEngine::fireSounds;
std::vector<sf::SoundBuffer> SoundEngine::menuImpactSounds;
std::vector<sf::SoundBuffer> SoundEngine::dynamiteSounds;

std::vector<sf::Sound> SoundEngine::globalSounds;

std::random_device SoundEngine::rd;
std::mt19937 SoundEngine::gen(SoundEngine::rd());

std::unordered_map<SoundEngine::SoundType, std::chrono::steady_clock::time_point> SoundEngine::lastPlayedTime;
std::chrono::milliseconds SoundEngine::minInterval(50);

void SoundEngine::init()
{
	sf::SoundBuffer temp;

	const std::string liquidDripSoundPaths[] = {
		"data\\sounds\\water\\water1.ogg",
		"data\\sounds\\water\\water2.ogg",
		"data\\sounds\\water\\water3.ogg",
		"data\\sounds\\water\\water4.ogg",
		"data\\sounds\\water\\water5.ogg"
	};
	for (int i = 0; i < 5; i++)
	{
		if (!temp.loadFromFile(liquidDripSoundPaths[i]))
		{
			// error
		}
		liquidDripSounds.push_back(temp);
	}

	const std::string bubbleSoundPaths[] = {
	"data\\sounds\\bubble\\bubble1.ogg",
	"data\\sounds\\bubble\\bubble2.ogg",
	"data\\sounds\\bubble\\bubble3.ogg",
	"data\\sounds\\bubble\\bubble4.ogg",
	"data\\sounds\\bubble\\bubble5.ogg"
	};
	for (int i = 0; i < 5; i++)
	{
		if (!temp.loadFromFile(bubbleSoundPaths[i]))
		{
			// error
		}
		bubbleSounds.push_back(temp);
	}

	const std::string sizzleSoundPaths[] = {
		"data\\sounds\\sizzle\\sizzle1.ogg",
		"data\\sounds\\sizzle\\sizzle2.ogg",
		"data\\sounds\\sizzle\\sizzle3.ogg",
		"data\\sounds\\sizzle\\sizzle4.ogg"
	};
	for (int i = 0; i < 4; i++)
	{
		if (!temp.loadFromFile(sizzleSoundPaths[i]))
		{
			// error
		}
		sizzleSounds.push_back(temp);
	}

	const std::string fireSoundPaths[] = {
		"data\\sounds\\fire\\fire1.ogg",
		"data\\sounds\\fire\\fire2.ogg",
		"data\\sounds\\fire\\fire3.ogg",
		"data\\sounds\\fire\\fire4.ogg"
	};
	for (int i = 0; i < 4; i++)
	{
		if (!temp.loadFromFile(fireSoundPaths[i]))
		{
			// error
		}
		fireSounds.push_back(temp);
	}

	const std::string menuImpactSoundPaths[] = {
		"data\\sounds\\menu_impact\\menu_impact1.ogg",
		"data\\sounds\\menu_impact\\menu_impact2.ogg",
		"data\\sounds\\menu_impact\\menu_impact3.ogg",
		"data\\sounds\\menu_impact\\menu_impact4.ogg",
		"data\\sounds\\menu_impact\\menu_impact5.ogg",
		"data\\sounds\\menu_impact\\menu_impact6.ogg",
		"data\\sounds\\menu_impact\\menu_impact7.ogg"
	};
	for (int i = 0; i < 7; i++)
	{
		if (!temp.loadFromFile(menuImpactSoundPaths[i]))
		{
			// error
		}
		menuImpactSounds.push_back(temp);
	}

	const std::string dynamiteSoundPaths[] = {
		"data\\sounds\\dynamite\\dynamite1.ogg",
		"data\\sounds\\dynamite\\dynamite2.ogg"
	};
	for (int i = 0; i < 2; i++)
	{
		if (!temp.loadFromFile(dynamiteSoundPaths[i]))
		{
			// error
		}
		dynamiteSounds.push_back(temp);
	}
}

void SoundEngine::playSound(SoundType soundType, int col, int colSize)
{
	// skip the sound if the timeout hasn't finished
	auto now = std::chrono::steady_clock::now();
	if (lastPlayedTime.find(soundType) != lastPlayedTime.end() &&
		std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPlayedTime[soundType]) < minInterval) {
		return;
	}

	double centeredValue = col - (colSize / 2.0);
	float location = (centeredValue / (colSize / 2.0)) / 10;

	switch (soundType)
	{
	case SoundType::LiquidDrip:
		if (!liquidDripSounds.empty())
		{
			std::uniform_int_distribution<int> randomLiquidDrip(0, liquidDripSounds.size() - 1);
			std::uniform_int_distribution<int> randomLiquidDripPitch(80, 100);
			sf::Sound sound;
			configureSound(sound, liquidDripSounds[randomLiquidDrip(gen)], sf::Vector3f(location, 0.f, 1.f), randomLiquidDripPitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Bubble:
		if (!bubbleSounds.empty())
		{
			std::uniform_int_distribution<int> randomBubble(0, bubbleSounds.size() - 1);
			std::uniform_int_distribution<int> randomBubblePitch(80, 100);
			sf::Sound sound;
			configureSound(sound, bubbleSounds[randomBubble(gen)], sf::Vector3f(location, 0.f, 1.f), randomBubblePitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Sizzle:
		if (!sizzleSounds.empty())
		{
			std::uniform_int_distribution<int> randomSizzle(0, sizzleSounds.size() - 1);
			std::uniform_int_distribution<int> randomSizzlePitch(80, 100);
			sf::Sound sound;
			configureSound(sound, sizzleSounds[randomSizzle(gen)], sf::Vector3f(location, 0.f, 1.f), randomSizzlePitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Fire:
		if (!fireSounds.empty())
		{
			std::uniform_int_distribution<int> randomFire(0, fireSounds.size() - 1);
			std::uniform_int_distribution<int> randomFirePitch(80, 100);
			sf::Sound sound;
			configureSound(sound, fireSounds[randomFire(gen)], sf::Vector3f(location, 0.f, 1.f), randomFirePitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::MenuImpact:
		if (!menuImpactSounds.empty())
		{
			std::uniform_int_distribution<int> randomMenuImpact(0, menuImpactSounds.size() - 1);
			std::uniform_int_distribution<int> randomMenuImpactPitch(80, 100);
			sf::Sound sound;
			configureSound(sound, menuImpactSounds[randomMenuImpact(gen)], sf::Vector3f(location, 0.f, 1.f), randomMenuImpactPitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Dynamite:
		if (!dynamiteSounds.empty())
		{
			std::uniform_int_distribution<int> randomDynamite(0, dynamiteSounds.size() - 1);
			std::uniform_int_distribution<int> randomDynamitePitch(80, 100);
			sf::Sound sound;
			configureSound(sound, dynamiteSounds[randomDynamite(gen)], sf::Vector3f(location, 0.f, 1.f), randomDynamitePitch(gen));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	}

	if (globalSounds.size() >= 256)
	{
		std::cout << "Purging sounds (" << globalSounds.size() << ")" << std::endl;
		purgeSounds();
	}
}

void SoundEngine::configureSound(sf::Sound& sound, sf::SoundBuffer& soundBuffer, sf::Vector3f position, int pitch)
{
	sound.setPosition(position);
	sound.setPitch(pitch / 100.f);
	sound.setBuffer(soundBuffer);
}

void SoundEngine::purgeSounds()
{
	// remove sounds that have finished playing
	globalSounds.erase(std::remove_if(globalSounds.begin(), globalSounds.end(),
		[](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
		globalSounds.end());
}

int SoundEngine::getVoiceCount()
{
	return globalSounds.size();
}