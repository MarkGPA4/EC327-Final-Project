#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "candyJar.hpp"
#include "SandJar.hpp"
#include "Menu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");

    int WIDTH = window.getSize().x;
    int HEIGHT = window.getSize().y;

    vector<Jar*> jars;
    vector<Jar*> jarsComplete;
    vector<Jar*> jarsNotComplete;

    array<vector<Jar*>*, 3> jarTypes;

    SandJar SJAR(5,WIDTH, HEIGHT, "im jar 1", "look at me");
    SandJar SJAR2(5,WIDTH, HEIGHT, "im jar 2", "look at me");
    SandJar SJAR3(5,WIDTH, HEIGHT, "im jar 3", "look at me");
    SandJar SJAR4(5,WIDTH, HEIGHT, "im jar 4", "look at me");
    SandJar SJAR5(5,WIDTH, HEIGHT, "im jar 5", "look at me");
    SJAR2.move(300, 0);
    SJAR3.move(600, 0);
    SJAR4.move(900, 0);
    SJAR5.move(1200, 0);

    int curJar = 0;
    int aToggle;
    int jarType = 0;

    bool menuShow = false;
    bool up = true;

    jars.push_back(&SJAR);
    jars.push_back(&SJAR2);
    jars.push_back(&SJAR3);
    jars.push_back(&SJAR4);
    jars.push_back(&SJAR5);

    jarsNotComplete.push_back(&SJAR);
    jarsNotComplete.push_back(&SJAR2);

    jarsComplete.push_back(&SJAR);

    jarTypes[0] = &jars;
    jarTypes[1] = &jarsComplete;
    jarTypes[2] = &jarsNotComplete;


    Menu menu(WIDTH, HEIGHT);

    int jarAddAnim = 0;



    //Load background image
    sf::Texture backTex;
    if(!backTex.loadFromFile("background.png"))
        return EXIT_FAILURE;
    sf::Sprite background(backTex);
    background.setScale((float) HEIGHT / backTex.getSize().y, (float) HEIGHT / backTex.getSize().y);
    background.setOrigin(backTex.getSize().x/2, backTex.getSize().y/2);
    background.setPosition(WIDTH / 2, HEIGHT / 2);
    cout << WIDTH << "   " << backTex.getSize().x;

    //Set base background color
    sf::Color backColor(146,214,255, 1);
    sf::View view = window.getDefaultView();

    sf::Font font;

    if(!font.loadFromFile("CaviarDreams.ttf"))
    {
        throw "Cant locate font file";
    }

    sf::Text jarTitle;
    jarTitle.setFont(font);
    jarTitle.setCharacterSize(40); // in pixels, not points!
    // set the color
    jarTitle.setColor(sf::Color::Black);
    jarTitle.setPosition(WIDTH / 2, HEIGHT / 4);
    jarTitle.setStyle(sf::Text::Bold);


    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }

        if(sf::Touch::isDown(0))
        {
            sf::Vector2i position = sf::Touch::getPosition(0);

            for(int i = 0; i < jarTypes[jarType]->size(); i++)
                jarTypes[jarType]->at(i)->incAnim();
        }
        else {
           // for(int i = 0; i < jars.size(); i++)
           //     jars[i]->decAnim();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            if(!menu.isShown() && aToggle == 1 && curJar < jarTypes[jarType]->size() - 1 == !jars[curJar]->isAnim()) 
            {

                for(int i = 0; i < jarTypes[jarType]->size(); i++)
                    jarTypes[jarType]->at(i)->move(-300, 0);
                curJar++;
            }

            aToggle = 0;
        }
        else {
            aToggle = 1;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
	        sf::Vector2i position = sf::Mouse::getPosition(window);

            int res = -1;
            if(up)
            {
                res = menu.checkInput(position.x, position.y);
                jarAddAnim = 50;
            }

            if(res == 0)//working clicked
            {
                jarType = 0;
                curJar = 0;
            } 
            else if(res == 1)//check clicked
            {
                jarType = 2;
                curJar = 0;
            }    
            else if(res == 2)//x clicked
            {
                jarType = 1;
                curJar = 0;
            } 

            up = false;
        }
        else
        {
            up = true;
           // for(int i = 0; i < jarTypes[jarType]->size(); i++)
               // jarTypes[jarType]->at(i)->decAnim();
        }

        if(jarAddAnim > 0)
        {
            jarTypes[jarType]->at(curJar)->incAnim();
            jarAddAnim--;
        }
        else {
            jarTypes[jarType]->at(curJar)->decAnim();
        }

        jarTitle.setString(jarTypes[jarType]->at(curJar)->getTitle());

        sf::FloatRect textRect = jarTitle.getLocalBounds();
        jarTitle.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        jarTitle.setPosition(sf::Vector2f(WIDTH/2.0f,HEIGHT/5.0f));

        window.clear(backColor);
        window.draw(background);
        for(int i = 0; i < jarTypes[jarType]->size(); i++)
                jarTypes[jarType]->at(i)->draw(window);

        window.draw(jarTitle);
        menu.draw(window);
        window.display();
    }
}
