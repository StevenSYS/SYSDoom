#include "action.h"
#include "d_player.h"
#include "p_spec.h"
#include "s_sound.h"

ACTION_RUN {
	if (
		data != NULL &&
		thing->type == MT_PLAYER
	) {
		if (type == ACTTYPE_LINEDEF_USE) {
			P_ChangeSwitchTexture(line, 1);
		}
		thing->player->message = data;
	}
	return 0;
}

ACTION_TYPE(act_message, "message");