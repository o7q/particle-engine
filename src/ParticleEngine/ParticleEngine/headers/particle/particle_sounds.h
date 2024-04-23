#pragma once

#ifndef PARTICLE_SOUNDS_H
#define PARTICLE_SOUNDS_H

#include <iostream>
#include <random>
#include "SFML/Audio.hpp"

class SoundEngine {
private:
	static std::vector<sf::SoundBuffer> waterSounds;
	static std::vector<sf::Sound> sounds;

public:
	enum class SoundType {
		WaterDrip
	};

	static sf::Sound sound;
	static std::random_device rd;
	static std::mt19937 gen;

	static void init();
	static void playSound(SoundType soundType);
	static void purgeSounds();
};

#endif