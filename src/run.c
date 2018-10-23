/*
 * run.c
 *
 *  Created on: 2018/10/06
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

void accel(float b) {
	float tempo;
	x_global = 0;
	accel_global = b;
	if (accel_global > 0)
		tempo = 100 / accel_global;
	else if (accel_global < 0)
		tempo = -100 / accel_global;
	distance_global = speed_global * tempo + 0.5 * accel_global * tempo * tempo;

//	myprintf("%f", distance_global);
//	distance_global = 45;
	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST1 = 1;
	if (accel_global < 0) {
		accel_global = 0;
		while (x_global <= 90 - (distance_global + length_global))
			;
		x_global = 0;
	}
	while (x_global <= distance_global)
		;
//		myprintf("%d,%d,%d\n", SENLF_global, SENC_global, SENRF_global);
	x_global = 0;
	if (accel_global > 0) {
		accel_global = 0;
		while (x_global <= 90 - distance_global)
			;
	} else {
		speed_global = 0;
		MTU2.TSTR.BIT.CST0 = 0;
		MTU2.TSTR.BIT.CST1 = 0;
	}
	x_global = 0;
}
void map_clear() {
	int i, j;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			map_global[i][j] = 255;
		}
	}
}
int enq_z(struct queue *que, int input) {
	if (que->arr_z[que->last] <= MAX_DATA) {
		que->arr_z[que->last] = input;
		que->last++;
		if (que->last == 16)
			que->last = 0;
		return 0;
	} else
		return -1;
}
int deq_z(struct queue *que) {
	int output = que->arr_z[que->first];
	if (output != 0) {
		que->arr_z[que->first] = 0;
		que->first++;
		if (que->first == 16)
			que->first = 0;
		return output;
	} else
		return -1;
}
int enq_y(struct queue *que, int input) {
	if (que->arr_y[que->last] <= MAX_DATA) {
		que->arr_y[que->last] = input;
		que->last++;
		if (que->last == 16)
			que->last = 0;
		return 0;
	} else
		return -1;
}
int deq_y(struct queue *que) {
	int output = que->arr_y[que->first];
	if (output != 0) {
		que->arr_y[que->first] = 0;
		que->first++;
		if (que->first == 16)
			que->first = 0;
		return output;
	} else
		return -1;
}
void init_queue(struct queue *que) {
	int i;
	for (i = 0; i < MAX_DATA; i++) {
		que->arr_z[i] = 0;
		que->arr_y[i] = 0;
		que->first = 0;
		que->last = 0;
	}
}
void maprule_level2() {
	int loop = 1, a = 0, i = 1, j = 0, stock = 0;
	struct queue que;
	init_queue(&que);
	map_clear();
	map_global[1][0] = 0;
	while (loop) {
		loop = 0;
		i = deq_z(&que);
		j = deq_y(&que);
		if (get_wall(i, j, 0) != 1 && map_global[i][j + 1] == 255
				&& j + 1 != 16) {
			map_global[i][j + 1] = a + 1;
			loop = 1;
		}
		if (get_wall(i, j, 1) != 1 && map_global[i + 1][j] == 255
				&& i + 1 != 16) {
			map_global[i + 1][j] = a + 1;
			loop = 1;
		}
		if (get_wall(i - 1, j, 1) != 1 && map_global[i - 1][j] == 255
				&& i - 1 != -1) {
			map_global[i - 1][j] = a + 1;
			loop = 1;
		}
		if (get_wall(i, j - 1, 0) != 1 && map_global[i][j - 1] == 255
				&& j - 1 != -1) {
			map_global[i][j - 1] = a + 1;
			loop = 1;
		}
	}

}
void maprule(int mode) {
	int a = 0, i, j;
	int loop = 1;

	map_global[1][0] = 0;
	while (loop) {
		loop = 0;
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if (map_global[i][j] == a) {
					if (get_wall(i, j, 0,mode) != 1 && map_global[i][j + 1] == 255
							&& j + 1 != 16) {
						map_global[i][j + 1] = a + 1;
						loop = 1;
					}
					if (get_wall(i, j, 1,mode) != 1 && map_global[i + 1][j] == 255
							&& i + 1 != 16) {
						map_global[i + 1][j] = a + 1;
						loop = 1;
					}
					if (get_wall(i - 1, j, 1,mode) != 1
							&& map_global[i - 1][j] == 255 && i - 1 != -1) {
						map_global[i - 1][j] = a + 1;
						loop = 1;
					}
					if (get_wall(i, j - 1, 0,mode) != 1
							&& map_global[i][j - 1] == 255 && j - 1 != -1) {
						map_global[i][j - 1] = a + 1;
						loop = 1;
					}
				}
			}
		}
//		myprintf("%d\n", a);
		a++;
	}
}

void shortest_route() {
	int i = 0;
	for (i = 0; i < 15; i++) {
		Nwalldata_global[i].knownwall = Nwalldata_global[i].wall
				| ~(Nwalldata_global[i].known);
		Ewalldata_global[i].knownwall = Ewalldata_global[i].wall
				| ~(Ewalldata_global[i].known);
	}
	maprule(2);
}
void shortest_run() {
	shortest_route();

}
void RUN(float sp1) {
	speed_global = sp1;
	accel(1800);
	accel_global = 0;
	while (SENC_global < 150)
		;
	accel(-1800);
	speed_global = 0;
}
int hikaku() {
	short stock;
	int loop = 1, flag = 0;
	stock = map_global[i_global][j_global];
	if (canedir_global == 0) {
		if (map_global[i_global][j_global - 1] <= stock && j_global - 1 != -1) {
			stock = map_global[i_global][j_global - 1];
			loop = 1;
			flag = 3;
		}
		if (map_global[i_global][j_global + 1] <= stock && j_global + 1 != 16
				&& SENC_global < 70) {
			stock = map_global[i_global][j_global + 1];
			loop = 1;
			flag = 1;
		}
		if (map_global[i_global + 1][j_global] <= stock&& i_global + 1 != 16
		&& SENRF_global < THRESHORD) {
			stock = map_global[i_global + 1][j_global];
			loop = 1;
			flag = 2;
		}
		if (map_global[i_global - 1][j_global] <= stock&& i_global - 1 != -1
		&& SENLF_global < THRESHORD) {
			stock = map_global[i_global - 1][j_global];
			loop = 1;
			flag = 4;
		}
	} else if (canedir_global == 1) {
		if (map_global[i_global - 1][j_global] <= stock && i_global - 1 != -1) {
			stock = map_global[i_global - 1][j_global];
			loop = 1;
			flag = 3;
		}
		if (map_global[i_global + 1][j_global] <= stock && i_global + 1 != 16
				&& SENC_global < 70) {
			stock = map_global[i_global + 1][j_global];
			loop = 1;
			flag = 1;
		}
		if (map_global[i_global][j_global - 1] <= stock&& j_global - 1 != -1
		&& SENRF_global < THRESHORD) {
			stock = map_global[i_global][j_global - 1];
			loop = 1;
			flag = 2;
		}
		if (map_global[i_global][j_global + 1] <= stock && j_global + 1 != 16
				&& SENLF_global < 130) {
			stock = map_global[i_global][j_global + 1];
			loop = 1;
			flag = 4;
		}
	} else if (canedir_global == 2) {
		if (map_global[i_global][j_global + 1] <= stock && j_global + 1 != 16) {
			stock = map_global[i_global][j_global + 1];
			loop = 1;
			flag = 3;
		}
		if (map_global[i_global][j_global - 1] <= stock && j_global - 1 != -1
				&& SENC_global < 70) {
			stock = map_global[i_global][j_global - 1];
			loop = 1;
			flag = 1;
		}
		if (map_global[i_global + 1][j_global] <= stock
				&& SENLF_global < THRESHORD && i_global + 1 != 16) {
			stock = map_global[i_global + 1][j_global];
			loop = 1;
			flag = 4;
		}
		if (map_global[i_global - 1][j_global] <= stock&& i_global - 1 != -1
		&& SENRF_global < THRESHORD) {
			stock = map_global[i_global - 1][j_global];
			loop = 1;
			flag = 2;
		}
	} else if (canedir_global == 3) {
		if (map_global[i_global + 1][j_global] <= stock && i_global + 1 != 16) {
			stock = map_global[i_global + 1][j_global];
			loop = 1;
			flag = 3;
		}
		if (map_global[i_global - 1][j_global] <= stock && i_global - 1 != -1
				&& SENC_global < 70) {
			stock = map_global[i_global - 1][j_global];
			loop = 1;
			flag = 1;
		}
		if (map_global[i_global][j_global + 1] <= stock&& j_global + 1 != 16
		&& SENRF_global < THRESHORD) {
			stock = map_global[i_global][j_global + 1];
			loop = 1;
			flag = 2;
		}
		if (map_global[i_global][j_global - 1] <= stock&& j_global - 1 != -1
		&& SENLF_global < THRESHORD) {
			stock = map_global[i_global][j_global - 1];
			loop = 1;
			flag = 4;
		}

	}
	return flag;
}

void Adati() {
	short stock = 0;
	int loop = 1, flag = 0, on = 0;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			map_global[i][j] = 255;
		}
	}
	ang_global = 0;
	muki_global = 0;
	i_global = 0;
	j_global = 1;
	distance_global = 0;
	accel_global = 0;
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
	MTU2.TSTR.BIT.CST0 = 1;
	MTU2.TSTR.BIT.CST0 = 1;
	while (loop) {
		flag++;

		x_global = 0;
		add_wall();
		maprule(0);
		loop = 0;
//		stock = map_global[i_global][j_global];
		on = hikaku();

		if (on == 1) {
			wait(200);
			daikei(180.0);
			ang_global = 0;
			loop = 1;
//			output_wall();
//			myprintf("i=%d,j=%d\n", i_global, j_global);
//			myprintf("%d\n", canedir_global);
		} else if (on == 2) {
			if (SENLF_global >= 130) {
				wait(200);
				daikei(90.0);
				wait(200);
				turn(-90);			//90進んで右回転して90進
				wait(200);
				go_back();
				wait(200);
				daikei(90.0);

				loop = 1;
//				output_wall();
//				myprintf("i=%d,j=%d\n", i_global, j_global);
//				myprintf("%d\n", canedir_global);
			} else {
				wait(200);
				daikei(90.0);
				wait(200);
				turn(-90);			//90進んで右回転して90進
				wait(200);
				daikei(90.0);
				loop = 1;
//				output_wall();
				myprintf("i=%d,j=%d\n", i_global, j_global);
//				myprintf("%d\n", canedir_global);
			}

		} else if (on == 3) {
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
			loop = 1;
//			output_wall();
//			myprintf("i=%d,j=%d\n", i_global, j_global);
//			myprintf("%d\n", canedir_global);
		} else if (on == 4) {
			if (SENRF_global >= 130) {
				wait(200);
				daikei(90.0);			//90進んで左回転して90進む
				wait(200);
				turn(91.0);
				wait(200);
				go_back();
				wait(200);
				daikei(90.0);
				loop = 1;
//				output_wall();
//				myprintf("i=%d,j=%d\n", i_global, j_global);
//				myprintf("%d\n", canedir_global);
			} else {
				wait(200);
				daikei(90.0);			//90進んで左回転して90進む
				wait(200);
				turn(91.0);
				wait(200);
				daikei(90);
				loop = 1;
//				output_wall();
//				myprintf("i=%d,j=%d\n", i_global, j_global);
//				myprintf("%d\n", canedir_global);
			}
		} else {
			daikei(90);
			wait(200);
			turn(180);
			wait(400);
			daikei(90);
//			loop=1;
			loop = 0;
//			myprintf("%d,%d", on, canedir_global);
//			output_wall();
//			myprintf("i=%d,j=%d\n", i_global, j_global);
//			myprintf("%d\n", canedir_global);
		}
		if (canedir_global == 0)
			j_global++;
		else if (canedir_global == 1)
			i_global++;
		else if (canedir_global == 2)
			j_global--;
		else if (canedir_global == 3)
			i_global--;
	}
}
void non_stop() {
	int loop = 1, flag = 0, on = 0, end = 0;
//	map_clear();
	ang_global = 0;
	muki_global = 16;
	i_global = 0;
	j_global = 1;
	canedir_global = 0;
	distance_global = 0;
	accel_global = 0;
	turn(-90);
	wait(100);
	go_back();
	wait(100);
	turn(91);
	wait(100);
	go_back();
	wait(100);
	speed_global = 200;
//	accel(Max_acc);

	while (loop) {
		loop = 0;
		x_global = 0;
//		MTU2.TSTR.BIT.CST0 = 0;
//		MTU2.TSTR.BIT.CST0 = 0;
		flag++;
//		myprintf("hello");
//		for (i = 0; i < 16; i++) {
//			for (j = 0; j < 16; j++) {
//				map_global[i][j] = 255;
//			}
//		}
		map_clear();
		add_wall();
		maprule(0);
		on = hikaku();
//		myprintf("%d\n", canedir_global);
//		myprintf("%f\n", x_global);
		length_global = x_global;
		if (end == 0) {
			accel(Max_acc);
//			while (x_global <= 90 - distance_global)
//				;
			end++;
		}
		if (on == 1) {
			LED1 = 0;
			LED2 = 0;
			LED3 = 1;
			loop = 1;
			accel_global = 0;

			x_global = 0;
			distance_global = 0;
//			myprintf("%f\n",length_global);

			while (x_global <= 180 - length_global)
				;
//				myprintf("%d,%d,%d\n", SENLF_global, SENC_global, SENRF_global);
		} else if (on == 2) {
			if (SENLF_global > THRESHORD) {
				LED1 = 0;
				LED2 = 1;
				LED3 = 0;
				loop = 1;
//				end = 0;
				accel(Min_acc);
				wait(200);
				//			speed_global = 200;
				//			go(90-distance_global, 0);
				//			wait(200);
				turn(-90);
				wait(200);
				go_back();
				wait(200);
				speed_global = 200;
				//			go(90, 0);
				accel(Max_acc);
				//			wait(200);
			} else {
				LED1 = 0;
				LED2 = 1;
				LED3 = 0;
				loop = 1;
//				end = 0;
				accel(Min_acc);
				wait(200);
//			speed_global = 200;
//			go(90-distance_global, 0);
//			wait(200);
				turn(-90);
				wait(200);
				speed_global = 200;
//			go(90, 0);
				accel(Max_acc);
//			wait(200);
			}
		} else if (on == 3) {
			LED1 = 0;
			LED2 = 1;
			LED3 = 1;
			loop = 1;
//			end = 0;
			accel(Min_acc);
			wait(200);
			turn(90);
			wait(200);
			go_back();
			wait(100);
			turn(90);
			wait(200);
			go_back();
			wait(200);
			speed_global = 200;
//			go(90, 0);
//			wait(200);
			accel(Max_acc);
		} else if (on == 4) {
			if (SENRF_global > THRESHORD) {
				LED1 = 1;
				LED2 = 0;
				LED3 = 0;
				loop = 1;
//				end = 0;
				accel(Min_acc);
				wait(200);
				//			speed_global = 200;
				//			go(90-distance_global, 0);
				//			wait(200);
				turn(90);
				wait(200);
				go_back();
				wait(200);
				speed_global = 200;
				//			go(90-distance_global, 0);
				//			wait(200);
				accel(Max_acc);
			} else {
				LED1 = 1;
				LED2 = 0;
				LED3 = 0;
				loop = 1;
//				end = 0;
				accel(Min_acc);
				wait(200);
//			speed_global = 200;
//			go(90-distance_global, 0);
//			wait(200);
				turn(90);
				wait(200);
				speed_global = 200;
//			go(90-distance_global, 0);
//			wait(200);
				accel(Max_acc);
			}
		} else {
			go(40, 0);
			wait(200);
			turn(180);
		}
		if (canedir_global == 0)
			j_global++;
		else if (canedir_global == 1)
			i_global++;
		else if (canedir_global == 2) {
			j_global--;
			if (j_global < 0)
				j_global = 0;
		} else if (canedir_global == 3) {
			i_global--;
			if (i_global < 0)
				i_global = 0;
		}
//		myprintf("i=%d,j=%d\ndir=%d,map=%d\n", i_global, j_global,
//				canedir_global, map_global[i_global][j_global]);

		flag++;

//		myprintf("stop");

	}
//	myprintf("stop");
//	output_wall();
//	add_wall();
	speed_global = 0;

}
