#include "menu/menu.h"

#include "world/world_generator.h"

#include "tools/random.h"
#include "tools/logger.h"

MainMenu::MainMenu(sf::RenderWindow& renderWindow, ParticleWorld* particleWorld) : Menu(renderWindow), particleWorld(particleWorld)
{

}

MenuType MainMenu::tick()
{
	if (init())
	{
		sf::Image titleImage;
		if (!titleImage.loadFromFile("data\\objects\\menu\\title.png"))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load menuTitle!");
		}
		sf::Image titleImage_pressAnyKey;
		if (!titleImage_pressAnyKey.loadFromFile("data\\objects\\menu\\title_press_any_key.png"))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load menuTitlePressAnyKey!");
		}

		int random_world = Random::genInt(0, 1);

		ParticleWorld::ParticleInstance titleParticle;
		ParticleWorld::ParticleInstance subTitleParticle;

		switch (random_world)
		{
		case 0: // 0 = ocean
			generateWorld(particleWorld, WorldType::Ocean);
			titleParticle.material = ParticleWorld::Material::Fire;
			titleParticle.materialType = ParticleWorld::MaterialType::Liquid;
			titleParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			//mainMenu_music[0]->play();
			break;
		case 1: // 1 = swamp
			generateWorld(particleWorld, WorldType::Swamp);
			titleParticle.material = ParticleWorld::Material::Fire;
			titleParticle.materialType = ParticleWorld::MaterialType::Liquid;
			titleParticle.physicsType = ParticleWorld::PhysicsType::Fire;
			//mainMenu_music[1]->play();
			break;
		}

		particleWorld->imageToParticles(particleWorld->getRowSize() / 2 - particleWorld->getRowSize() / 4, particleWorld->getColSize() / 2, titleImage, titleParticle, true);
		particleWorld->imageToParticles(particleWorld->getRowSize() / 2, particleWorld->getColSize() / 2, titleImage_pressAnyKey, titleParticle, true);
	}

	if (update())
	{
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
			//for (int i = 0; i < mainMenu_music.size(); ++i)
			//{
			//	mainMenu_music[i]->stop();
			//}

			return MenuType::SANDBOX_MENU;
		}
	}

	return MenuType::MAIN_MENU;
}