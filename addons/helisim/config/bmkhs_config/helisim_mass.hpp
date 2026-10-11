/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

    //TODO(MH47G): the Bo 105's mass, balance, seats and stations as a placeholder.
    //Empty airframe. No EmptyMassVariants - no fitted equipment changes it.
    emptyMass         = 1675; //kg
    emptyMom          = 5468.875;

    //Maximum gross mass - bounds the fixed test weight
    maxGrossMass      = 2500; //kg

    //Fuselage station datum and CG limits
    fsDatum             = 5.445;      //m, station 0 reference
    fwdCgLimit          = 2.370;    //m
    aftCgLimit          = 2.050;    //m
    comCorrection[]     = {0.000, 0.000, -0.326};
    //Casual mode center of mass
    casualModeCom[]     = {0.000, 0.810, 0.975};

/////////////////////////////////////////////////////////////////////////////////////////////
// Indexed mass items ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Every mass item is {arm, mass}: arm[] is {lateral, longitudinal, vertical} in metres,
    //right-positive / nose-positive, in the same surveyed frame as fsDatum.

    //SEATS. Occupancy is resolved against fullCrew, so an empty seat adds no mass.
    //  role       - "driver" | "gunner" | "commander" | "turret" | "cargo"
    //  turret[]   - turret path for gunner/commander/turret seats; {} for the driver
    //  cargoIndex - cargo slot for role = "cargo"; -1 otherwise
    numSeats = 6;
    class Seats {
        class Seat01 {  //pilot
            arm[]      = {0.364, 3.433, -1.022};
            mass       = 100.0;
            role       = "driver";
            turret[]   = {};
            cargoIndex = -1;
        };
        class Seat02 {  //copilot / gunner
            arm[]      = {-0.375, 3.400, -1.020};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {0};
            cargoIndex = -1;
        };
        class Seat03 {  //rear left
            arm[]      = {-0.394, 2.538, -0.899};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {1};
            cargoIndex = -1;
        };
        class Seat04 {  //rear right
            arm[]      = {0.354, 2.544, -0.937};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {2};
            cargoIndex = -1;
        };
        class Seat05 {  //rear left outside
            arm[]      = {-0.742, 2.816, -1.161};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {3};
            cargoIndex = -1;
        };
        class Seat06 {  //rear right outside
            arm[]      = {0.756, 2.851, -1.166};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {4};
            cargoIndex = -1;
        };
    };

    //STATIONS - the HOT launchers
    numStations = 2;
    class Stations {
        class Station01 {  //left
            arm[]    = {-1.614, 2.015, -1.153};
            pylons[] = {1, 3, 5};
        };
        class Station02 {  //right
            arm[]    = {1.614, 2.015, -1.153};
            pylons[] = {2, 4, 6};
        };
    };

    numMagazines = 0;

    //TODO(MH47G): the Bo 105's HOT launchers as a placeholder.
    numStores = 1;
    class Stores {
        class Store01 {  //HOT 1 / HOT 2
            match        = "hot_heat";
            launcherMass = 25.5;    //kg, 3 x 8.5 kg tube
            massPerRound = 23.5;    //kg
            isTank       = 0;
        };
    };
