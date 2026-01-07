#include "action.h"
#include "d_player.h"
#include "p_spec.h"
#include "s_sound.h"

ACTION_RUN {
	if (
		thing->type != MT_PLAYER &&
		side == 1
	) {
		return 0;
	}
	
	if (data == NULL) {
		return 1;
	}
	
	if (type == ACTTYPE_LINEDEF_USE) {
		P_ChangeSwitchTexture(line, 1);
	}
	
	thing->player->message = data;
	
	if (!reuse) {
		line->special = 0;
	}
	return 0;
}

ACTION_TYPE(message, "message");