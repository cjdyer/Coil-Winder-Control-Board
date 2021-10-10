#include <Callback.h>
#include "mbed.h"
#include "StepperMotor.h"

StepperMotor::StepperMotor(
    PinName out_0,
    PinName out_1)
    : turn_count(0)
    , pin_zero(out_0)
    , pin_one(out_1)
    { }

void StepperMotor::set_direction(bool dir)
{
    pin_zero = dir;
}

void StepperMotor::single_step(float wait_time)
{
    pin_one = true;
    wait(wait_time / 10000);
    pin_one = false;
    wait(wait_time / 10000);
    turn_count += 0.005f;
}

void StepperMotor::single_turn(float wait_time)
{
    for(int i = 0; i < 200; i++)
    {
        single_step(wait_time);
    }
}

void StepperMotor::turn(float amount, float wait_time)
{
    for(int i = 0; i < 200 * amount; i++)
    {
        single_step(wait_time);
    }
}
;
