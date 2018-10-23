/*
 * global.h
 *
 *  Created on: 2018/09/19
 *      Author: ilove
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
extern int dutyr_global, dutyl_global, batt_global, SENLB_global, SENLF_global,
		SENC_global, SENRF_global, SENRB_global, logsenR_global,
		logsenL_global,logR_global,logL_global,muki_global,i_global,j_global,i,j,SENR_global,SENC_global,SENL_global;
extern float distance_global, x_global, accel_global, speed_global,
		BATTERY_global, TARGET_global, ct_global, changeL_global, changeR_global,
		speedL_global, speedR_global,ang_global,sp_global,length_global;
extern short canedir_global,map_global[16][16];
typedef struct {
	unsigned short wall;
	unsigned short known;
	unsigned short knownwall;
}walldata;

extern walldata Ewalldata_global[16],Nwalldata_global[16];

extern struct queue{
	int arr_z[MAX_DATA];
	int arr_y[MAX_DATA];
	int first;
	int last;
};

#endif /* GLOBAL_H_ */
