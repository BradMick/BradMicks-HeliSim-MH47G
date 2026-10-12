/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel tanks ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  variableName - the aircraft names its own tank variables. Core prefixes bmkhs_ and appends
//              the field: "fwdTank" publishes bmkhs_fwdTankMass, bmkhs_fwdTankMax,
//              bmkhs_fwdTankLow. Names must be unique. Do not include the bmkhs_ prefix.
//  arm[]     - {lateral, longitudinal, vertical} in m, right-positive / nose-positive
//  capacity  - kg of usable fuel
//  lowFuelKg - low-level caution threshold in kg; 0 for no caution on this tank
//  removable - 1 if the tank can be taken out; 0 is always fitted
//  role      - "main" (an engine can draw from it) or "xfer" (feeds the mains only)

    //Six tanks, three a side, arms from fm.p3d (placed as the fuselage is). Each engine draws
    //from its own side's main tank; each side's aux tanks transfer into that main - fn_setup
    //turns the aux transfer on. Main 3750 lb, aux ~1700 lb (user): 14,300 lb, 6486 kg.
    //TODO(MH47G): lowFuelKg, a crossfeed position, and the aux pumps as crew switches.
    numCrossfeedModes = 1;
    class CrossfeedModes {
        class Norm { position = "NORM"; engSources[] = {"leftMainTank", "rightMainTank"}; };
    };

    //The main-to-main XFER pump - fn_setup leaves it OFF.
    xferDestinations[] = {"LEFT", "RIGHT"};

    numFuelTanks = 6;
    class FuelTanks {
        class FuelTank01 {
            variableName = "leftMainTank";
            arm[]     = {-1.800, -0.035, 2.039};
            capacity  = 1701.0;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "main";
        };
        class FuelTank02 {
            variableName = "rightMainTank";
            arm[]     = {1.800, -0.035, 2.039};
            capacity  = 1701.0;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "main";
        };
        class FuelTank03 {
            variableName = "leftFwdAuxTank";
            arm[]     = {-1.800, 2.674, 2.110};
            capacity  = 771.1;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "xfer";
            class Outputs { class Main { tank = "leftMainTank"; }; };
        };
        class FuelTank04 {
            variableName = "rightFwdAuxTank";
            arm[]     = {1.800, 2.674, 2.110};
            capacity  = 771.1;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "xfer";
            class Outputs { class Main { tank = "rightMainTank"; }; };
        };
        class FuelTank05 {
            variableName = "leftAftAuxTank";
            arm[]     = {-1.800, -2.504, 1.974};
            capacity  = 771.1;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "xfer";
            class Outputs { class Main { tank = "leftMainTank"; }; };
        };
        class FuelTank06 {
            variableName = "rightAftAuxTank";
            arm[]     = {1.800, -2.504, 1.974};
            capacity  = 771.1;
            lowFuelKg = 0.0;
            removable = 0;
            role      = "xfer";
            class Outputs { class Main { tank = "rightMainTank"; }; };
        };
    };

    numAuxTanks = 0;
