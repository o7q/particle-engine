#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "headers/tools/menu/button.h"
#include "menus/menus.h"

#include "particle/particle_sounds.h"

const std::string version = "v1.0.0";
const std::string windowTitle = "particle engine " + version;

const unsigned int titleBarSize = 25;

const sf::Vector2u uiSize(1550, 750);
const sf::Vector2u uiOffset(10, 10 + titleBarSize);

const unsigned int pixelSize = 2;
const unsigned int rowSize = 300;
const unsigned int colSize = uiSize.x / pixelSize - uiOffset.x;

const unsigned int simSpeed = 5;

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	sf::Font baseFont;
	if (!baseFont.loadFromFile("data\\fonts\\alagard.ttf"))
	{
		// error
	}

	SoundEngine::init();
	Menu currentMenu = Menu::Main;

	ParticleWorld::ParticleInstance test;
	test.material = ParticleWorld::Material::Water;
	test.materialType = ParticleWorld::MaterialType::Liquid;
	test.physicsType = ParticleWorld::PhysicsType::Water;
	particleWorld->setParticle(10, 10, test);
	particleWorld->setParticle(9, 10, test);

	sf::Text titleBarText;

	titleBarText.setFont(baseFont);
	titleBarText.setCharacterSize(16);
	titleBarText.setString(windowTitle);
	titleBarText.setFillColor(sf::Color(100, 100, 100));
	titleBarText.setPosition(6, 2);

	Button* titleBarPanel = new Button(
		sf::Vector2f(0, 0), sf::Vector2f(uiSize.x, titleBarSize), sf::Color(20, 20, 20),
		sf::Color(0, 0, 0), "", 0, baseFont,
		"titleBarPanel"
	);

	Button* closeButton = new Button(
		sf::Vector2f(uiSize.x - titleBarSize, 0), sf::Vector2f(titleBarSize, titleBarSize), sf::Color(100, 20, 20),
		sf::Color(0, 0, 0), "", 0, baseFont,
		"closeButton"
	);

	std::vector<Button*> sandboxMenu_buttons = sandboxMenu_getButtons(rowSize, pixelSize, uiOffset.x, uiOffset.y, baseFont);
	ParticleWorld::ParticleInstance sandbox_drawingParticle;
	sandbox_drawingParticle.material = ParticleWorld::Material::Sand;
	sandbox_drawingParticle.materialType = ParticleWorld::MaterialType::Solid;

	std::vector<sf::Music*> mainMenu_music = mainMenu_getMusic();

	renderWindow.setFramerateLimit(60);

	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);

	bool clickedOnTitlebar = false;
	bool exitProgram = false;

	int menuTransitionCountdown = 0;

	particleWorld->freeze();

	bool menuChange = true;
	bool windowInFocus = true;

	std::string hoveredButtonId = "";
	while (renderWindow.isOpen())
	{
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
				currentMenu = sandboxMenu_run(renderWindow, pixelSize, particleWorld, sandboxMenu_buttons, sandbox_drawingParticle, localMousePos, uiOffset);
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

		if (!particleWorld->isFrozen())
		{
			for (int i = 0; i < simSpeed; ++i)
			{
				updateParticleWorld(particleWorld);
			}
		}

		renderParticleWorld(particleWorld, renderWindow, uiOffset.x, uiOffset.y, pixelSize);

		titleBarPanel->draw(renderWindow);
		closeButton->draw(renderWindow);
		renderWindow.draw(titleBarText);

		renderWindow.display();
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