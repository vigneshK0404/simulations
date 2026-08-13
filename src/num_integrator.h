#pragma once
#include <vector>
#include "vec2.h"


const double dt = 0.01;

struct particle
{
    vec2<double> pos;
    vec2<double> vel;
    vec2<double> acc;

    particle(double x0, double y0, double vx0=0, double vy0=0, double ax0=0, double ay0=0) : pos(x0,y0), vel(vx0,vy0), acc(ax0,ay0) {}
    
};

class num_integrator
{
    public:
	std::vector<particle*> particle_list;
	size_t p_size;

	num_integrator(std::vector<particle*>& p_list) : particle_list(p_list) {p_size = particle_list.size();}
	
	void update()
	{
	    for(particle* p : particle_list)
	    {
		p->vel += p->acc*dt;
		p->pos += p->vel*dt;

	    }
	}

};


