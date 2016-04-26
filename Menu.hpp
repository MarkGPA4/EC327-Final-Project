#ifndef Menu_HPP
#define Menu_HPP
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace std;

class Menu
{
	public:

		Menu(int, int);
		void draw(sf::RenderWindow&);
		void toggleDisplay();
		int checkInput(int x, int y);
		bool isShown();



	private:
		bool shown = false;
		int windowW;
		int windowH;

		vector<sf::Texture*> textures;
		vector<sf::Sprite*> sprites;
		bool isClicked(sf::Sprite, int, int);

};

#endif