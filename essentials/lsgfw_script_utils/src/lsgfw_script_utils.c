#define LSGFW_SCRIPT_UTILS_IMPLEMENTATION
#include <lsgfw_script_utils.h>

lsgfw_script_utils_t lsgfw_script_utils =
{
    load_file,
	free_file,
	clamp,
	clampf,
	clampllu,
	clampll,
	clampu,
	clampi
};

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
    shput(universe->world_v[world_i].global, LSGFW_SCRIPT_UTILS_TAG, (void*) &lsgfw_script_utils);
}

char* load_file(char* file_name)
{
    FILE* f = fopen(file_name, "rb");
	if (!f)
		return NULL;
	
	fseek(f, 0L, SEEK_END);
	long f_len = ftell(f);
	rewind(f);
	
	char* source = NULL;

	arrsetlen(source, f_len + 1);
	fread(source, sizeof(char), f_len, f);
	source[f_len] = 0;

	fclose(f);

	return source;
}

void free_file(char* file_source)
{
	arrfree(file_source);
}

double clamp(double a, double min, double max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}

float clampf(float a, float min, float max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}

u64_t clampllu(u64_t a, u64_t min, u64_t max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}

i64_t clampll(i64_t a, i64_t min, i64_t max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}

u32_t clampu(u32_t a, u32_t min, u32_t max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}

i32_t clampi(i32_t a, i32_t min, i32_t max)
{
	if (a > max)
		return max;
	else if (a < min)
		return min;

	return a;
}
