#ifndef    COIL_WINDER
#define    COIL_WINDER
 
#include "mbed.h"
 
class CoilWinder {
public:
    
    
    CoilWinder(
        float diameter_coil,
        float diameter_bobbin,
        int pos_winder,
        int pos_guide
    );
    
    void initateSystem(void);
    
    void calibrate(void);
    
    bool validate(bool);
    
    bool userReady(int type);
    
    void operation(void);
    
private:
    Ticker t;
    bool safe_mode;
    
    void _interupt(void);
};
    
#endif