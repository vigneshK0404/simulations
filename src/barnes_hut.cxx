#include "barnes_hut.h"


void barnes_hut::build_tree(std::unique_ptr<node> current_node, particle* par)
{
    // base case
    if(!current_node->p && !current_node->TR && !current_node->TL && !current_node->BR && !current_node->BL)
    {
	current_node->p = par;
	current_node->total_mass = 1;
    }
    return;

    //recursive case
    current_node->total_mass++;
    double node_X = current_node->center.X();
    double node_Y = current_node->center.Y();
    double node_W = current_node->width;
    
    bool right = (par->pos.X()>=node_X);
    bool up = (par->pos.Y()>=current_node->node_Y);

    if(right&&up)
    {	
	if(!current_node->TR)
	{
	    vec2<double> nc(node_X + node_W/2, node_Y + node_W/2);
	    current_node->TR = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->TR, par);

    }

    if(!right&&up)
    {	
	if(!current_node->TL)
	{
	    vec2<double> nc(node_X - node_W/2, node_Y + node_W/2);
	    current_node->TL = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->TL, par);
    }

    if(right&&!up)
    {	
	if(!current_node->BR)
	{
	    vec2<double> nc(node_X + node_W/2, node_Y - node_W/2);
	    current_node->BR = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->BR, par);
    }

    if(!right&&!up)
    {	
	if(!current_node->BL)
	{
	    vec2<double> nc(node_X - node_W/2, node_Y - node_W/2);
	    current_node->BL = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->BL, par);
    }



    cur_par = current_node->p;
    current_node->p = nullptr;

    build_tree(current_node, cur_par);    

}

vec2<double> barnes_hut::center_of_mass(std::unique_ptr<node> c_node)
{
    
}




