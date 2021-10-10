#ifndef    MBED_STEPPERMOTOR
#define    MBED_STEPPERMOTOR
 
#include "mbed.h"

class StepperMotor {
public:

    /** Create a stepper motor object connected to specified DigitalOut pins
     *
     *  @param out_0 DigitalOut pin for motor direction
     *  @param out_1 DigitalOut pin for motor pulse signal
     */
    StepperMotor(
        PinName out_0 = PC_0,
        PinName out_1 = PC_1
    );

    /** Set the direction the motor should move
     *
     *  @param direction the motor should move in operation : LEFT (default), RIgHT
     */
    void set_direction(bool dir);

    void single_step(float wait_time);
    
    void single_turn(float wait_time);
    
    void turn(float amount, float wait_time);
    
    float turn_count;
    
private:
 
    DigitalOut  pin_zero;
    DigitalOut  pin_one;
    
};
 
 
#endif