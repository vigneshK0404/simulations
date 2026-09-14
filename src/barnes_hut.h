#pragma once
#include "particle.h"


struct node
{
    std::unique_ptr<node> TR;
    std::unique_ptr<node> TL;
    std::unique_ptr<node> BR;
    std::unique_ptr<node> BL;

    vec2<double> center;
    double width;
    vec2<double> COM;
    double total_mass;

    particle* p;
    
    node(vec2<double> c, double w) : center(c), width(w), total_mass(0), TR(nullptr), TL(nullptr), BR(nullptr), BL(nullptr), p(nullptr),{}
};

class quad_tree
{
    private:
	std::unique_ptr<node> root;

    public:
	quad_tree() : root(nullptr){}
	void build_tree(node*, particle*);
	vec2<double> center_of_mass(node*);
    	~quad_tree();


};

