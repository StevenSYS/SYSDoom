#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui/cimgui.h>
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif

#include "lang.h"
#include "macros.h"
#include "action.h"

#define SAVELOAD(_func) \
	for (i = 0; i < actions.count; i++) { \
		/* Clear any unneeded data after the first NULL terminator from the name and data variables */ \
		CLEAN(actions.i[i].name, ACTION_LENGTH_NAME); \
		CLEAN(actions.i[i].data, ACTION_LENGTH_DATA); \
		\
		_func( \
			file, \
			&actions.i[i].type, \
			sizeof(unsigned char) \
		); \
		\
		_func( \
			file, \
			&actions.i[i].id, \
			sizeof(unsigned short) \
		); \
		\
		_func( \
			file, \
			&actions.i[i].name, \
			sizeof(char[ACTION_LENGTH_NAME]) \
		); \
		\
		_func( \
			file, \
			&actions.i[i].data, \
			sizeof(char[ACTION_LENGTH_DATA]) \
		); \
		\
		_func( \
			file, \
			&actions.i[i].tag, \
			sizeof(short) \
		); \
		\
		actions.i[i].inputId = (int)actions.i[i].id; \
		actions.i[i].inputTag = (int)actions.i[i].tag; \
	}

#define CLEAN(_var, _len) \
	active = 0; \
	\
	for (j = 0; j < _len; j++) { \
		if ( \
			active && \
			_var[j] \
		) { \
			_var[j] = 0; \
		} else if ( \
			!active && \
			!_var[j] \
		) { \
			active = 1; \
		} \
	}

static unsigned int i;

static SDL_IOStream *file;

static actions_t actions = {
	NULL,
	0
};

static int addAct() {
	if (actions.count < 0xFFFFFFFF) {
		actions.count++;
		
		MULTISTRUCT_RESIZE(action_t, actions, 1);
		
		actions.i[actions.count - 1].type = 0;
		actions.i[actions.count - 1].id = 0;
		actions.i[actions.count - 1].tag = -1;
		actions.i[actions.count - 1].inputId = 0;
		actions.i[actions.count - 1].inputTag = -1;
		
		for (i = 0; i < ACTION_LENGTH_NAME; i++) {
			actions.i[actions.count - 1].name[i] = 0;
		}
		
		for (i = 0; i < ACTION_LENGTH_DATA; i++) {
			actions.i[actions.count - 1].data[i] = 0;
		}
	}
	return 0;
}

static int removeAct() {
	if (actions.count > 0) {
		actions.count--;
		
		MULTISTRUCT_RESIZE(action_t, actions, 1);
	}
	return 0;
}

static int save() {
	char active;
	unsigned char j;
	
	file = SDL_IOFromFile(ACTION_FILE, "w");
	
	if (file == NULL) {
		return 1;
	}
	
	SAVELOAD(SDL_WriteIO);
	SDL_CloseIO(file);
	return 0;
}

static int load() {
	char active;
	unsigned char j;
	
	file = SDL_IOFromFile(ACTION_FILE, "r");
	
	if (
		file == NULL ||
		SDL_GetIOSize(file) % ACTION_SIZE
	) {
		return 1;
	}
	
	actions.count = SDL_GetIOSize(file) / ACTION_SIZE;
	MULTISTRUCT_RESIZE(action_t, actions, 1);
	
	SAVELOAD(SDL_ReadIO);
	SDL_CloseIO(file);
	return 0;
}

static void renderAction(action_t *action) {
	igCheckbox(
		LANG_ACTION_SECTOR,
		(bool *)&action->type
	);
	
	if (igInputInt(
		LANG_ACTION_ID,
		&action->inputId,
		1,
		2,
		ImGuiInputTextFlags_None
	)) {
		if (action->inputId > 0xFFFF) {
			action->inputId = 0xFFFF;
		} else if (action->inputId < 0) {
			action->inputId = 0;
		}
		
		action->id = (unsigned short)action->inputId;
	}
	
	if (igInputInt(
		LANG_ACTION_TAG,
		&action->inputTag,
		1,
		2,
		ImGuiInputTextFlags_None
	)) {
		if (action->inputTag > 0x7FFF) {
			action->inputTag = 0x7FFF;
		} else if (action->inputTag < -0x7FFF) {
			action->inputTag = -0x7FFF;
		}
		
		action->tag = (short)action->inputTag;
	}
	
	igInputText(
		LANG_ACTION_NAME,
		action->name,
		ACTION_LENGTH_NAME,
		ImGuiInputTextFlags_None,
		NULL,
		NULL
	);
	
	igInputText(
		LANG_ACTION_DATA,
		action->data,
		ACTION_LENGTH_DATA,
		ImGuiInputTextFlags_None,
		NULL,
		NULL
	);
	return;
}

void action_init() {
	if (load()) {
		actions.count = 0;
	}
	return;
}

void action_render() {
	for (i = 0; i < actions.count; i++) {
		igPushID_Int(i);
		renderAction(&actions.i[i]);
		igSeparator();
		igPopID();
	}
	
	if (igButton("+", (ImVec2){ 0.0f, 0.0f })) {
		addAct();
	}
	
	igSameLine(30.0f, 0.0f);
	
	if (igButton("-", (ImVec2){ 0.0f, 0.0f })) {
		removeAct();
	}
	
	if (igButton(LANG_ACTION_SAVE, (ImVec2){ 0.0f, 0.0f })) {
		if (save()) {
			ERROR_MESSAGE(
				LANG_ERROR_SAVE,
				SDL_GetError()
			);
		}
	}
	
	if (igButton(LANG_ACTION_LOAD, (ImVec2){ 0.0f, 0.0f })) {
		if (load()) {
			ERROR_MESSAGE(
				LANG_ERROR_LOAD,
				SDL_GetError()
			);
		}
	}
	return;
}

void action_uninit() {
	MULTISTRUCT_UNINIT(actions);
	return;
}