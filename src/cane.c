/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  cane                                   */
/*      FILE         :  cane.c                                 */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  SH-2                                   */
/*      CPU TYPE     :  SH7125                                 */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/

//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
	void abort(void);
}
#endif
#include "stdio.h"
#include "stdlib.h"
#include "iodefine.h"
#include "serial.h"
#include "init.h"
#include "function.h"
#include "define.h"
#include "global.h"
#include "sensor.h"
#include "mtu.h"
#include "run.h"
#include "wall.h"
//#define reset PE.DRL.BIT.B2
//#define enable PE.DRL.BIT.B8
//#define motor_R PE.DRL.BIT.B0
//#define motor_L PE.DRL.BIT.B4
//#define LED1 PB.DR.BIT.B2
//#define LED2 PB.DR.BIT.B3
//#define LED3 PB.DR.BIT.B5
//#define LEDLB PA.DRL.BIT.B11
//#define LEDLF PA.DRL.BIT.B12
//#define LEDC PA.DRL.BIT.B13
//#define LEDRF PA.DRL.BIT.B14
//#define LEDRB PA.DRL.BIT.B15
//#define SOUND PE.DRL.BIT.B6
//#define SWICH1 PA.DRL.BIT.B6
//#define SWICH2 PA.DRL.BIT.B7
//#define SWICH3 PA.DRL.BIT.B8
//#define MAX_x 1000
//#define ACCEL_x 1000
//#define TARGET 540
double angacc, angvel, time;
int /*SENRB, SENRF, SENC, SENLB, SENLF,*/c = 0;
int flag=0;
void main(void) {
	initCMT();
	init_sci1();
	initAD();
	init_mtu();
	pfcall();
	//SENSOR
for(i=0;i<16;i++){
	Nwalldata_global[i].knownwall=0;
	Ewalldata_global[i].knownwall=0;
}
//while(a<10){
//		LEDRF = 1;
//		wait(50);
//		LEDRF = 0;
//		wait(50);
//		a++;
//}
//		myprintf("SENLB %d,SENLF %d,SENC %d,SENRF %d,SENRB %d\n", SENLB, SENLF,
//				SENC, SENRF, SENRB); //SENC向き逆
//		wait(500);
//	}

//台形加速モデル

//	if (x<=ACCEL_x) {
//		speed += accel * 0.001;
//		x += speed * 0.001;
//	} else if (MAX_x-x<=ACCEL_x) {
//		speed -= accel * 0.001;
//		x += speed * 0.001;
//	}
	//	励磁
	LED1 = 1;
	for (i_global = 0; i_global > 15; i_global++) {
		Ewalldata_global[i_global].wall = 0;
		Nwalldata_global[i_global].wall = 0;
	}
	Ewalldata_global[0].wall |= 1;
	while (1) {
		switch (c) {
		case 1:
			LED1 = 0;
			LED2 = 0;
			LED3 = 1;

			c = mode_select(c);

			if (c == 1) {
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();
				LED2 = 1;

//				while (1)
//					myprintf("battery=%d,BATTERY=%f\n", batt_global,
//							BATTERY_global);
				excitation();
				wait(100);
				sp_global = 0.3;
				speed_global = 300;
				left_hand(0, 1);
//				motor_L = 0;
//				x_global=0;
//				MTU2.TSTR.BIT.CST0 = 1;
//				MTU2.TSTR.BIT.CST1 = 1;
//				while (x_global <= 360)
//					;
//				time = 0;
//				while (time < 20) {
//					turn(90);
//					wait(500);
//					time++;
//				}
//				go(180, 0);
//				speed_global = 0;
//				speed_global = 0;
//				distance_global = 360;
//				speed_global = 300;
//				daikei(360.0);
//				LED1=1;
//				daikei();
//				LED2=1;
//				daikei();
//				LED3=1;
//				go(TARGET, 1000);
//				go((double)distance_global - 2*TARGET, 0);
//				go(TARGET, -1000);

//				go(1800, 0);
			}
			continue;
		case 2:
			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			c = mode_select(c);

			if (c == 2) {
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();

				excitation();
				wait(100);
				speed_global = 200;
				sp_global = 0.2;
				Adati();
//				RUN(300);
//				wait(1000);
//				RUN(300);
//				for (i_global = 0; i_global < 16; i_global++) {
//					for (j_global = 0; j_global < 16; j_global++) {
//						map_global[i_global][j_global] = 0;
//					}
//				}
//				i_global = 0, j_global = 0;
//				muki_global=1;
//				turn(90);
//				left_hand(0, 1);
//				wait(1000);
//				int i, j;
//				for (i = 0; i < 16; i++) {
//					for (j = 0; j < 16; j++) {
//						map_global[i][j] = 0;
//					}
//				}
//				i = 0, j = 0;
//				left_hand(0, 0);

//				wall_control();
			}
			continue;
		case 3:
			LED1 = 0;
			LED2 = 1;
			LED3 = 1;
			c = mode_select(c);
			if (c == 3) {
				//回転するよ
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();
				sensor();
				excitation();
				wait(100);
				muki_global = 0;
//				output_wall();
//				sp_global = 2;
//				speed_global = 200;
//				speed_global = 200;
//				go(90, 0);
//				speed_global = 0;
				while (1) {
//					myprintf("%d,%d\n", logL_global, logR_global);
//////					myprintf("%d,%d\n",logsenL_global,logsenR_global);
					myprintf("SENLB=%d,SENLF=%d,SENC=%d,SENRF=%d,SENRB=%d\n",
							SENLB_global, SENLF_global, SENC_global,
							SENRF_global, SENRB_global);
				}
//				duty(50000,50000);
			}

			continue;
		case 4:
			LED1 = 1;
			LED2 = 0;
			LED3 = 0;
			c = mode_select(c);
			if (c == 4) {
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();
				excitation();
				wait(100);
				sp_global = 0.1;
				speed_global = 200;
//				go(180*14,0);
//				speed_global=0;
				accel_global = 0;
				while(flag<40){
					turn(-90);
					wait(200);
					flag++;
				}
//				accel(Max_acc);
//				while (x_global <= 180)
//					;
//				accel_global = 0;
//				x_global = 0;
//				distance_global = 0;
//				while (x_global <= 180)
//					;
//				accel_global = 0;
//				x_global = 0;
//				distance_global = 0;
//				while (x_global <= 180)
//					;
//				accel(Min_acc);
//				x_global = 0;
//				MTU2.TSTR.BIT.CST0 = 1;
//				MTU2.TSTR.BIT.CST1 = 1;
//				while (x_global <= 180 * 14)
//					;
//				speed_global = 0;
//				go_daikei(180.0 * 14.0, 1700);
//				while (1) {
//					myprintf("%d,%d\n", logL_global, logR_global);
//				}
				//speed_global = 200;
				//distance_global = 90;
				//go(distance_global, 1000);
//				speed_global = 300;
//				daikei(540);
//				x_global = 0;
//				accel_global = 1000;
//				while (1) {
//					if (x_global <= 1000) {
//						MTU2.TSTR.BIT.CST0 = 1;
//						MTU2.TSTR.BIT.CST1 = 1;
////						x = integral(&speed, 10000);
//						myprintf("%f,%f\n", x_global, speed_global);
//					} else if (x_global > 1000) {
//						MTU2.TSTR.BIT.CST0 = 1;
//						MTU2.TSTR.BIT.CST1 = 1;
//						accel_global = 0;
//
////						x = integral(&speed, -10000);
//						myprintf("%f ,%f\n", x_global, speed_global);
//					}
//					if (speed_global <= 0) {
//						MTU2.TSTR.BIT.CST0 = 0;
//						MTU2.TSTR.BIT.CST1 = 0;
//						break;
//					}
//				}
			}
			continue;
		case 5:	//台形加速
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			c = mode_select(c);
			if (c == 5) {
//				speed_global = 300;
//				x_global = 0;
//				accel_global = 1000;
//				sp_global = 2.0;
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();
				excitation();
				wait(100);
				speed_global = 200;
				x_global = 0;
				accel_global = 0;
				sp_global = 0.2;
				non_stop();
				myprintf("stop");
//				go(360, 1000);
//				go(720, 0);
//				go(360, -1000);
//					if (x <= 540) {
//						accel = 1000;
////						x = integral(&speed, 3000);
//						myprintf("%f\n", speed);
//					} else if (x > 540 && x <= 1620) {
//						accel = 0;
////						x = integral(&speed, 0);
//						myprintf("%f\n", speed);
//					} else if (x > 1620) {
//						accel = -1000;
////						x = integral(&speed, -3000);
//						myprintf("%f\n", speed);
//					}
//				if (speed_global < 0) {
//					MTU2.TSTR.BIT.CST0 = 0;
//					MTU2.TSTR.BIT.CST1 = 0;
//					break;
//				}

			}
			continue;
		case 6:
			LED1 = 1;
			LED2 = 1;
			LED3 = 0;
			c = mode_select(c);
			if (c == 6) {
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				Lipo();
				excitation();
				speed_global = 200;
				sp_global = 0.2;
				length_global=0;
				accel(Max_acc);
//				MTU2.TSTR.BIT.CST0 = 0;
//				MTU2.TSTR.BIT.CST1 = 0;
				while (x_global < 180 * 13)
					;
				accel(Min_acc);
//				canedir_global=2;
//				i_global=3;
//				j_global=4;
//				add_wall();
//				myprintf("%d", Nwalldata_global[4].wall);
//				output_wall();
//				wait(100);
//				turn(-90);
//				myprintf("%d", canedir_global);
//				wait(100);
//				go_back();
//				wait(100);
//				turn(91);
//				myprintf("%d", canedir_global);
//				wait(100);
//				go_back();
//				wait(100);
//				daikei(90);
//				Adati();
//				myprintf("%d,%d", i_global, j_global);

//				i_global=0,j_global=0;
//				myprintf("%d\n",hikaku());
//				excitation();
//				speed_global = 200.0;
//				accel_global = 0;
//				x_global = 0;
//				motor_L = 0;
////
//				turn(180);
//				accel_global = 1000;
//
//				while (1)
//					myprintf("%f,%f", x_global, speed_global);
			}
			continue;
		case 7:
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			c = mode_select(c);

			if (c == 7) {

				LED1 = 0;
				LED2 = 0;
				LED3 = 0;

//				excitation();
//				wait(500);
//				maprule();
//				input_wall(0, 2, 0);
//				input_wall(1, 2, 0);
//				input_wall(2, 2, 0);
//				input_wall(2, 2, 1);
//				input_wall(2, 2, 1);
				output_wall(0);
				output_wall(2);
				shortest_route();
				output_wall(1);
				myprintf("i=%d,j=%d\n", i_global, j_global);
				myprintf("%d\n", canedir_global);
//				MTU2.TSTR.BIT.CST0 = 1;
//				MTU2.TSTR.BIT.CST1 = 1;
//				speed_global = 200;
//				accel_global = 0;
//				while (SENC_global < 200)
//					;
//				go_back();
//				while (1) {
//					if (SENLF_global >= 150) {
////						myprintf("SENLF=%d\n",SENLF_global);
//						LED1 = 0;
//						LED2 = 0;
//						LED3 = 1;
//					} if (SENC_global >= 130) {
////						myprintf("SENC=%d\n",SENC_global);
//						LED1 = 0;
//						LED2 = 1;
//						LED3 = 0;
//					} if (SENRF_global >= 130) {
////						myprintf("SENRF=%d\n",SENRF_global);
//						LED1 = 1;
//						LED2 = 0;
//						LED3 = 0;
//					}
//				}
			}
			continue;
		default:
			c = 1;
			continue;
		}

//		x = integral(&speed, accel);
//			myprintf("%f,%f,%d\n", speed, accel, duty_r);
//		//PB.DR.BIT.B3 = 1;
////		myprintf("%f\n", BATTERY);
////		wait(100);
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif