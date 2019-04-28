#include "main.h"
void SW_Que_Init(PtrQue_TypeDef * swq)
{
}
BOOL_t SW_Cmd_Exec(PtrQue_TypeDef * swq)
{
	int i;
	SW_Handle_t * sw;
	for (i = 0; i < __PTRQUE_COUNT(swq); i++)
	{
		if (PtrQue_Query(swq, (void **)&sw))
		{
			if (sw->command_new)
				break;
		}
	}
	if (i >= __PTRQUE_COUNT(swq))
		return FALSE;
	SW_Control(sw);
	return TRUE;
}

void SW_Control(SW_Handle_t * sw)
{
	sw->command_new = FALSE;
	if (sw->status == sw->action)
	{
		sw->result = RES_KEEP;
		return;
	}
	switch (sw->action)
	{
		case ACT_OFF:
			SW_OFF(sw);
			break;
		case ACT_ON:
			SW_ON(sw);
			break;
		case ACT_STOP:
			SW_STOP(sw);
			break;
	}
}
CommandResType_t SW_OFF(SW_Handle_t * sw)
{
	CommandResType_t res;
	switch (sw->type)
	{
		case SW_FAN:
			res = RES_FAILED;
			break;
		case SW_SUNSHADE:
		case SW_TOPFILM:
		case SW_SIDEFILM:
			K_ON(sw->k1_port, sw->k1_pin);
			K_OFF(sw->k2_port, sw->k2_pin);
			sw->status = ACT_OFF;
			res = RES_OK;
			break;
		case SW_LIGHT:
			res = RES_FAILED;
			break;
	}
	return res;
}
CommandResType_t SW_ON(SW_Handle_t * sw)
{
	switch (sw->type)
	{
		case SW_FAN:
		case SW_SUNSHADE:
		case SW_TOPFILM:
		case SW_SIDEFILM:
			K_OFF(sw->k1_port, sw->k1_pin);
			K_ON(sw->k2_port, sw->k2_pin);
			break;
		case SW_LIGHT:
			K_ON(sw->k1_port, sw->k1_pin);
			K_OFF(sw->k2_port, sw->k2_pin);
			break;
	}
	sw->status = ACT_ON;
	return RES_OK;
}
CommandResType_t SW_STOP(SW_Handle_t * sw)
{
	K_OFF(sw->k1_port, sw->k1_pin);
	K_OFF(sw->k2_port, sw->k2_pin);
	sw->status = ACT_OFF;
	return RES_OK;
}
