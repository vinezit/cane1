/*
 * run.h
 *
 *  Created on: 2018/10/06
 *      Author: ilove
 */

#ifndef RUN_H_
#define RUN_H_

void accel(float b);
void RUN(float sp1);
void map_clear();
int enq_z(struct queue *que,int input);
int deq_z(struct queue *que);
void init_queue();
void maprule(int mode);
void shortest_route();
int hikaku();
void Adati();
void non_stop();
#endif /* RUN_H_ */
