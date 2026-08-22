#pragma once
#include <vector>
#include "particle.h"

const double dt = 1.0/60;


class num_integrator
{
    public:
	double upper_bound;
	double lower_bound;
	double right_bound;
	double left_bound;

	num_integrator(double ub, double lob, double leb, double rb) : upper_bound(ub), lower_bound(lob), right_bound(rb), left_bound(leb){}

	void bounce(particle* p)
	{
	    
	    double x = p->pos.X();
	    double y = p->pos.Y();
	    bool upper = (y >= upper_bound);
	    bool lower = (y <= lower_bound);
	    bool right = (x >= right_bound);
	    bool left = (x <= left_bound);

	    if(!upper && !lower && !right && !left)
		return;

	    vec2<double> norm_vector;

	    if(upper && right){vec2<double> n_v(-1,-1); n_v.norm(); norm_vector = n_v; vec2<double> n_pos(right_bound, upper_bound); p->pos = n_pos;}
            else if(upper && left){vec2<double> n_v(1,-1);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(left_bound, upper_bound);p->pos = n_pos;}
            else if(lower && right){vec2<double> n_v(-1,1);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(right_bound, lower_bound);p->pos = n_pos;}
            else if(lower && left){vec2<double> n_v(1,1);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(left_bound, lower_bound);p->pos = n_pos;}
            else if(upper){vec2<double> n_v(0,-1);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(p->pos.X(), upper_bound);p->pos = n_pos;}
            else if(lower){vec2<double> n_v(0,1);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(p->pos.X(), lower_bound);p->pos = n_pos;}
            else if(right){vec2<double> n_v(-1,0);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(right_bound, p->pos.Y());p->pos = n_pos;}
            else if(left){vec2<double> n_v(1,0);n_v.norm(); norm_vector = n_v; vec2<double> n_pos(left_bound, p->pos.Y());p->pos = n_pos;}

	    double dot_prod = p->vel.dot(norm_vector) * 2;
	    p->vel -= norm_vector*dot_prod;
	}
	
	void update(std::vector<std::unique_ptr<particle>>& particle_list)
	{
	    for(std::unique_ptr<particle>& p : particle_list)
	    {
		
		bounce(p.get());
			
		p->vel += p->acc*dt;
		p->pos += p->vel*dt;
	    }
	}

	
};


