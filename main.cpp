#include "mbed.h"
#include "StepperMotor.h"

// Naming and Syntax
//
// myFuction() = Functions
// my_variable = Variables
// MY_DEFINE   = Defines
// MyType      = TypeDefs
// i, j, k     = Index variables

// Procedure
//
// Init system
// User Initated > Calibrate ( Run to limits, finishing at left input ) : Display warning
// User Initated > Recieve inputs
// Validisation of inputs
// Declare ready to user
// User inputs coil > All movement systems off 100% till confirm
// User Initated > Ready check : Display warning
// Begin spin fuction
// Finish spin function

// Codes
//
// 

// Motor Controls 
//
// bobbinMotor FALSE = Wind, TRUE = Unwind
// railMotor FALSE = Out, TRUE = In
//
// railMotor fastest = 10
// bobbinMotor fastest = 8
    
RawSerial pc(USBTX, USBRX);
StepperMotor bobbinMotor(PA_8, PA_9);
StepperMotor railMotor(PB_4, PB_10);
DigitalIn limit(PC_8);

char buffer[20];
int len = 0;
float turns_count = 0;
bool begin_data = false;
bool direction = false;
bool running = false;

void turnWatcher()
{
    if(turns_count != 0 && bobbinMotor.turn_count != 0)
    {
        if(bobbinMotor.turn_count >= turns_count)
            exit(0);
    }
}

void initiliseSequence()
{
    railMotor.set_direction(true);
    while(!limit) { railMotor.single_step(8); }
    railMotor.set_direction(false);
    while(limit) { railMotor.single_step(8); }
    railMotor.turn(0.38, 15);//0.25 works(sticks to side) // 0.2 too close
}

void windSequence()
{   
    for(int i = 0; i < 5; i++)
    {
        bobbinMotor.turn(1, 9);
        railMotor.turn(0.038, 15); //0.038 
        turnWatcher();
    }  
    for(int i = 0; i < 30; i++)
    {
        bobbinMotor.turn(1, 9);
        railMotor.turn(0.032, 15); //0.32
        turnWatcher();
    }
    for(int j = 0; j < 5; j++)
    {
        direction = !direction;
        railMotor.set_direction(direction);
        
        for(int i = 0; i < 34; i++)
        {
            bobbinMotor.turn(1, 9);
            railMotor.turn(0.032, 15); // 0.032
            turnWatcher();
        }
    }
}
            
void doCommand(int command_length)
{
    char command = buffer[0];
    if(command == 'S')
    {
        if(!running)
        {
            pc.printf("Coil winder started.\n");
            running = true;
            initiliseSequence();
            windSequence();
        }
        else
        {
            pc.printf("Coil winder stopped.\n");
            exit(0);
        }
    }
    else if(command == 'P')
        pc.printf("Ping sent and received.\n");
    else if(command == 'C')
    {
        pc.printf("Calculation data received.\n");
        char buffer2[19];
        strncpy (buffer2, buffer+1, command_length);
        buffer2[command_length] = '\0';
        float f;
        f = (float)atof(buffer2); 
        turns_count = f;
    }
}

void onDataReceived()
{
    char input = pc.getc();
    if(input == 'B')
        begin_data = true;
    else if(begin_data)
    {
        if (input == '\n')
        {
            doCommand(len);
            len = 0;
            begin_data = false;
        } 
        else 
        {
            buffer[len++] = input;
            if(len >= 19)
                len = 0;
        }
    }
}

int main() 
{   
    wait_ms(200); // Setup time
    
    pc.attach(&onDataReceived);
    
    pc.baud(9600);
    pc.format(); // Defualt = 8 bits, No parity, 1 Stop bit
    
    while(true);
}