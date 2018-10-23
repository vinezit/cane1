/*
 * global.c

 *
 *  Created on: 2018/09/19
 *      Author: ilove
 */
#include "define.h"
int dutyr_global, dutyl_global, batt_global, SENRB_global, SENRF_global,
		SENC_global, SENLB_global, SENLF_global, accel_global, logsenR_global,
		logsenL_global, logR_global,logL_global, muki_global=16,i_global=0,j_global=0,i,j,SENR_global,SENC_global,SENL_global;
unsigned int canedir_global;
float speed_global, speedR_global, speedL_global, x_global, BATTERY_global,
		TARGET_global, ct_global, changeL_global, changeR_global, ang_global,sp_global;
float distance_global = 0,length_global=0;

unsigned short map_global[16][16];

typedef struct {
	unsigned short wall;
	unsigned short known;
	unsigned short knownwall;
}walldata;
walldata Nwalldata_global[15],Ewalldata_global[15];

struct queue{
	int arr_z[MAX_DATA];
	int arr_y[MAX_DATA];
	int first;
	int last;
};
