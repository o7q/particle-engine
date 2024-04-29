#pragma once

#ifndef PARTICLE_SOUNDS_H
#define PARTICLE_SOUNDS_H

#include <iostream>
#include <random>
#include <chrono>
#include <unordered_map>

#include <SFML/Audio.hpp>

class SoundEngine {
public:
	enum class SoundType {
		LiquidDrip,
		Bubble,
		Sizzle,
		Fire,
		MenuImpact,
		DynamiteExplosion,
		NukeExplosion
	};

	static sf::Sound sound;
	static std::random_device rd;
	static std::mt19937 gen;

	static void init();
	static void playSound(SoundType soundType, int, int);
	static void purgeSounds();
	static int getVoiceCount();

private:
	static void configureSound(sf::Sound&, sf::SoundBuffer&, sf::Vector3f, int);

	static std::vector<sf::Sound> globalSounds;
	static std::unordered_map<SoundType, std::chrono::steady_clock::time_point> lastPlayedTime;
	static std::chrono::milliseconds minInterval;

	static std::vector<sf::SoundBuffer> liquidDripSounds;
	static std::vector<sf::SoundBuffer> bubbleSounds;
	static std::vector<sf::SoundBuffer> sizzleSounds;
	static std::vector<sf::SoundBuffer> fireSounds;
	static std::vector<sf::SoundBuffer> menuImpactSounds;
	static std::vector<sf::SoundBuffer> dynamiteExplosionSounds;
	static std::vector<sf::SoundBuffer> nukeExplosionSounds;
};

#endif