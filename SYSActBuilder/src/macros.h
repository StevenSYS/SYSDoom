#ifndef __MACROS__
#define __MACROS__
	#include "main.h"
	
	/* Errors */
	#define ERROR_MESSAGE(...) \
		char _buffer[255]; \
		SDL_snprintf(_buffer, 255, __VA_ARGS__); \
		SDL_LogError( \
			SDL_LOG_CATEGORY_ERROR, \
			__VA_ARGS__ \
		); \
		SDL_ShowSimpleMessageBox( \
			SDL_MESSAGEBOX_ERROR, \
			"ERROR", \
			_buffer, \
			NULL \
		); \
		main_noWait = 1;
	
	/* Misc. */
	#define ITR(_condission, _ret) \
		if (_condission) { \
			return _ret; \
		}
#endif