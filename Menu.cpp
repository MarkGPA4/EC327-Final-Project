#include "Menu.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

Menu::Menu(int width, int height) 
{
	windowW = width;
	windowH = height;
	float scale = .2f;

	for(int i = 0; i < 5; i++)
	{
		textures.push_back(new sf::Texture());
		sprites.push_back(new sf::Sprite());
	}	

    if(!textures[0]->loadFromFile("menu_arrow.png"))
    {
    	throw "Image not found";
    }


    if(!textures[1]->loadFromFile("menu_add.png"))
    {
    	throw "Image not found";
    }

    if(!textures[2]->loadFromFile("menu_completed.png"))
    {
    	throw "Image not found";
    }

    if(!textures[3]->loadFromFile("menu_delete.png"))
    {
    	throw "Image not found";
    }


    if(!textures[4]->loadFromFile("menu_notcom.png"))
    {
    	throw "Image not found";
    }

    for(int i = 0; i < 5; i++)
    {
    	sprites[i]->setTexture(*textures[i], true);
    	sprites[i]->setOrigin(textures[i]->getSize().x/2, textures[i]->getSize().y/2);
    	sprites[i]->setScale(.2f, .2f);
    }

    std::cout << textures[0]->getSize().x << std::endl;
    sprites[0]->setPosition(textures[0]->getSize().x * scale, textures[0]->getSize().x * scale);
    
    sprites[1]->setPosition(windowW / 4, windowH / 4);
    sprites[2]->setPosition(3 * windowW / 4, windowH / 4);
    sprites[3]->setPosition(windowW / 4, 3 * windowH / 4);
    sprites[4]->setPosition(3 * windowW / 4, 3 * windowH / 4);

}

void Menu::toggleDisplay()
{
	shown = !shown;
	if(shown)
		sprites[0]->setRotation(-90);
	else
		sprites[0]->setRotation(0);
}

bool Menu::isClicked(sf::Sprite s, int x, int y)
{
	int xLoc = s.getPosition().x - s.getOrigin().x * s.getScale().x;
	int yLoc = s.getPosition().y - s.getOrigin().y * s.getScale().y;
	int width = s.getTexture()->getSize().x * s.getScale().x;
	int height = s.getTexture()->getSize().y * s.getScale().y;

	if(x > xLoc && x < xLoc + width && y > yLoc && y < yLoc + height)
		return true;
	return false;
}

bool Menu::isShown() {
	return shown;
}

int Menu::checkInput(int x, int y)
{
	if(isClicked(*sprites[0], x, y))
	{
		toggleDisplay();
	}	
	else if(isClicked(*sprites[2], x, y))
	{
		//Check clicked
		return 1;
	}
	else if(isClicked(*sprites[4], x, y))
	{
		//X clicked
		return 2;
	}


	return -1;
}

void Menu::draw(sf::RenderWindow& window)
{

	sf::Color rectColor(0,0,0,255 * .8);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(windowW, windowH));
	rectangle.setFillColor(rectColor);
	if(shown)
	{
		window.draw(rectangle);
		for(int i = 1; i < sprites.size(); i++)
			window.draw(*sprites[i]);
	}
	window.draw(*sprites[0]);
}