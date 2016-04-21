#include <iostream>
#include <string>
#include <vector>
#include "candyJar.hpp"
using namespace std;



candyJar::candyJar(int Capacity){
capacity=Capacity;
}

candyJar::candyJar(double Width, double Height, int Capacity){
width=Width;
height=Height;
capacity=Capacity;
}



void candyJar::addCandy(candy& Candy,const candyJar& Jar){
capacity-=1;

if (Jar.capacity>Jar.AllCandy.size()){
	

	if (AllCandy.size()==0){
		Candy.x=Candy.length;
		Candy.y=Candy.width;

	}

	else if (AllCandy.size()>=1){

		if ((Jar.width-AllCandy.back().x) > Candy.length ){
			Candy.x=AllCandy.back().x+Candy.length;
			Candy.y=AllCandy.back().y;
												 }

		else{ 
			Candy.x=Candy.length;
			Candy.y=AllCandy.back().y+Candy.width;
			}

	
	}
AllCandy.push_back(Candy);
					   }

}







int main(){

candy Candy1 = { .width=10, .length=20};

candyJar Jar(40, 50, 40);

Jar.addCandy(Candy1, Jar);

candy Candy2 = { .width=10, .length=20};

Jar.addCandy(Candy2, Jar);

cout<<"There is "<<Jar.AllCandy.size()<<" pieces of candy"<<endl;

cout<<"They are at:";
cout<<"("<<Candy1.x<<","<<Candy1.y<<")";
cout<<"("<<Candy2.x<<","<<Candy2.y<<")"<<endl; 


return 0;
}


