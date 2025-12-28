#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif

/* Macros */
#define MULTISTRUCT_MALLOC SDL_malloc
#define MULTISTRUCT_REALLOC SDL_realloc
#define MULTISTRUCT_FREE SDL_free