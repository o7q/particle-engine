#include "game.hpp"

void GameWindow::init()
{
	Button* titleBarPanel = new Button(*renderWindow, baseFont);
	titleBarPanel->setSize(sf::Vector2f(uiSize.x, titleBarHeight));
	titleBarPanel->setColor(sf::Color(20, 20, 20));
	titleBarPanel->setHighlightMode(Button::HighlightMode::NONE);

	Button* closeButton = new Button(renderWindow, baseFont);
	closeButton->setPosition(sf::Vector2f(uiSize.x - titleBarHeight, 0));
	closeButton->setSize(sf::Vector2f(titleBarHeight, titleBarHeight));
	closeButton->setColor(sf::Color(100, 20, 20));

	renderWindow = new sf::RenderWindow(sf::VideoMode(uiSize.x, uiSize.y), "", sf::Style::None);
	particleGame = new ParticleGame();
}

void GameWindow::setWindowTitle(std::string windowTitle)
{
	this->windowTitle = windowTitle;
	renderWindow->setTitle(windowTitle);
}

void GameWindow::run()
{
	while (renderWindow->isOpen())
	{
		clock_t start = clock();

		renderWindow->clear();

		LOCAL_MOUSE_POS = sf::Mouse::getPosition(*renderWindow);
		GLOBAL_MOUSE_POS = sf::Mouse::getPosition();
		WINDOW_GLOBAL_POS = renderWindow->getPosition();

		MOUSE_DOWN = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		sf::Event event;
		while ((*renderWindow).pollEvent(event))
		{
			if (event.type == sf::Event::Closed || shouldExit)
			{
				renderWindow->close();
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				WINDOW_IN_FOCUS = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				WINDOW_IN_FOCUS = false;
			}
		}

		if (closeButton->hasMouseClicked())
		{
			shouldExit = true;
		}

		if (MOUSE_DOWN && !titlebarPanel->isMouseHover())
		{
			clickedOnTitlebar = false;
		}

		if (!MOUSE_DOWN)
		{
			clickedOnTitlebar = true;
		}

		if (MOUSE_DOWN && titlebarPanel->isMouseHover() && clickedOnTitlebar)
		{
			renderWindow->setPosition(
				sf::Vector2i(
					WINDOW_INITIAL_GLOBAL_POS.x + GLOBAL_MOUSE_POS.x - MOUSE_INITIAL_GLOBAL_POS.x,
					WINDOW_INITIAL_GLOBAL_POS.y + GLOBAL_MOUSE_POS.y - MOUSE_INITIAL_GLOBAL_POS.y
				)
			);

			WINDOW_USER_POS = renderWindow->getPosition();
			// skip particle processing to improve dragging performance
		}
		else
		{
			MOUSE_INITIAL_GLOBAL_POS = GLOBAL_MOUSE_POS;
			WINDOW_INITIAL_GLOBAL_POS = WINDOW_GLOBAL_POS;
		}

		particleGame->update(*renderWindow);

		renderWindow->display();

		clock_t end = clock();
		double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
		FRAMERATE = static_cast<int>(std::round(1 / elapsed_time));
	}
}