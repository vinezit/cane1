/*
 * sensor.c
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
#include "mtu.h"
#include "sensor.h"

void initAD(void) {
	STB.CR4.BIT._AD0 = 0;	//AD0設定
	AD0.ADCR.BIT.ADST = 0;
	AD0.ADCSR.BIT.ADCS = 0;
	AD0.ADCSR.BIT.TRGE = 0;
	AD0.ADCSR.BIT.CKSL = 0;
	AD0.ADCSR.BIT.ADIE = 0;
	AD0.ADCSR.BIT.ADM = 0;
	AD0.ADCSR.BIT.CH = 0;

	STB.CR4.BIT._AD1 = 0;	//AD1設定
	AD1.ADCR.BIT.ADST = 0;
	AD1.ADCSR.BIT.ADCS = 0;
	AD1.ADCSR.BIT.TRGE = 0;
	AD1.ADCSR.BIT.CKSL = 0;
	AD1.ADCSR.BIT.ADIE = 0;
	AD1.ADCSR.BIT.ADM = 0;
	AD1.ADCSR.BIT.CH = 0;
}


void sensor() {
	int charge_time = 0, Senvalue1 = 0, Senvalue2 = 0;
//	AD0.ADCR.BIT.ADST = 0; //左下センサAD変換開始
//	AD0.ADCSR.BIT.CH = 3;
//	AD0.ADCR.BIT.ADST = 1;
//
//	while (AD0.ADCSR.BIT.ADF == 0)
//		;
//	AD0.ADCSR.BIT.ADF = 0;
//	charge_time = 0;
//	LEDLB = 1;
//	Senvalue1 = AD0.ADDR3 >> 6;
//
//	while (charge_time <= LEDTIME1)
//		charge_time++;
//
//	AD0.ADCR.BIT.ADST = 0;
//	AD0.ADCSR.BIT.CH = 3;
//	AD0.ADCR.BIT.ADST = 1;
//	while (AD0.ADCSR.BIT.ADF == 0)
//		;
//	AD0.ADCSR.BIT.ADF = 0;
//	charge_time = 0;
//	LEDLB = 0;
//
//	while (charge_time <= LEDTIME2)
//		charge_time++;
//	Senvalue2 = AD0.ADDR3 >> 6;
//	SENLB_global = Senvalue2 - Senvalue1; //左下センサAD変化終了

	Senvalue1 = 0, Senvalue2 = 0;
	AD1.ADCR.BIT.ADST = 0; //真ん中センサAD変化開始
	AD1.ADCSR.BIT.CH = 0;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
//	LEDC = 1;
	charge_time = 0;
	LEDC = 1;
	Senvalue1 = AD1.ADDR4 >> 6;
	while (charge_time <= LEDTIME1)
		charge_time++;

	AD1.ADCR.BIT.ADST = 0;
	AD1.ADCSR.BIT.CH = 0;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
	charge_time = 0;
	LEDC = 0;
	Senvalue2 = AD1.ADDR4 >> 6;
	while (charge_time <= LEDTIME2)
		charge_time++;

	SENC_global = Senvalue2 - Senvalue1; //真ん中センサAD変換終了

	Senvalue1 = 0, Senvalue2 = 0;
	AD1.ADCR.BIT.ADST = 0; //左前センサAD変換開始
	AD1.ADCSR.BIT.CH = 1;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
//	LEDLF = 1;
	charge_time = 0;
	LEDLF = 1;
	Senvalue1 = AD1.ADDR5 >> 6;
	while (charge_time <= LEDTIME1)
		charge_time++;

	AD1.ADCR.BIT.ADST = 0;
	AD1.ADCSR.BIT.CH = 1;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
	charge_time = 0;
	LEDLF = 0;

	while (charge_time <= LEDTIME2)
		charge_time++;
	Senvalue2 = AD1.ADDR5 >> 6;
	SENLF_global = Senvalue2 - Senvalue1; //左前センサAD変換終了

	Senvalue1 = 0, Senvalue2 = 0;
	AD1.ADCR.BIT.ADST = 0; //右前センサAD変換開始
	AD1.ADCSR.BIT.CH = 2;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
//	LEDRF = 1;
	charge_time = 0;
	LEDRF = 1;
	Senvalue1 = AD1.ADDR6 >> 6;
	while (charge_time <= LEDTIME1)
		charge_time++;

	AD1.ADCR.BIT.ADST = 0;
	AD1.ADCSR.BIT.CH = 2;
	AD1.ADCR.BIT.ADST = 1;
	while (AD1.ADCSR.BIT.ADF == 0)
		;
	AD1.ADCSR.BIT.ADF = 0;
	charge_time = 0;
	LEDRF = 0;
	Senvalue2 = AD1.ADDR6 >> 6;
	while (charge_time <= LEDTIME2)
		charge_time++;

	SENRF_global = Senvalue2 - Senvalue1; //右前センサ終了

//	Senvalue1 = 0, Senvalue2 = 0;
//	AD1.ADCR.BIT.ADST = 0; //右後センサAD変換開始
//	AD1.ADCSR.BIT.CH = 3;
//	AD1.ADCR.BIT.ADST = 1;
////	LEDRB = 1;
//	while (AD1.ADCSR.BIT.ADF == 0)
//		;
//	AD1.ADCSR.BIT.ADF = 0;
//
//	charge_time = 0;
//	LEDRB = 1;
//	Senvalue1 = AD1.ADDR7 >> 6;
//	while (charge_time <= LEDTIME1)
//		charge_time++;
//
//	AD1.ADCR.BIT.ADST = 0;
//	AD1.ADCSR.BIT.CH = 3;
//	AD1.ADCR.BIT.ADST = 1;
//	//	LEDRB = 1;
//	while (AD1.ADCSR.BIT.ADF == 0)
//		;
//	AD1.ADCSR.BIT.ADF = 0;
//	charge_time = 0;
//	LEDRB = 0;
//	Senvalue2 = AD1.ADDR7 >> 6;
//	while (charge_time <= LEDTIME2)
//		charge_time++;
//
//	SENRB_global = Senvalue2 - Senvalue1; //右後センサAD変換終了
//	wait(10);

}
void change() {
	static int logsenL1, logsenR1, logsenR2, logsenL2, logsenR3, logsenL3, logsenR4,
			logsenL4, logsenR5, logsenL5, logsenL6, logsenR6, logsenL7,
			logsenR7;
	logsenR_global = logsenR1;
	logsenR1 = logsenR2;
	logsenR2 = logsenR3;
	logsenR3 = logsenR4;
	logsenR4 = logsenR5;
	logsenR5 = logsenR6;
	logsenR6 = logsenR7;
	logsenR7 = SENRF_global;

	logsenL_global = logsenL1;
	logsenL1 = logsenL2;
	logsenL2 = logsenL3;
	logsenL3 = logsenL4;
	logsenL4 = logsenL5;
	logsenL5 = logsenL6;
	logsenL6 = logsenL7;
	logsenL7 = SENLF_global;

	logL_global = logsenL_global - SENLF_global;
	logR_global = logsenR_global - SENRF_global;
	SENLF_global=(logsenL1+logsenL2+logsenL3+logsenL4+logsenL5+logsenL6+logsenL7)/7;
	SENRF_global=(logsenR1+logsenR2+logsenR3+logsenR4+logsenR5+logsenR6+logsenR7)/7;
}
float wall_control() {
	float control, error, senr_ref = 330, senl_ref = 330;
	if (SENLF_global <= 200 && SENRF_global > 200)
		error = -2 * (SENRF_global - senr_ref);
	else if (SENRF_global <= 200 && SENLF_global > 200)
		error = 2 * (SENLF_global - senl_ref);
	else if (SENLF_global > 200 && SENRF_global > 200)
		error = (SENLF_global - senl_ref) - (SENRF_global - senr_ref);
	control = sp_global * error;
	return control;
//	speedR_global = speed_global + control;
//	speedL_global = speed_global - control;
//	myprintf("%f,%f", speedR_global, speedL_global);
}
