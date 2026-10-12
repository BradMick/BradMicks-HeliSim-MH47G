/////////////////////////////////////////////////////////////////////////////////////////////
// Engine ////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    // Engines - T55-GA-714A  ///////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    class Engines {
        class Engine01 {
            name            = "eng01";
            damageRole      = "engines";
            damageRoleIndex = 0;

            //Whole assembly
            engineType  = "turboShaftEngine";   //engine model
            designRpm   = 15066;                //100% Np
            npFly       = 1.00;                 //governed Np in FLY
            maxFuelFlow = 0.1599;               //kg/s per unit of fuel
            powerKw     = 3108;                 //100% torque

            //Overspeed
            maxNg        = 1.12;                //spool ceiling
            ngOvrspdProt = 0;                   //Ng overspeed trip, 0 = none
            npOvrspdProt = 1.148;               //Np overspeed trip

            //Limits - {limit, seconds above it, damage divisor}
            oilPsiLimits[] = {0.389, 1.000};    //normal range, fraction of full scale
            ngMin          = 0.50;              //ground idle minimum
            ngLimits[]     = {{1.11, 0, 20}};
            npLimits[]     = {{1.115, 0, 20}};
            tqLimits[]     = {{1.00, 0, 5}};
            tgtLimits[]    = {{816, 1800, 1000}, {854, 600, 2000}, {899, 150, 2000}, {932, 12, 2000}, {943, 0, 2000}};
            tqLimitsSe[]   = {{1.23, 0, 5}};
            tgtLimitsSe[]  = {{816, 1800, 1000}, {854, 600, 2000}, {899, 150, 2000}, {932, 12, 2000}, {943, 0, 2000}};

            //Compressor
            class Compressor {
                pressureRatio = 9.32;    //at Ng 1.0
                massFlow      = 13.199;  //kg/s at Ng 1.0, standard day
                inletDiameter = 1.248;   //m
                ramRecovery   = 1.0;     //share of ram pressure rise kept

                compDrag      = 3.4;     //spool-down drag, compDrag * ng^2
                compDragFloor = 0.10;    //minimum spool-down drag

                //Airflow multiplier by FAT, {FAT, multiplier}
                airflowTable[] = {
                     {-40, 1.1210}
                    ,{-30, 1.1229}
                    ,{-20, 1.1169}
                    ,{-10, 1.1116}
                    ,{  0, 1.0989}
                    ,{ 10, 1.0025}
                    ,{ 15, 1.0072}
                    ,{ 20, 1.0098}
                    ,{ 30, 1.0063}
                    ,{ 40, 0.9928}
                };

                //{Ng / maxNg, pressure ratio, airflow, efficiency, compressor turbine expansion}
                compressorMap[] = {
                    {0.0000, 0.1073, 0.0000, 0.544, 0.4781}
                    ,{0.0500, 0.1083, 0.0116, 0.544, 0.4781}
                    ,{0.1000, 0.1116, 0.0329, 0.544, 0.4781}
                    ,{0.1500, 0.1169, 0.0604, 0.544, 0.4781}
                    ,{0.2000, 0.1247, 0.0930, 0.544, 0.4781}
                    ,{0.2500, 0.1352, 0.1300, 0.544, 0.4781}
                    ,{0.3000, 0.1488, 0.1709, 0.544, 0.4781}
                    ,{0.3500, 0.1661, 0.2153, 0.544, 0.4781}
                    ,{0.4000, 0.1874, 0.2631, 0.544, 0.4781}
                    ,{0.4938, 0.2416, 0.4314, 0.700, 0.2548}
                    ,{0.7411, 0.5180, 0.5133, 0.634, 0.5071}
                    ,{0.9911, 1.2713, 1.0307, 0.658, 0.6069}
                    ,{1.0000, 1.3005, 1.0492, 0.659, 0.6105}
                };

                //Start
                lightOffNg = 0.15;       //fuel introduced
                selfSustNg = 0.52;       //starter cuts out
                idleNg     = 0.553;      //ground idle

                //Ng limiter - ngLimitMax min (ngLimitBase + ngLimitSlope * FAT)
                ngLimitMax   = 1.11;
                ngLimitBase  = 1.11;
                ngLimitSlope = 0.0;
            };

            //Combustor
            class Combustor {
                fuelLhv             = 43000;    //kJ/kg
                combustorEfficiency = 0.99;

                maxTgt      = 9999;      //TGT limiter, twin engine
                maxTgtSe    = 9999;      //TGT limiter, single engine
                startTgt    = 927;       //start limit
                startMinTgt = 80;        //TGT required before the power lever is moved

                residualHeatGain = 0.003;   //un-purged start runaway
            };

            //Compressor turbine
            class CompressorTurbine {
                turbineEfficiency = 0.88;
                spoolInertia      = 5.0;
            };

            //Power turbine
            class PowerTurbine {
                ptEfficiency  = 0.88;
                ptInertia     = 0.60;
                ptDrag        = 0.06;    //released turbine drag, ptDrag * np^2
                ptDragFloor   = 0.05;    //minimum released turbine drag
            };

            //Governor
            class Governor {
                fuelIdle = 0.403;        //fuel at IDLE
                fuelFly  = 3.136;        //fuel at FLY

                startFuelBase = 0.50;    //light-off fuel, fraction of idle fuel

                ffwdGain = 1.00;         //collective anticipation

                leverTravelTime = 15.0;  //seconds, idle to fly
                loadShareGain   = 8.0;   //load sharing trim rate

                pid[] = {80.0000, 40.0000, 0.0000, 0.0750};   //Np governor {kp, ki, kd, ki_clamp}

                gate[] = {};
            };

            //Starter
            class Starter {
                type      = "pneumatic";
                torque    = 0.45;        //stalled torque
                runawayNg = 0.25;        //where motoring settles
                gate[]    = {};
            };
        };
        class Engine02 : Engine01 {
            name            = "eng02";
            damageRoleIndex = 1;
        };
    };
