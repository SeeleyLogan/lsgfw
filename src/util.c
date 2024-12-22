LSGFW_API u8_t lsgfw_glob(lsgfw_glob_t* glob, const char* glob_path, const char* pattern)
{
	u32_t glob_path_len = strlen(glob_path);

#if defined(_WIN32) || defined(__CYGWIN__)

#else
	DIR* dir = opendir(glob_path);

	if (!dir)
		return LSGFW_FAIL;
	
	char** sub_dirs = NULL;
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
		if (entry->d_type == DT_REG || entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
		{
			char* full_path = NULL;
			u32_t d_name_len = strlen(entry->d_name);

			arrsetlen(full_path, glob_path_len + d_name_len + 2);
		
			memcpy(full_path, glob_path, glob_path_len);
			full_path[glob_path_len] = '/';
			memcpy(full_path + glob_path_len + 1, entry->d_name, d_name_len + 1);
			
			if (entry->d_type == DT_REG)
				arrput(*glob, full_path);
			else
				arrput(sub_dirs, full_path);
		}

	closedir(dir);
#endif

	for (u32_t i = 0; i < arrlen(sub_dirs); i++)
	{
		lsgfw_glob(glob, sub_dirs[i], pattern);
		arrfree(sub_dirs[i]);
	}

	return LSGFW_SUCCESS;
}

LSGFW_API void lsgfw_free_glob (lsgfw_glob_t glob)
{
	for (u32_t i = 0; i < arrlen(glob); i++)
		arrfree(glob[i]);

	arrfree(glob);
}

