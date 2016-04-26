#include <iostream>
#include <string>
#include <vector>
#include "SandJar.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>


SandJar::SandJar(int Capacity){
  capacity=Capacity;
  init();
}

SandJar::SandJar(int Capacity, int WindowW, int WindowH, std::string titl, std::string desc){
  capacity=Capacity;
  windowW = WindowW;
  windowH = WindowH;
  title = titl;
  descrip = desc;
  init();
}

void SandJar::init() {

  //Load images for jar and create sprites
  if(!jT1.loadFromFile("halfjar1.png"))
  {
      cout << "FUUCCCKKKK";
  }
  jarFront.setTexture(jT1, true);
  jarFront.setScale(scale, scale);
  jarFront.setOrigin(jT1.getSize().x/2, jT1.getSize().y/2);
  jarFront.setPosition(windowW / 2, windowH / 2);

  if(!jT2.loadFromFile("halfjar2.png"))
  {

  }
  jarBack.setTexture(jT2, true);
  jarBack.setScale(scale, scale);
  jarBack.setOrigin(jT2.getSize().x/2, jT2.getSize().y/2);
  jarBack.setPosition(windowW / 2, windowH / 2);

  //Setup sandstream

  stream  = new sf::Uint8[sand_width * sand_height * 4];

  for(int i = 0; i < sand_width * sand_height * 4; i++)
  {
    stream[i] = 0;
  }

  double rad = 20;

  el_w = 980 * scale;
  el_h = 454 * scale;

  el_w2 = 976 * scale;
  el_h2 = 375 * scale;

  streamIm.create(sand_width, sand_height, stream);
  streamTex.loadFromImage(streamIm);
  streamS.setTexture(streamTex, true);
  streamS.setOrigin(streamTex.getSize().x/2, 0);
  streamS.setPosition(windowW / 2, 100);

  //Setup sand fill
  elPW = jT2.getSize().x * .2;
  elPH = jT2.getSize().y * .2;

  circLoc = elPH - 20 * .2 - el_h / 2;
  circLoc2 = circLoc;

  sand  = new sf::Uint8[elPW * elPH * 4];

  for(int i = 0; i < elPH; i++)
  {
    for(int i2 = 0; i2 < elPW; i2++)
    {

      sand[(elPW * i * 4) + 4 * i2] = 211 + rand() % 44;
      sand[(elPW * i * 4) + 4 * i2 + 1] = 199 - rand() % 80;
      sand[(elPW * i * 4) + 4 * i2 + 2] = 162 + rand() % 80;

      //check bottom elipse
      if((((i - circLoc) * (i - circLoc) / ((float) el_h * el_h / 4)) + ((i2 - elPW / 2) * (i2 - elPW / 2) / ((float) el_w * el_w / 4))) <= 1 && i >= circLoc|| ((i < circLoc && i > circLoc2) && (i2 > elPW / 2 - el_w / 2) && (i2 < elPW / 2 + el_w / 2)))
        sand[(elPW * i * 4) + 4 * i2 + 3] = 255;
      else
        sand[(elPW * i * 4) + 4 * i2 + 3] = 0;

      //checktopelipse/
      double ellip = (((i - circLoc2) * (i - circLoc2) / ((float) el_h2 * el_h2 / 4)) + ((i2 - elPW / 2) * (i2 - elPW / 2) / ((float) el_w2 * el_w2 / 4)));
      if(ellip<= 1)
        sand[(elPW * i * 4) + 4 * i2 + 3] = 255;

      if(ellip - 1 <= .08 && ellip - 1 >= -.08)
      {
        sand[(elPW * i * 4) + 4 * i2] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 1] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 2] = 0;
      }
    }
  }

  fillIm.create(elPW, elPH, sand);
  fillTex.loadFromImage(fillIm);
  fillS.setTexture(fillTex, true);
  fillS.setOrigin(fillTex.getSize().x/2, fillTex.getSize().y/2);
  fillS.setPosition(windowW / 2, windowH / 2);

}

void SandJar::incAnim() {
  if(animTime < sand_height / 10)
    animTime++;
  else
    sandTimer = ((sand_height - (sand_height / 10)) / 10);
  update();
}

void SandJar::decAnim() {
  if(animTime > 0)
  {
     animTime--;
  }  
  if(sandTimer > 0)
      sandTimer--;
  update();
}

void SandJar::move(int x, int y)
{
  jarFront.move(x,y);
  jarBack.move(x,y);
  fillS.move(x,y);
}

void SandJar::setScale(float scl)
{
  float new_scl = scl * scale;
  jarFront.setScale(new_scl,new_scl);
  jarBack.setScale(new_scl,new_scl);
  //fillS is already relative to the original scale
  fillS.setScale(scl, scl);
}

