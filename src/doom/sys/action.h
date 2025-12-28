#ifndef __ACTION__
#define __ACTION__

#include "r_defs.h"

#include "multistruct.h"

/* Macros */
#define ACTION_RUN \
	static int run( \
		const enum action_type type, \
		const char *data, \
		line_t *line, \
		sector_t *sector, \
		int side, \
		mobj_t *thing \
	) \
	
#define ACTION_TYPE( \
	_vName, \
	_name \
) \
	actionType_t _vName = { \
		_name, \
		&run \
	}

/* Enums */
enum action_type {
	/* Linedef */
	ACTTYPE_LINEDEF_WALK,
	ACTTYPE_LINEDEF_USE,
	ACTTYPE_LINEDEF_SHOOT,
	
	/* Sector */
	ACTTYPE_SECTOR
};

/* Function Typedefs */
typedef int (actRun)(
	const enum action_type,
	const char *,
	line_t *,
	sector_t *,
	int,
	mobj_t *
);

/* Structs */
typedef struct {
	const char *name;
	actRun *run;
} actionType_t;

/* Multistructs */
MULTISTRUCT(actionTypes_t, actionType_t);

/* Functions */
int action_init();
int action_run(
	const enum action_type type,
	const action_t *action,
	line_t *line,
	sector_t *sector,
	int side,
	mobj_t *thing
);
void action_uninit();

#endif