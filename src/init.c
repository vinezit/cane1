/*
 * init.c
 *
 *  Created on: 2017/08/30
 *      Author: ilove
 */

#include "iodefine.h"
#include "serial.h"
#include "init.h"



void initCMT(void)	//CMT割込の設定
{
	STB.CR4.BIT._CMT = 0;	//CMTスタンバイ解除

	//  (1)コンペアマッチタイマスタートレジスタ（CMSTR）
	CMT.CMSTR.BIT.STR0 = 0;	// ステータスレジスタ　0：カウント停止, 1：カウント開始

	//  (2)コンペアマッチタイマコントロール／ステータスレジスタ（CMCSR）
	CMT0.CMCSR.BIT.CMIE = 1;     //割り込みイネーブル許可
	CMT0.CMCSR.BIT.CKS = 0;     //1/8
	CMT0.CMCSR.BIT.CMF = 0;     //フラグをクリア
	CMT0.CMCOR = 3124;  //割り込み周期
	INTC.IPRJ.BIT._CMT0 = 15;  //割り込み優先度(15)
	CMT.CMSTR.BIT.STR0 = 1;
}



