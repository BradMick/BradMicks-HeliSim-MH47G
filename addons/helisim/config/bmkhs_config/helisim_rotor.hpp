/////////////////////////////////////////////////////////////////////////////////////////////
// Rotors - Blade Element Theory ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//Per-rotor arrays, one entry per rotor in order.

    numRotors            = 2;

    //Identity
    rotorType[]          = {0,      1};           //0 = main, 1 = tail
    rotorDirection[]     = {0,      0};           //0 = ccw, 1 = cw

    //Placement
    rotorPivot[]         = {
                            { 0.00,  2.06,  0.000}   //m
                          , { 0.00, -6.98, -0.075}
                          };
    rotorRotation[]      = {
                            {0.0,  0.0, 0.0}         //deg
                          , {0.0, 90.0, 0.0}
                          };
    rotorMastLength[]    = {0.70,   -0.87};       //m

    //Drive
    rotorGearRatio[]     = {72.291, 14.90};

    //Blade
    rotorNumBlades[]     = {4,      4};
    rotorNumElements[]   = {4.0,    4.0};         //blade elements per blade
    rotorAirfoil[]       = {"NACA 4418", "NACA 0012"};
    rotorBladeCutout[]   = {1.15,   0.15};        //m, root cutout
    rotorBladeLength[]   = {7.315,  1.402};       //m
    rotorBladeChord[]    = {0.533,  0.253};       //m
    rotorBladeTwist[]    = {-9,     -8};          //deg
    rotorBladeMass[]     = {72.108, 5.131};       //kg
    rotorDelta3[]        = {0.5,    0.5};         //pitch-flap coupling

    //Flap response, {longitudinal, lateral} s
    rotorFlapTimeConst[] = {
                            {2.0, 3.0}
                          , {0.5, 0.5}
                          };

    //Blade pitch ranges, deg
    rotorPitchMin[]      = {-10,    0};
    rotorPitchMid[]      = {0,      0};
    rotorPitchMax[]      = {20,     0};
    rotorRollMin[]       = {-10.5,  0};
    rotorRollMid[]       = {0,      0};
    rotorRollMax[]       = {7,      0};
    rotorCollMin[]       = {1,      -15};
    rotorCollMid[]       = {0,      0};
    rotorCollMax[]       = {19,     27};

    //Model bindings
    rotorAnimSource[]    = {"rotorH",       "rotorV"};
    rotorHitPoint[]      = {"hithrotor",    "hitvrotor"};
