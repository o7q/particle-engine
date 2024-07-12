#pragma once

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.hpp"
#include "particle/particle_renderer.hpp"
#include "particle/particle_sounds.hpp"

#include "init.hpp"

#include "menu/menu.hpp"

#include "menu/controls/button.hpp"

#include "effects/effects.hpp"

#include "tools/random.hpp"
#include "tools/logger.hpp"

class ParticleGame {
public:
	void update(sf::RenderWindow&);

	const std::string VERSION = "v1.0.0";
private:
	void handleMenuChange();

	int FRAMERATE = 0;

	sf::Vector2u uiSize = sf::Vector2u(1550, 750);

	ParticleWorld* particleWorld;
	ParticleRenderer* particleRenderer;

	MainMenu* mainMenu;
	SandboxMenu* sandboxMenu;

	sf::Font baseFont;

	MenuType currentMenu = MenuType::MAIN_MENU;

	unsigned int simulationSpeed = 3;
};

class GameWindow {
public:

	void init();
	void setWindowTitle(std::string);

	void run();

private:

	Button* titlebarPanel;
	Button* closeButton;

	std::string windowTitle = "particle engine";

	sf::RenderWindow* renderWindow;
	ParticleGame* particleGame;

	bool clickedOnTitlebar = false;

	bool shouldExit = false;

	bool MOUSE_DOWN = false;
	bool WINDOW_IN_FOCUS = false;
	int FRAMERATE = 0;

	sf::Vector2i& LOCAL_MOUSE_POS;
	sf::Vector2i& GLOBAL_MOUSE_POS;
	sf::Vector2i& WINDOW_GLOBAL_POS;

	sf::Vector2i MOUSE_INITIAL_GLOBAL_POS;
	sf::Vector2i WINDOW_INITIAL_GLOBAL_POS;
	sf::Vector2i WINDOW_USER_POS;
};