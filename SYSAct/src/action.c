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
		actions.i[actions.count - 1].reuse = 1;
		actions.i[actions.count - 1].id = 0;
		actions.i[actions.count - 1].inputId = 0;
		
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
	file = SDL_IOFromFile(ACTION_FILE, "w");
	
	if (file == NULL) {
		return 1;
	}
	
	for (i = 0; i < actions.count; i++) {
		SDL_WriteIO(
			file,
			&actions.i[i].type,
			sizeof(unsigned char)
		);
		
		SDL_WriteIO(
			file,
			&actions.i[i].reuse,
			sizeof(char)
		);
		
		SDL_WriteIO(
			file,
			&actions.i[i].id,
			sizeof(unsigned short)
		);
		
		SDL_WriteIO(
			file,
			&actions.i[i].name,
			sizeof(char[ACTION_LENGTH_NAME])
		);
		
		SDL_WriteIO(
			file,
			&actions.i[i].data,
			sizeof(char[ACTION_LENGTH_DATA])
		);
	}
	SDL_CloseIO(file);
	return 0;
}

static int load() {
	file = SDL_IOFromFile(ACTION_FILE, "r");
	
	if (
		file == NULL ||
		SDL_GetIOSize(file) % ACTION_SIZE
	) {
		return 1;
	}
	
	actions.count = SDL_GetIOSize(file) / ACTION_SIZE;
	MULTISTRUCT_RESIZE(action_t, actions, 1);
	
	for (i = 0; i < actions.count; i++) {
		SDL_ReadIO(
			file,
			&actions.i[i].type,
			sizeof(unsigned char)
		);
		
		SDL_ReadIO(
			file,
			&actions.i[i].reuse,
			sizeof(char)
		);
		
		SDL_ReadIO(
			file,
			&actions.i[i].id,
			sizeof(unsigned short)
		);
		
		SDL_ReadIO(
			file,
			&actions.i[i].name,
			sizeof(char[ACTION_LENGTH_NAME])
		);
		
		SDL_ReadIO(
			file,
			&actions.i[i].data,
			sizeof(char[ACTION_LENGTH_DATA])
		);
		
		actions.i[i].inputId = actions.i[i].id;
	}
	SDL_CloseIO(file);
	return 0;
}

static void renderAction(action_t *action) {
	igCheckbox(
		action->type ? LANG_ACTION_SECTOR : LANG_ACTION_LINEDEF,
		(bool *)&action->type
	);
	
	igCheckbox(
		LANG_ACTION_REUSE,
		(bool *)&action->reuse
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