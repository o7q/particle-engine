#include "menus/menus.h"
#include "tools/menu/button.h"
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "tools/menu/button.h"
#include "menus/menus.h"

Menu sandboxMenu_run(sf::RenderWindow& renderWindow, int pixelSize, ParticleWorld* particleWorld, std::vector<Button*> sandboxButtons, ParticleWorld::ParticleInstance& drawingParticle, sf::Vector2i localMousePos, sf::Vector2u uiOffset)
{
	std::string hoveredButtonId = "";
	for (int i = 0; i < sandboxButtons.size(); i++)
	{
		bool mouseHovering = sandboxButtons[i]->isMouseHover(localMousePos.x, localMousePos.y);
		sandboxButtons[i]->highlight(mouseHovering);

		if (mouseHovering)
		{
			hoveredButtonId = sandboxButtons[i]->id;
		}

		sandboxButtons[i]->draw(renderWindow);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (hoveredButtonId == "stoneButton")
		{
			drawingParticle.material = ParticleWorld::Material::Stone;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
		}
		else if (hoveredButtonId == "sandButton")
		{
			drawingParticle.material = ParticleWorld::Material::Sand;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
		}
		else if (hoveredButtonId == "dirtButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dirt;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
		}
		else if (hoveredButtonId == "grassButton")
		{
			drawingParticle.material = ParticleWorld::Material::Grass;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
		}
		else if (hoveredButtonId == "waterButton")
		{
			drawingParticle.material = ParticleWorld::Material::Water;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
		}
		else if (hoveredButtonId == "iceButton")
		{
			drawingParticle.material = ParticleWorld::Material::Ice;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
		}
		else if (hoveredButtonId == "fireButton")
		{
			drawingParticle.material = ParticleWorld::Material::Fire;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
		}
		else if (hoveredButtonId == "gasolineButton")
		{
			drawingParticle.material = ParticleWorld::Material::Gasoline;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
		}
		else if (hoveredButtonId == "smokeButton")
		{
			drawingParticle.material = ParticleWorld::Material::Smoke;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
		}
		else if (hoveredButtonId == "toxicGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::ToxicGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
		}
		else if (hoveredButtonId == "flammableGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::FlammableGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
		}
		else if (hoveredButtonId == "airButton")
		{
			drawingParticle.material = ParticleWorld::Material::Air;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
		}
		else if (hoveredButtonId == "pauseButton")
		{
			if (particleWorld->isFrozen())
			{
				particleWorld->unfreeze();
			}
			else
			{
				particleWorld->freeze();
			}
		}

		particleWorld->paintParticles((localMousePos.y - uiOffset.y) / pixelSize, (localMousePos.x - uiOffset.x) / pixelSize, 5, drawingParticle);
	}

	return Menu::Sandbox;
}