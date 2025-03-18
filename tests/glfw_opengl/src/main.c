#define LS_PLUGS_IMPLEMENTATION
#include <ls_plugs.h>
#include <stdio.h>

ls_plugs_outlet_t outlet = NEW_OUTLET;

int main()
{
    load_plugs  (&outlet, "./scripts", "*.so");
    invoke_plugs(&outlet);
    free_outlet (&outlet);
}