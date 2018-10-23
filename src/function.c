/*
 * function.c
 *
 *  Created on: 2018/08/11
 *      Author: ilove
 */
#include "stdio.h"
#include "stdlib.h"
#include "iodefine.h"
#include "serial.h"
#include "init.h"
#include "define.h"
#include "global.h"
#include "function.h"
#include "sensor.h"
#include "mtu.h"
volatile int count = 0;
volatile float dt = 0.001, d = 0;

void integral() {
	speed_global += accel_global * dt;
	x_global += speed_global * dt;
}

void wait(int a) {

	count = 0;
	while (count <= a)
		;
}

void interrupt_cmt0() {  //割り込む関数

	CMT0.CMCSR.BIT.CMF = 0;  //フラグクリア
	count++;
	integral();
	if (enable == 1)
		sensor();
	change();
	ct_global = wall_control();
	if (speed_global < 200 || motor_L == 0 || motor_R == 0 || logR_global > 10
			|| logL_global > 10 || SENC_global > 250)
		ct_global = 0;
}
void duty(int a, int b) {
	MTU20.TGRA = a;
	MTU21.TGRA = b;
	MTU20.TGRB = a / 2; //トリガ
	MTU21.TGRB = b / 2;
	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST1 = 1;

}

void Lipo() {
	AD0.ADCR.BIT.ADST = 0;
	AD0.ADCSR.BIT.CH = 0;
	AD0.ADCR.BIT.ADST = 1;
	while (AD0.ADCSR.BIT.ADF == 0)
		;
	AD0.ADCSR.BIT.ADF = 0;

	batt_global = AD0.ADDR0 >> 6;

	BATTERY_global = (float) batt_global * 0.01528670369 + 0.171;

	if (BATTERY_global <= 11.1) { //battery下限
		while (1) {
			MTU2.TSTR.BIT.CST0 = 0;
			MTU2.TSTR.BIT.CST1 = 0;
			LED3 = 0;
			LED1 = 1;
			wait(100);
			LED1 = 0;
			LED2 = 1;
			wait(100);
			LED2 = 0;
			LED3 = 1;
			wait(100);
//			SOUND = 1;
//			wait(500);
//			SOUND = 0;
//			wait(1000);
		}
	}
}
int mode_select(int a) {
	while (1) {
		if (SWICH1 == 0 && a == 1) {
			wait(500);
			a = 7;
			return a;
			break;
		} else if (SWICH3 == 0) {
			wait(500);
			return a;
			break;
		} else if (SWICH1 == 0) {
			wait(500);
			a--;
			return a;
			break;
		} else if (SWICH2 == 0) {
			wait(500);
			a++;
			return a;
			break;
		}
	}
	return -2;
}
void go(float a, int b) {
	x_global = 0;
	accel_global = b;
	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST1 = 1;
	while (x_global <= a) {
//		myprintf("%f,%f\n",speed_global,accel_global);
//		if (speed_global > 500) {
//			accel_global = 0;
//			speed_global = 500;
//		} else if (speed_global <= 180) {
//			accel_global = 0;
//			speed_global = 180;
//		}
	}
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;

	TARGET_global = 0;
}
void go_speed(float a, int b) {
	x_global = 0;
	accel_global = b;
	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST1 = 1;
	if (accel_global > 0) {
		while (speed_global < a)
//			myprintf("%f,%f\n",speed_global,accel_global)
			;
	} else if (accel_global < 0) {
		while (speed_global > a)
//			myprintf("%f,%f\n",speed_global,accel_global)
			;
	}
	TARGET_global = x_global;
}

