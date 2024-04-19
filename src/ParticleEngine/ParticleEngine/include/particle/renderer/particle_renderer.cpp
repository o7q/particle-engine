#include "particle/particle_world.h"
#include "particle/particle_renderer.h"
#include "tools/tools.h"

void renderParticles(ParticleWorld* particleWorld, sf::RenderWindow& renderWindow, int pixelSize)
{
	sf::VertexArray quad(sf::Quads, 4);
	for (int row = 0; row < particleWorld->rowSize; row++)
	{
		for (int col = 0; col < particleWorld->colSize; col++)
		{
			bool renderPixel = false;
			int r = 0, g = 0, b = 0, a = 0;

			float brightnessColor = particleWorld->getParticle(row, col).brightnessMultiplier;
			float wetnessColor = particleWorld->getParticle(row, col).wetnessMultiplier;

			switch (particleWorld->getParticle(row, col).material)
			{
			case ParticleWorld::Material::Stone: {
				r = 160 * brightnessColor;
				g = 160 * brightnessColor;
				b = 160 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Sand: {
				r = 245 / wetnessColor * brightnessColor;
				g = 228 / wetnessColor * brightnessColor;
				b = 118 / wetnessColor * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Sandstone: {
				r = 189 / wetnessColor * brightnessColor;
				g = 176 / wetnessColor * brightnessColor;
				b = 91 / wetnessColor * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Dirt: {
				r = 77 / wetnessColor * brightnessColor;
				g = 54 / wetnessColor * brightnessColor;
				b = 15 / wetnessColor * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Grass: {
				r = 60 * brightnessColor;
				g = 110 * brightnessColor;
				b = 33 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::RedFlower: {
				r = 255 * brightnessColor;
				g = 59 * brightnessColor;
				b = 59 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::PinkFlower: {
				r = 246 * brightnessColor;
				g = 122 * brightnessColor;
				b = 255 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::YellowFlower: {
				r = 255 * brightnessColor;
				g = 222 * brightnessColor;
				b = 92 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::BlueFlower: {
				r = 84 * brightnessColor;
				g = 178 * brightnessColor;
				b = 255 * brightnessColor;
				a = 255;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Water: {
				r = 34;
				g = 152 * (brightnessColor == 1 ? 1 : 0.99);
				b = 218 * (brightnessColor == 1 ? 1 : 0.99);
				a = 200 * (brightnessColor == 1 ? 1 : 0.99);

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Gasoline: {
				r = 215;
				g = 219;
				b = 77;
				a = 230 * brightnessColor;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Fire: {
				std::uniform_int_distribution<int> dist(0, 2);
				double fireFlicker = dist(particleWorld->gen) / 2.0;
				r = 255;
				g = 191 * fireFlicker;
				b = 0;
				a = 255 * fireFlicker;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Ice: {
				r = 120 * brightnessColor;
				g = 212 * brightnessColor;
				b = 240 * brightnessColor;
				a = 240;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Smoke: {
				r = 120;
				g = 120;
				b = 120;
				a = 240 * brightnessColor;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::Steam: {
				r = 220;
				g = 220;
				b = 220;
				a = 220 * brightnessColor;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::ToxicGas: {
				r = 81;
				g = 97;
				b = 47;
				a = 235 * brightnessColor;

				renderPixel = true;
				break;
			}
			case ParticleWorld::Material::FlammableGas: {
				r = 156;
				g = 133;
				b = 81;
				a = 235 * brightnessColor;

				renderPixel = true;
				break;
			}
			}

			r = verify256Range(r);
			g = verify256Range(g);
			b = verify256Range(b);

			if (renderPixel)
			{
				quad[0].position = sf::Vector2f(col * pixelSize, row * pixelSize);
				quad[1].position = sf::Vector2f(col * pixelSize + pixelSize, row * pixelSize);
				quad[2].position = sf::Vector2f(col * pixelSize + pixelSize, row * pixelSize + pixelSize);
				quad[3].position = sf::Vector2f(col * pixelSize, row * pixelSize + pixelSize);

				quad[0].color = sf::Color(r, g, b, a);
				quad[1].color = sf::Color(r, g, b, a);
				quad[2].color = sf::Color(r, g, b, a);
				quad[3].color = sf::Color(r, g, b, a);

				renderWindow.draw(quad);
			}
		}
	}
}