#include <webots/keyboard.h>
#include <webots/robot.h>

#include <arm.h>
#include <base.h>
#include <gripper.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_STEP 32

static void step() {
  if (wb_robot_step(TIME_STEP) == -1) {
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}

static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do {
    step();
  } while (start_time + sec > wb_robot_get_time());
}

static void automatic_behavior() {
  passive_wait(2.0);
  base_reset();
  passive_wait(2.0);
  base_backwards();
  passive_wait(2.0);
  base_forwards();
  passive_wait(2.0);
  base_turn_left();
  passive_wait(2.0);
  base_turn_right();
  passive_wait(2.0);
  base_strafe_left();
  passive_wait(2.0);
  base_strafe_right();
  passive_wait(2.0);
  base_reset();
  passive_wait(2.0);
}

int main(int argc, char **argv) {
  wb_robot_init();

  base_init();
  arm_init();
  gripper_init();
  passive_wait(2.0);

  if (argc > 1 && strcmp(argv[1], "demo") == 0)
    automatic_behavior();

  wb_robot_cleanup();

  return 0;
}
