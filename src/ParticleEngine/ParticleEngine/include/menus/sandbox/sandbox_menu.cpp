#include "menus/menus.h"
#include "tools/menu/button.h"
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

Menu sandboxMenu_run(sf::RenderWindow& renderWindow, int pixelSize, ParticleWorld* particleWorld, std::vector<Button*> sandboxButtons, ParticleWorld::ParticleInstance& drawingParticle, sf::Vector2i localMousePos, sf::Vector2u uiOffset)
{
	std::string hoveredButtonId = "";

	for (int i = 0; i < sandboxButtons.size(); ++i)
	{
		hoveredButtonId = sandboxButtons[i]->handleClick(localMousePos.x, localMousePos.y);
		if (hoveredButtonId != "")
		{
			break;
		}
	}

	for (int i = 0; i < sandboxButtons.size(); ++i)
	{
		sandboxButtons[i]->draw(renderWindow);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (hoveredButtonId == "stoneButton")
		{
			SoundEngine::playSound(SoundEngine::SoundType::WaterDrip);
			drawingParticle.material = ParticleWorld::Material::Stone;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
		}
		else if (hoveredButtonId == "sandButton")
		{
			drawingParticle.material = ParticleWorld::Material::Sand;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Sand;
		}
		else if (hoveredButtonId == "dirtButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dirt;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Dirt;
		}
		else if (hoveredButtonId == "grassButton")
		{
			drawingParticle.material = ParticleWorld::Material::Grass;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Grass;
		}
		else if (hoveredButtonId == "waterButton")
		{
			drawingParticle.material = ParticleWorld::Material::Water;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
		}
		else if (hoveredButtonId == "iceButton")
		{
			drawingParticle.material = ParticleWorld::Material::Ice;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Ice;
		}
		else if (hoveredButtonId == "fireButton")
		{
			drawingParticle.material = ParticleWorld::Material::Fire;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Fire;
		}
		else if (hoveredButtonId == "gasolineButton")
		{
			drawingParticle.material = ParticleWorld::Material::Gasoline;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
		}
		else if (hoveredButtonId == "smokeButton")
		{
			drawingParticle.material = ParticleWorld::Material::Smoke;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
		}
		else if (hoveredButtonId == "toxicGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::ToxicGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
		}
		else if (hoveredButtonId == "flammableGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::FlammableGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
		}
		else if (hoveredButtonId == "airButton")
		{
			//SoundEngine::updateSounds();
			drawingParticle.material = ParticleWorld::Material::Air;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
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