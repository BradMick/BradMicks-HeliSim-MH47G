/////////////////////////////////////////////////////////////////////////////////////////////
// Flight Controls //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//PID gains are {kp, ki, kd, ki_clamp}.
//  alwaysOn         - hold engages whenever it can and re-engages after a pilot override; the
//                     keys neither engage nor release it. 0 = key engaged.
//  HydraulicBoost   - aircraft without an FMC only.

    //Input
    inputLagValue     = 0.95;     //control input smoothing

    //Casual mode attitude
    autoAttLevelPitch = -5.0;     //deg, level pitch target
    autoAttRollLimit  = 30.0;     //deg, bank commanded by the roll key
    pidAutoAttPitch[] = {0.0925, 0.0025, 0.0220, 0.0025};
    pidAutoAttRoll[]  = {0.0400, 0.0015, 0.0250, 0.0015};

    //Auto pedal
    pidAutoPedalHdg[]  = {0.0500, 0.0025, 0.0125, 30.000};   //hover, heading
    pidAutoPedalNtt[]  = {0.0150, 0.0040, 0.0025, 18.750};   //below 50 ft, nose-to-tail sideslip
    pidAutoPedalAero[] = {0.3000, 0.2500, 0.1000, 0.2000};   //above 50 ft, ball centred

    //Trim
    class Trim {
        forceTrim   = 1;          //centering device (magnetic brakes)
        class Beep {
            gate[]  = {};
            rate[]  = {0.10, 0.10};           //{pitch, roll} trim travel per second
            lag     = 0.1;                    //s, press to movement
            moves[] = {"stick", "stick"};
        };
    };

    //FMC
    class FMC {
        class Sas {
            gate[]      = {};
            pitch[]     = {0.1500, 0.0000, 0.0020, 0.0000};
            roll[]      = {0.1000, 0.0000, 0.0020, 0.0000};
            yaw[]       = {0.1500, 0.0250, 0.0060, 0.0500};
        };
        class AttitudeHold {
            gate[]      = {};
            posPitch[]  = {0.1500, 0.0070, 0.1200, 0.0070};   //position hold
            posRoll[]   = {0.0550, 0.0070, 0.0900, 0.0070};
            attPitch[]  = {0.0925, 0.0025, 0.0450, 0.0025};   //attitude hold
            attRoll[]   = {0.0400, 0.0015, 0.0180, 0.0015};
            alwaysOn    = 0;
        };
        class AltitudeHold {
            gate[]      = {};
            rad[]       = {0.0500, 0.0001, 0.0050, 0.0001};   //radar altitude
            bar[]       = {0.0010, 0.0000, 0.0008, 0.0000};   //barometric altitude
            alwaysOn    = 0;
        };
        class HeadingHold {
            gate[]      = {};
            hdg[]       = {0.0750, 0.0200, 0.0050, 0.0200};   //heading
            trn[]       = {0.2500, 0.0600, 0.3000, 0.1500};   //turn coordination
            alwaysOn    = 1;
        };
    };
