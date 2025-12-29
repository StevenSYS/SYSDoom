#ifndef __ACTION__
#define __ACTION__

#include "multistruct.h"

/* Macros */
#define ACTION_FILE "ACTIONS"

#define ACTION_LENGTH_NAME 50
#define ACTION_LENGTH_DATA 100

#define ACTION_SIZE \
	( \
		sizeof(unsigned char) + \
		sizeof(unsigned short) + \
		sizeof(char[ACTION_LENGTH_NAME]) + \
		sizeof(char[ACTION_LENGTH_DATA]) + \
		sizeof(short) \
	)

/* Structs */
typedef struct {
	unsigned char type;
	unsigned short id;
	char name[ACTION_LENGTH_NAME];
	char data[ACTION_LENGTH_DATA];
	short tag;
	int inputId;
	int inputTag;
} action_t;

/* Multistructs */
MULTISTRUCT(actions_t, action_t);

/* Functions */
void action_init();
void action_render();
void action_uninit();

#endif