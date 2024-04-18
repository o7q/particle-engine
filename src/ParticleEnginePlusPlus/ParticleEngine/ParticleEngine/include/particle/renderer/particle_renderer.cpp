#include "particle/particle_world.h"
#include "particle/particle_renderer.h"

void renderParticles(ParticleWorld* particleWorld, sf::RenderWindow& renderWindow, int pixelSize)
{
	sf::VertexArray quad(sf::Quads, 4);
	int r = 0, g = 0, b = 0;
	for (int row = 0; row < particleWorld->rowSize; row++)
	{
		for (int col = 0; col < particleWorld->colSize; col++)
		{
			bool render = false;
			r = 0, g = 0, b = 0;

			float brightnessColor = particleWorld->getParticle(row, col).brightnessMultiplier;
			float wetnessColor = particleWorld->getParticle(row, col).wetnessMultiplier;

			switch (particleWorld->getParticle(row, col).material)
			{
			case ParticleWorld::Material::Sand:
				r = 245 / wetnessColor * brightnessColor;
				g = 228 / wetnessColor * brightnessColor;
				b = 118 / wetnessColor * brightnessColor;
				render = true;
				break;
			case ParticleWorld::Material::Water:
				r = 72 * brightnessColor;
				g = 136 * brightnessColor;
				b = 240 * brightnessColor;
				render = true;
				break;
			case ParticleWorld::Material::Smoke:
				r = 120 * brightnessColor;
				g = 120 * brightnessColor;
				b = 120 * brightnessColor;
				render = true;
				break;
			}

			if (render)
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