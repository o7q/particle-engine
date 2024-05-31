#include "menu/menu.h"
#include "world/world_generator.h"

SandboxMenu::SandboxMenu(sf::RenderWindow& renderWindow, ParticleWorld* particleWorld, ParticleRenderer* particleRenderer) : Menu(renderWindow), particleWorld(particleWorld), particleRenderer(particleRenderer)
{
}

MenuType SandboxMenu::tick()
{
	if (init())
	{

	}

	if (update())
	{
		sf::Vector2f mouseWorldCoords = particleRenderer->windowToWorldCoordinates(LOCAL_MOUSE_POSITION);

		std::string clickedButtonId = "";

		for (Button* button : buttons)
		{
			if (button->hasMouseClicked())
			{
				clickedButtonId = button->getId();
			}
		}

		if (clickedButtonId == "stoneButton")
		{
			drawingParticle.material = ParticleWorld::Material::Stone;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (clickedButtonId == "sandButton")
		{
			drawingParticle.material = ParticleWorld::Material::Sand;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Sand;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
		}
		else if (clickedButtonId == "dirtButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dirt;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Dirt;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "grassButton")
		{
			drawingParticle.material = ParticleWorld::Material::Grass;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Grass;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "waterButton")
		{
			drawingParticle.material = ParticleWorld::Material::Water;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = true;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "iceButton")
		{
			drawingParticle.material = ParticleWorld::Material::Ice;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Ice;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "fireButton")
		{
			drawingParticle.material = ParticleWorld::Material::Fire;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "gasolineButton")
		{
			drawingParticle.material = ParticleWorld::Material::Gasoline;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Water;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "smokeButton")
		{
			drawingParticle.material = ParticleWorld::Material::Smoke;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "acidGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::AcidGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::AcidSmoke;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "flammableGasButton")
		{
			drawingParticle.material = ParticleWorld::Material::FlammableGas;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "airButton")
		{
			drawingParticle.material = ParticleWorld::Material::Air;
			drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::NoGravity;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "acidButton")
		{
			drawingParticle.material = ParticleWorld::Material::Acid;
			drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Acid;
			drawingParticle.flammable = true;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "dynamiteButton")
		{
			drawingParticle.material = ParticleWorld::Material::Dynamite;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Explosive;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "nukeButton")
		{
			drawingParticle.material = ParticleWorld::Material::Nuke;
			drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			drawingParticle.physicsType = ParticleWorld::PhysicsType::Nuke;
			drawingParticle.flammable = false;
			drawingParticle.createsSteam = false;
			// drawingParticle.toolMode = "draw";
		}
		else if (clickedButtonId == "pauseButton")
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

		if (MOUSE_DOWN)
		{
			particleWorld->paintParticles(mouseWorldCoords.y, mouseWorldCoords.x, 6, drawingParticle, ParticleWorld::Shape::Circle);
		}
	}

	return MenuType::SANDBOX_MENU;
}

std::vector<Button*> SandboxMenu::getDefaultButtons(sf::RenderWindow& renderWindow, sf::Font& font, sf::Vector2i uiOffset, sf::Vector2u renderWindowSize)
{
	std::vector<Button*> sandboxMenu_materialButtons;

	Button* stoneButton = new Button(renderWindow, font);
	stoneButton->setPosition(sf::Vector2f(0 + uiOffset.x, renderWindowSize.y + uiOffset.y));
	stoneButton->setSize(sf::Vector2f(25, 25));
	stoneButton->setColor(sf::Color(160, 160, 160));
	stoneButton->setId("stoneButton");
	sandboxMenu_materialButtons.push_back(stoneButton);

	Button* sandButton = new Button(renderWindow, font);
	sandButton->setPosition(sf::Vector2f(stoneButton->getPos().x + stoneButton->getSize().x, renderWindowSize.y + uiOffset.y));
	sandButton->setSize(sf::Vector2f(25, 25));
	sandButton->setColor(sf::Color(245, 228, 118));
	sandButton->setId("sandButton");
	sandboxMenu_materialButtons.push_back(sandButton);

	Button* dirtButton = new Button(renderWindow, font);
	dirtButton->setPosition(sf::Vector2f(sandButton->getPos().x + sandButton->getSize().x, renderWindowSize.y + uiOffset.y));
	dirtButton->setSize(sf::Vector2f(25, 25));
	dirtButton->setColor(sf::Color(77, 54, 15));
	dirtButton->setId("dirtButton");
	sandboxMenu_materialButtons.push_back(dirtButton);

	Button* grassButton = new Button(renderWindow, font);
	grassButton->setPosition(sf::Vector2f(dirtButton->getPos().x + dirtButton->getSize().x, renderWindowSize.y + uiOffset.y));
	grassButton->setSize(sf::Vector2f(25, 25));
	grassButton->setColor(sf::Color(60, 110, 33));
	grassButton->setId("grassButton");
	sandboxMenu_materialButtons.push_back(grassButton);

	Button* waterButton = new Button(renderWindow, font);
	waterButton->setPosition(sf::Vector2f(dirtButton->getPos().x + dirtButton->getSize().x, renderWindowSize.y + uiOffset.y));
	waterButton->setSize(sf::Vector2f(25, 25));
	waterButton->setColor(sf::Color(72, 136, 240));
	waterButton->setId("waterButton");
	sandboxMenu_materialButtons.push_back(waterButton);

	Button* iceButton = new Button(renderWindow, font);
	iceButton->setPosition(sf::Vector2f(waterButton->getPos().x + waterButton->getSize().x, renderWindowSize.y + uiOffset.y));
	iceButton->setSize(sf::Vector2f(25, 25));
	iceButton->setColor(sf::Color(120, 212, 240));
	iceButton->setId("iceButton");
	sandboxMenu_materialButtons.push_back(iceButton);

	Button* fireButton = new Button(renderWindow, font);
	fireButton->setPosition(sf::Vector2f(iceButton->getPos().x + iceButton->getSize().x, renderWindowSize.y + uiOffset.y));
	fireButton->setSize(sf::Vector2f(25, 25));
	fireButton->setColor(sf::Color(255, 191, 0));
	fireButton->setId("fireButton");
	sandboxMenu_materialButtons.push_back(fireButton);

	Button* gasolineButton = new Button(renderWindow, font);
	gasolineButton->setPosition(sf::Vector2f(fireButton->getPos().x + fireButton->getSize().x, renderWindowSize.y + uiOffset.y));
	gasolineButton->setSize(sf::Vector2f(25, 25));
	gasolineButton->setColor(sf::Color(215, 219, 77));
	gasolineButton->setId("gasolineButton");
	sandboxMenu_materialButtons.push_back(gasolineButton);

	Button* smokeButton = new Button(renderWindow, font);
	smokeButton->setPosition(sf::Vector2f(gasolineButton->getPos().x + gasolineButton->getSize().x, renderWindowSize.y + uiOffset.y));
	smokeButton->setSize(sf::Vector2f(25, 25));
	smokeButton->setColor(sf::Color(120, 120, 120));
	smokeButton->setId("smokeButton");
	sandboxMenu_materialButtons.push_back(smokeButton);

	Button* acidGasButton = new Button(renderWindow, font);
	acidGasButton->setPosition(sf::Vector2f(smokeButton->getPos().x + smokeButton->getSize().x, renderWindowSize.y + uiOffset.y));
	acidGasButton->setSize(sf::Vector2f(25, 25));
	acidGasButton->setColor(sf::Color(81, 97, 47));
	acidGasButton->setId("acidGasButton");
	sandboxMenu_materialButtons.push_back(acidGasButton);

	Button* flammableGasButton = new Button(renderWindow, font);
	flammableGasButton->setPosition(sf::Vector2f(acidGasButton->getPos().x + acidGasButton->getSize().x, renderWindowSize.y + uiOffset.y));
	flammableGasButton->setSize(sf::Vector2f(25, 25));
	flammableGasButton->setColor(sf::Color(156, 133, 81));
	flammableGasButton->setId("flammableGasButton");
	sandboxMenu_materialButtons.push_back(flammableGasButton);

	Button* airButton = new Button(renderWindow, font);
	airButton->setPosition(sf::Vector2f(flammableGasButton->getPos().x + flammableGasButton->getSize().x, renderWindowSize.y + uiOffset.y));
	airButton->setSize(sf::Vector2f(25, 25));
	airButton->setColor(sf::Color(255, 255, 255));
	airButton->setId("airButton");
	sandboxMenu_materialButtons.push_back(airButton);

	Button* acidButton = new Button(renderWindow, font);
	acidButton->setPosition(sf::Vector2f(airButton->getPos().x + airButton->getSize().x, renderWindowSize.y + uiOffset.y));
	acidButton->setSize(sf::Vector2f(25, 25));
	acidButton->setColor(sf::Color(225, 255, 125));
	acidButton->setId("acidButton");
	sandboxMenu_materialButtons.push_back(acidButton);

	Button* dynamiteButton = new Button(renderWindow, font);
	dynamiteButton->setPosition(sf::Vector2f(acidButton->getPos().x + acidButton->getSize().x, renderWindowSize.y + uiOffset.y));
	dynamiteButton->setSize(sf::Vector2f(25, 25));
	dynamiteButton->setColor(sf::Color(110, 33, 29));
	dynamiteButton->setId("dynamiteButton");
	sandboxMenu_materialButtons.push_back(dynamiteButton);

	Button* nukeButton = new Button(renderWindow, font);
	nukeButton->setPosition(sf::Vector2f(dynamiteButton->getPos().x + dynamiteButton->getSize().x, renderWindowSize.y + uiOffset.y));
	nukeButton->setSize(sf::Vector2f(25, 25));
	nukeButton->setColor(sf::Color(63, 107, 49));
	nukeButton->setId("nukeButton");
	sandboxMenu_materialButtons.push_back(nukeButton);

	Button* pauseButton = new Button(renderWindow, font);
	pauseButton->setPosition(sf::Vector2f(400, renderWindowSize.y + uiOffset.y + 20));
	pauseButton->setSize(sf::Vector2f(80, 25));
	pauseButton->setColor(sf::Color(63, 107, 49));
	pauseButton->setId("pauseButton");
	pauseButton->setTextString("Pause");
	pauseButton->setTextColor(sf::Color(255, 0, 0));
	pauseButton->setColor(sf::Color(0, 0, 0));
	sandboxMenu_materialButtons.push_back(pauseButton);

	return sandboxMenu_materialButtons;
}