#include "game.hpp"

void ParticleGame::handleMenuChange()
{

}

void ParticleGame::update(sf::RenderWindow& renderWindow)
{
	particleRenderer->render();

	switch (currentMenu)
	{
	case MenuType::MAIN_MENU:
		currentMenu = mainMenu->tick();
		menuChange = currentMenu != MenuType::MAIN_MENU;
		break;
	case MenuType::SANDBOX_MENU:
		currentMenu = sandboxMenu->tick();
		menuChange = currentMenu != MenuType::SANDBOX_MENU;
		break;
	}

	if (menuChange)
	{
		shakeEffect->setShakeLength(10);
		//menuChangeSound.play();
	}

	if (!particleWorld->isFrozen())
	{
		for (int i = 0; i < simSpeed; ++i)
		{
			particleWorld->update();
		}
	}

	if (windowInFocus)
	{
		float translateSpeed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 30.0f : 10.0f;
		float zoomSpeed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 1.1f : 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			particleRenderer->translate(sf::Vector2f(0.0f * translateSpeed, -1.0f * translateSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			particleRenderer->translate(sf::Vector2f(0.0f * translateSpeed, 1.0f * translateSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			particleRenderer->translate(sf::Vector2f(-1.0f * translateSpeed, 0.0f * translateSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			particleRenderer->translate(sf::Vector2f(1.0f * translateSpeed, 0.0f * translateSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			particleRenderer->zoom(1.01 * zoomSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			particleRenderer->zoom(0.99 / zoomSpeed);
		}
	}


	titleBarPanel->draw();
	renderWindow.draw(titleBarText);

	closeButton->draw();

	particleCountText.setString("Particles: " + std::to_string(0));
	renderWindow.draw(particleCountText);

	fpsText.setString("FPS: " + std::to_string(FRAMERATE));
	renderWindow.draw(fpsText);
}