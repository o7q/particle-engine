#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "headers/tools/menu/button.h"
#include "menus/menus.h"

const std::string version = "v1.0.0";
const std::string windowTitle = "particle engine " + version;

const unsigned int titleBarSize = 25;

const sf::Vector2u uiSize(1550, 750);
const sf::Vector2u uiOffset(10, 10 + titleBarSize);

const unsigned int pixelSize = 2;
const unsigned int rowSize = 300;
const unsigned int colSize = uiSize.x / pixelSize - uiOffset.x;

const unsigned int simSpeed = 3;

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	sf::Font baseFont;
	if (!baseFont.loadFromFile("data\\fonts\\alagard.ttf"))
	{
		// error
	}

	Menu currentMenu = Menu::MainIntro;

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
	ParticleWorld::ParticleInstance sandbox_drawingParticle = particleWorld->getDefaultInstance();
	sandbox_drawingParticle.material = ParticleWorld::Material::Sand;
	sandbox_drawingParticle.materialType = ParticleWorld::MaterialType::Solid;

	std::vector<sf::Music*> mainMenuIntro_music = mainMenuIntro_getMusic();

	renderWindow.setFramerateLimit(0);

	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);

	bool clickedOnTitlebar = false;
	bool exitProgram = false;

	int menuTransitionCountdown = 0;

	particleWorld->freeze();

	//std::cout << static_cast<int>(particleWorld->getParticle(13, 9).color.r);

	bool menuChange = true;

	while (renderWindow.isOpen())
	{
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || exitProgram)
			{
				renderWindow.close();
			}
		}

		sf::Vector2i localMousePos = sf::Mouse::getPosition(renderWindow);
		sf::Vector2i globalMousePos = sf::Mouse::getPosition();
		bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		bool closeButtonHovered = closeButton->isMouseHover(localMousePos.x, localMousePos.y);
		closeButton->highlight(closeButtonHovered);

		sf::Vector2i windowGlobalPosition = renderWindow.getPosition();

		if (mouseDown && !titleBarPanel->isMouseHover(localMousePos.x, localMousePos.y))
		{
			clickedOnTitlebar = false;
		}

		if (mouseDown)
		{
			if (closeButtonHovered)
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
			case Menu::MainIntro:
				currentMenu = mainMenuIntro_run(renderWindow, particleWorld, mainMenuIntro_music, menuChange);
				if (currentMenu != Menu::MainIntro)
				{
					menuChange = true;
					menuTransitionCountdown = 60;
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
					menuTransitionCountdown = 60;
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
			for (int i = 0; i < simSpeed; i++)
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

	for (sf::Music* music : mainMenuIntro_music) {
		delete music;
	}

	delete titleBarPanel;
	delete closeButton;

	delete particleWorld;

	return 0;
}