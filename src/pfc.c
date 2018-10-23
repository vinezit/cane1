/*
 * pfc.c
 *
 *  Created on: 2018/08/11
 *      Author: ilove
 */
#include "iodefine.h"
#include "serial.h"
#include "init.h"
void pfcall(void){
	PFC.PEIORL.BIT.B0 = 1;
	PFC.PEIORL.BIT.B1 = 1;
	PFC.PEIORL.BIT.B2 = 1;
	PFC.PEIORL.BIT.B4 = 1;
	PFC.PEIORL.BIT.B5 = 1;
	PFC.PEIORL.BIT.B6 = 1;
	PFC.PEIORL.BIT.B8 = 1;

	PFC.PEIORL.BIT.B10 = 1;
	PFC.PAIORL.BIT.B15 = 0;
	PFC.PAIORL.BIT.B6 = 0;
	PFC.PAIORL.BIT.B7 = 0;
	PFC.PAIORL.BIT.B8 = 0;
	PFC.PAIORL.BIT.B11 = 1;
	PFC.PAIORL.BIT.B12 = 1;
	PFC.PAIORL.BIT.B13 = 1;
	PFC.PAIORL.BIT.B14 = 1;
	PFC.PAIORL.BIT.B15 = 1;
	PFC.PBIORL.BIT.B2 = 1; //PB2の入力設定
	PFC.PBIORL.BIT.B3 = 1;
	PFC.PBIORL.BIT.B5 = 1;
	PFC.PEIORL.BIT.B0 = 1;
	PFC.PEIORL.BIT.B1 = 1;
	PFC.PEIORL.BIT.B3 = 1;
	PFC.PEIORL.BIT.B4 = 1;
	PFC.PEIORL.BIT.B5 = 1;
}

