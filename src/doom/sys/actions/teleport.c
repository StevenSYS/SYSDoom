#include "action.h"
#include "d_player.h"
#include "p_spec.h"

ACTION_RUN {
	if (side == 1) {
		return 0;
	}
	
	if (type == ACTTYPE_LINEDEF_USE) {
		P_ChangeSwitchTexture(line, 1);
	}
	
	EV_Teleport(
		line,
		side,
		thing,
		false,
		data == NULL ? false : data[0] != '0'
	);
	
	if (!reuse) {
		line->special = 0;
	}
	return 0;
}

ACTION_TYPE(act_teleport, "teleport");