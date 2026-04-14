/*
 * Description: Precision Farming Teleoperation Controller
 * Provides continuous holonomic chassis control and 
 * granular joint-by-joint manipulation for selective harvesting.
 */

#include <webots/keyboard.h>
#include <webots/robot.h>
#include <webots/motor.h>

#include <arm.h>
#include <base.h>
#include <gripper.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TIME_STEP 32

static void display_helper_message() {
  printf("\n=========================================\n");
  printf("   PRECISION FARM-BOT ENGAGED\n");
  printf("=========================================\n");
  printf(" CHASSIS (Hold to Drive):\n");
  printf("   W / S : Drive Forward / Backward\n");
  printf("   A / D : Strafe Left / Right\n");
  printf("   Q / E : Turn Left / Right\n\n");
  printf(" ARM JOINTS (Precision Increments):\n");
  printf("   1, 2, 3, 4, 5 : Move Joint Forward\n");
  printf("   Shift + (1-5) : Move Joint Backward\n\n");
  printf(" GRIPPER:\n");
  printf("   G : Toggle Grip / Release\n");
  printf("=========================================\n\n");
}

int main(int argc, char **argv) {
  wb_robot_init();

  // Initialize subsystems from included headers
  base_init();
  arm_init();
  gripper_init();

  display_helper_message();

  // Enable keyboard listening
  wb_keyboard_enable(TIME_STEP);

  // Define and fetch the 5 arm motors directly for precision override
  WbDeviceTag arm_motors[5];
  arm_motors[0] = wb_robot_get_device("arm1");
  arm_motors[1] = wb_robot_get_device("arm2");
  arm_motors[2] = wb_robot_get_device("arm3");
  arm_motors[3] = wb_robot_get_device("arm4");
  arm_motors[4] = wb_robot_get_device("arm5");

  // Set safe starting angles for the arm (Folded/Transport position)
  double arm_targets[5] = {0.0, 1.57, -1.57, 1.57, 0.0}; 
  for(int i = 0; i < 5; i++) {
      wb_motor_set_position(arm_motors[i], arm_targets[i]);
  }

  bool gripper_closed = false;
  int previous_key = -1;

  // The Super-Loop
  while (wb_robot_step(TIME_STEP) != -1) {
    int key = wb_keyboard_get_key();

    // --- CHASSIS CONTROL (Continuous Holonomic) ---
    if (key == 'W') base_forwards();
    else if (key == 'S') base_backwards();
    else if (key == 'A') base_strafe_left();
    else if (key == 'D') base_strafe_right();
    else if (key == 'Q') base_turn_left();
    else if (key == 'E') base_turn_right();
    else base_reset(); // Immediately stop moving if no drive key is held

    // --- ARM CONTROL (Precision Joint Increments) ---
    double step = 0.015; // Granular step size for delicate movements
    
    // Joint 1 (Base Pan)
    if (key == '1') arm_targets[0] += step;
    else if (key == '!' || key == ('1' | WB_KEYBOARD_SHIFT)) arm_targets[0] -= step;

    // Joint 2 (Shoulder Tilt)
    if (key == '2') arm_targets[1] += step;
    else if (key == '@' || key == ('2' | WB_KEYBOARD_SHIFT)) arm_targets[1] -= step;

    // Joint 3 (Elbow Tilt)
    if (key == '3') arm_targets[2] += step;
    else if (key == '#' || key == ('3' | WB_KEYBOARD_SHIFT)) arm_targets[2] -= step;

    // Joint 4 (Wrist Tilt)
    if (key == '4') arm_targets[3] += step;
    else if (key == '$' || key == ('4' | WB_KEYBOARD_SHIFT)) arm_targets[3] -= step;

    // Joint 5 (Wrist Twist)
    if (key == '5') arm_targets[4] += step;
    else if (key == '%' || key == ('5' | WB_KEYBOARD_SHIFT)) arm_targets[4] -= step;

    // Apply the newly calculated targets to the motors
    for(int i = 0; i < 5; i++) {
        wb_motor_set_position(arm_motors[i], arm_targets[i]);
    }

    // --- GRIPPER CONTROL (Toggle Action) ---
    // The previous_key check prevents the gripper from spastically opening/closing if you hold 'G' too long
    if (key == 'G' && previous_key != 'G') {
      if (gripper_closed) {
          gripper_release();
          printf("[SYS] Gripper: RELEASED\n");
      } else {
          gripper_grip();
          printf("[SYS] Gripper: CLOSED\n");
      }
      gripper_closed = !gripper_closed;
    }

    previous_key = key;
  }

  wb_robot_cleanup();
  return 0;
}