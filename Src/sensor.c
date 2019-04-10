#include "main.h"
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

void Sensors_Que_Init(PtrQue_TypeDef * sq)
{
	Sensor_Handle_t * sh;
	ModBus_Cmd_Union_t * mbcmd;
	ModBus_Resp_Union_t * mbresp;
	uint16_t mb_crc;
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
		sh->modbus_cmd->cmd.regaddr = 0x0000;
		sh->modbus_cmd->cmd.regcount = 0x0004;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_IHT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的CO2温湿度传感器继续完成初始化
	{
		sh->type = SEN_CO2_T_H;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x02;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = 0x0000;
		sh->modbus_cmd->cmd.regcount = 0x0003;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_CO2HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x03;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = 0x0000;
		sh->modbus_cmd->cmd.regcount = 0x0002;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x04;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = 0x0000;
		sh->modbus_cmd->cmd.regcount = 0x0002;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的土壤温湿度传感器继续完成初始化
	{
		sh->type = SEN_TEMP_HUMI;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_t);
		sh->modbus_cmd->cmd.rs485addr = 0x05;
		sh->modbus_cmd->cmd.funcode = 0x03;
		sh->modbus_cmd->cmd.regaddr = 0x0000;
		sh->modbus_cmd->cmd.regcount = 0x0002;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_HT_t);
	}
	if (PtrQue_Query(sq, (void **)&sh)) //对传感器队列中的电导率盐分传感器继续完成初始化
	{
		sh->type = SEN_COND_SALT;
		sh->mb_cmdsize = sizeof(ModBus_Cmd_Ext_t);
		sh->modbus_cmd->cmd_ext.rs485addr = 0x0a;
		sh->modbus_cmd->cmd_ext.funcode = 0x01;
		sh->modbus_cmd->cmd_ext.datasize = 0x04;
		sh->modbus_cmd->cmd_ext.regaddr = 0x0000;
		sh->modbus_cmd->cmd_ext.regcount = 0x0002;
		mb_crc = crc16_calc(sh->modbus_cmd->cmdbytes, sh->mb_cmdsize - 2);
		sh->modbus_cmd->cmd.crcl = (uint8_t)mb_crc;
		sh->modbus_cmd->cmd.crch = (uint8_t)(mb_crc >> 8);
		sh->mb_respsize = sizeof(ModBus_Resp_CS_t);
	}
}
