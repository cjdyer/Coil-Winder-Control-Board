#include "mbed.h"
#include "CoilWinder.h"

CoilWinder::CoilWinder(
    float diameter_coil,
    float diameter_bobbin,
    int pos_winder,
    int pos_guide) :
    safe_mode(true)
    {
        t.attach(callback(this, &CoilWinder::_interupt), 10.0);
    }
    
    void CoilWinder::initateSystem(void) {
        while(1);
    }

    void CoilWinder::calibrate(void) {
        while(1);
    }

    bool CoilWinder::validate(bool) {
        return true;
    }

    bool CoilWinder::userReady(int type) {
        return true;
    }

    void CoilWinder::operation(void) {
        while(1);
    }

    void CoilWinder::_interupt(void) {
        while(1);
    }
;   
