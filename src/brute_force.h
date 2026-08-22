#pragma once
#include "particle.h"

const double sf = 1e3;

double calc_KE(std::vector<std::unique_ptr<particle>>& p_list)
{
    double KE = 0;
    for(const std::unique_ptr<particle>& p : p_list)
    {
	KE += 0.5 * (p->vel.dot(p->vel));
    }

    return KE;
}



class brute_force
{
    public:
	brute_force() = default;

	double calculate_accel(std::vector<std::unique_ptr<particle>>& p_list)
	{
	    size_t p_size = p_list.size();
	    vec2<double> tmp;

	    double KE = calc_KE(p_list);

	    double pot_E = 0;

	    for(auto& p : p_list)
	    {
		p->acc = tmp;
	    }

	    for(size_t i = 0; i < p_size; ++i)
	    {
		vec2<double> pos_i = p_list[i]->pos;

		for(size_t j = i+1; j < p_size; ++j)
		{
		    vec2<double> delta = p_list[j]->pos - pos_i;
		    double r = delta.mag();
		    pot_E += std::log(r)*sf;
		    vec2<double> force = delta / (r*r);

		    p_list[i]->acc += force*sf;
		    p_list[j]->acc -= force*sf;

		}
	    }

	    return pot_E + KE;

	}



};






