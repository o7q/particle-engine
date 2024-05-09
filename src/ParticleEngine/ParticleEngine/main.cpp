#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

#include "init.h"

#include "menu/menu.h"

#include "menu/controls/button.h"

#include "effects/effects.h"

#include "tools/random.h"
#include "tools/logger.h"

const std::string version = "v1.0.0";
const std::string windowTitle = "particle engine " + version;

const unsigned int titleBarHeight = 25; // in pixels

const sf::Vector2u uiSize(1550, 750);

const sf::Vector2i uiOffset(10, 10 + titleBarHeight);

const unsigned int rowSize = 300; // amount of particle pixels for row
const unsigned int colSize = 400; // amount of particle pixels for column

const unsigned int simSpeed = 3; // how many physics steps will be performed each frame
const unsigned int maxFps = 0; // max fps (set to 0 for no limit, as defined in: sf::Window::setFrameRateLimit())

int main()
{
	// init render window
	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	renderWindow.setFramerateLimit(maxFps);

	sf::Vector2i renderWindowUserPosition(renderWindow.getPosition());

	// init particle world and freeze physics
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);
	particleWorld->freeze();

	sf::Vector2u particleRendererSize(uiSize.x - uiOffset.x * 2, uiSize.y - 100);
	ParticleRenderer* particleRenderer = new ParticleRenderer(particleRendererSize, renderWindow);
	particleRenderer->setUIOffset(uiOffset);

	// init random
	Random::init();
	// init sound engine
	SoundEngine::init();

	// specify startup menu
	MenuType currentMenu = MenuType::MAIN_MENU;

	// get base font
	sf::Font baseFont = Init::getBaseFont();

	MainMenu* mainMenu = new MainMenu(renderWindow, particleWorld);

	SandboxMenu* sandboxMenu = new SandboxMenu(renderWindow, particleWorld, particleRenderer);
	std::vector<Button*> sandboxMenu_buttons = sandboxMenu->getDefaultButtons(renderWindow, baseFont, uiOffset, particleRendererSize);
	sandboxMenu->setButtons(sandboxMenu_buttons);

	// configure main overlay texts
	sf::Text titleBarText = Init::configureText(baseFont, windowTitle, 16, sf::Color(100, 100, 100), sf::Vector2f(6, 2));
	sf::Text particleCountText = Init::configureText(baseFont, "Particles: 0", 16, sf::Color(255, 255, 255), sf::Vector2f(0, uiSize.y - 17));
	sf::Text fpsText = Init::configureText(baseFont, "FPS: 0", 16, sf::Color(255, 255, 255), sf::Vector2f(0, uiSize.y - 28));
	// default fpsString value
	std::string fpsString = "FPS: 0";

	// configure main buttons
	Button* titleBarPanel = new Button(renderWindow, baseFont);
	titleBarPanel->setSize(sf::Vector2f(uiSize.x, titleBarHeight));
	titleBarPanel->setColor(sf::Color(20, 20, 20));
	titleBarPanel->setHighlightMode(Button::HighlightMode::NONE);

	Button* closeButton = new Button(renderWindow, baseFont);
	closeButton->setPosition(sf::Vector2f(uiSize.x - titleBarHeight, 0));
	closeButton->setSize(sf::Vector2f(titleBarHeight, titleBarHeight));
	closeButton->setColor(sf::Color(100, 20, 20));

	// create the set for the unlocked material buttons, this will store the ids for unlocked buttons
	std::unordered_set<std::string> sandbox_unlockedMaterialButtons;

	// init menu position vectors
	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);
	// distribution for min/max shake
	std::uniform_int_distribution<int> shakeDist(0, 10);

	// global vars that are used by the window
	bool exitProgram = false;
	// menuChange will be changed if a menuChange has happened, it should only ever be true for 1 frame
	bool menuChange = true;
	bool clickedOnTitlebar = false;
	bool windowInFocus = true;

	ShakeEffect* shakeEffect = new ShakeEffect(renderWindow, particleWorld, renderWindowUserPosition);

	while (renderWindow.isOpen())
	{
		shakeEffect->tick();

		// start clock for fps measurer
		clock_t start = clock();

		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || exitProgram)
			{
				renderWindow.close();
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				windowInFocus = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				windowInFocus = false;
			}
		}

		sf::Vector2i localMousePos = sf::Mouse::getPosition(renderWindow);
		sf::Vector2i globalMousePos = sf::Mouse::getPosition();
		sf::Vector2i windowGlobalPosition = renderWindow.getPosition();

		bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (mouseDown && !titleBarPanel->isMouseHover())
		{
			clickedOnTitlebar = false;
		}

		if (!mouseDown)
		{
			clickedOnTitlebar = true;
		}

		if (closeButton->hasMouseClicked())
		{
			exitProgram = true;
		}

		if (mouseDown && titleBarPanel->isMouseHover() && clickedOnTitlebar)
		{
			renderWindow.setPosition(
				sf::Vector2i(
					windowInitialGlobalPos.x + globalMousePos.x - mouseInitialGlobalPos.x,
					windowInitialGlobalPos.y + globalMousePos.y - mouseInitialGlobalPos.y
				)
			);

			renderWindowUserPosition = renderWindow.getPosition();
			// skip particle processing to improve dragging performance
			continue;
		}
		else
		{
			mouseInitialGlobalPos = globalMousePos;
			windowInitialGlobalPos = windowGlobalPosition;
		}

		renderWindow.clear();

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
				updateParticleWorld(particleWorld, particleRenderer);
			}
		}

		if (windowInFocus)
		{
			float translateSpeed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 5.0f : 1.0f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				particleRenderer->translate(ParticleRenderer::Direction::UP, translateSpeed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				particleRenderer->translate(ParticleRenderer::Direction::DOWN, translateSpeed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				particleRenderer->translate(ParticleRenderer::Direction::LEFT, translateSpeed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				particleRenderer->translate(ParticleRenderer::Direction::RIGHT, translateSpeed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				particleRenderer->zoom(0.1f * translateSpeed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				particleRenderer->zoom(-0.1f * translateSpeed);
			}
		}

		int particleCount = particleRenderer->render(particleWorld);

		titleBarPanel->draw();
		renderWindow.draw(titleBarText);

		closeButton->draw();

		particleCountText.setString("Particles: " + std::to_string(particleCount));
		renderWindow.draw(particleCountText);

		fpsText.setString(fpsString);
		renderWindow.draw(fpsText);

		renderWindow.display();

		clock_t end = clock();
		double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
		int fps = static_cast<int>(std::round(1 / elapsed_time));
		fpsString = "FPS: " + std::to_string(fps);
	}

	delete mainMenu;
	delete sandboxMenu;

	delete titleBarPanel;
	delete closeButton;

	delete particleWorld;
	delete particleRenderer;

	return 0;
}