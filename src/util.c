LSGFW_API u8_t lsgfw_glob(lsgfw_glob_t* glob, const char* glob_path, const char* pattern)
{
	u32_t glob_path_len = strlen(glob_path);

#if defined(_WIN32) || defined(__CYGWIN__)

#else
	char* path_pattern = NULL;
	u32_t pattern_len = strlen(pattern);

	arrsetlen(path_pattern, glob_path_len + pattern_len + 1);
	
	memcpy(path_pattern, glob_path, glob_path_len);
	memcpy(path_pattern + glob_path_len, pattern, pattern_len + 1);	

	DIR* dir = opendir(glob_path);

	if (!dir)
		return LSGFW_FAIL;
	
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		char* full_path = NULL;
		u32_t d_name_len = strlen(entry->d_name);

		arrsetlen(full_path, glob_path_len + d_name_len + 2);
		
		memcpy(full_path, glob_path, glob_path_len);
		full_path[glob_path_len] = '/';
		memcpy(full_path + glob_path_len + 1, entry->d_name, d_name_len + 1);
		
		if (fnmatch(path_pattern, full_path, 0) != FNM_NOMATCH)	
			arrput(*glob, full_path);
	}

	closedir(dir);
#endif

	return LSGFW_SUCCESS;
}

LSGFW_API void lsgfw_free_glob(lsgfw_glob_t glob)
{
	for (u32_t i = 0; i < arrlen(glob); i++)
		arrfree(glob[i]);

	arrfree(glob);
}

