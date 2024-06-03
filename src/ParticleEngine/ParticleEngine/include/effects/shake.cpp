#include "effects/effects.hpp"

#include "tools/random.hpp"

ShakeEffect::ShakeEffect(sf::RenderWindow& renderWindow, ParticleWorld* particleWorld, sf::Vector2i& renderWindowUserPosition) : Effector(renderWindow, particleWorld), renderWindowUserPosition(renderWindowUserPosition)
{

}

void ShakeEffect::setShakeLength(int shakeLength)
{
	this->shakeLength = shakeLength;
}

void ShakeEffect::tick()
{
	if (shakeLength <= 0)
	{
		shakeLength = 0;
		return;
	}

	shakeInitialPos = renderWindowUserPosition;

	std::uniform_int_distribution<int> shakeDist(0, 10);

	renderWindow.setPosition(
		sf::Vector2i(
			shakeInitialPos.x + 10 * Random::genInt(0, 10) * std::sqrt(shakeLength) / 10.0f,
			shakeInitialPos.y + 10 * Random::genInt(0, 10) * std::sqrt(shakeLength) / 10.0f
		)
	);

	shakeLength--;

	if (shakeLength <= 0)
	{
		renderWindow.setPosition(shakeInitialPos);
	}
}