#pragma once
#include <vector>
#include "vec2.h"


const double dt = 0.001;

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
	double upper_bound;
	double lower_bound;
	double right_bound;
	double left_bound;

	num_integrator(double ub, double lob, double rb, double leb) : upper_bound(ub), lower_bound(lob), right_bound(rb), left_bound(leb){}

	void bounce(particle* p, vec2<double> norm_vector)
	{
	    double dot_prod = p->vel.dot(norm_vector) * 2;
	    p->vel -= norm_vector*dot_prod;
	}
	
	void update(std::vector<particle*>& particle_list)
	{
	    for(particle* p : particle_list)
	    {
		double x = p->pos.X();
		double y = p->pos.Y();

		bool upper = (y >= upper_bound);
		bool lower = (y <= lower_bound);
		bool right = (x >= right_bound);
		bool left = (x <= left_bound);

		if(upper && right){vec2<double> n_v(-1,-1); n_v.norm(); bounce(p,n_v);}
		else if(upper && left){vec2<double> n_v(1,-1); n_v.norm(); bounce(p,n_v);}
		else if(lower && right){vec2<double> n_v(-1,1); n_v.norm(); bounce(p,n_v);}
		else if(lower && left){vec2<double> n_v(1,1); n_v.norm(); bounce(p,n_v);}
		else if(upper){vec2<double> n_v(0,-1); n_v.norm(); bounce(p,n_v);}
		else if(lower){vec2<double> n_v(0,1); n_v.norm(); bounce(p,n_v);}
		else if(right){vec2<double> n_v(-1,0); n_v.norm(); bounce(p,n_v);}
		else if(left){vec2<double> n_v(1,0); n_v.norm(); bounce(p,n_v);}

		p->vel += p->acc*dt;
		p->pos += p->vel*dt;

	    }
	}

};


