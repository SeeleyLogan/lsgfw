#include <test.h>

void PlugMain(outlet_t* outlet)
{
    switch (((glfw_opengl_t*) outlet->user_ptr)->v1_0.phase)
    {
        case 0:
            Start(outlet);
        break;

        case 1:
            Update(outlet);
        break;

        case 2:
            End(outlet);
        break;
    }
}

void Start(outlet_t* outlet)
{
    printf("Start!\n");
}

u8_t i = 0;

void Update(outlet_t* outlet)
{
    i++;
    printf("Update!\n");

    if (i == 10)
        ((glfw_opengl_t*) outlet->user_ptr)->v1_0.phase = 2;
}

void End(outlet_t* outlet)
{
    printf("End!\n");
}
