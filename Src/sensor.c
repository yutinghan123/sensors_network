#include "main.h"
const char * SENS_TYPE_STR[] = {"SEN_TEMP_HUMI", "SEN_ILLUM_T_H", "SEN_CO2_T_H", "SEN_COND_SALT"};
/*发送传感器Modbus命令*/
BOOL_t Modbus_Send_Cmd(Sensor_Handle_t * hs)
{
	return TRUE;
}
/*接收传感器Modbus响应*/
BOOL_t Modbus_Receive_Resp(Sensor_Handle_t * hs)
{	
	return TRUE;
}

//
BOOL_t Modbus_Data_Proc(Sensor_Handle_t * hs, void * result)
{
	return TRUE;
}

/*解析传感器数据，以指针形式返回解析结果*/
BOOL_t Sens_Data_Proc(Sensor_Handle_t * hs)
{
	return TRUE;
}

void Sensors_Polling(PtrQue_TypeDef * sq)
{
	int i;
	Sensor_Handle_t * hs;
	for (i = 0; i < __PTRQUE_COUNT(sq); i++)
	{
		if (PtrQue_Query(sq, (void **)&hs))
		{
			Modbus_Send_Cmd(hs);
			HAL_Delay(MODBUS_TIMEOUT);
			if (Modbus_Receive_Resp(hs)) {
				
			}
		}
	}
}

#if (DEBUG_ON == 1)
void Sensors_Que_Print(PtrQue_TypeDef * sq)
{
	int i, j;
	Sensor_Handle_t * sh;
	printf("\r\n ######## sensors que ########\r\n");
	for (i = 0; i < __PTRQUE_COUNT(sq); i++)
	{
		printf("***** Sensor %d *****\r\n", i + 1);
		PtrQue_Query(sq, (void **)&sh);
		printf("type: %s\r\n", SENS_TYPE_STR[sh->type]);
		printf("modbus command: ");
		for (j = 0; j < sh->mb_cmdsize; j++) {
			printf("0x%x ", sh->modbus_cmd->cmdbytes[j]);
		}
		printf("\r\n");
		printf("modbus response: ");
		for (j = 0; j < sh->mb_respsize; j++) {
			printf("0x%x ", sh->modbus_resp->respbytes[j]);
		}
		printf("\r\n");
	}
	printf("\r\n #############################\r\n");
}
#endif

void Sensors_Que_Init(PtrQue_TypeDef * sq)
{
	Sensor_Handle_t * sh;
	ModBus_Cmd_Union_t * mbcmd;
	ModBus_Resp_Union_t * mbresp;
	int i;
	for (i = 0; i < PTRQUESIZE; i++) //初始化传感器队列，并完成传感器句柄部分初始化
	{
		sh = (Sensor_Handle_t *)malloc(sizeof(Sensor_Handle_t));
		mbcmd = (ModBus_Cmd_Union_t *)malloc(sizeof(ModBus_Cmd_Union_t));
		mbresp = (ModBus_Resp_Union_t *)malloc(sizeof(ModBus_Resp_Union_t));
		sh->modbus_cmd = mbcmd;
		sh->modbus_resp = mbresp;
		PtrQue_In(sq, (void *)sh);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的光照温湿度传感器继续完成初始化
	{
		sh->type = SEN_ILLUM_T_H;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x01;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd.regcount = l2b16(0x0004u);
		sh->modbus_cmd->cmd.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_IHT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的CO2温湿度传感器继续完成初始化
	{
		sh->type = SEN_CO2_T_H;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x02;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd.regcount = l2b16(0x0003u);
		sh->modbus_cmd->cmd.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_CO2HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x03;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd.regcount = l2b16(0x0002u);
		sh->modbus_cmd->cmd.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x04;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd.regcount = l2b16(0x0002u);
		sh->modbus_cmd->cmd.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x05;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd.regcount = l2b16(0x0002u);
		sh->modbus_cmd->cmd.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的电导率盐分传感器继续完成初始化
	{
		sh->type = SEN_COND_SALT;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_Ext_t);
		sh->modbus_cmd->cmd_ext.rs485addr = 0x0a;
		sh->modbus_cmd->cmd_ext.funcode = 0x01;
		sh->modbus_cmd->cmd_ext.datasize = 0x04;
		sh->modbus_cmd->cmd_ext.regaddr = l2b16(0x0000u);
		sh->modbus_cmd->cmd_ext.regcount = l2b16(0x0002u);
		sh->modbus_cmd->cmd_ext.crc16 = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->mb_respsize = sizeof(ModBus_Resp_CS_t);
	}
#if (DEBUG_ON == 1)
	Sensors_Que_Print(sq);
#endif
}
