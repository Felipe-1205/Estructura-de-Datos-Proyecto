
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;


struct Point {
	int x;
	int y;
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0;
		y = 0;
	}
};


struct Node {
    Elemento* elemento;
    Point pos;
    Node(Elemento* _elemento)
    {
        elemento = _elemento;
        pos = Point(elemento->get_coordX(), elemento->get_coordY());
    }
    Node() { elemento = nullptr; }
};



class Quad {
	
	Point topLeft;
	Point botRight;

	
	Node* n;

	
	Quad* topLeftTree;
	Quad* topRightTree;
	Quad* botLeftTree;
	Quad* botRightTree;

public:
	Quad()
	{
		topLeft = Point(0, 0);
		botRight = Point(0, 0);
		n = NULL;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
	}
	Quad(Point topL, Point botR)
	{
		n = NULL;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
		topLeft = topL;
		botRight = botR;
	}
	void insert(Node*);
	Node* search(Point);
	bool inBoundary(Point);
  vector<Node*> en_cuadrante(Quad* quad, double x1, double y1, double x2, double y2);
};


void Quad::insert(Node* node)
{
	if (node == NULL)
		return;

	
	if (!inBoundary(node->pos))
		return;

	
	if (abs(topLeft.x - botRight.x) <= 1&& abs(topLeft.y - botRight.y) <= 1) {
		if (n == NULL)
			n = node;
		return;
	}

	if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
		// topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topLeftTree == NULL)
				topLeftTree = new Quad(
					Point(topLeft.x, topLeft.y),
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2));
			topLeftTree->insert(node);
		}

		// botLeftTree
		else {
			if (botLeftTree == NULL)
				botLeftTree = new Quad(
					Point(topLeft.x,
						(topLeft.y + botRight.y) / 2),
					Point((topLeft.x + botRight.x) / 2,
						botRight.y));
			botLeftTree->insert(node);
		}
	}
	else {
		// topRightTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topRightTree == NULL)
				topRightTree = new Quad(
					Point((topLeft.x + botRight.x) / 2,
						topLeft.y),
					Point(botRight.x,
						(topLeft.y + botRight.y) / 2));
			topRightTree->insert(node);
		}

		// botRightTree
		else {
			if (botRightTree == NULL)
				botRightTree = new Quad(
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2),
					Point(botRight.x, botRight.y));
			botRightTree->insert(node);
		}
	}
}


Node* Quad::search(Point p)
{
	
	if (!inBoundary(p))
		return NULL;

	
	if (n != NULL)
		return n;

	if ((topLeft.x + botRight.x) / 2 >= p.x) {
		// topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		// botLeftTree
		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		// topRightTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		// botRightTree
		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
}


bool Quad::inBoundary(Point p)
{
	return (p.x >= topLeft.x && p.x <= botRight.x
			&& p.y >= topLeft.y && p.y <= botRight.y);
}

vector<Node*> Quad::en_cuadrante(Quad* quad, double x1, double y1, double x2, double y2)
{
    vector<Node*> nodesInRange;
 
    
    if (quad == NULL) return nodesInRange;
 
    
    if (!quad->inBoundary(Point(x1, y1)) || !quad->inBoundary(Point(x2, y2))) return nodesInRange;
 
    
    if (quad->n != NULL && quad->n->pos.x >= x1 && quad->n->pos.x <= x2 && quad->n->pos.y >= y1 && quad->n->pos.y <= y2) {
        nodesInRange.push_back(quad->n);
    }
 
    
    if (quad->topLeftTree != NULL) {
        vector<Node*> nodes = en_cuadrante(quad->topLeftTree, x1, y1, x2, y2);
        nodesInRange.insert(nodesInRange.end(), nodes.begin(), nodes.end());
    }
    if (quad->topRightTree != NULL) {
        vector<Node*> nodes = en_cuadrante(quad->topRightTree, x1, y1, x2, y2);
        nodesInRange.insert(nodesInRange.end(), nodes.begin(), nodes.end());
    }
    if (quad->botLeftTree != NULL) {
        vector<Node*> nodes = en_cuadrante(quad->botLeftTree, x1, y1, x2, y2);
        nodesInRange.insert(nodesInRange.end(), nodes.begin(), nodes.end());
    }
    if (quad->botRightTree != NULL) {
        vector<Node*> nodes = en_cuadrante(quad->botRightTree, x1, y1, x2, y2);
        nodesInRange.insert(nodesInRange.end(), nodes.begin(), nodes.end());
    }
 
    return nodesInRange;
};
