/*
 * wall.c
 *
 *  Created on: 2018/10/02
 *      Author: ilove
 */
#include "iodefine.h"
#include "serial.h"
#include "init.h"
#include "define.h"
#include "global.h"
#include "function.h"
#include "sensor.h"
#include "math.h"

int BIT_FLAG_1 = 0x0001; // 2進数 : (0000 0000 0000 0001)
int BIT_FLAG_2 = 0x0002; // 2進数 : (0000 0000 0000 0010)
int BIT_FLAG_4 = 0x0004; // 2進数 : (0000 0000 0000 0100)
int BIT_FLAG_8 = 0x0008; // 2進数 : (0000 0000 0000 1000)

void add_wall() {

	if (canedir_global == 0) { //北向きならその区画の北と東
		Ewalldata_global[i_global].known |= (1 << j_global);
		if (i_global - 1 != -1)
			Ewalldata_global[i_global - 1].known |= (1 << j_global);
		Nwalldata_global[j_global].known |= (1 << i_global);
		if (SENRF_global > THRESHORD) {
			Ewalldata_global[i_global].wall |= (1 << j_global);
		}
		if (SENC_global > 150) {
			Nwalldata_global[j_global].wall |= (1 << i_global);
		}
		if (SENLF_global > THRESHORD && i_global - 1 != -1) {
			Ewalldata_global[i_global - 1].wall |= (1 << j_global);
		}
//		if (ang_global == 90) {
//			if (SENRF_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//			if (SENC_global > 130)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//		} else if (ang_global == -90) {
//			if (SENRF_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//			if (SENC_global > 130)
//				Ewalldata_global[i_global].wall |= (1 << j_global);
//		} else {
//			if (SENRF_global > 130)
//				Ewalldata_global[i_global].wall |= (1 << j_global);
//			if (SENC_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//		}
	} else if (canedir_global == 1) { //東向きなら下の区画の北と区画の東
		Ewalldata_global[i_global].known |= (1 << j_global);
		if (j_global - 1 != -1)
			Nwalldata_global[j_global - 1].known |= (1 << i_global);
		Nwalldata_global[j_global].known |= (1 << i_global);
		if (SENRF_global > THRESHORD && j_global - 1 != -1) {
			Nwalldata_global[j_global - 1].wall |= (1 << i_global);
		}
		if (SENC_global > 150) {
			Ewalldata_global[i_global].wall |= (1 << j_global);
		}
		if (SENLF_global > THRESHORD) {
			Nwalldata_global[j_global].wall |= (1 << i_global);
		}
//		if (ang_global == 90) {
//			if (SENRF_global > 130)
//				Ewalldata_global[i_global].wall |= (1 << j_global);
//			if (SENC_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//		} else if (ang_global == -90) {
//			if (SENRF_global > 130 && i_global - 1 != -1)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//			if (SENC_global > 130)
//				Nwalldata_global[j_global - 1].wall |= (1 << i_global);
//		} else {
//			if (SENRF_global > 130 && j_global - 1 != -1)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//			if (SENC_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//		}
	} else if (canedir_global == 2) { //南向きなら下の区画の北と隣の区画の東
		Ewalldata_global[i_global].known |= (1 << j_global);
		if (i_global - 1 != -1)
			Ewalldata_global[i_global - 1].known |= (1 << j_global);
		if (j_global - 1 != -1)
			Nwalldata_global[j_global - 1].known |= (1 << i_global);
		if (SENRF_global > THRESHORD && i_global - 1 != -1) {
			Ewalldata_global[i_global - 1].wall |= (1 << j_global);
		}
		if (SENC_global > 150 && j_global - 1 != -1) {
			Nwalldata_global[j_global - 1].wall |= (1 << i_global);
		}
		if (SENLF_global > THRESHORD) {
			Ewalldata_global[i_global].wall |= (1 << j_global);
		}

//		if (ang_global == 90) {
//			if (SENRF_global > 130 && j_global - 1 != -1)
//				Nwalldata_global[j_global - 1].wall |= (1 << i_global);
//			if (SENC_global > 130)
//				Ewalldata_global[i_global].wall |= (1 << j_global);
//		} else if (ang_global == -90) {
//			if (SENRF_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//			if (SENC_global > 130 && i_global - 1 != -1)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//		} else {
//			if (SENRF_global > 130 && i_global - 1 != -1)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//			if (SENC_global > 130 && j_global - 1 != -1)
//				Nwalldata_global[j_global - 1].wall |= (1 << i_global);
//		}
	} else if (canedir_global == 3) { //西向きなら区画の北と隣の区画の東
		if (i_global - 1 != -1)
			Ewalldata_global[i_global - 1].known |= (1 << j_global);
		if (j_global - 1 != -1)
			Nwalldata_global[j_global - 1].known |= (1 << i_global);
		Nwalldata_global[j_global].known |= (1 << i_global);
		if (SENRF_global > THRESHORD) {
			Nwalldata_global[j_global].wall |= (1 << i_global);
		}
		if (SENC_global > 150 && i_global - 1 != -1) {
			Ewalldata_global[i_global - 1].wall |= (1 << j_global);
		}
		if (SENLF_global > THRESHORD && j_global - 1 != -1) {
			Nwalldata_global[j_global - 1].wall |= (1 << i_global);
		}
//		if (ang_global == 90) {
//			if (SENRF_global > 130 && i_global - 1 != -1)
//				Nwalldata_global[i_global - 1].wall |= (1 << j_global);
//			if (SENC_global > 130 && j_global - 1 != -1)
//				Nwalldata_global[j_global - 1].wall |= (1 << i_global);
//		} else if (ang_global == -90) {
//			if (SENRF_global > 130)
//				Ewalldata_global[i_global].wall |= (1 << j_global);
//			if (SENC_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//		} else {
//			if (SENRF_global > 130)
//				Nwalldata_global[j_global].wall |= (1 << i_global);
//			if (SENC_global > 130 && i_global - 1 != -1)
//				Ewalldata_global[i_global - 1].wall |= (1 << j_global);
//		}
	}
	ang_global = 0;
}
void input_wall(int z, int y, int dir) {
	if (dir == 0) {
		Nwalldata_global[y].wall |= (1 << z);
	} else {
		Ewalldata_global[z].wall |= (1 << y);

	}
}
int get_wall(int z, int y, int dir, int mode) {
	if (mode == 0) {
		if (dir == 0) {
			if ((Nwalldata_global[y].wall & (1 << z)) != 0) {
				return 1;
			} else
				return 0;
		} else {
			if ((Ewalldata_global[z].wall & (1 << y)) != 0) {
				return 1;
			} else
				return 0;
		}
	} else if (mode == 1) {
		if (dir == 0) {
			if ((Nwalldata_global[y].knownwall & (1 << z)) != 0) {
				return 1;
			} else
				return 0;
		} else {
			if ((Ewalldata_global[z].knownwall & (1 << y)) != 0) {
				return 1;
			} else
				return 0;
		}
	} else {
		if (dir == 0) {
			if ((Nwalldata_global[y].known & (1 << z)) != 0) {
				return 1;
			} else
				return 0;
		} else {
			if ((Ewalldata_global[z].known & (1 << y)) != 0) {
				return 1;
			} else
				return 0;
		}
	}
}
void output_wall(int mode) {
	int a, b, c, d;
	int walldata;
	myprintf("+");

	for (a = 0; a < 16; a++) {
		myprintf("-----+");
	}
	for (b = 15; b > -1; b--) {

		myprintf("\n");
		myprintf("|");

		for (c = 0; c < 16; c++) {
			walldata = get_wall(c, b, 1, mode);
			if (walldata == 1) {
				myprintf("%5d|", map_global[c][b]);
			} else {
				myprintf("%5d ", map_global[c][b]);
			}

		}
		myprintf("\b");
		myprintf("|");
		myprintf("\n");
		myprintf("+");
		for (c = 0; c < 16; c++) {
			walldata = get_wall(c, b - 1, 0, mode);
			if (walldata == 1 || b == 0) {
				myprintf("-----+");
			} else {
				myprintf("     +");
			}

		}
	}
	myprintf("\n");
//	myprintf("+");
//	for (a = 0; a < 16; a++) {
//		myprintf("-----+");
//	}

}
