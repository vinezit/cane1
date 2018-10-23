/*
 * mtu.c

 *
 *  Created on: 2018/09/24
 *      Author: ilove
 */
#include "iodefine.h"
#include "serial.h"
#include "init.h"
#include "define.h"
#include "global.h"
#include "function.h"
#include "sensor.h"

void init_mtu() {

	STB.CR4.BIT._MTU2 = 0; //スタンバイモードoff
	PFC.PECRL1.BIT.PE1MD = 1;
	PFC.PECRL2.BIT.PE5MD = 1;
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;
	MTU2.TRWER.BIT.RWE = 1;
	MTU2.TOER.BYTE = 0xff;
	MTU20.TCNT = 0;
	MTU21.TCNT = 0;
	MTU20.TMDR.BYTE = 0x00; // タイマ通常動作
	MTU21.TMDR.BYTE = 0x00;
	MTU2.TSYR.BIT.SYNC0 = 1; //チャンネル０同期動作
	MTU2.TSYR.BIT.SYNC1 = 1;
	MTU20.TCR.BIT.TPSC = 0; //TCNTのカウンタクロック設定
	MTU21.TCR.BIT.TPSC = 0; //
	MTU20.TCR.BIT.CKEG = 0; //カウント場所	立ち上がり
	MTU21.TCR.BIT.CKEG = 0;
	MTU20.TCR.BIT.CCLR = 1; //カウンタクリア　コンペアマッチでクリア
	MTU21.TCR.BIT.CCLR = 1;
	MTU20.TIOR.BIT.IOA = 1; //TGRA 設定
	MTU20.TIOR.BIT.IOB = 2; //TGRB 設定
	MTU21.TIOR.BIT.IOA = 1;
	MTU21.TIOR.BIT.IOB = 2;
	MTU20.TMDR.BIT.MD = 3;
	MTU21.TMDR.BIT.MD = 3;
	MTU20.TGRA = 10000;
	MTU20.TGRB = 5000;
	MTU21.TGRA = 10000;
	MTU21.TGRB = 5000;
//	duty(10000, 10000); //duty 関数
	MTU20.TIER.BIT.TGIEA = 1;
	MTU21.TIER.BIT.TGIEA = 1;
	MTU20.TSR.BIT.TGFA = 0;
	MTU21.TSR.BIT.TGFA = 0;
	INTC.IPRD.BIT._MTU20G = 15;
	INTC.IPRD.BIT._MTU21G = 15;
//	MTU20.TCNT = 1;
//	MTU21.TCNT = 1;
//	MTU2.TSTR.BIT.CST0 = 1;
//	MTU2.TSTR.BIT.CST1 = 1;
}

void interrput_mtu20() {
	MTU20.TSR.BIT.TGFA = 0;
//	wall_control();

	//ct_global = wall_control();
//	if (speed_global < 200 /*|| motor_L == 0 || motor_R == 0 || log_global < 100*/)
//		ct_global = 0;
	speedR_global = speed_global - ct_global;
//	speedR_global = speed_global;
	dutyr_global = (int) (10112001 / speedR_global);
	MTU20.TGRA = dutyr_global;
	MTU20.TGRB = dutyr_global / 2;

//	LED1 = 1;
}
void interrput_mtu21() {
	MTU21.TSR.BIT.TGFA = 0;
//	wall_control();
	//log_global = logsenL_global - SENLF_global;
//	if (speed_global >= 200 || motor_L != 0 || motor_R != 0)
	//ct_global = wall_control();
//	if (speed_global < 200 /*|| motor_L == 0 || motor_R == 0 || log_global < 100*/)
//		ct_global = 0;
	speedL_global = speed_global + ct_global;
//	speedL_global = speed_global;
	dutyl_global = (int) (10112001 / speedL_global);
	MTU21.TGRA = dutyl_global;
	MTU21.TGRB = dutyl_global / 2;
//	LED2 = 1;
}

