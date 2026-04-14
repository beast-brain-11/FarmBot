#ifndef BASE_H
#define BASE_H

#include <webots/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void base_init();

void base_reset();
void base_forwards();
void base_backwards();
void base_turn_left();
void base_turn_right();
void base_strafe_left();
void base_strafe_right();

void base_move(double vx, double vy, double omega);
void base_forwards_increment();
void base_backwards_increment();
void base_turn_left_increment();
void base_turn_right_increment();
void base_strafe_left_increment();
void base_strafe_right_increment();

void base_goto_init(double time_step);
void base_goto_set_target(double x, double y, double a);
void base_goto_run();
bool base_goto_reached();

#ifdef __cplusplus
}
#endif

#endif
