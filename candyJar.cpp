#include <iostream>
#include <string>
#include <vector>
#include "candyJar.hpp"
using namespace std;



candyJar::candyJar(int capacity){
capacity=this->capacity;
}

candyJar::candyJar(double Width, double Height, int Capacity){
width=Width;
height=Height;
capacity=Capacity;
}



candyJar candyJar::addCandy(candy& Candy,const candyJar& Jar){
int Capacity = capacity-1;

if (Jar.capacity>Jar.AllCandy.size()){
	AllCandy.push_back(Candy);

if (AllCandy.size()==1){
	Candy.x=Candy.length;
	Candy.y=Candy.width;
}

if(AllCandy.back().x < Jar.width){
	Candy.x=AllCandy.back().x+Candy.length;
	Candy.y=AllCandy.back().y;
}

else{ 
	Candy.x=Candy.width;
	Candy.y=AllCandy.back().y+Candy.width;
}

}
return candyJar(Capacity);
}




int main(){

candy Candy = { .width=10, .length=20, .x=15, .y=0};

candyJar Jar(30, 50, 40);

Jar.addCandy(Candy, Jar);

cout<<"There is "<<Jar.AllCandy.size()<<" pieces of candy"<<endl;






return 0;
}

