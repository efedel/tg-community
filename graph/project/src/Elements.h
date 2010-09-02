#ifndef Graph_h
#define Graph_h

#include <map>

//TODO change this to a template asap
typedef void * Pointer;

class Vertex;
class Edge;

typedef map<unsigned int, Vertex> Vertices;
typedef map<unsigned int, Edge>   Edges;

class Element
{
	unsigned int address;
	std::string name; // is this really necessary?
	Pointer data; //replace this with a TEMPLATE NOW. I MEAN NOW.
	public:
	virtual Element()  = 0;
	virtual ~Element() = 0;
	virtual Element(const Element & from) = 0;
	// do we need to overload = and *?
};

class Vertex : public Element
{
	Vertices &vertices;
	public: 
	Vertex();
	~Vertex();
	Vertex(const Vertex & from);
	Vertex operator=(const Vertex & from);
};

class Edge : public Element
{
	Edges &edges;
	public:
	Edge();
	~Edge();
	Edge(const Edge & from);
	Edge operator=(const Edge & from);
}

#endif
