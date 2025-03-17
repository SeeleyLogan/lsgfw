#define LS_PLUGS_IMPLEMENTATION
#include <ls_plugs.h>
#include <stdio.h>

typedef unsigned 	char		bool_t;
typedef unsigned 	char		u8_t;
typedef signed		char		i8_t;
typedef unsigned 	short		u16_t;
typedef signed		short		i16_t;
typedef unsigned 	long		u32_t;
typedef signed		long		i32_t;
typedef unsigned	long long	u64_t;
typedef signed		long long	i64_t;

ls_plugs_outlet_t outlet = LS_PLUGS_NEW_OUTLET;

int main()
{
    ls_plugs_load_plugs(&outlet, "./scripts", "*.so");
    printf("%d\n", arrlenu(outlet.plug_handle_v));
}