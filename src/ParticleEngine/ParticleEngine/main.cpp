#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

#include "menus/menus.h"

#include "tools/menu/button.h"

const std::string version = "v1.0.0";
const std::string windowTitle = "particle engine " + version;

const unsigned int titleBarHeight = 25;

const sf::Vector2u uiSize(1550, 750);

const sf::Vector2i uiOffsetInital(10, 10);
sf::Vector2i uiOffset = uiOffsetInital;

const unsigned int pixelSize = 2;
const unsigned int rowSize = (uiSize.y - uiOffset.y * 2) / pixelSize - 100 / pixelSize;
const unsigned int colSize = (uiSize.x - uiOffset.x * 2) / pixelSize;

const unsigned int simSpeed = 3;
const unsigned int maxFps = 0;

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	sf::Font baseFont;
	if (!baseFont.loadFromFile("data\\fonts\\alagard.ttf"))
	{
		// error
	}

	SoundEngine::init();
	Menu currentMenu = Menu::Main;

	sf::Text titleBarText;
	titleBarText.setFont(baseFont);

	titleBarText.setCharacterSize(16);
	titleBarText.setString(windowTitle);
	titleBarText.setFillColor(sf::Color(100, 100, 100));
	titleBarText.setPosition(6, 2);

	sf::Text particleCountText;
	particleCountText.setFont(baseFont);
	particleCountText.setCharacterSize(16);
	particleCountText.setString("Particles: 0");
	particleCountText.setFillColor(sf::Color(255, 255, 255));
	particleCountText.setPosition(0, uiSize.y - particleCountText.getGlobalBounds().height - 6);

	sf::Text fpsText;
	fpsText.setFont(baseFont);
	fpsText.setCharacterSize(16);
	fpsText.setString("FPS: 0");
	fpsText.setFillColor(sf::Color(255, 255, 255));
	fpsText.setPosition(0, uiSize.y - fpsText.getGlobalBounds().height - particleCountText.getGlobalBounds().height - 6);

	Button* titleBarPanel = new Button(
		sf::Vector2f(0, 0), sf::Vector2f(uiSize.x, titleBarHeight), sf::Color(20, 20, 20),
		sf::Color(0, 0, 0), "", 0, baseFont,
		"titleBarPanel"
	);

	Button* closeButton = new Button(
		sf::Vector2f(uiSize.x - titleBarHeight, 0), sf::Vector2f(titleBarHeight, titleBarHeight), sf::Color(100, 20, 20),
		sf::Color(0, 0, 0), "", 0, baseFont,
		"closeButton"
	);

	std::vector<Button*> sandboxMenu_buttons = sandboxMenu_getButtons(rowSize, pixelSize, titleBarHeight, uiOffset, baseFont);
	ParticleWorld::ParticleInstance sandbox_drawingParticle;
	sandbox_drawingParticle.material = ParticleWorld::Material::Sand;
	sandbox_drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
	sandbox_drawingParticle.physicsType = ParticleWorld::PhysicsType::Sand;

	std::vector<sf::Music*> mainMenu_music = mainMenu_getMusic();

	renderWindow.setFramerateLimit(maxFps);

	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);

	int menuTransitionCountdown = 0;

	bool clickedOnTitlebar = false;
	bool exitProgram = false;

	particleWorld->freeze();

	bool menuChange = true;
	bool windowInFocus = true;

	std::string fpsString = "FPS: 0";

	sf::VertexArray quadClump(sf::Quads);
	quadClump.resize(particleWorld->getColSize() * particleWorld->getRowSize() * 4);

	sf::Sound menuChangeSound;

	const std::string menuChangeSoundPaths[] = {
		"data\\sounds\\menu_impact\\menu_impact1.ogg",
		"data\\sounds\\menu_impact\\menu_impact2.ogg",
		"data\\sounds\\menu_impact\\menu_impact3.ogg",
		"data\\sounds\\menu_impact\\menu_impact4.ogg",
		"data\\sounds\\menu_impact\\menu_impact5.ogg",
		"data\\sounds\\menu_impact\\menu_impact6.ogg",
		"data\\sounds\\menu_impact\\menu_impact7.ogg"
	};

	std::vector<sf::SoundBuffer> menuChangeSounds;

	sf::SoundBuffer temp;
	for (int i = 0; i < 7; i++)
	{
		if (!temp.loadFromFile(menuChangeSoundPaths[i]))
		{
			// error
		}
		menuChangeSounds.push_back(temp);
	}
	std::uniform_int_distribution<int> shakeDist(0, 10);
	std::string hoveredButtonId = "";

	while (renderWindow.isOpen())
	{
		int shakeCountdown = particleWorld->getShakeCountdown();
		if (particleWorld->getShakeCountdown() > 0)
		{
			uiOffset.x = uiOffsetInital.x * shakeDist(gen) * std::sqrt(shakeCountdown) / 10.0f;
			uiOffset.y = uiOffsetInital.y * shakeDist(gen) * std::sqrt(shakeCountdown) / 10.0f;
			particleWorld->setShakeCountdown(shakeCountdown - 1);

			if (shakeCountdown == 0)
			{
				uiOffset.x = uiOffsetInital.x;
				uiOffset.y = uiOffsetInital.y;
			}
		}

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

		// handle close button
		hoveredButtonId = closeButton->handleClick(localMousePos.x, localMousePos.y);

		if (mouseDown && !titleBarPanel->isMouseHover(localMousePos.x, localMousePos.y))
		{
			clickedOnTitlebar = false;
		}

		if (mouseDown)
		{
			if (hoveredButtonId != "")
			{
				exitProgram = true;
			}
		}
		else
		{
			clickedOnTitlebar = true;
		}

		if (mouseDown && titleBarPanel->isMouseHover(localMousePos.x, localMousePos.y) && clickedOnTitlebar)
		{
			renderWindow.setPosition(
				sf::Vector2i(
					windowInitialGlobalPos.x + globalMousePos.x - mouseInitialGlobalPos.x,
					windowInitialGlobalPos.y + globalMousePos.y - mouseInitialGlobalPos.y
				)
			);
			// skip particle processing to improve dragging performance
			continue;
		}
		else
		{
			mouseInitialGlobalPos = globalMousePos;
			windowInitialGlobalPos = windowGlobalPosition;
		}

		renderWindow.clear();

		if (menuTransitionCountdown < 1)
		{
			switch (currentMenu)
			{
			case Menu::Main:
				currentMenu = mainMenu_run(renderWindow, particleWorld, mainMenu_music, menuChange);
				if (currentMenu != Menu::Main)
				{
					menuChange = true;
					menuTransitionCountdown = 0;
				}
				else
				{
					menuChange = false;
				}
				break;
			case Menu::Sandbox:
				currentMenu = sandboxMenu_run(renderWindow, pixelSize, particleWorld, sandboxMenu_buttons, sandbox_drawingParticle, localMousePos, uiOffset, titleBarHeight);
				if (currentMenu != Menu::Sandbox)
				{
					menuChange = true;
					menuTransitionCountdown = 0;
				}
				else
				{
					menuChange = false;
				}
				break;
			}
		}
		else
		{
			menuTransitionCountdown--;
		}

		if (menuChange)
		{
			std::uniform_int_distribution<int> dist(0, menuChangeSounds.size() - 1);
			std::random_device rd;
			std::mt19937 gen(rd());

			menuChangeSound.setBuffer(menuChangeSounds[dist(gen)]);
			menuChangeSound.play();
		}

		if (!particleWorld->isFrozen())
		{
			for (int i = 0; i < simSpeed; ++i)
			{
				updateParticleWorld(particleWorld);
			}
		}

		int particleCount = renderParticleWorld(particleWorld, renderWindow, quadClump, uiOffset, titleBarHeight, pixelSize);

		titleBarPanel->draw(renderWindow);
		renderWindow.draw(titleBarText);

		closeButton->draw(renderWindow);

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

	for (Button* button : sandboxMenu_buttons) {
		delete button;
	}

	for (sf::Music* music : mainMenu_music) {
		delete music;
	}

	delete titleBarPanel;
	delete closeButton;

	delete particleWorld;

	return 0;
}