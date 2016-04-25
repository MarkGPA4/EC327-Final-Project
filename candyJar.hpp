#ifndef CANDYJAR_HPP
#define CANDYJAR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct candy{
double width,length;
double x,y;
friend ostream& operator<<(ostream& os, candy c)
	{
		os << c.x << c.y;
		return os;

	};

friend istream& operator>>(istream& is, candy c)
	{
		is >> c.x >> c.y;
		return is;   
	};


friend ofstream &operator<<(ofstream& b, candy c)
	{
		b << c.x << c.y;
		return b;

	};

friend ifstream &operator>>(ifstream& a, candy c)
	{
		a >> c.x >> c.y;
		return a;   
	};

};




/////////////////////////////////////////////////


class candyJar
{

public:
	//initializer
	int count=1;
	ofstream myfile;

	candyJar(const double,const double,const int);
	candyJar(const int);
	candyJar(const vector<candy>);
	//function for adding candy
	void addCandy(candy&, const candyJar&);
	//a vector that stores candy
	vector<candy> AllCandy;
	vector<candyJar> AllJars;
	friend ostream& operator<<(ostream& , const candyJar&);
    friend istream& operator>>(istream& , candyJar&);

    friend ofstream& operator<<(ofstream& of, const candyJar& c){
    	of<<c.title<<"|"<<c.description<<"|"<<c.timeWorkedOn<<"|"<<c.status<<"|"<<c.ICO; 
    	return of;
    }

    friend ifstream& operator>>(ifstream& , candyJar&);




private:
	//dimension of the candy jar
	double width, height;
	//number of pieces of candy the jar can store
	int capacity;
};





#endif
