#include "particle/particle_world.h"
#include "particle/particle_renderer.h"

void renderParticles(ParticleWorld* particleWorld, sf::RenderWindow& renderWindow, int pixelSize)
{
	sf::VertexArray quad(sf::Quads, 4);
	for (int row = 0; row < particleWorld->rowSize; row++)
	{
		for (int col = 0; col < particleWorld->colSize; col++)
		{
			bool renderCurrent = false;
			int r = 0, g = 0, b = 0;

			float brightnessColor = particleWorld->getParticle(row, col).brightnessMultiplier;
			float wetnessColor = particleWorld->getParticle(row, col).wetnessMultiplier;

			switch (particleWorld->getParticle(row, col).material)
			{
			case ParticleWorld::Material::Sand: {
				r = 245 / wetnessColor * brightnessColor;
				g = 228 / wetnessColor * brightnessColor;
				b = 118 / wetnessColor * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Water: {
				r = 72 * brightnessColor;
				g = 136 * brightnessColor;
				b = 240 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Smoke: {
				r = 120 * brightnessColor;
				g = 120 * brightnessColor;
				b = 120 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Ice: {
				r = 120 * brightnessColor;
				g = 212 * brightnessColor;
				b = 240 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Stone: {
				r = 160 * brightnessColor;
				g = 160 * brightnessColor;
				b = 160 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Dirt: {
				r = 77 / wetnessColor * brightnessColor;
				g = 54 / wetnessColor * brightnessColor;
				b = 15 / wetnessColor * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Grass: {
				r = 60 * brightnessColor;
				g = 110 * brightnessColor;
				b = 33 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::RedFlower: {
				r = 255 * brightnessColor;
				g = 59 * brightnessColor;
				b = 59 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::PinkFlower: {
				r = 246 * brightnessColor;
				g = 122 * brightnessColor;
				b = 255 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::YellowFlower: {
				r = 255 * brightnessColor;
				g = 222 * brightnessColor;
				b = 92 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::BlueFlower: {
				r = 84 * brightnessColor;
				g = 178 * brightnessColor;
				b = 255 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Fire: {
				std::uniform_int_distribution<int> dist(0, 2);
				double fireFlicker = dist(particleWorld->gen) / 2.0;
				r = 255 * fireFlicker;
				g = 191 * fireFlicker;
				b = 0 * fireFlicker;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::Gasoline: {
				r = 215 * brightnessColor;
				g = 219 * brightnessColor;
				b = 77 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::ToxicGas: {
				r = 81 * brightnessColor;
				g = 97 * brightnessColor;
				b = 47 * brightnessColor;
				renderCurrent = true;
				break;
			}
			case ParticleWorld::Material::FlammableGas: {
				r = 156 * brightnessColor;
				g = 133 * brightnessColor;
				b = 81 * brightnessColor;
				renderCurrent = true;
				break;
			}
			}

			if (renderCurrent)
			{
				quad[0].position = sf::Vector2f(col * pixelSize, row * pixelSize);
				quad[1].position = sf::Vector2f(col * pixelSize + pixelSize, row * pixelSize);
				quad[2].position = sf::Vector2f(col * pixelSize + pixelSize, row * pixelSize + pixelSize);
				quad[3].position = sf::Vector2f(col * pixelSize, row * pixelSize + pixelSize);

				quad[0].color = sf::Color(r, g, b);
				quad[1].color = sf::Color(r, g, b);
				quad[2].color = sf::Color(r, g, b);
				quad[3].color = sf::Color(r, g, b);

				renderWindow.draw(quad);
			}
		}
	}
}