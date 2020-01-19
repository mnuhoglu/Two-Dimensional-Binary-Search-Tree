#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Header.h"
using namespace std;

int main()
{
	ifstream ifs;
	ifs.open("rectdb.txt");// file opened here
	string s;
	getline(ifs,s);//first line taken in order to get the plane
	stringstream ss(s);
	 int top,left,bottom,right;
	ss>>top>>left>>bottom>>right;
	TwoDimTree Extent(top,left,bottom,right);//root of the tree
	TwoDimTreeNode *Eqtent= new TwoDimTreeNode(top,left,bottom,right);
	int x,y;
	while(getline(ifs,s))//putting rectangles in to correct vectors
	{
		stringstream sss(s);
		int x,y,z,t;
		sss >> x >> y >> z >> t; 
		if(t == -1 || x== -1 || y == -1 || x == -1)//break when there's -1 
			break;
		
		Rectangle rec(x,y,z,t);//new rectangle created here
		Extent.insert(rec,Eqtent);
	}
	
	while(cin >> x >> y )//take input until -1 
	{
		if(x==-1 || y==-1)
			break;
		int count=0;
		vector<Rectangle> vec;//this vector holds the ones we'll print to the screen
		Extent.search(x,y,Eqtent,count,vec);
		cout << count << endl;
		for(int k=0;k<vec.size();k++)
			cout << vec[k].topGet() << " " << vec[k].left() << " "  << vec[k].bottom() << " " << vec[k].right() << endl;
	}

	return 0;
}