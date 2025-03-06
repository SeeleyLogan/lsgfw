#define LSGFW_SCRIPT_UTILS_IMPLEMENTATION
#include <lsgfw_script_utils.h>

lsgfw_script_utils_t lsgfw_script_utils =
{
    load_file,
	free_file
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
