#include "menus/menus.h"
#include "tools/menu/button.h"
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

Menu sandboxMenu_run(sf::RenderWindow& renderWindow, int pixelSize, ParticleWorld* particleWorld, std::vector<Button*> sandboxButtons, ParticleWorld::ParticleInstance& drawingParticle, sf::Vector2i localMousePos, sf::Vector2i uiOffset, int titleBarHeight)
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
			drawingParticle.material = ParticleWorld::Material::Stone;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "sandButton")
		{
			drawingParticle.material = ParticleWorld::Material::Sand;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Sand;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "dirtButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dirt;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Dirt;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "grassButton")
		{
			drawingParticle.material = ParticleWorld::Material::Grass;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Grass;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "waterButton")
		{
			drawingParticle.material = ParticleWorld::Material::Water;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = true;
		}
		else if (hoveredButtonId == "iceButton")
		{
			drawingParticle.material = ParticleWorld::Material::Ice;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Ice;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "fireButton")
		{
			drawingParticle.material = ParticleWorld::Material::Fire;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "gasolineButton")
		{
			drawingParticle.material = ParticleWorld::Material::Gasoline;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "smokeButton")
		{
			drawingParticle.material = ParticleWorld::Material::Smoke;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "acidGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::AcidGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::AcidSmoke;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "flammableGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::FlammableGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "airButton")
		{
			drawingParticle.material = ParticleWorld::Material::Air;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "acidButton")
		{
			drawingParticle.material = ParticleWorld::Material::Acid;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Acid;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
		}
		else if (hoveredButtonId == "dynamiteButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dynamite;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Explosive;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			}
		else if (hoveredButtonId == "pauseButton")
		{
			SoundEngine::purgeSounds();
			if (particleWorld->isFrozen())
			{
				particleWorld->unfreeze();
			}
			else
			{
				particleWorld->freeze();
			}
		}

		particleWorld->paintParticles((localMousePos.y - uiOffset.y - titleBarHeight) / pixelSize, (localMousePos.x - uiOffset.x) / pixelSize, 6, drawingParticle, ParticleWorld::Shape::Circle);
	}

	return Menu::Sandbox;
}