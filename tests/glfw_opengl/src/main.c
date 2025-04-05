#define LS_PLUGS_IMPLEMENTATION
#include <glfw_opengl.h>

ls_plugs_outlet_t outlet  = NEW_OUTLET;
glfw_opengl_t glfw_opengl =
{
    .v1_0 = (v1_0_t)
    {
        .phase = 0
    }
};

int main()
{
    outlet.user_ptr = &glfw_opengl;
    load_plugs  (&outlet, "./scripts", "*.dll");
    
    invoke_plugs(&outlet);  // Start
    glfw_opengl.v1_0.phase++;
    while (glfw_opengl.v1_0.phase != 2)
        invoke_plugs(&outlet);  // Update
    invoke_plugs(&outlet);  // End

    free_outlet (&outlet);
}