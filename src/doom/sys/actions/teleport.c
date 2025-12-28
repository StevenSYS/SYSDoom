#include "action.h"
#include "d_player.h"
#include "p_spec.h"

ACTION_RUN {
	switch (type) {
		case ACTTYPE_LINEDEF_USE:
			P_ChangeSwitchTexture(line, 1);
		case ACTTYPE_LINEDEF_SHOOT:
		case ACTTYPE_LINEDEF_WALK:
			EV_Teleport(line, side, thing);
			break;
		default:
			break;
	}
	return 0;
}

ACTION_TYPE(act_teleport, "teleport");