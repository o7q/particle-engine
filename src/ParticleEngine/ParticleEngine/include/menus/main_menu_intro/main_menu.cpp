#include "menus/menus.h"
#include "tools/menu/button.h"
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"
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

		std::uniform_int_distribution<int> dist(0, 1);
		std::random_device rd;
		std::mt19937 gen(rd());

		int random = dist(gen);

		ParticleWorld::ParticleInstance titleParticle;
		ParticleWorld::ParticleInstance subTitleParticle;

		switch (random)
		{
		case 0: // 0 = ocean
			generateWorld(particleWorld, WorldType::Ocean);
			titleParticle.material = ParticleWorld::Material::Fire;
			titleParticle.materialType = ParticleWorld::MaterialType::Liquid;
			titleParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			mainMenu_music[0]->play();
			break;
		case 1: // 1 = swamp
			generateWorld(particleWorld, WorldType::Swamp);
			titleParticle.material = ParticleWorld::Material::Fire;
			titleParticle.materialType = ParticleWorld::MaterialType::Liquid;
			titleParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			mainMenu_music[1]->play();
			break;
		}

		particleWorld->imageToParticles(particleWorld->getRowSize() / 2 - particleWorld->getRowSize() / 4, particleWorld->getColSize() / 2, titleImage, titleParticle, true);
		particleWorld->imageToParticles(particleWorld->getRowSize() / 2, particleWorld->getColSize() / 2, titleImage_pressAnyKey, titleParticle, true);
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