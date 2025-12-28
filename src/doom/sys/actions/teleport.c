#include "action.h"
#include "d_player.h"
#include "p_spec.h"

ACTION_RUN {
	if (type == ACTTYPE_LINEDEF_USE) {
		P_ChangeSwitchTexture(line, 1);
	}
	EV_Teleport(line, side, thing, false);
	return 0;
}

ACTION_TYPE(act_teleport, "teleport");
