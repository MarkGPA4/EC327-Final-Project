#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "candyJar.hpp"
using namespace std;



candyJar::candyJar(int Capacity){
capacity=Capacity;
width=40;
height=50;
AllJars.push_back(candyJar(capacity));
}

candyJar::candyJar(double Width, double Height, int Capacity){
width=Width;
height=Height;
capacity=Capacity;
}
candyJar::candyJar(vector<candy> allcandy){
AllCandy=allcandy;
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

/*
Can you write a couple functions to save the current program state to emory.
Basically, the information to store is this: each jar objects, which there 
are any number of needs to be stored. Each one has the following things stored
with it: title(string), times worked on(int), descpition(string), status(I/C/O) 
(ICO is Incomplete/Complete/Ongoing). I think the best way to do this is two functions.
One to read/one to write. So basically, if the read function can decode each thing in a 
loop (jar1,jar2, jar3 in any order) then I can just add some constructors to your code. 
For the write function, it should write a single jar to the file, overwriting it if it 
is already stored in the file. Other than that, its coming along smoothly. 
*/



/*
void write(candyJar& Jar){
	ofstream myfile;
	myfile.open("jar.txt");
	for (vector<candy>::iterator it = Jar.AllCandy.begin();it!= Jar.AllCandy.end();++it)
		{
			myfile<<*it<<" ";
		}
	myfile.close();
}

void read(){
	ifstream myfile;

	myfile.open("jar.txt");

	string candy;

	vector<string> Allcandy;

	while (not myfile.eof()){  // read a line
		 myfile >> candy;
		 Allcandy.push_back(candy);
    }

    myfile.close();

    // print out the contents of the file.
    for (auto candy: Allcandy){
    	cout << candy << endl;
    } 

}
*/
void write(){
	ofstream myfile;
	myfile.open("jar.txt");

	for (vector<candy>::iterator it = Jars.begin();it!= Jars.end();++it)
		{
			myfile<<*it<<" "<<"\n";
		}

	myfile.close();

	}


void read(){
	ifstream thisfile; // note: this is an IFSTREAM, "I" stands for INPUT

	string theline;          // we will store the text using these variables
	vector<string> contents;
    
    //read a file one line at a time with getline()

	thisfile.open("jar.txt");

	while (getline(thisfile,theline))  // read a line
		 contents.push_back(theline);  // put it in the vector
    thisfile.close(); 

    // print out the contents of the file.

    for (auto line: contents){
		title=line.substr(0, findFirstof("|")); 
		line.erase(title.size()+1,0);
		descpition=line.substr(0, findFirstof("|"));
		line.erase(descpition.size()+1,0);
		timeWorkedOn=line.substr(0, findFirstof("|")); 
		line.erase(timeWorkedOn.size()+1,0);
		status=line.substr(0,findFirstof("|"));
		line.erase(status.size()+1,0)
		ICO=line.substr(0,findFirstof("|"));
    	}
	}



void write(){}


void reloadJars(){



}


int main(){



candy Candy1 = { .width=10, .length=20};

candyJar Jar(40, 50, 40);

Jar.addCandy(Candy1, Jar);

candy Candy2 = { .width=10, .length=20};

Jar.addCandy(Candy2, Jar);

write(Jar);
read();
cout<<"There is "<<Jar.AllCandy.size()<<" pieces of candy"<<endl;

cout<<"They are at:";
cout<<"("<<Candy1.x<<","<<Candy1.y<<")";
cout<<"("<<Candy2.x<<","<<Candy2.y<<")"<<endl; 


for (vector<candy>::iterator it = Jar.AllCandy.begin();it!= Jar.AllCandy.end();++it)

	{
		cout<<*it<<endl;
	}



return 0;
}


/* get line from file


string theline;           // we will store the text using these variables
	vector<string> contents;
    
    //read a file one line at a time with getline()

	thisfile.open("reading_a_file_by_lines.cpp");

	while (getline(thisfile,theline))  // read a line
		 contents.push_back(theline);  // put it in the vector
    
    thisfile.close(); 

    // print out the contents of the file.
    for (auto line: contents){
    	cout << line << endl;
    }

*/