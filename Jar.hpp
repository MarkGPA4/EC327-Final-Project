#ifndef JAR_HPP
#define JAR_HPP
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>

class Jar 
{
	public:

		virtual void add() = 0;
		virtual void draw(sf::RenderWindow&) = 0;
		virtual void update() = 0;
		virtual void move(int,int) = 0;
		virtual void setScale(float) = 0;
		virtual void incAnim() = 0;
		virtual void decAnim() = 0;
		virtual bool isAnim() = 0;
		virtual std::string getTitle() = 0;
		virtual int getTimesWorkedOn() = 0;
		virtual std::string getDescription() = 0;

};

#endif