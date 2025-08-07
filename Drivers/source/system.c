
#include "system.h"


void System ()
{
	VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;
}
