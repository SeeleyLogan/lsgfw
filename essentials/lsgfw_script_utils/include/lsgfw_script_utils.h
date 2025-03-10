#ifndef LSGFW_SCRIPT_UTILS_H
#define LSGFW_SCRIPT_UTILS_H

#ifndef LSGFW_SCRIPT_UTILS_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_SCRIPT_UTILS_TAG "lsgfw_script_utils"
#else
    #error "Tag collision detected"
#endif  // #ifndef LSGFW_SCRIPT_UTILS_TAG

#include <lsgfw.h>

#include <stb/stb_ds.h>

#include <stdio.h>

#ifdef LSGFW_SCRIPT_UTILS_IMPLEMENTATION

char* load_file(char* file_name);
void  free_file(char* file_source);

double clamp   (double a, double min, double max);
float  clampf  (float  a, float  min, float  max);
u64_t  clampllu(u64_t  a, u64_t  min, u64_t  max);
i64_t  clampll (i64_t  a, i64_t  min, i64_t  max);
u32_t  clampu  (u32_t  a, u32_t  min, u32_t  max);
i32_t  clampi  (i32_t  a, i32_t  min, i32_t  max);

#endif // #ifdef LSGFW_SCRIPT_UTILS_IMPLEMENTATION

typedef struct lsgfw_script_utils_s
{
    char*  (*load_file)(char*);
    void   (*free_file)(char*);
    double (*clamp)    (double, double, double);
    float  (*clampf)   (float,  float,  float);
    u64_t  (*clampllu) (u64_t,  u64_t,  u64_t);
    i64_t  (*clampll)  (i64_t,  i64_t,  i64_t);
    u32_t  (*clampu)   (u32_t,  u32_t,  u32_t);
    i32_t  (*clampi)   (i32_t,  i32_t,  i32_t);
}
lsgfw_script_utils_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_script_utils_load(lsgfw_kv_t* lsgfw_kv, lsgfw_script_utils_t* lsgfw_script_utils)
{
    *lsgfw_script_utils = *(lsgfw_script_utils_t*) shget(lsgfw_kv, LSGFW_SCRIPT_UTILS_TAG);
}

#endif  // #ifndef LSGFW_SCRIPT_UTILS_H
