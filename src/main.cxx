#include "raylib.h"
#include "resource_dir.h"
#include <random>
#include <vector>
#include <memory>

#include "brute_force.h"
#include "num_integrator.h"

const double upper_bound = 1000;
const double lower_bound = 0;
const double left_bound = 0;
const double right_bound = 1000;
const int FPS = 60;


double change_coord_system(double y)
{
    y += lower_bound;
    return y;
}


int main ()
{

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> position_x(left_bound, right_bound);
    std::uniform_real_distribution<> position_y(lower_bound, upper_bound);
    std::normal_distribution<double> velocity_x(upper_bound/5, std::sqrt(upper_bound));
    std::normal_distribution<double> velocity_y(right_bound/6, std::sqrt(right_bound));

    std::vector<std::unique_ptr<particle>> p_list;
    for(int i = 0; i < 10; ++i)
    {
	p_list.emplace_back(std::make_unique<particle>(position_x(gen), position_y(gen),0,0,0,0));

    }
    
    num_integrator n_I(upper_bound, lower_bound,left_bound,right_bound);
    brute_force bf;

    

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);	
    InitWindow(right_bound, upper_bound, "Paricle_Window");
    SetTargetFPS(FPS);

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");
    int counter = 0;
    // game loop
    while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
    {
	bf.calculate_accel(p_list);
	n_I.update(p_list);

	std::cout << n_I.calc_KE(p_list) << "\n";

	BeginDrawing();	
	ClearBackground(BLACK);
	for(const auto& p : p_list)
	{
	    DrawCircle(p->pos.X(),change_coord_system(p->pos.Y()),5.0f,WHITE);
	}
	EndDrawing();

	counter++;
    }


    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
