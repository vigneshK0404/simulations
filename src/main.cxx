#include "raylib.h"
#include "resource_dir.h"
#include <random>
#include <vector>

#include "brute_force.h"
#include "num_integrator.h"


int main ()
{

    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 2.0);*/


    particle* p = new particle(500,500,300,100,0,0);
    std::vector<particle*> p_list = {p};

    num_integrator n_I(0,1000,1000,0);

    

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);	
    InitWindow(1000, 1000, "Paricle_Window");
    SetTargetFPS(60);

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // game loop
    while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
    {
    
	n_I.update(p_list);

	BeginDrawing();	
	ClearBackground(BLACK);
	DrawCircle(p->pos.X(),p->pos.Y(),10.0f,WHITE);
	EndDrawing();
    }


    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
