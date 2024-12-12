LSGFW_API void* lsgfw_get_shared_lib_handle(const char* file_path)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	HINSTANCE handle = LoadLibrary(file_path);	
#else
	void* handle = dlopen(file_path, RTLD_NOW);
#endif

	if (!handle)
		return LSGFW_SHARED_LIB_LOAD_FAILED;

	return handle;
}

LSGFW_API void* lsgfw_get_shared_lib_func(void* handle, const char* func_name)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	void (*func_addr)() = (void*) GetProcAddress(handle, func_name);
#else
	void (*func_addr)() = dlsym(handle, func_name);
#endif

	return func_addr;
}

LSGFW_API void lsgfw_close_shared_lib(void* handle)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	FreeLibrary(handle);
#else
	dlclose(handle);
#endif
}

