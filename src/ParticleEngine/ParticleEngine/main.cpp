#include <iostream>

#include <SFML/Graphics.hpp>

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

const bool useDevPaths = false;

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	sf::Font baseFont;
	std::string fontPaths[] = {
		"data\\fonts\\alagard.ttf",
		"..\\alagard.ttf"
	};

	std::string baseFontPath = useDevPaths ? "assets\\alagard.ttf" : "data\\fonts\\alagard.ttf";

	if (!baseFont.loadFromFile(baseFontPath))
	{
		// error
	}

	Menu currentMenu = Menu::Sandbox;

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

	std::vector<Button*> sandbox_buttons = sandbox_getButtons(rowSize, pixelSize, uiOffset.x, uiOffset.y, baseFont);
	ParticleWorld::ParticleInstance sandbox_drawingParticle;
	sandbox_drawingParticle.material = ParticleWorld::Material::Sand;
	sandbox_drawingParticle.materialType = ParticleWorld::MaterialType::Solid;

	renderWindow.setFramerateLimit(0);

	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);

	bool clickedOnTitlebar = false;
	bool exitProgram = false;

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
			continue;
		}
		else
		{
			mouseInitialGlobalPos = globalMousePos;
			windowInitialGlobalPos = windowGlobalPosition;
		}

		renderWindow.clear();

		for (int i = 0; i < simSpeed; i++)
		{
			updateParticleWorld(particleWorld);
		}

		renderParticleWorld(particleWorld, renderWindow, uiOffset.x, uiOffset.y, pixelSize);

		switch (currentMenu)
		{
		case Menu::Sandbox:
			currentMenu = sandbox_run(renderWindow, pixelSize, particleWorld, sandbox_buttons, sandbox_drawingParticle, localMousePos, uiOffset);
			break;
		}

		titleBarPanel->draw(renderWindow);
		closeButton->draw(renderWindow);
		renderWindow.draw(titleBarText);

		renderWindow.display();
	}

	delete particleWorld;

	return 0;
}