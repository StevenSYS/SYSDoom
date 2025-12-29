#include <stdio.h>

#include "action.h"
#include "p_local.h"

ACTION_RUN {
	const char *idStr = data + 1;
	
	mobj_t *mo;
	
	if (side == 1) {
		return 0;
	}
	
	if (data == NULL) {
		return 1;
	}
	
	if (type == ACTTYPE_LINEDEF_USE) {
		P_ChangeSwitchTexture(line, reuse);
	}
	
	mo = P_SpawnMobj(
		-0x7FFFFFFF,
		-0x7FFFFFFF,
		-0x7FFFFFFF,
		atoi(idStr)
	);
	EV_Teleport(line, side, mo, true, data[0] != '0');
	
	if (!reuse) {
		line->special = 0;
	}
	return 0;
}

ACTION_TYPE(act_spawnThing, "spawnThing");