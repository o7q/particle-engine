#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>

std::vector<sf::Music*> mainMenu_getMusic()
{
	std::vector<sf::Music*> mainMenu_music;

	sf::Music* ambient_wind = new sf::Music();
	if (!ambient_wind->openFromFile("data\\music\\ambient\\ambient_wind.ogg"))
	{
		// error
	}
	ambient_wind->setLoop(true);

	sf::Music* ambient_swamp = new sf::Music();
	if (!ambient_swamp->openFromFile("data\\music\\ambient\\ambient_swamp.ogg"))
	{
		// error
	}
	ambient_swamp->setLoop(true);

	mainMenu_music.push_back(ambient_wind);
	mainMenu_music.push_back(ambient_swamp);

	return mainMenu_music;
}