void SandJar::update() {

  if(animTime != 0 || sandTimer != 0)
  {
    updateStream();
    updateSand();
  }
  sand_height = fillS.getPosition().y - fillS.getOrigin().y + circLoc2 - streamS.getPosition().y;
}

void SandJar::updateSand() 
{
  if(circLoc2 > 69 && ((animTime >= (sand_height / 14)) || (sandTimer > 0 && animTime > 0)))
  {
    circLoc2 -= .25;
  }
  
  
  for(int i = 0; i < elPH; i++)
  {
    //if(animTime < 10)
    //  break;
    for(int i2 = 0; i2 < elPW; i2++)
    {
      //Always update the black circle
      double ellip = (((i - circLoc2) * (i - circLoc2) / ((float) el_h2 * el_h2 / 4)) + ((i2 - elPW / 2) * (i2 - elPW / 2) / ((float) el_w2 * el_w2 / 4)));

      if(ellip < 1)
      {
        sand[(elPW * i * 4) + 4 * i2] = 211 + rand() % 44;
        sand[(elPW * i * 4) + 4 * i2 + 1] = 199 - rand() % 80;
        sand[(elPW * i * 4) + 4 * i2 + 2] = 162 + rand() % 80;
      }

      if(ellip - 1 <= .08 && ellip - 1 >= -.08)
      {
        sand[(elPW * i * 4) + 4 * i2] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 1] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 2] = 0;
      }

      if(sand[(elPW * i * 4) + 4 * i2 + 3] > 0 && sand[(elPW * i * 4) + 4 * i2] != 0)
        continue;

      sand[(elPW * i * 4) + 4 * i2] = 211 + rand() % 44;
      sand[(elPW * i * 4) + 4 * i2 + 1] = 199 - rand() % 80;
      sand[(elPW * i * 4) + 4 * i2 + 2] = 162 + rand() % 80;

      //check top elipse
      if(ellip<= 1)
        sand[(elPW * i * 4) + 4 * i2 + 3] = 255;

      if(ellip - 1 <= .08 && ellip - 1 >= -.08)
      {
        sand[(elPW * i * 4) + 4 * i2] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 1] = 0;
        sand[(elPW * i * 4) + 4 * i2 + 2] = 0;
      }
    }
  }

  fillIm.create(elPW, elPH, sand);
  fillTex.loadFromImage(fillIm);
  fillS.setTexture(fillTex, true);
  fillS.setOrigin(fillTex.getSize().x/2, fillTex.getSize().y/2);
}

void SandJar::updateStream() {

  for(int i = sand_width * sand_height * 4 - 1; i > sand_width * 4 * 10; i-=4)
  {
    if(stream[i - sand_width * 4 * 10] > 0 && animTime >= prevAnimTime)
      stream[i] = 255;
    else
      stream[i] = stream[i - sand_width * 4 * 10];
    stream[i - 1] = stream[i - 1 - sand_width * 4 * 10];
    stream[i - 2] = stream[i - 2 - sand_width * 4 * 10];
    stream[i - 3] = stream[i - 3 - sand_width * 4 * 10];
  }
  if(animTime >= prevAnimTime){

    for(int i = 0; i < 100; i++)
    {
      for(int i2 = 0; i2 < sand_width; i2++)
      {
        int rand1 = rand() % sand_width / 5;
        int rand2 = -rand() % sand_width / 5;
        stream[sand_width * 4 * i + 4 * i2] = 211 + rand() % 44;
        stream[sand_width * 4 * i + 4 * i2 + 1] = 199 - rand() % 80;
        stream[sand_width * 4 * i + 4 * i2 + 2] = 162 + rand() % 80;

        if(i2 > rand1 && i2 < sand_width + rand2)
          stream[sand_width * 4 * i + 4 * i2 + 3] = (int) (2.55 * i); 
        else
          stream[sand_width * 4 * i + 4 * i2 + 3] = 0;                   
      }
    }}
    else {
      for(int i = 0; i < 30 * sand_width * 4; i++)
      {
        stream[i] = 0;
      }
    }

    streamIm.create(sand_width, sand_height, stream);
    streamTex.loadFromImage(streamIm);
    streamS.setTexture(streamTex, true);

    prevAnimTime= animTime;
}

void SandJar::add() {
  capacity += 1;
}

void SandJar::draw(sf::RenderWindow& window) {

  window.draw(jarBack);
  window.draw(fillS);
  window.draw(streamS);
  window.draw(jarFront);
}

bool SandJar::isAnim() {
  return animTime != 0;
}

std::string SandJar::getTitle() {
  return title;
}

int SandJar::getTimesWorkedOn() {
  return timesWorked;
}

std::string SandJar::getDescription() {
  return descrip;
}
