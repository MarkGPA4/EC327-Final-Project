#ifndef CANDYJAR_HPP
#define CANDYJAR_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct candy{
double width,length;
double x,y;
};


class candyJar
{

public:
	//initializer
	candyJar(const double,const double,const int);
	candyJar(const int);
	//function for adding candy
	candyJar addCandy(candy&, const candyJar&);
	//a vector that stores candy
	vector<candy> AllCandy;

private:
	//dimension of the candy jar
	double width, height;
	//number of pieces of candy the jar can store
	int capacity;

};


#endif
