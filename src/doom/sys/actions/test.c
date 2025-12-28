#include <stdio.h>

#include "action.h"

ACTION_RUN {
	printf("Test - %u\n", type);
	return 0;
}

ACTION_TYPE(act_test, "test");