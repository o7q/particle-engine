#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

#include <SFML/Audio.hpp>

#include "particle/particle_sounds.hpp"

#include "tools/random.hpp"
#include "tools/logger.hpp"

std::vector<sf::SoundBuffer> SoundEngine::liquidDripSounds;
std::vector<sf::SoundBuffer> SoundEngine::bubbleSounds;
std::vector<sf::SoundBuffer> SoundEngine::sizzleSounds;
std::vector<sf::SoundBuffer> SoundEngine::fireSounds;
std::vector<sf::SoundBuffer> SoundEngine::menuImpactSounds;
std::vector<sf::SoundBuffer> SoundEngine::dynamiteExplosionSounds;
std::vector<sf::SoundBuffer> SoundEngine::nukeExplosionSounds;

std::vector<sf::Sound> SoundEngine::globalSounds;

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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load liquidDripSounds!");
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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load bubbleSounds!");
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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load sizzleSounds!");
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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load fireSounds!");
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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load menuImpactSounds!");
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
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load dynamiteSounds!");
		}
		dynamiteExplosionSounds.push_back(temp);
	}

	const std::string nukeSoundPaths[] = {
	"data\\sounds\\nuke\\nuke1.ogg",
	"data\\sounds\\nuke\\nuke2.ogg"
	};
	for (int i = 0; i < 2; i++)
	{
		if (!temp.loadFromFile(nukeSoundPaths[i]))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load nukeSounds!");
		}
		nukeExplosionSounds.push_back(temp);
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

	float centeredValue = col - (colSize / 2.0);
	float location = (centeredValue / (colSize / 2.0)) / 10;

	switch (soundType)
	{
	case SoundType::LiquidDrip:
		if (!liquidDripSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, liquidDripSounds[Random::genInt(0, liquidDripSounds.size() - 1)], sf::Vector3f(location, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Bubble:
		if (!bubbleSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, bubbleSounds[Random::genInt(0, bubbleSounds.size() - 1)], sf::Vector3f(location, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Sizzle:
		if (!sizzleSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, sizzleSounds[Random::genInt(0, sizzleSounds.size() - 1)], sf::Vector3f(location, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::Fire:
		if (!fireSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, fireSounds[Random::genInt(0, fireSounds.size() - 1)], sf::Vector3f(location, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::MenuImpact:
		if (!menuImpactSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, menuImpactSounds[Random::genInt(0, menuImpactSounds.size() - 1)], sf::Vector3f(0.f, 0.f, 0.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::DynamiteExplosion:
		if (!dynamiteExplosionSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, dynamiteExplosionSounds[Random::genInt(0, dynamiteExplosionSounds.size() - 1)], sf::Vector3f(location, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	case SoundType::NukeExplosion:
		if (!nukeExplosionSounds.empty())
		{
			sf::Sound sound;
			configureSound(sound, nukeExplosionSounds[Random::genInt(0, nukeExplosionSounds.size() - 1)], sf::Vector3f(0.f, 0.f, 1.f), Random::genInt(80, 100));
			globalSounds.push_back(sound);
			globalSounds.back().play();
			lastPlayedTime[soundType] = now;
		}
		break;
	}

	if (globalSounds.size() >= 256)
	{
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
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Purging sounds (" + std::to_string(globalSounds.size()) + ")");

	// remove sounds that have finished playing
	globalSounds.erase(std::remove_if(globalSounds.begin(), globalSounds.end(),
		[](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
		globalSounds.end());
}

int SoundEngine::getVoiceCount()
{
	return globalSounds.size();
}