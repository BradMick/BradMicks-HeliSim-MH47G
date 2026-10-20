/////////////////////////////////////////////////////////////////////////////////////////////
// Flight Controls //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//Field reference: \bmkhs_helisim\fmc.hpp. PID gains {kp, ki, kd, limit}.

    //Input
    inputLagValue     = 0.95;     //control input smoothing

    //Casual mode attitude
    autoAttLevelPitch = -5.0;     //deg, level pitch target
    autoAttRollLimit  = 30.0;     //deg, bank commanded by the roll key
    pidAutoAttPitch[] = {0.0925, 0.0025, 0.0220, 0.1};
    pidAutoAttRoll[]  = {0.0400, 0.0015, 0.0250, 0.1};

    //Auto pedal
    pidAutoPedalHdg[]  = {0.0500, 0.0025, 0.0125, 0.075};    //hover, heading
    pidAutoPedalNtt[]  = {0.0150, 0.0040, 0.0025, 0.075};    //below 50 ft, nose-to-tail sideslip
    pidAutoPedalAero[] = {0.3000, 0.2500, 0.1000, 0.05};     //above 50 ft, ball centred

    //Trim
    class Trim {
        class Beep {
            gate[]  = {};
            rate[]  = {0.10, 0.10};           //{pitch, roll} trim travel per second
        };
    };

    //FMC
    class FMC {
        class Sas {
            gate[]      = {};
            pitch[]     = {0.0026, 0.0000, 0.000035, 0.00};
            roll[]      = {0.0017, 0.0000, 0.000035, 0.00};
            yaw[]       = {0.0026, 0.00044, 0.00010, 0.001276};
        };
        class AttitudeHold {
            gate[]      = {};
            subModes[]  = {"att", "spd"};
            alwaysOn    = 1;
            spdAboveKts = 40;
            attPitch[]  = {0.0925, 0.0025, 0.0450, 0.1};      //attitude hold
            attRoll[]   = {0.0400, 0.0015, 0.0180, 0.1};
            spdPitch[]  = {0.5000, 0.0500, 0.0000, 10};      //airspeed hold - retune
            trimGain[]  = {10, 10};         //deg per unit of beep trim
        };
        class AltitudeHold {
            gate[]      = {};
            rad[]       = {0.015, 0.00003, 0.0015, 0.05};      //radar altitude
            bar[]       = {0.0003, 0.0000, 0.00024, 0.00};   //barometric altitude
        };
        class HeadingHold {
            gate[]      = {};
            subModes[]  = {"hdg", "trn"};
            hdg[]       = {0.0750, 0.0200, 0.0050, 0.1};      //heading
            trn[]       = {0.2500, 0.0600, 0.3000, 0.009};    //turn coordination
        };
    };
