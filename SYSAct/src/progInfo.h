#ifndef __PROGINFO__
#define __PROGINFO__

#include "lang.h"

/* - Program - */
#ifndef PROGRAM_PRE_RELEASE
	#define PROGRAM_PRE_RELEASE 1
#endif

#define PROGRAM_NAME "SYSAct"
#if PROGRAM_PRE_RELEASE
	#define PROGRAM_VERSION "1.0pre"
#else
	#define PROGRAM_VERSION "1.0"
#endif

/* - Path - */
#define PATH_SETTINGS LANG_FILENAME_SETTINGS
#define PATH_GAMELIST LANG_FILENAME_GAME_LIST
#define PATH_REDIRECTS LANG_FILENAME_REDIRECTS

/* - Render - */
#define RENDER_WIDTH 320
#define RENDER_HEIGHT 480

/* - Size - */
#define SIZE_GAMELIST 22

/* - Length - */

/* Misc. */
#define LENGTH_BUFFER 255

/* - Max FPS - */
#define MAX_FPS 30

#endif