void turn(float ang) {
	float target;
	speed_global = 200;
	x_global = 0;
	ang_global = ang;
	dir();
	if (ang < 0) {
		motor_R = 0;
		distance_global = 260.40 * (-ang / 360.0);
	} else if (ang >= 0) {
		motor_L = 0;
		distance_global = 268.90 * (ang / 360.0);
	}
//	distance_global = 267.04 * (ang / 360.0);
	target = distance_global / 5;
	accel_global = 0;
//	MTU2.TSTR.BIT.CST0 = 1;
//	MTU2.TSTR.BIT.CST1 = 1;
	go(target, 1500);
	go(distance_global - 2 * target, 0);
	go(target, -1500);
	speed_global = 0;
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;
	if (motor_L == 0)
		motor_L = 1;
	if (motor_R == 0)
		motor_R = 1;
}
void go_back() {
//	turn(91);
//
//	wait(1000);
	motor_L = 0;
	motor_R = 0;
	speed_global = 180;
	go(90, 0);
	speed_global = 0;
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;
	motor_L = 1;
	motor_R = 1;

	speed_global = 180;
	wait(100);

	go(40, 0);
	speed_global = 0;
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;
//	wait(1000);
//	MTU2.TSTR.BIT.CST0 = 0;
//	MTU2.TSTR.BIT.CST1 = 0;
//	speed_global=200;
//	turn(91);
//	MTU2.TSTR.BIT.CST0 = 0;
//	MTU2.TSTR.BIT.CST1 = 0;
//	motor_L = 0;
//	motor_R = 0;
//	speed_global = 180;
//	wait(1000);
//	go(50, 0);
//	speed_global = 0;
//	MTU2.TSTR.BIT.CST0 = 0;
//	MTU2.TSTR.BIT.CST1 = 0;
//	motor_L = 1;
//	motor_R = 1;
//
//	x_global = 0;
//	speed_global = 180;
//	wait(1000);
//	go(125, 0);
//	speed_global = 0;
}
void dir() {

	if (ang_global <= -90) {
		muki_global++;
		canedir_global = abs(muki_global % 4);
	} else if (ang_global >= 90) {
		muki_global--;
		canedir_global = abs(muki_global % 4);
	} else if (ang_global == 180) {
		muki_global += 2;
		canedir_global = abs(muki_global % 4);
	} else
		canedir_global = abs(muki_global % 4);

//	if (canedir_global == 0)
//		map_global[i_global][j_global+1] = 1;
//	else if (canedir_global == 1)
//		map_global[i_global+1][j_global] = 1;
//	else if (canedir_global == 2)
//		map_global[i_global][j_global-1] = 1;
//	else if (canedir_global == 3)
//		map_global[i_global-1][j_global] = 1;
//	myprintf("%d,%d\n",i_global,j_global);

}

int FLAG() {
	int flag = 0;
	float kyori = distance_global;
//	if (motor_L == 0 || motor_R == 0) {
//		flag = 0;
//		return flag;
	/*	} else*/if (distance_global > 90) {
		flag = 1;
		return flag;
	} else if (distance_global <= 90) {
		flag = -1;
		return flag;
	}
	return -2;
}

void go_daikei(float a, float b) {
	float tempo;
	x_global = 0;
	accel_global = b;
	tempo = 150 / accel_global;
	distance_global = speed_global * tempo + 0.5 * accel_global * tempo * tempo;
//	distance_global = 45;

	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST1 = 1;
	while (x_global <= distance_global)
		;
	accel_global = 0;
	x_global = 0;
	while (x_global <= a - 2 * distance_global)
		;
	accel_global = -b;
	x_global = 0;
	while (x_global <= distance_global)
		;
	speed_global = 0;
}
void daikei(float a) {
	int flag;
	float tar;
	distance_global = a;
	flag = FLAG();
//speed_global = 200;
	if (flag == -1) {
		speed_global = 200;
		go_daikei(distance_global, 1700);
//		tar = distance_global / 5;
//		go(tar, 1000);
//		go(distance_global - 2 * tar, 0);
//		go(tar, -1000);
//		if (SENC_global > 50)
//			while (SENC_global < 130)
//				;
//		go_speed(300, 1700);
//		go(distance_global - 2 * TARGET_global, 0);
//		go(200, -1700);
	} else if (flag == 1) {
		//float tousoku;
//		tousoku = distance_global - 2 * TARGET_global;
//		go(distance_global,0);
		speed_global = 200;
		go_daikei(distance_global, 1700);
//		tar = distance_global / 5;
//		go(47, 1700);
//		go_speed(500, 1700);
//		go(distance_global - 2 * 47, 0);
//		go_speed(300, -1700);
//		go(47, -1700);
//		if (SENC_global > 50)
//			while (SENC_global < 130)
//				;
	}
	speed_global = 0;
	MTU2.TSTR.BIT.CST0 = 0;
	MTU2.TSTR.BIT.CST1 = 0;
//		while (speed_global <= 0)
//			accel_global = -2000;

//		MTU2.TSTR.BIT.CST0 = 0;
//		MTU2.TSTR.BIT.CST1 = 0;
//	} else if (flag == 0) {
//		speed_global = 100;
//		distance_global = 276.46 * (ang_global / 360.0);
//		go(distance_global * 2 / 5, 1000);
//		go(distance_global / 5, 0);
//		go(distance_global * 2 / 5, -1000);
//		while (speed_global >= 0)
//			accel_global = -3000;
//	}
}
void excitation() {
	reset = 1;
	enable = 0;
	wait(10);
	reset = 0;
	enable = 1;
	motor_R = 1;
	motor_L = 1;
}

