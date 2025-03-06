#ifndef LSGFW_SCRIPT_UTILS_H
#define LSGFW_SCRIPT_UTILS_H

#ifndef LSGFW_SCRIPT_UTILS_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_SCRIPT_UTILS_TAG "lsgfw_script_utils"
#else
    #error "Tag collision detected"
#endif  // #ifndef LSGFW_SCRIPT_UTILS_TAG

#include <lsgfw.h>
#include <stdio.h>
#include <stb/stb_ds.h>

#ifdef LSGFW_SCRIPT_UTILS_IMPLEMENTATION

char* load_file(char* file_name);
void  free_file(char* file_source);

#endif // #ifdef LSGFW_SCRIPT_UTILS_IMPLEMENTATION

typedef struct lsgfw_script_utils_s
{
    char* (*load_file)(char*);
    void  (*free_file)(char*);
}
lsgfw_script_utils_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_script_utils_load(lsgfw_kv_t* lsgfw_kv, lsgfw_script_utils_t* lsgfw_script_utils)
{
    *lsgfw_script_utils = *(lsgfw_script_utils_t*) shget(lsgfw_kv, LSGFW_SCRIPT_UTILS_TAG);
}

#endif  // #ifndef LSGFW_SCRIPT_UTILS_H
