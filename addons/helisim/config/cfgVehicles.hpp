#include "\bmkhs_helisim\fmOverride.hpp"

class CfgVehicles {
    class Helicopter_Base_H;
    //The base Chinook, reopened with its own parent so its config is extended, not replaced.
    //Everything else about the aircraft - model, crew, weapons, fuel capacity - stays as it is.
    //It is the only Chinook class that sets the force coefficients; Block 1 and Block 2
    //inherit them, so no variant needs the override again.
    class PGS_Chinook_Base : Helicopter_Base_H {
        //Core owns the force coefficients - packs cannot tune them
        BMKHS_FM_OVERRIDE

        #include "bmkhs_mh47g_config.hpp"
    };
};
