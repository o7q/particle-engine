#include "menus/menus.h"
#include "tools/menu/button.h"
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "tools/menu/button.h"
#include "menus/menus.h"
#include "world/world_generator.h"

Menu mainMenu_run(sf::RenderWindow& renderWindow, ParticleWorld* particleWorld, std::vector<sf::Music*> mainMenu_music, bool doOnce)
{
	if (doOnce)
	{
		sf::Image titleImage;
		if (!titleImage.loadFromFile("data\\objects\\menu\\title.png"))
		{
			// error
		}
		sf::Image titleImage_pressAnyKey;
		if (!titleImage_pressAnyKey.loadFromFile("data\\objects\\menu\\title_press_any_key.png"))
		{
			// error
		}

		std::uniform_int_distribution<int> dist(1, 1);
		std::random_device rd;
		std::mt19937 gen(rd());

		int random = dist(gen);

		ParticleWorld::ParticleInstance mainMenuParticle = particleWorld->getDefaultInstance();

		switch (random)
		{
		case 0: // 0 = ocean
			generateWorld(particleWorld, WorldType::Ocean);
			mainMenuParticle.material = ParticleWorld::Material::Fire;
			mainMenuParticle.materialType = ParticleWorld::MaterialType::Liquid;
			mainMenuParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			mainMenu_music[0]->play();
			break;
		case 1: // 1 = swamp
			generateWorld(particleWorld, WorldType::Swamp);
			mainMenuParticle.material = ParticleWorld::Material::FlammableGas;
			mainMenuParticle.materialType = ParticleWorld::MaterialType::Gas;
			mainMenuParticle.physicsType = ParticleWorld::PhysicsType::Smoke;
			mainMenu_music[1]->play();
			break;
		}

		particleWorld->imageToParticles(particleWorld->getRowSize() / 2 - titleImage.getSize().y * 2, particleWorld->getColSize() / 2 - titleImage.getSize().x / 2, titleImage, mainMenuParticle, true);
		particleWorld->imageToParticles(particleWorld->getRowSize() / 2, particleWorld->getColSize() / 2 - titleImage_pressAnyKey.getSize().x / 2, titleImage_pressAnyKey, mainMenuParticle, true);
	}

	bool anyKeyPressed = false;
	for (int key = 0; key < sf::Keyboard::KeyCount; ++key)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
		{
			anyKeyPressed = true;
			break;
		}
	}

	if (anyKeyPressed)
	{
		particleWorld->unfreeze();
		for (int i = 0; i < mainMenu_music.size(); ++i)
		{
			mainMenu_music[i]->stop();
		}
		return Menu::Sandbox;
	}

	return Menu::Main;
}