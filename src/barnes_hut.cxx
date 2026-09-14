#include "barnes_hut.h"


void barnes_hut::build_tree(node* current_node, particle* par)
{
    // base case
    if(!current_node->p && !current_node->TR && !current_node->TL && !current_node->BR && !current_node->BL)
    {
	current_node->p = par;
	current_node->total_mass = 1;
	return;
    }
    
    //recursive case
    current_node->total_mass++;
    double node_X = current_node->center.X();
    double node_Y = current_node->center.Y();
    double node_W = current_node->width;
    
    bool right = (par->pos.X()>=node_X);
    bool up = (par->pos.Y() >= node_Y);

    if(current_node->p)
    {
	current_node->total_mass--;
	cur_par = current_node->p;
	current_node->p = nullptr;
	build_tree(current_node, cur_par);    
    }


    if(right&&up)
    {	
	if(!current_node->TR)
	{
	    vec2<double> nc(node_X + node_W/4, node_Y + node_W/4);
	    current_node->TR = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->TR.get(), par);

    }

    if(!right&&up)
    {	
	if(!current_node->TL)
	{
	    vec2<double> nc(node_X - node_W/4, node_Y + node_W/4);
	    current_node->TL = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->TL.get(), par);
    }

    if(right&&!up)
    {	
	if(!current_node->BR)
	{
	    vec2<double> nc(node_X + node_W/4, node_Y - node_W/4);
	    current_node->BR = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->BR.get(), par);
    }

    if(!right&&!up)
    {	
	if(!current_node->BL)
	{
	    vec2<double> nc(node_X - node_W/4, node_Y - node_W/4);
	    current_node->BL = std::make_unique<node>(nc,node_W/2);
	}
	
	build_tree(current_node->BL.get(), par);
    } 
}

vec2<double> barnes_hut::center_of_mass(node* c_node)
{
   //base case
   vec2<double> c_com;
   if(!c_node->TR && !c_node->TL && !c_node->BR && !c_node->BL)
   {
	c_node->COM = c_node->p->pos;
	return c_node->COM; 
   }

   if(c_node->TR)
       c_com += center_of_mass(c_node->TR.get());
   
   if(c_node->TL)
       c_com += center_of_mass(c_node->TL.get());
   
   if(c_node->BR)
       c_com += center_of_mass(c_node->BR.get());
   
   if(c_node->BL)
       c_com += center_of_mass(c_node->BL.get());

   c_node->COM = c_com/c_node->total_mass;

   return c_node->COM*(c_node->total_mass);
   
}




