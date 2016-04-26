#ifndef SANDJAR_HPP
#define SANDJAR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Jar.hpp"

using namespace std;

class SandJar : public Jar
{

public:
  //initializer
  SandJar(const int, const int, const int, string, string);
  SandJar(const int);
  //function for adding candy
  void add();
  void update();
  void draw(sf::RenderWindow&);
  //a vector that stores candy

  void incAnim();
  void decAnim();
  void move(int, int);
  void setScale(float);
  bool isAnim();

  string getTitle();
  int getTimesWorkedOn();
  string getDescription();


private:
  //Strings
  string title, descrip;
  int timesWorked;
  //dimension of the candy jar
  double windowW, windowH;
  int capacity;

  sf::Sprite jarFront;
  sf::Sprite jarBack;

  //Textures must be kept in scope
  sf::Texture jT1;
  sf::Texture jT2;

  float scale = .2f;

  int el_w, el_h, el_w2, el_h2;

  int sand_width = 75;
  int sand_height = 700;
  int sandTimer = 0;

  sf::Uint8 *stream;
  sf::Uint8 *sand;

  sf::Texture streamTex;
  sf::Texture fillTex;

  sf::Image streamIm;
  sf::Image fillIm;

  sf::Sprite streamS;
  sf::Sprite fillS;

  int animTime = 0;
  int prevAnimTime = 0;

  int elPW, elPH, circLoc;
  double circLoc2;

  void init();
  void updateStream();
  void updateSand();

};


#endif