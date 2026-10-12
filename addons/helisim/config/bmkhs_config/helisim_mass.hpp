/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

    //Datum, CG limits and the empty CG from fm.p3d's referenceDatum, fwdCgLimit and aftCgLimit,
    //placed as the fuselage is (helisim_fuselage.hpp line 2) - the panels' frame, longitudinal y.
    //Empty airframe. No EmptyMassVariants - fitted kit is Equipment below.
    emptyMass         = 11150;     //kg
    emptyMom          = 93237.79;  //empty CG mid-way between the limits (user): station 8.362 m (329.2 in)

    //Maximum gross mass - bounds the fixed test weight
    maxGrossMass      = 24494; //kg - 54,000 lb

    //Fuselage station datum and CG limits
    fsDatum             = 8.012;    //m, station 0 reference - fm.p3d referenceDatum
    fwdCgLimit          = 0.145;    //m - station 7.870 m (309.8 in)
    aftCgLimit          = -0.845;   //m - station 8.860 m (348.8 in)
    comCorrection[]     = {0.000, 0.000, 1.724};   //vertical only - nudged in game, 2026-10-11
    //Casual mode center of mass - Arma frame, between the rotors: picks straight up with no input
    casualModeCom[]     = {-0.003, -1.721, -1.279};

/////////////////////////////////////////////////////////////////////////////////////////////
// Indexed mass items ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Every mass item is {arm, mass}: arm[] is {lateral, longitudinal, vertical} in metres,
    //right-positive / nose-positive, in the same surveyed frame as fsDatum.

    //SEATS. Occupancy is resolved against fullCrew, so an empty seat adds no mass.
    //  role       - "driver" | "gunner" | "commander" | "turret" | "cargo"
    //  turret[]   - turret path for gunner/commander/turret seats; {} for the driver
    //  cargoIndex - cargo slot for role = "cargo"; -1 otherwise
    //Arms measured in game with tools/seats.sqf (occupant's pelvis).
    #define SEAT_MASS_CREW  100.0   //220 lb - pilots, gunners
    #define SEAT_MASS_TROOP 149.7   //330 lb - infantry with combat load, every cabin seat (UH-60's)
    #define SEAT_DRIVER(cls,x,y,z)   class cls { arm[] = {x,y,z}; mass = SEAT_MASS_CREW;  role = "driver"; turret[] = {};  cargoIndex = -1; };
    #define SEAT_TURRET(cls,t,x,y,z) class cls { arm[] = {x,y,z}; mass = SEAT_MASS_CREW;  role = "turret"; turret[] = {t}; cargoIndex = -1; };
    #define SEAT_CARGO(cls,c,x,y,z)  class cls { arm[] = {x,y,z}; mass = SEAT_MASS_TROOP; role = "cargo";  turret[] = {};  cargoIndex = c; };
    numSeats = 34;
    class Seats {
        SEAT_DRIVER(Seat01,0.499,6.186,1.910)
        SEAT_TURRET(Seat02,0,-0.479,6.195,1.909)
        SEAT_TURRET(Seat03,1,-0.795,4.123,2.055)
        SEAT_TURRET(Seat04,2,0.886,4.055,2.055)
        SEAT_TURRET(Seat05,3,-0.894,-4.461,1.783)
        SEAT_TURRET(Seat06,4,0.575,-4.211,1.783)
        SEAT_TURRET(Seat07,5,-0.038,5.286,2.069)
        SEAT_TURRET(Seat08,6,0.795,-3.900,1.887)
        SEAT_TURRET(Seat09,8,0.709,-6.426,0.684)
        SEAT_TURRET(Seat10,9,-0.742,-6.006,0.778)
        //TODO(MH47G): turrets 7, 10 and 11 did not measure (tools/seats.sqf could not seat a unit) -
        //check them in game, put in their arms, uncomment and raise numSeats.
        //SEAT_TURRET(SeatNN,7,x,y,z)
        //SEAT_TURRET(SeatNN,10,x,y,z)
        //SEAT_TURRET(SeatNN,11,x,y,z)
        SEAT_CARGO(Seat11,0,-0.858,2.867,1.674)
        SEAT_CARGO(Seat12,1,0.831,2.874,1.674)
        SEAT_CARGO(Seat13,2,-0.866,2.212,1.663)
        SEAT_CARGO(Seat14,3,0.832,2.199,1.667)
        SEAT_CARGO(Seat15,4,-0.862,1.544,1.645)
        SEAT_CARGO(Seat16,5,0.810,1.542,1.639)
        SEAT_CARGO(Seat17,6,-0.839,0.895,1.639)
        SEAT_CARGO(Seat18,7,0.837,0.867,1.625)
        SEAT_CARGO(Seat19,8,-0.855,0.186,1.590)
        SEAT_CARGO(Seat20,9,0.829,0.197,1.594)
        SEAT_CARGO(Seat21,10,-0.827,-0.465,1.608)
        SEAT_CARGO(Seat22,11,0.830,-0.490,1.594)
        SEAT_CARGO(Seat23,12,-0.825,-1.124,1.570)
        SEAT_CARGO(Seat24,13,0.812,-1.157,1.573)
        SEAT_CARGO(Seat25,14,-0.839,-1.853,1.559)
        SEAT_CARGO(Seat26,15,0.789,-1.889,1.561)
        SEAT_CARGO(Seat27,16,0.002,4.161,1.309)
        SEAT_CARGO(Seat28,17,0.003,3.135,1.315)
        SEAT_CARGO(Seat29,18,0.002,2.128,1.245)
        SEAT_CARGO(Seat30,19,0.002,1.071,1.247)
        SEAT_CARGO(Seat31,20,0.001,0.047,1.189)
        SEAT_CARGO(Seat32,21,0.003,-1.001,1.189)
        SEAT_CARGO(Seat33,22,0.002,-2.014,1.142)
        SEAT_CARGO(Seat34,23,0.003,-3.065,1.125)
    };

    //No pylons - no stations or stores.
    numStations = 0;

    //Fitted kit - counted while its hide animation is on the installedPhase side of 0.5. Door guns
    //dry, at each gunner's seat (UH-60 pack weights); the belts are magazines.
    numEquipment = 14;
    class Equipment {
        class Equipment01 {  //M134D left - 39 gun + 3.4 mount
            animation      = "Hide_M134_1";
            installedPhase = 0;
            mass           = 42.4;
            arm[]          = {-0.795, 4.123, 2.055};
        };
        class Equipment02 {  //M134D right
            animation      = "Hide_M134_2";
            installedPhase = 0;
            mass           = 42.4;
            arm[]          = { 0.886, 4.055, 2.055};
        };
        class Equipment03 {  //M240 left - 12.5 gun (estimate) + 3.4 mount
            animation      = "Hide_M240_1";
            installedPhase = 0;
            mass           = 15.9;
            arm[]          = {-0.894, -4.461, 1.783};
        };
        class Equipment04 {  //M240 right
            animation      = "Hide_M240_2";
            installedPhase = 0;
            mass           = 15.9;
            arm[]          = { 0.575, -4.211, 1.783};
        };
        class Equipment05 {  //AAR probe - 502 lb complete system, Army flight test, Chinook-type (airframe unconfirmed)
            animation      = "Hide_Probe";
            installedPhase = 0;
            mass           = 228;
            arm[]          = { 1.000, 7.000, 1.200};
        };
        class Equipment06 {  //Armor plating - US Army Chinook ballistic protection system, ~3,500 lb (2013), along the cabin
            animation      = "Hide_Armor_Plating";
            installedPhase = 0;
            mass           = 1588;
            arm[]          = { 0.000, 0.000, 1.300};
        };
        class Equipment07 {  //Cargo door armor - estimate
            animation      = "Hide_Armor_Hoist";
            installedPhase = 0;
            mass           = 35;
            arm[]          = { 1.100, 4.300, 1.900};
        };
        class Equipment08 {  //Fuel dump pipe - estimate
            animation      = "Hide_Fuel_Dump_Pipe";
            installedPhase = 0;
            mass           = 4;
            arm[]          = { 0.000, -6.500, 1.000};
        };
        class Equipment09 {  //Door plug - estimate
            animation      = "HideCrewDoor";
            installedPhase = 0;
            mass           = 20;
            arm[]          = { 1.100, 4.300, 1.900};
        };
        class Equipment10 {  //Window plug, forward left - estimate
            animation      = "Hide_Fwd_L_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = {-1.200, 4.120, 2.050};
        };
        class Equipment11 {  //Window plug, forward right - estimate
            animation      = "Hide_Fwd_R_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = { 1.200, 4.060, 2.050};
        };
        class Equipment12 {  //Window plug, aft left - estimate
            animation      = "Hide_Aft_L_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = {-1.200, -4.460, 1.780};
        };
        class Equipment13 {  //Window plug, aft right - estimate
            animation      = "Hide_Aft_R_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = { 1.200, -4.210, 1.780};
        };
        class Equipment14 {  //Skis - estimate (Airglas CH-47 ski weight not found)
            animation      = "Hide_Skis";
            installedPhase = 0;
            mass           = 110;
            arm[]          = { 0.000, 0.000, 0.300};
        };
    };

    //Internal rounds - counted per round left, all magazines matching each entry (UH-60 pack weights).
    numMagazines = 3;
    class Magazines {
        class Mag01 {  //M134D belts, both forward doors
            match        = "4000rnd_65x39";
            arm[]        = { 0.046, 4.089, 2.055};
            massPerRound = 0.0254;
        };
        class Mag02 {  //M240 belts, both aft windows
            match        = "250rnd_762x51";
            arm[]        = {-0.160, -4.336, 1.783};
            massPerRound = 0.0254;
        };
        class Mag03 {  //flares - TODO(MH47G): arm is an estimate
            match        = "cmflare";
            arm[]        = { 0.000, -3.000, 1.500};
            massPerRound = 0.25;
        };
    };

    numStores = 0;
