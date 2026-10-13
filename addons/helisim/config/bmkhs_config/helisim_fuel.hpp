/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//CROSSFEED
//  position      - crossfeed switch position name.
//  engSources[]  - tank each engine draws from, by engine.
//
//XFER
//  xferDestinations[] - main tanks the XFER pump can fill.
//
//TANKS
//  variableName  - tank name; Core publishes bmkhs_<name>Mass, Max and Low. Unique, no bmkhs_ prefix.
//  arm[]         - {lateral, longitudinal, vertical} m, right / nose / up positive.
//  capacity      - kg usable.
//  lowFuelKg     - kg low-fuel caution; 0 = none.
//  removable     - 1 = can be removed, 0 = always fitted.
//  role          - "main" (an engine draws from it) or "xfer" (feeds a main).
//  Outputs       - xfer only: the main tank it feeds.

    //Crossfeed
    numCrossfeedModes = 1;
    class CrossfeedModes {
        class Norm { position = "NORM"; engSources[] = {"leftMainTank", "rightMainTank"}; };
    };

    //Xfer
    xferDestinations[] = {"LEFT", "RIGHT"};

    //Tanks
    numFuelTanks = 6;
    class FuelTanks {
        class FuelTank01 {
            variableName = "leftMainTank";
            arm[]        = {-1.800, -0.035, 2.039};
            capacity     = 1701.0;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "main";
        };
        class FuelTank02 {
            variableName = "rightMainTank";
            arm[]        = {1.800, -0.035, 2.039};
            capacity     = 1701.0;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "main";
        };
        class FuelTank03 {
            variableName = "leftFwdAuxTank";
            arm[]        = {-1.800, 2.674, 2.110};
            capacity     = 771.1;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "xfer";
            class Outputs { class Main { tank = "leftMainTank"; }; };
        };
        class FuelTank04 {
            variableName = "rightFwdAuxTank";
            arm[]        = {1.800, 2.674, 2.110};
            capacity     = 771.1;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "xfer";
            class Outputs { class Main { tank = "rightMainTank"; }; };
        };
        class FuelTank05 {
            variableName = "leftAftAuxTank";
            arm[]        = {-1.800, -2.504, 1.974};
            capacity     = 771.1;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "xfer";
            class Outputs { class Main { tank = "leftMainTank"; }; };
        };
        class FuelTank06 {
            variableName = "rightAftAuxTank";
            arm[]        = {1.800, -2.504, 1.974};
            capacity     = 771.1;
            lowFuelKg    = 0.0;
            removable    = 0;
            role         = "xfer";
            class Outputs { class Main { tank = "rightMainTank"; }; };
        };
    };

    //Station tanks - fuel on a pylon station
    numAuxTanks = 0;