void left_hand(int z, int y) {
//	unsigned short map[16][16];
//	int i, j;
	int f = 0;
//	for (i_global = 0; i_global < 16; i_global++) {
//		for (j_global = 0; j_global < 16; j_global++) {
//			map_global[i_global][j_global] = 0;
//		}
//	}
//	i = 0, j = 0;
//	speed_global = 300;
	muki_global = 4;
	i_global = 0;
	j_global = 1;
	distance_global = 0;
	accel_global = 0;
//motor_L = 1;
	turn(-90);
	wait(100);
	go_back();
	wait(100);
	turn(91);
	wait(100);
	go_back();
	wait(100);
	daikei(91);
	wait(100);

	while (/*map_global[z][y] == 0*/f < 10) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				map_global[i][j] = 255;
			}
		}
		add_wall();
		maprule();

		if (SENLF_global < 100) {
			if (SENRF_global >= 100) { //左壁なし
//			myprintf("SENLF=%d", SENLF_global);
				LED1 = 1;
				LED2 = 0;
				LED3 = 0;
				wait(200);
				daikei(90.0);			//90進んで左回転して90進む
				wait(200);
				turn(91.0);
				wait(200);
				go_back();
				wait(200);
				daikei(90.0);

//				dir();
//				myprintf("%d,%d\n",i_global,j_global);
			} else {

				wait(200);
				daikei(90.0);			//90進んで左回転して90進む
				wait(200);
				turn(91.0);
				wait(200);
				daikei(90);

//				dir();
//				myprintf("%d,%d\n",i_global,j_global);
			}
		} else if (/*SENLF_global >= 130 && */SENC_global < 90) { //左壁あり前なし
//			myprintf("SENC=%d", SENC_global);

			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			wait(200);
			daikei(180.0); //180進む

//						dir();
//			myprintf("%d,%d\n",i_global,j_global);
		} else if (SENRF_global < 100) { //左＆前あり右なし
//			myprintf("SENRF=%d", SENRF_global);
			LED1 = 0;
			LED2 = 0;
			LED3 = 1;
			wait(200);
			daikei(90.0);
			wait(200);
			turn(-90);			//90進んで右回転して90進
			wait(200);
			go_back();
			wait(200);
			daikei(90.0);
			//			dir();
//			myprintf("%d,%d\n",i_global,j_global);
		} else { //行き止まり

			wait(200);
			daikei(90.0);		//180回転して
			wait(200);
			turn(-90);
			wait(200);
			go_back();
			wait(200);
			turn(-90);
			wait(200);
			go_back();
			wait(200);
			daikei(90);

//			dir();
//			myprintf("%d,%d\n",i_global,j_global);
			//			daikei(90.0);
		}
		f++;
//		myprintf("%d", canedir_global);
		if (canedir_global == 0)
			j_global++;
		else if (canedir_global == 1)
			i_global++;
		else if (canedir_global == 2)
			j_global--;
		else if (canedir_global == 3)
			i_global--;
//		myprintf("i=%d,j=%d",i_global,j_global);
		output_wall();
	}
	daikei(90);
	wait(100);
	turn(180);
}
