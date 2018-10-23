/*
 * function.h
 *
 *  Created on: 2018/08/11
 *      Author: ilove
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

void wait(int a);
void interrupt_cmt0();
void duty(int a, int b);
void integral();
void Lipo();
int mode_select(int a);
void go(float a, int b);
void go_speed(float a, int b);
void go_back();
void turn(float ang);
int FLAG();
void dir();
void go_daikei(float a, float b);
void excitation();
void daikei(float a);
void left_hand(int z,int y);
#endif /* FUNCTION_H_ */
