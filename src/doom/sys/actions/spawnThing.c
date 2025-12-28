#include <stdio.h>

#include "action.h"
#include "p_local.h"

ACTION_RUN {
	mobj_t *mo;
	
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
		data[0] - '0'
	);
	EV_Teleport(line, side, mo, true);
	return 0;
}

ACTION_TYPE(act_spawnThing, "spawnThing");