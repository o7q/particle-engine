#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

#include "tools/menu/button.h"

#include "menus/menus.h"

Menu sandboxMenu_run(
	sf::RenderWindow& renderWindow,
	ParticleRenderer* particleRenderer,
	ParticleWorld* particleWorld,
	std::vector<Button*> sandboxButtons,
	ParticleWorld::DrawingParticle& drawingParticle,
	sf::Vector2i localMousePos,
	sf::Vector2i uiOffset,
	std::unordered_set<std::string>& unlockedButtons
)
{
	std::string hoveredButtonId = "";

	sf::Vector2f mouseWorldCoords = particleRenderer->mouseToWorldCoordinates(localMousePos);

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
		for (std::string buttonId : unlockedButtons)
		{
			if (sandboxButtons[i]->getId() == buttonId || true)
			{
				sandboxButtons[i]->enable();
				break;
			}
			else if (sandboxButtons[i]->getType() != "ui")
			{
				sandboxButtons[i]->disable();
			}
		}

		sandboxButtons[i]->draw(renderWindow);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (drawingParticle.toolMode == "inspect")
			switch (
				particleWorld->getParticle(
					(localMousePos.y - uiOffset.y)/* / pixelSize*/,
					(localMousePos.x - uiOffset.x)/* / pixelSize*/).material
				)
			{
			case ParticleWorld::Material::Stone:
				unlockedButtons.insert("stoneButton");
				break;
			case ParticleWorld::Material::Sand:
				unlockedButtons.insert("sandButton");
				break;
			case ParticleWorld::Material::Dirt:
				unlockedButtons.insert("dirtButton");
				break;
			case ParticleWorld::Material::Grass:
				unlockedButtons.insert("grassButton");
				break;
			case ParticleWorld::Material::Water:
				unlockedButtons.insert("waterButton");
				break;
			case ParticleWorld::Material::Ice:
				unlockedButtons.insert("iceButton");
				break;
			case ParticleWorld::Material::Fire:
				unlockedButtons.insert("fireButton");
				break;
			case ParticleWorld::Material::Gasoline:
				unlockedButtons.insert("gasolineButton");
				break;
			case ParticleWorld::Material::Smoke:
				unlockedButtons.insert("smokeButton");
				break;
			case ParticleWorld::Material::AcidGas:
				unlockedButtons.insert("acidGasButton");
				break;
			case ParticleWorld::Material::FlammableGas:
				unlockedButtons.insert("flammableGasButton");
				break;
			case ParticleWorld::Material::Air:
				unlockedButtons.insert("airButton");
				break;
			case ParticleWorld::Material::Acid:
				unlockedButtons.insert("acidButton");
				break;
			case ParticleWorld::Material::Dynamite:
				unlockedButtons.insert("dynamiteButton");
				break;
			case ParticleWorld::Material::Nuke:
				unlockedButtons.insert("nukeButton");
				break;
			}

		if (hoveredButtonId == "stoneButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Stone;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "sandButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Sand;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Sand;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "dirtButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Dirt;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Dirt;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "grassButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Grass;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Grass;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "waterButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Water;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = true;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "iceButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Ice;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Ice;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "fireButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Fire;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Fire;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "gasolineButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Gasoline;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.particleInstance.flammable = true;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "smokeButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Smoke;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "acidGasButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::AcidGas;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::AcidSmoke;
			drawingParticle.particleInstance.flammable = true;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "flammableGasButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::FlammableGas;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.particleInstance.flammable = true;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "airButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Air;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "acidButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Acid;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Acid;
			drawingParticle.particleInstance.flammable = true;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "dynamiteButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Dynamite;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Explosive;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
		}
		else if (hoveredButtonId == "nukeButton")
		{
			drawingParticle.particleInstance.material = ParticleWorld::Material::Nuke;
			drawingParticle.particleInstance.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.particleInstance.physicsType = ParticleWorld::PhysicsType::Nuke;
			drawingParticle.particleInstance.flammable = false;
			drawingParticle.particleInstance.createsSteam = false;
			drawingParticle.toolMode = "draw";
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
		else if (hoveredButtonId == "inspectButton")
		{
			drawingParticle.toolMode = "inspect";
		}

		if (drawingParticle.toolMode == "draw")
		{
			particleWorld->paintParticles(mouseWorldCoords.y, mouseWorldCoords.x, 6, drawingParticle.particleInstance, ParticleWorld::Shape::Circle);
		}
	}

	return Menu::Sandbox;
}