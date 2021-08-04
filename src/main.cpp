/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Karina Tam                                                */
/*    Created:      Thu Jul 15 2021                                           */
/*    Description:  Girl Powered 2021 Template                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// arm                  motor         8               
// claw                 motor         3               
// leftDrive            motor         1               
// rightDrive           motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

bool arcadeControl = true;    // controls whether the drivebase is driven in tank style (false) or arcade style (true)
double driveSpeed = 0.75;     // changes the maximum drive speed (range is from 0 to 1)
int threshold = 5;            // controls the minimum speed of the drivebase

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  /* --------------------------------------------------------------------------
  SAMPLE PROGRAM:
  moveClaw(25); // Keeps grip on object

  turnAngle(-90); // Turn left
  wait(200, msec);

  moveArm(200); // Move the arm up
  wait(300, msec);
  moveArm(1); // Holds arm up

  moveDistance(10); // Move forwards

  moveClaw(-200); // Drop ring
  wait(150, msec);
  moveClaw(0);
  ---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool holdClaw = false;

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if (Controller1.ButtonL1.pressing())
    {
      moveClaw (150);
      holdClaw = true;
    }
    else if (Controller1.ButtonL2.pressing())
    {
      moveClaw (-150);
      holdClaw = false;
    }
    else if (holdClaw)
    {
      // holding power for the claw
      claw.spin(forward, 0.5, volt);
    }
    else
    {
      moveClaw (0);
    }

    if (Controller1.ButtonR1.pressing())
    {
      moveArm (80);
    }
    else if (Controller1.ButtonR2.pressing())
    {
      moveArm (-60);
    }
    else
    {
      // holding power to keep the arm up
      arm.spin(forward, 0.5, volt);
    }

    if (arcadeControl)
    {
      int forward = Controller1.Axis3.position();
      int turn = Controller1.Axis1.position();

      if (abs(forward) < threshold)
      {
        forward = 0;
      }
      if (abs(turn) < threshold)
      {
        turn = 0;
      }

      int maxSpeed = 200 * driveSpeed;
      if (abs(forward+turn) > maxSpeed)
      {
        moveLeft (maxSpeed);
      }
      else
      {
        moveLeft(forward+turn);
      }
      if (abs(forward-turn) > maxSpeed)
      {
        moveRight(maxSpeed);
      }
      else
      {
        moveRight(forward-turn);
      }
    }
    else
    {
      int right = Controller1.Axis2.position();
      int left = Controller1.Axis3.position();
      if (abs(left) < threshold)
      {
        left = 0;
      }
      if (abs(right) < threshold)
      {
        right = 0;
      }
      moveLeft (left*2*driveSpeed);
      moveRight (right*2*driveSpeed);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
