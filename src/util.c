bool_t lsgfw_glob(lsgfw_glob_t* glob, const char* glob_path, const char* pattern)
{
	u32_t glob_path_len = strlen(glob_path);
	char* path_pattern = NULL;
	u32_t pattern_len = strlen(pattern);

	arrsetlen(path_pattern, glob_path_len + pattern_len + 1);

	memcpy(path_pattern, glob_path, glob_path_len);
	memcpy(path_pattern + glob_path_len, pattern, pattern_len + 1);	

#if defined(_WIN32)
	WIN32_FIND_DATAA file_data;
	HANDLE file_handle = FindFirstFileA(path_pattern, &file_data);
	do
	{
		char* full_path = NULL;
		u32_t file_name_len = strlen(file_data.cFileName);

		arrsetlen(full_path, glob_path_len + file_name_len + 1);

		memcpy(full_path, glob_path, glob_path_len);
		memcpy(full_path + glob_path_len, file_data.cFileName, file_name_len + 1);

		arrput(*glob, full_path);
	}
	while (FindNextFileA(file_handle, &file_data));
#else

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

void lsgfw_free_glob(lsgfw_glob_t glob)
{
	for (u32_t i = 0; i < arrlen(glob); i++)
		arrfree(glob[i]);

	arrfree(glob);
}
