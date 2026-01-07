#include "action.h"
#include "d_player.h"
#include "p_spec.h"
#include "p_mobj.h"

ACTION_RUN {
	if (
		side == 1 ||
		thing->flags & MF_CORPSE ||
		thing->flags2 & MF2_FROZEN
	) {
		return 0;
	}
	
	if (type == ACTTYPE_LINEDEF_USE) {
		P_ChangeSwitchTexture(line, 1);
	}
	
	thing->flags2 |= (MF2_FROZEN | MF2_BREAKABLE);
	
	if (!reuse) {
		line->special = 0;
	}
	return 0;
}

ACTION_TYPE(freeze, "freeze");