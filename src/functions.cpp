#include "vex.h"

using namespace vex;

int sgn (double num)
{
  if (num < 0)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

void moveArm (double velocity)
{
  if (sgn(velocity) > 0)
  {
    arm.spin(fwd, fabs(velocity), rpm);
  }
  else
  {
    arm.spin(reverse, fabs(velocity), rpm);
  }
}

void moveClaw (double velocity)
{
  if (sgn(velocity) > 0)
  {
    claw.spin(fwd, fabs(velocity), rpm);
  }
  else
  {
    claw.spin(reverse, fabs(velocity), rpm);
  }
}

void moveLeft (double velocity)
{
  if (sgn(velocity) > 0)
  {
    leftDrive.spin(fwd, fabs(velocity), rpm);
  }
  else
  {
    leftDrive.spin(reverse, fabs(velocity), rpm);
  }
}

void moveRight (double velocity)
{
  if (sgn(velocity) > 0)
  {
    rightDrive.spin(fwd, fabs(velocity), rpm);
  }
  else
  {
    rightDrive.spin(reverse, fabs(velocity), rpm);
  }
}

void moveDrive (double velocity)
{
  moveRight (velocity);
  moveLeft (velocity);
}

void moveRightVolts (double power)
{
  if (sgn(power) > 0)
  {
    rightDrive.spin(forward, fabs(power), volt);
  }
  else
  {
    rightDrive.spin(reverse, fabs(power), volt);
  }
}

void moveLeftVolts (double power)
{
  if (sgn(power) > 0)
  {
    leftDrive.spin(forward, fabs(power), volt);
  }
  else
  {
    leftDrive.spin(reverse, fabs(power), volt);
  }
}

void moveDriveVolts (double power)
{
  moveLeftVolts(power);
  moveRightVolts(power);
}

double maxVolt = 7;
double minVolt = 0.25;
double ENCODER_PER_INCH = 35;
double ENCODER_PER_DEGREE = 4.1;
double gearRatio = 1;

void setmaxVolt (double power)
{
  maxVolt = fabs(power);
}

void setminVolt (double power)
{
  minVolt = fabs(power);
}

void setGearRatio (double newRatio)
{
  gearRatio = newRatio;
}

void turnAngle (double angle)
{
  // Variables
  float error, current;
  float stopPoint = 13;
  double output;
  float kP = 0.055;

  angle = angle * ENCODER_PER_DEGREE * gearRatio;

  // reset the encoder and accelerate
  rightDrive.resetPosition();
  leftDrive.resetPosition();

  current = 0;
  error = angle;

  // the robot moves for the main portion of the function
  while (fabs(error) > stopPoint)
  {
    current = (leftDrive.position(deg) - rightDrive.position(deg)) / 2;

    error = angle - current;

    // Final Output
    output = kP * error;

    if (fabs(output) > maxVolt) {
      output = maxVolt * sgn(output);
    }
    if (fabs(output) < minVolt) {
      output = minVolt * sgn(output);
    }

    moveLeftVolts(output);
    moveRightVolts(output * -1);

    wait(10, msec);
  }

  moveDriveVolts(0);
}

void moveDistance (double inches)
{
  // Variables
  float error, currentLength;
  float stopPoint = 13;
  float output;
  float kP = 0.06;

  inches = inches * ENCODER_PER_INCH * gearRatio;
  
  // reset the encoder and accelerate
  rightDrive.resetPosition();
  leftDrive.resetPosition();

  currentLength = 0;
  error = inches;

  // the robot moves for the main portion of the function
  while (fabs(error) > stopPoint)
  {
    currentLength = (rightDrive.position(deg) + leftDrive.position(deg)) / 2;

    error = inches - currentLength;

    // Final Output
    output = kP * error;

    if (fabs(output) > maxVolt) {
      output = maxVolt * sgn(output);
    }
    if (fabs(output) < minVolt) {
      output = minVolt * sgn(output);
    }

    moveDriveVolts(output);

    wait(10, msec);
  }

  moveDriveVolts(0);
}