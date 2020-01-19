#include <iostream>
#include <vector>

using namespace std;

class Rectangle {//rectangle class created
public:
	Rectangle() {};
	Rectangle(int top,int left,int bottom,int right)
	{
		Top = top;
		Left = left;
		Bottom = bottom;
		Right = right;
	};
	int topGet(){
		return Top;}
	int left(){
		return Left;}
	int bottom(){
		return Bottom;}
	int right(){
		return Right;}

private:
	int Top;
	int Left;
	int Bottom;
	int Right;
};


class TwoDimTreeNode{//nodes of the tree created
private:
	Rectangle Extent;
	vector<Rectangle> Vertical,Horizontal;
	TwoDimTreeNode *TopLeft,*TopRight,*BottomLeft,*BottomRight;
	friend class TwoDimTree;
public:
	TwoDimTreeNode(){};
		TwoDimTreeNode(int a, int b, int c, int d)
		{
			Rectangle rx(a,b,c,d);
			Extent = rx;
			TopLeft=NULL;
			TopRight=NULL;
			BottomRight=NULL;
			BottomRight=NULL;
		}

		
};


class TwoDimTree {//root of the tree
public:
	TwoDimTree () {};
	TwoDimTree(int x,int y,int z,int v)
		{
			Rectangle rec(x,y,z,v);
			Extent=rec;
			TwoDimTreeNode * topright=NULL;	 
			TwoDimTreeNode*topleft =NULL;
			TwoDimTreeNode *bottomright	=NULL;
			TwoDimTreeNode*bottomleft=NULL;
		};
	void insert(Rectangle rec,TwoDimTreeNode *&t);
	void search(int x, int y,TwoDimTreeNode *t,int& c0unt,vector<Rectangle>& vec);
private:
	Rectangle Extent;
	TwoDimTreeNode *TopLeft,*TopRight,*BottomLeft,*BottomRight;
};

void TwoDimTree :: insert(Rectangle rex,TwoDimTreeNode *&t)//rectangles inserted to vectors here
{
	int y1 = t->Extent.topGet();
	int y2 = t->Extent.bottom();
	int x1 = t->Extent.left();
	int x2 = t->Extent.right();

		if(rex.left() <= (x1+x2)/2 && (x1+x2)/2 < rex.right())
		{
			t->Vertical.push_back(rex);
		}
		else if(rex.topGet() <= (y1+y2)/2 && (y1+y2)/2 < rex.bottom())
		{
			t->Horizontal.push_back(rex);
		}
		else {
			if( rex.bottom() > (y1+y2)/2 && rex.right() < (x1+x2)/2)
			{
				if(t->BottomLeft == NULL){
					TwoDimTreeNode *bl = new TwoDimTreeNode(2*y1,x1,y2,x2/2);
				 t->BottomLeft = bl;
				 insert(rex,t->BottomLeft); }
				else
					insert(rex,t->BottomLeft);
			}
			else if( rex.bottom() > (y1+y2)/2 && rex.right() > (x1+x2)/2)
			{
				if(t->BottomRight == NULL){
					TwoDimTreeNode *br = new TwoDimTreeNode(y2/2,x2/2,y2,x2);
				t->BottomRight = br;
				insert(rex,t->BottomRight); }
				else
					insert(rex,t->BottomRight);
			}
			else if ( rex.topGet() < (y1+y2)/2 && rex.right() < (x1+x2)/2)
			{
				if(t->TopLeft == NULL){
				TwoDimTreeNode *tl = new TwoDimTreeNode(y1,x1,y2/2,x2/2);
				t->TopLeft = tl;
				insert(rex,t->TopLeft);}
				else
					insert(rex,t->TopLeft);
			}
			else if( rex.topGet() < (y1+y2)/2 && rex.right() > (x1+x2)/2)
			{
				if(t->TopRight == NULL)
				{
					TwoDimTreeNode *tr = new TwoDimTreeNode(y1,2*x1,y2/2,x2);
					t->TopRight = tr;
					insert(rex,t->TopRight);}
				else
					insert(rex,t->TopRight);
			}
		}
}

void TwoDimTree :: search (int x,int y,TwoDimTreeNode* t,int& c0unt,vector<Rectangle>& vec)//rectangles which include the query point created here
{
	int y1 = t->Extent.topGet();
	int y2 = t->Extent.bottom();
	int x1 = t->Extent.left();
	int x2 = t->Extent.right();
	int i = 0;
	int k = 0;
	for(int j=0 ; j < t->Vertical.size() ; j++)
	{
		if(t->Vertical[i].left() <= x < t->Vertical[i].right()  && t->Vertical[i].topGet() <= y < t->Vertical[i].bottom())
		{
				c0unt++;
				vec.push_back(t->Vertical[i]);
		}
		i++;
	}
	
	for(int j=0 ; j < t->Horizontal.size() ; j++)
	{
		if(t->Horizontal[k].left() <= x && x < t->Horizontal[k].right()  && t->Horizontal[k].topGet() <= y && y < t->Horizontal[k].bottom())
		{
				c0unt++;
				cout << t->Horizontal[k].topGet() << " " << t->Horizontal[k].left() << " " << t->Horizontal[k].bottom() << " " << t->Horizontal[k].right() << endl;
		}
		k++;
	}

	if( y > (y1+y2)/2 && x < (x1+x2)/2 && t->BottomLeft != NULL)
			{
				search(x,y,t->BottomLeft,c0unt,vec); 
			}
	else if( y > (y1+y2)/2 && x > (x1+x2)/2 && t->BottomRight != NULL)
			{
				search(x,y,t->BottomRight,c0unt,vec); 
			}
	else if ( y < (y1+y2)/2 && x < (x1+x2)/2 && t->TopLeft != NULL)
			{
				search(x,y,t->TopLeft,c0unt,vec);
			}
	else if( y < (y1+y2)/2 && x > (x1+x2)/2 && t->TopRight != NULL)
			{
				search(x,y,t->TopRight,c0unt,vec);
			}
		}

