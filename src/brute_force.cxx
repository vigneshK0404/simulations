#include "num_integrator.h"
#include "vec2.h"


void calculate_accel(std::vector<particle*>& p_list)
{
    size_t p_size = p_list.size();

    for(size_t i = 0; i < p_size; ++i)
    {
	vec2<double> pos_i = p_list[i]->pos;

	for(size_t j = i+1; j < p_size; ++j)
	{
	    vec2<double> delta = p_list[j]->pos - pos_i; 
	    vec2<double> force = delta / delta.mag();

	    p_list[i]->acc += force;
	    p_list[j]->acc -= force;
	    
	}
    }

}





