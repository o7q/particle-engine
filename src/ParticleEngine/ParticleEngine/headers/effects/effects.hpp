#pragma once

#include <random>

#include "SFML/Graphics.hpp"

#include "particle/particle_world.hpp"


class Effector {
public:
	Effector(sf::RenderWindow&, ParticleWorld*);

protected:
	sf::RenderWindow& renderWindow;

private:
	ParticleWorld* particleWorld;
};

class ShakeEffect : public Effector {
public:
	ShakeEffect(sf::RenderWindow&, ParticleWorld*, sf::Vector2i&);

	void setShakeLength(int);
	void tick();

private:
	sf::Vector2i& renderWindowUserPosition;

	int shakeLength = 0;
	sf::Vector2i shakeInitialPos;
};