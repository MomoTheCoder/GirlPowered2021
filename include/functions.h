#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

using namespace vex;

void moveArm (double velocity);
void moveClaw (double velocity);
void moveLeft (double velocity);
void moveRight (double velocity);
void moveDrive (double velocity);

void setMaxVelocity (double velocity);
void setMinVelocity (double velocity);
void setGearRatio (double newRatio);
void turnAngle (double angle);
void moveDistance (double inches);

#endif
