#include <stdio.h>
#include <string.h>

#include "action.h"

#define REGISTER( \
	_vName, \
	_var, \
	_type \
) \
	if (_var.i != NULL) { \
		extern _type _vName; \
		_var.i[_var.count] = _vName; \
	} \
	_var.count++;

#define ACTION_REGISTER(_vName) \
	REGISTER( \
		act_ ## _vName, \
		types, \
		actionType_t \
	)

#define TYPE_REGISTER(_func, _var, _type, _label) \
	_label: \
	_func(&_var); \
	\
	if ( \
		_var.i == NULL && \
		_var.count \
	) { \
		MULTISTRUCT_INIT(_type, _var, 1); \
		_var.count = 0; \
		goto _label; \
	}

static actionTypes_t types;

static void regAct() {
	ACTION_REGISTER(freeze);
	ACTION_REGISTER(message);
	ACTION_REGISTER(spawnThing);
	ACTION_REGISTER(teleport);
	return;
}

int action_init() {
	TYPE_REGISTER(
		regAct,
		types,
		actionType_t,
		actReg
	);
	return 0;
}

int action_run(
	const enum action_type type,
	const action_t *action,
	const char reuse,
	line_t *line,
	sector_t *sector,
	int side,
	mobj_t *thing
) {
	unsigned int i;
	
	if (
		action == NULL ||
		action->name == NULL
	) {
		return 1;
	}
	
	for (i = 0; i < types.count; i++) {
		if (strcmp(action->name, types.i[i].name) == 0) {
			return types.i[i].run(
				type,
				reuse,
				action->data,
				line,
				sector,
				side,
				thing
			);
		}
	}
	
	fprintf(stderr, "Action: Unknown action: %s\n", action->name);
	return 1;
}

void action_uninit() {
	MULTISTRUCT_UNINIT(types);
	return;
}