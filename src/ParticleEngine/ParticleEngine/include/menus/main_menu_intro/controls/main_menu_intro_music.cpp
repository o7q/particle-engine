#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>

std::vector<sf::Music*> mainMenuIntro_getMusic()
{
	std::vector<sf::Music*> mainMenuIntro_music;

	sf::Music* ambient_wind = new sf::Music();
	if (!ambient_wind->openFromFile("data\\sounds\\ambient\\ambient_wind.ogg"))
	{
		// error
	}
	ambient_wind->setLoop(true);

	sf::Music* ambient_swamp = new sf::Music();
	if (!ambient_swamp->openFromFile("data\\sounds\\ambient\\ambient_swamp.ogg"))
	{
		// error
	}
	ambient_swamp->setLoop(true);

	mainMenuIntro_music.push_back(ambient_wind);
	mainMenuIntro_music.push_back(ambient_swamp);

	return mainMenuIntro_music;
}