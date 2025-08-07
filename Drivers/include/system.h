

#include "std_types.h"

#define VTOR                 *((volatile uint32 *)(0xe000ed08UL))
#define FLASH_BASE              0x08000000U 
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE 
#define VECT_TAB_OFFSET         0x00008000U 