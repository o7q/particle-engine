#pragma once

#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.hpp"
#include "particle/particle_renderer.hpp"

#include "menu/controls/button.hpp"

enum MenuType {
	MAIN_MENU,
	SANDBOX_MENU
};

class Menu {
public:
	Menu(sf::RenderWindow&);
	~Menu();

	virtual MenuType tick();

	void setButtons(std::vector<Button*>);

	virtual std::vector<Button*> getDefaultButtons(sf::RenderWindow&, sf::Font&, sf::Vector2i, sf::Vector2u);

protected:
	bool init();
	bool update();

	sf::Vector2i LOCAL_MOUSE_POSITION;
	std::string CLICKED_BUTTON_ID = "";
	bool MOUSE_DOWN = false;

	sf::Vector2i uiOffset;
	std::vector<Button*> buttons;

private:
	sf::RenderWindow& renderWindow;

	bool doInit = true;
};

class MainMenu : public Menu {
public:
	MainMenu(sf::RenderWindow&, ParticleWorld*);

	MenuType tick() override;

private:
	ParticleWorld* particleWorld;
};

class SandboxMenu : public Menu {
public:
	SandboxMenu(sf::RenderWindow&, ParticleWorld*, ParticleRenderer*);

	MenuType tick() override;

	std::vector<Button*> getDefaultButtons(sf::RenderWindow&, sf::Font&, sf::Vector2i, sf::Vector2u) override;

private:
	ParticleWorld* particleWorld;
	ParticleRenderer* particleRenderer;

	ParticleWorld::Particle drawingParticle;
};