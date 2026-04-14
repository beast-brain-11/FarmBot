#include "gripper.h"

#include <webots/motor.h>
#include <webots/robot.h>

#include "tiny_math.h"

#define LEFT 0
#define RIGHT 1

#define MIN_POS 0.0
#define MAX_POS 0.025
#define OFFSET_WHEN_LOCKED 0.021

static WbDeviceTag fingers;

void gripper_init() {
  fingers = wb_robot_get_device("finger::left");

  wb_motor_set_velocity(fingers, 0.03);
}

void gripper_grip() {
  wb_motor_set_position(fingers, MIN_POS);
}

void gripper_release() {
  wb_motor_set_position(fingers, MAX_POS);
}

void gripper_set_gap(double gap) {
  double v = bound(0.5 * (gap - OFFSET_WHEN_LOCKED), MIN_POS, MAX_POS);
  wb_motor_set_position(fingers, v);
}
