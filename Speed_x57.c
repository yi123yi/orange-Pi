#include "Speed_x57.h"
#include <stdbool.h>
/**********************************************************
***	ZDT_X57步进闭环控制例程
**********************************************************/

/**
	*	@brief		将当前位置清零
	*	@param		addr	：电机地址
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
uint8_t cmd[16] = {0}; 

void ZDT_X57_Reset_CurPos_To_Zero(uint8_t addr)
{
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0x0A;												// 功能码
	cmd[2] =  0x6D;												// 辅助码
	cmd[3] =  0x6B;												// 校验字节

}

/**
	*	@brief		解除过压保护/过流保护/过热保护/堵转保护
	*	@param		addr	：电机地址
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Reset_Clog_Pro(uint8_t addr)
{
	 
	
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0x0E;												// 功能码
	cmd[2] =  0x52;												// 辅助码
	cmd[3] =  0x6B;												// 校验字节
}

/**
	*	@brief		读取系统参数
	*	@param		addr	：电机地址
	*	@param		s			：系统参数类型
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Read_Sys_Params(uint8_t addr, SysParams_t s)
{
	
	
	// 装载命令
	cmd[0] =  addr;												// 地址

	switch(s)															// 功能码
	{
		case S_VER	: cmd[1] = 0x1F; break;
		case S_RL		: cmd[1] = 0x20; break;
		case S_PID	: cmd[1] = 0x21; break;
		case S_VBUS	: cmd[1] = 0x24; break;
		case S_CBUS	: cmd[1] = 0x26; break;
		case S_CPHA	: cmd[1] = 0x27; break;
		case S_ENC	: cmd[1] = 0x30; break;
		case S_ENCL	: cmd[1] = 0x31; break;
		case S_TPOS	: cmd[1] = 0x33; break;
		case S_VEL	: cmd[1] = 0x35; break;
		case S_CPOS	: cmd[1] = 0x36; break;
		case S_PERR	: cmd[1] = 0x37; break;
		case S_TEMP	: cmd[1] = 0x39; break;
		case S_FLAG	: cmd[1] = 0x3A; break;
		case S_Conf	: cmd[1] = 0x42; break;
		case S_State: cmd[1] = 0x43; break;
		default: break;
	}

	cmd[2] =  0x6B;												// 校验字节
	
}
/**
	*	@brief		使能信号控制
	*	@param		addr	：电机地址
	*	@param		state	：使能状态			，true为使能电机，false为关闭电机
	*	@param		multi	：多机同步标志	，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_En_Control(uint8_t addr, bool state, uint8_t multi)
{

	
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xF3;												// 功能码
	cmd[2] =  0xAB;												// 辅助码
	cmd[3] =  (uint8_t)state;							// 使能状态
	cmd[4] =  multi;											// 多机同步运动标志
	cmd[5] =  0x6B;												// 校验字节

}
/**
	*	@brief		力矩模式
	*	@param		addr	：电机地址
	*	@param		sign	：符号					，0为正，其余值为负
	*	@param		t_ramp：斜率(Ma/s)		，范围0 - 65535Ma/s
	*	@param		torque：力矩(Ma)			，范围0 - 4000Ma
	*	@param		multi	：多机同步标志	，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Torque_Control(uint8_t addr, uint8_t sign, uint16_t t_ramp, uint16_t torque, uint8_t multi)
{
	
	
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xF5;												// 功能码
	cmd[2] =  sign;												// 符号（方向）
	cmd[3] =  (uint8_t)(t_ramp >> 8);			// 力矩斜率(Ma/s)高8位字节
	cmd[4] =  (uint8_t)(t_ramp >> 0);			// 力矩斜率(Ma/s)低8位字节
	cmd[5] =  (uint8_t)(torque >> 8);			// 力矩(Ma)高8位字节
	cmd[6] =  (uint8_t)(torque >> 0);			// 力矩(Ma)低8位字节
	cmd[7] =  multi;											// 多机同步运动标志
	cmd[8] =  0x6B;												// 校验字节
	
}

/**
	*	@brief		速度模式
	*	@param		addr	：电机地址
	*	@param		dir			：方向					，0为CW，其余值为CCW
	*	@param		v_ramp	：斜率(RPM/s)	，范围0 - 65535RPM/s
	*	@param		velocity：速度(RPM)		，范围0.0 - 4000.0RPM
	*	@param		multi		：多机同步标志	，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Velocity_Control(uint8_t addr, uint8_t dir, uint16_t v_ramp, float velocity, uint8_t multi)
{
	
	uint16_t vel = 0;

	// 将速度放大10倍发送过去
	vel = (uint16_t)ABS(velocity * 10.0f);

	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xF6;												// 功能码
	cmd[2] =  dir;												// 符号（方向）
	cmd[3] =  (uint8_t)(v_ramp >> 8);			// 速度斜率(RPM/s)高8位字节
	cmd[4] =  (uint8_t)(v_ramp >> 0);			// 速度斜率(RPM/s)低8位字节
	cmd[5] =  (uint8_t)(vel >> 8);				// 速度(RPM)高8位字节
	cmd[6] =  (uint8_t)(vel >> 0);				// 速度(RPM)低8位字节
	cmd[7] =  multi;											// 多机同步运动标志
	cmd[8] =  0x6B;												// 校验字节
}

/**
	*	@brief		直通位置模式
	*	@param		addr	：电机地址
	*	@param		dir			：方向										，0为CW，其余值为CCW
	*	@param		position：位置(°)								，范围0.0°- (2^32 - 1)°
	*	@param		raf			：相位位置/绝对位置标志	，0为相对位置，其余值为绝对位置
	*	@param		multi		：多机同步标志						，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Bypass_Position_Control(uint8_t addr, uint8_t dir, float position, uint8_t raf, uint8_t multi)
{
	 uint32_t pos = 0;

	// 将位置放大10倍发送过去
	pos = (uint32_t)ABS(position * 10.0f);

	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xFA;												// 功能码
	cmd[2] =  dir;												// 符号（方向）
	cmd[3] =  (uint8_t)(pos >> 24);				// 位置(bit24 - bit31)
	cmd[4] =  (uint8_t)(pos >> 16);				// 位置(bit16 - bit23)
	cmd[5] =  (uint8_t)(pos >> 8);				// 位置(bit8  - bit15)
	cmd[6] =  (uint8_t)(pos >> 0);				// 位置(bit0  - bit7 )
	cmd[7] =  raf;												// 相位位置/绝对位置标志
	cmd[8] =  multi;											// 多机同步运动标志
	cmd[9] =  0x6B;												// 校验字节
}

/**
	*	@brief		直通位置限速模式
	*	@param		addr	：电机地址
	*	@param		dir			：方向										，0为CW，其余值为CCW
	*	@param		velocity：最大速度(RPM)					，范围0.0 - 4000.0RPM
	*	@param		position：位置(°)								，范围0.0°- (2^32 - 1)°
	*	@param		raf			：相位位置/绝对位置标志	，0为相对位置，其余值为绝对位置
	*	@param		multi		：多机同步标志						，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Bypass_Position_LV_Control(uint8_t addr, uint8_t dir, float velocity, float position, uint8_t raf, uint8_t multi)
{
	 uint16_t vel = 0;uint32_t pos = 0;

	// 将速度和位置放大10倍发送过去
	vel = (uint16_t)ABS(velocity * 10.0f); pos = (uint32_t)ABS(position * 10.0f);

	// 装载命令
	cmd[0]  =  addr;											// 地址
	cmd[1]  =  0xFB;											// 功能码
	cmd[2]  =  dir;												// 符号（方向）
	cmd[3]  =  (uint8_t)(vel >> 8);				// 最大速度(RPM)高8位字节
	cmd[4]  =  (uint8_t)(vel >> 0);				// 最大速度(RPM)低8位字节	
	cmd[5]  =  (uint8_t)(pos >> 24);			// 位置(bit24 - bit31)
	cmd[6]  =  (uint8_t)(pos >> 16);			// 位置(bit16 - bit23)
	cmd[7]  =  (uint8_t)(pos >> 8);				// 位置(bit8  - bit15)
	cmd[8]  =  (uint8_t)(pos >> 0);				// 位置(bit0  - bit7 )
	cmd[9]  =  raf;												// 相位位置/绝对位置标志
	cmd[10] =  multi;											// 多机同步运动标志
	cmd[11] =  0x6B;											// 校验字节
	
}

/**
	*	@brief		梯形曲线位置模式
	*	@param		addr	：电机地址
	*	@param		dir			：方向										，0为CW，其余值为CCW
	*	@param		acc			：加速加速度(RPM/s)			，0为CW，其余值为CCW
	*	@param		dec			：减速加速度(RPM/s)			，0为CW，其余值为CCW
	*	@param		velocity：最大速度(RPM)					，范围0.0 - 4000.0RPM
	*	@param		position：位置(°)								，范围0.0°- (2^32 - 1)°
	*	@param		raf			：相位位置/绝对位置标志	，0为相对位置，其余值为绝对位置
	*	@param		multi		：多机同步标志						，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Traj_Position_Control(uint8_t addr, uint8_t dir, uint16_t acc, uint16_t dec, float velocity, float position, uint8_t raf, uint8_t multi)
{
	 uint16_t vel = 0; uint32_t pos = 0;

	// 将速度和位置放大10倍发送过去
	vel = (uint16_t)ABS(velocity * 10.0f); pos = (uint32_t)ABS(position * 10.0f);

	// 装载命令
	cmd[0]  =  addr;											// 地址
	cmd[1]  =  0xFD;											// 功能码
	cmd[2]  =  dir;												// 符号（方向）
	cmd[3]  =  (uint8_t)(acc >> 8);				// 加速加速度(RPM/s)高8位字节
	cmd[4]  =  (uint8_t)(acc >> 0);				// 加速加速度(RPM/s)低8位字节	
	cmd[5]  =  (uint8_t)(dec >> 8);				// 减速加速度(RPM/s)高8位字节
	cmd[6]  =  (uint8_t)(dec >> 0);				// 减速加速度(RPM/s)低8位字节	
	cmd[7]  =  (uint8_t)(vel >> 8);				// 最大速度(RPM)高8位字节
	cmd[8]  =  (uint8_t)(vel >> 0);				// 最大速度(RPM)低8位字节	
	cmd[9]  =  (uint8_t)(pos >> 24);			// 位置(bit24 - bit31)
	cmd[10] =  (uint8_t)(pos >> 16);			// 位置(bit16 - bit23)
	cmd[11] =  (uint8_t)(pos >> 8);				// 位置(bit8  - bit15)
	cmd[12] =  (uint8_t)(pos >> 0);				// 位置(bit0  - bit7 )
	cmd[13] =  raf;												// 相位位置/绝对位置标志
	cmd[14] =  multi;											// 多机同步运动标志
	cmd[15] =  0x6B;											// 校验字节
	
}

/**
	*	@brief		立即停止（所有控制模式都通用）
	*	@param		addr	：电机地址
	*	@param		multi	：多机同步标志，0为不启用，其余值启用
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Stop_Now(uint8_t addr, uint8_t multi)
{
	
	
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xFE;												// 功能码
	cmd[2] =  0x98;												// 辅助码
	cmd[3] =  multi;											// 多机同步运动标志
	cmd[4] =  0x6B;												// 校验字节
	
}

/**
	*	@brief		多机同步运动
	*	@param		addr	：电机地址
	*	@retval		地址 + 功能码 + 命令状态 + 校验字节
	*/
void ZDT_X57_Synchronous_motion(uint8_t addr)
{
	
	// 装载命令
	cmd[0] =  addr;												// 地址
	cmd[1] =  0xFF;												// 功能码
	cmd[2] =  0x66;												// 辅助码
	cmd[3] =  0x6B;												// 校验字节
	
}
