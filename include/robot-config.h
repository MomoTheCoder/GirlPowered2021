using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor arm;
extern motor claw;
extern motor leftDrive;
extern motor rightDrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );