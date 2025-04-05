#ifndef TEST_H
#define TEST_H

#define LS_GLOBALS_ONLY
#include <glfw_opengl.h>
#include <stdio.h>

LS_API void PlugMain(outlet_t*);

void Start(outlet_t* outlet);
void Update(outlet_t* outlet);
void End(outlet_t* outlet);

#endif  // #ifndef TEST_H
