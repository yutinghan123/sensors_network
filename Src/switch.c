#include "main.h"
BOOL_t Cmd_Exec(PtrQue_TypeDef * cq)
{
	int i;
	SW_Handle_t * sw;
	for (i = 0; i < __PTRQUE_COUNT(cq); i++)
	{
		if (PtrQue_Query(cq, (void **)&sw))
		{
			if (sw->command_new)
				break;
		}
	}
	if (i >= __PTRQUE_COUNT(cq))
		return FALSE;
	SW_Control(sw);
	return TRUE;
}

void SW_Control(SW_Handle_t * sw)
{
	sw->command_new = FALSE;
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
void SW_OFF(SW_Handle_t * sw)
{
	switch (sw->type)
	{
		case SW_FAN:
			break;
		case SW_SUNSHADE:
		case SW_TOPFILM:
		case SW_SIDEFILM:
			K_ON(sw->k1_port, sw->k1_pin);
			K_OFF(sw->k2_port, sw->k2_pin);
			break;
		case SW_LIGHT:
			break;
	}
}
void SW_ON(SW_Handle_t * sw)
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
}
void SW_STOP(SW_Handle_t * sw)
{
	K_OFF(sw->k1_port, sw->k1_pin);
	K_OFF(sw->k2_port, sw->k2_pin);
}
