
#ifndef GRIPPER_H
#define GRIPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void gripper_init();

void gripper_grip();  // dangerous to grip an object with this function -> creates a lot of internal constraints
void gripper_release();
void gripper_set_gap(double gap);

#ifdef __cplusplus
}
#endif

#endif
