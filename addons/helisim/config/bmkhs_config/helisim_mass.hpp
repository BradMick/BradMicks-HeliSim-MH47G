/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//AIRFRAME
//  emptyMass       - kg, empty airframe.
//  emptyMom        - empty moment; the empty CG is fsDatum - emptyMom / emptyMass.
//  maxGrossMass    - kg.
//  fsDatum         - m, fuselage station 0.
//  fwdCgLimit      - m from fsDatum, + forward.
//  aftCgLimit      - m from fsDatum, + forward.
//  comCorrection[] - m, centre of mass offset, realistic mode.
//  casualModeCom[] - m, centre of mass, casual mode.
//
//MASS ITEMS - arm[] is {lateral, longitudinal, vertical} m, right / nose / up positive.
//  Seats       - role "driver", "gunner", "commander", "turret" or "cargo"; turret[] path, {} for
//                the driver; cargoIndex for cargo, -1 otherwise. Counted when occupied.
//  Equipment   - counted while animation is on the installedPhase side of 0.5.
//  Magazines   - every magazine matching match; massPerRound kg, per round left.
//  Stations / Stores - pylons and what hangs on them.

    //Airframe
    emptyMass       = 11150;       //kg
    emptyMom        = 93237.79;
    maxGrossMass    = 24494;       //kg
    fsDatum         = 8.012;       //m
    fwdCgLimit      = 0.145;       //m
    aftCgLimit      = -0.845;      //m
    comCorrection[] = {0.000, 0.000, 1.724};
    casualModeCom[] = {-0.003, -1.721, -1.279};

    //Seats
    #define SEAT_MASS_CREW  100.0   //kg, crew
    #define SEAT_MASS_TROOP 149.7   //kg, troop with combat load
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
        //Turrets 7, 10 and 11 - arms to be measured in game
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

    //Equipment
    numEquipment = 14;
    class Equipment {
        class Equipment01 {  //M134D, left
            animation      = "Hide_M134_1";
            installedPhase = 0;
            mass           = 42.4;
            arm[]          = {-0.795, 4.123, 2.055};
        };
        class Equipment02 {  //M134D, right
            animation      = "Hide_M134_2";
            installedPhase = 0;
            mass           = 42.4;
            arm[]          = { 0.886, 4.055, 2.055};
        };
        class Equipment03 {  //M240, left
            animation      = "Hide_M240_1";
            installedPhase = 0;
            mass           = 15.9;
            arm[]          = {-0.894, -4.461, 1.783};
        };
        class Equipment04 {  //M240, right
            animation      = "Hide_M240_2";
            installedPhase = 0;
            mass           = 15.9;
            arm[]          = { 0.575, -4.211, 1.783};
        };
        class Equipment05 {  //Refuelling probe
            animation      = "Hide_Probe";
            installedPhase = 0;
            mass           = 228;
            arm[]          = { 1.000, 7.000, 1.200};
        };
        class Equipment06 {  //Armour plating
            animation      = "Hide_Armor_Plating";
            installedPhase = 0;
            mass           = 1588;
            arm[]          = { 0.000, 0.000, 1.300};
        };
        class Equipment07 {  //Cargo door armour
            animation      = "Hide_Armor_Hoist";
            installedPhase = 0;
            mass           = 35;
            arm[]          = { 1.100, 4.300, 1.900};
        };
        class Equipment08 {  //Fuel dump pipe
            animation      = "Hide_Fuel_Dump_Pipe";
            installedPhase = 0;
            mass           = 4;
            arm[]          = { 0.000, -6.500, 1.000};
        };
        class Equipment09 {  //Door plug
            animation      = "HideCrewDoor";
            installedPhase = 0;
            mass           = 20;
            arm[]          = { 1.100, 4.300, 1.900};
        };
        class Equipment10 {  //Window plug, forward left
            animation      = "Hide_Fwd_L_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = {-1.200, 4.120, 2.050};
        };
        class Equipment11 {  //Window plug, forward right
            animation      = "Hide_Fwd_R_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = { 1.200, 4.060, 2.050};
        };
        class Equipment12 {  //Window plug, aft left
            animation      = "Hide_Aft_L_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = {-1.200, -4.460, 1.780};
        };
        class Equipment13 {  //Window plug, aft right
            animation      = "Hide_Aft_R_Plug";
            installedPhase = 0;
            mass           = 6;
            arm[]          = { 1.200, -4.210, 1.780};
        };
        class Equipment14 {  //Skis
            animation      = "Hide_Skis";
            installedPhase = 0;
            mass           = 110;
            arm[]          = { 0.000, 0.000, 0.300};
        };
    };

    //Magazines
    numMagazines = 3;
    class Magazines {
        class Mag01 {  //M134D belts
            match        = "4000rnd_65x39";
            arm[]        = { 0.046, 4.089, 2.055};
            massPerRound = 0.0254;
        };
        class Mag02 {  //M240 belts
            match        = "250rnd_762x51";
            arm[]        = {-0.160, -4.336, 1.783};
            massPerRound = 0.0254;
        };
        class Mag03 {  //Flares
            match        = "cmflare";
            arm[]        = { 0.000, -3.000, 1.500};
            massPerRound = 0.25;
        };
    };

    //Stations and stores
    numStations = 0;
    numStores   = 0;
