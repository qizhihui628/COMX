#ifndef _MAIN_H
#define _MAIN_H

#include "type.h"
typedef enum
{
	NONE_STANDARD,
	ST_MODEBUS,
	AD_IO_MODBUS,
	PROTOCAL_NUM,
}protocal_mode_enum;
#define CURRENT_PROTOCAL NONE_STANDARD
typedef struct
{
	sc8 *module_name;
	protocal_mode_enum protocal_type;
	u8 com_adr;
}module_cfg_struct;

typedef struct
{
	sc8 *module_name;
	protocal_mode_enum protocal_type;
	u8 com_adr;
}module_ctrl_struct;

#endif
