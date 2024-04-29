#include <iostream>
#include <chrono>
#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "particle/particle_sounds.h"

#include "init.h"

#include "menus/menus.h"

#include "tools/menu/button.h"

const std::string version = "v1.0.0";
const std::string windowTitle = "particle engine " + version;

const unsigned int titleBarHeight = 25; // in pixels

const sf::Vector2u uiSize(1550, 750);

const sf::Vector2i uiOffsetInital(10, 10);
sf::Vector2i uiOffset = uiOffsetInital;

const unsigned int pixelSize = 2; // size of each pixel
const unsigned int rowSize = (uiSize.y - uiOffset.y * 2) / pixelSize - 100 / pixelSize;
const unsigned int colSize = (uiSize.x - uiOffset.x * 2) / pixelSize;

const unsigned int simSpeed = 3; // how many physics steps will be performed each frame
const unsigned int maxFps = 0; // max fps (set to 0 for no limit, as defined in: sf::Window::setFrameRateLimit())

int main()
{
	// init render window
	sf::RenderWindow renderWindow(sf::VideoMode(uiSize.x, uiSize.y), windowTitle, sf::Style::None);
	renderWindow.setFramerateLimit(maxFps);

	// init particle world and freeze physics
	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);
	particleWorld->freeze();

	// pre-initialize the VertexArray for the particle renderer
	sf::VertexArray quadClump(sf::Quads);
	quadClump.resize(particleWorld->getColSize() * particleWorld->getRowSize() * 4); // * 4 for each uint8 value (a, r, g, b)

	// init sound engine
	SoundEngine::init();

	// specify startup menu
	Menu currentMenu = Menu::Main;

	// init rand
	std::random_device rd;
	std::mt19937 gen(rd());

	// get base font
	sf::Font baseFont = Init::getBaseFont();

	// configure main overlay texts
	sf::Text titleBarText = Init::configureText(baseFont, windowTitle, 16, sf::Color(100, 100, 100), sf::Vector2f(6, 2));
	sf::Text particleCountText = Init::configureText(baseFont, "Particles: 0", 16, sf::Color(255, 255, 255), sf::Vector2f(0, uiSize.y - 17));
	sf::Text fpsText = Init::configureText(baseFont, "FPS: 0", 16, sf::Color(255, 255, 255), sf::Vector2f(0, uiSize.y - 28));
	// default fpsString value
	std::string fpsString = "FPS: 0";

	// configure main buttons
	Button* titleBarPanel = new Button(sf::Vector2f(0, 0), sf::Vector2f(uiSize.x, titleBarHeight), sf::Color(20, 20, 20), sf::Color(0, 0, 0), "", 0, baseFont, "titleBarPanel", "ui");
	Button* closeButton = new Button(sf::Vector2f(uiSize.x - titleBarHeight, 0), sf::Vector2f(titleBarHeight, titleBarHeight), sf::Color(100, 20, 20), sf::Color(0, 0, 0), "", 0, baseFont, "closeButton", "ui");

	// get the music for the main menu
	std::vector<sf::Music*> mainMenu_music = mainMenu_getMusic();

	// define and get the buttons for the sandbox
	std::vector<Button*> sandboxMenu_buttons = sandboxMenu_getButtons(rowSize, pixelSize, titleBarHeight, uiOffset, baseFont);
	// initialize the drawingParticle/tool
	ParticleWorld::DrawingParticle sandbox_drawingParticle;
	// create the set for the unlocked material buttons, this will store the ids for unlocked buttons
	std::unordered_set<std::string> sandbox_unlockedMaterialButtons;

	// init menu position vectors
	sf::Vector2i mouseInitialGlobalPos(0, 0);
	sf::Vector2i windowInitialGlobalPos(0, 0);
	// distribution for min/max shake
	std::uniform_int_distribution<int> shakeDist(0, 10);
	sf::Vector2i shakeInitialPos(renderWindow.getPosition().x, renderWindow.getPosition().y);

	// this will be used to create a delay between menu changes
	int menuTransitionCountdown = 0;

	// global vars that are used by the window
	bool exitProgram = false;
	// menuChange will be changed if a menuChange has happened, it should only ever be true for 1 frame
	bool menuChange = true;
	bool clickedOnTitlebar = false;
	bool windowInFocus = true;

	// the current hoveredButtonId in the main window
	std::string hoveredButtonId = "";
	//

	// menu_impact sound loader
	// sound that will play when the menu changes
	sf::Sound menuChangeSound;

	// read the menu change sounds (menu_impact)
	const std::string menuChangeSoundPaths[] = {
		"data\\sounds\\menu_impact\\menu_impact1.ogg",
		"data\\sounds\\menu_impact\\menu_impact2.ogg",
		"data\\sounds\\menu_impact\\menu_impact3.ogg",
		"data\\sounds\\menu_impact\\menu_impact4.ogg",
		"data\\sounds\\menu_impact\\menu_impact5.ogg",
		"data\\sounds\\menu_impact\\menu_impact6.ogg",
		"data\\sounds\\menu_impact\\menu_impact7.ogg"
	};

	// initialize buffer for menu_impacts
	std::vector<sf::SoundBuffer> menuChangeSounds;

	// load sounds into the buffer
	sf::SoundBuffer temp;
	for (int i = 0; i < 7; i++)
	{
		if (!temp.loadFromFile(menuChangeSoundPaths[i]))
		{
			// error
		}
		menuChangeSounds.push_back(temp);
	}
	//

	while (renderWindow.isOpen())
	{
		// start clock for fps measurer
		clock_t start = clock();

		int shakeCountdown = particleWorld->getShakeCountdown();
		if (particleWorld->getShakeCountdown() > 0)
		{
			renderWindow.setPosition(
				sf::Vector2i(
					shakeInitialPos.x + 10 * shakeDist(gen) * std::sqrt(shakeCountdown) / 10.0f,
					shakeInitialPos.y + 10 * shakeDist(gen) * std::sqrt(shakeCountdown) / 10.0f
				)
			);

			particleWorld->setShakeCountdown(shakeCountdown - 1);

			if (shakeCountdown <= 1)
			{
				renderWindow.setPosition(shakeInitialPos);
			}
		}

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
			if (hoveredButtonId == "closeButton")
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

			shakeInitialPos = renderWindow.getPosition();
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
				// the hideous mass (enjoy! ^w^)
				currentMenu = sandboxMenu_run(
					renderWindow,
					pixelSize,
					particleWorld,
					sandboxMenu_buttons,
					sandbox_drawingParticle,
					localMousePos,
					uiOffset,
					titleBarHeight,
					sandbox_unlockedMaterialButtons
				);
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
			std::uniform_int_distribution<int> menuChangeSoundsDist(0, menuChangeSounds.size() - 1);

			menuChangeSound.setBuffer(menuChangeSounds[menuChangeSoundsDist(gen)]);
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