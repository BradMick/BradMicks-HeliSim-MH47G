/////////////////////////////////////////////////////////////////////////////////////////////
// Rotors - Simple //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//AIRCRAFT
//  controlScheme   - how the controls reach the rotors: "conventional" (the default) or "tandem".
//                    TANDEM: lateral cyclic and collective as conventional; fore/aft cyclic moves
//                    lift from one rotor to the other (tandemPitchLiftCoef); pedal is lateral
//                    cyclic on each rotor, opposite ways (tandemYawLiftCoef).
//                    Neither moves collective, so neither moves torque.
//  numSimpleRotors - how many SimpleRotorNN classes follow.
//  nrLimits[]      - Nr {normal low, normal high, high rotor, maximum}.
//
//EVERY ROTOR
//  IDENTITY   type         "main" or "tail" - what the rotor IS.
//             direction    "ccw" or "cw", seen from above.
//             damageRole   the hitpoint role that destroys it; none - it cannot be destroyed.
//  PLACEMENT  pivot[]      {right, forward, up} m in Arma's model frame - Object Builder less
//                          boundingCenter: a point from fm.p3d, placed, less boundingCenter.
//             rotation[]   disc {pitch, roll, yaw} deg - the mast's lean.
//             mastLength   m along the disc's up axis, pivot to hub.
//  DRIVE      gearRatio    rotor to engine shaft - the transmission model shares it.
//             torqueTau    s, the torque filter.
//  BLADE      numBlades, bladeRadius (m), bladeChord (m), bladeMass (kg, one blade).
//  AERO       coneAngle    deg at full collective - the tips lift, the thrust moves inboard.
//             flapBackRollMax / flapBackPitchMax - deg at an advance ratio of 1.0, applied as
//                          blade flap: the disc tilts back as speed builds.
//             gndEffValue  thrust multiplier on the deck, back to 1.0 by one diameter up.
//             reacTqScalar the tangential drag that yaws the airframe; the transmission still
//                          feels all of it.
//  TABLES     liftCoefTable / dragCoefTable - rows are the control that loads the rotor
//                          (collective for a main, pedal for a tail), columns airspeed in m/s.
//                          The drag table is what the transmission feels.
//             controlMap[] optional - shapes the control between the table's rows.
//
//MAIN ONLY
//  autoTorque              driving torque per m/s of descent in autorotation.
//  LATERAL CYCLIC (roll)   rollFlapMin/Mid/Max - disc tilt, deg, from the centred stick;
//                          rollLiftCoef - the blades' lift change around the disc. Blade pitch
//                          and disc tilt together, as a rotor does.
//
//CONVENTIONAL ONLY
//  FORE/AFT CYCLIC (pitch) pitchFlapMin/Mid/Max, pitchLiftCoef - as lateral. A tandem does not
//                          tilt its discs fore and aft; it pitches with tandemPitchLiftCoef.
//
//TANDEM ONLY
//  position                "front" or "rear" - declared, not inferred. It sets which way the
//                          two tandem terms act on this rotor.
//  tandemPitchLiftCoef     lift coefficient added to every blade at full fore/aft stick: forward
//                          stick takes it off the front rotor and puts it on the rear.
//  tandemYawLiftCoef       pedal's blade lift change around the disc, as rollLiftCoef is lateral
//                          cyclic's - pedal is lateral cyclic on each rotor, opposite ways, and
//                          tilts the discs through rollFlap.
//
//  lctSchedule[]           LCT - the mast's tilt, deg, + forward (extend): rows airspeed kt, columns
//                          pressure altitude ft, header {"PA", ...}. Casual and realistic alike.
//  lctTime                 s for the LCT actuator's full stroke - it moves to the schedule at that rate.
//
//TAIL ONLY (a conventional tail rotor) - pedal is its table key; its disc does not tilt, so its
//cyclic fields are 0, and it usually declares a controlMap for the pedal's asymmetry.

    controlScheme   = "tandem";
    numSimpleRotors = 2;
    nrLimits[]      = {0.97, 1.01, 1.06, 1.11};

    class SimpleRotors {
        class SimpleRotor01 {
            //IDENTITY
            type             = "main";
            position         = "front";   //TANDEM ONLY
            direction        = "ccw";
            damageRole       = "mainRotor";
            //PLACEMENT
            pivot[]          = {-0.003, 4.213, 1.191};
            rotation[]       = {-5.43, 0.00, 0.00};
            mastLength       = 0.290;     //m
            //DRIVE
            gearRatio        = 66.960;
            torqueTau        = 0.10;      //s
            //BLADE
            numBlades        = 3;
            bladeRadius      = 9.145;     //m
            bladeChord       = 0.641;     //m
            bladeMass        = 159.000;   //kg
            //AERO
            coneAngle        = 12.0;      //deg at full collective
            flapBackRollMax  = 15.0;      //deg per unit advance ratio
            flapBackPitchMax = 9.0;
            gndEffValue      = 1.225;
            reacTqScalar     = 0.50;
            //MAIN ONLY
            autoTorque       = 80.0;
            rollFlapMin      = -12.0;     //deg
            rollFlapMid      =   0.0;
            rollFlapMax      =  12.0;
            rollLiftCoef     = 0.102;
            //CONVENTIONAL ONLY
            pitchFlapMin     = 0.0;
            pitchFlapMid     = 0.0;
            pitchFlapMax     = 0.0;
            pitchLiftCoef    = 0.0;
            //TANDEM ONLY
            tandemPitchLiftCoef = 0.686;
            tandemYawLiftCoef   = 1.8;
            lctTime             = 12.0;    //s
            lctSchedule[] = {
                        {"PA", 0, 5000, 10000, 15000, 20000}
                        ,{0, -1.200, -1.200, -0.200, 0.650, 1.350}
                        ,{40, -0.410, -0.540, -0.650, -0.760, -0.940}
                        ,{45, -0.260, -0.425, -0.570, -0.707, -0.895}
                        ,{50, -0.110, -0.310, -0.490, -0.655, -0.850}
                        ,{55, 0.040, -0.195, -0.410, -0.603, -0.805}
                        ,{60, 0.190, -0.080, -0.330, -0.550, -0.760}
                        ,{65, 0.420, 0.105, -0.190, -0.455, -0.695}
                        ,{70, 0.650, 0.290, -0.050, -0.360, -0.630}
                        ,{75, 0.930, 0.515, 0.125, -0.230, -0.545}
                        ,{80, 1.210, 0.740, 0.300, -0.100, -0.460}
                        ,{85, 1.545, 1.010, 0.515, 0.060, -0.345}
                        ,{90, 1.880, 1.280, 0.730, 0.220, -0.230}
                        ,{95, 2.260, 1.595, 0.980, 0.415, -0.090}
                        ,{100, 2.640, 1.910, 1.230, 0.610, 0.050}
                        ,{105, 2.620, 1.810, 1.055, 0.365, -0.255}
                        ,{110, 2.600, 1.710, 0.880, 0.120, -0.560}
                        ,{115, 2.645, 1.665, 0.745, -0.090, -0.840}
                        ,{120, 2.690, 1.620, 0.610, -0.300, -1.120}
                        ,{125, 2.815, 1.635, 0.530, -0.465, -1.200}
                        ,{130, 2.940, 1.650, 0.450, -0.630, -1.200}
                        ,{135, 3.155, 1.740, 0.425, -0.760, -1.200}
                        ,{140, 3.370, 1.830, 0.400, -0.890, -1.200}
                        ,{145, 3.680, 2.000, 0.440, -0.965, -1.200}
                        ,{150, 3.990, 2.170, 0.480, -1.040, -1.200}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0629, 0.0658, 0.0691, 0.0729, 0.0782, 0.0850, 0.0884, 0.0929, 0.0950, 0.0986, 0.0998, 0.1038, 0.1065, 0.1171, 0.1375, 0.2166, 0.3749}
                        ,{0.850, 0.5792, 0.5930, 0.6204, 0.6516, 0.6873, 0.7380, 0.8016, 0.8337, 0.8762, 0.8958, 0.9298, 0.9411, 0.9791, 1.0043, 1.1048, 1.2970, 2.0432, 3.5370}
                        ,{0.900, 0.5543, 0.5675, 0.5937, 0.6236, 0.6577, 0.7063, 0.7672, 0.7979, 0.8385, 0.8573, 0.8898, 0.9006, 0.9370, 0.9611, 1.0573, 1.2412, 1.9553, 3.3849}
                        ,{0.950, 0.5114, 0.5236, 0.5478, 0.5754, 0.6069, 0.6517, 0.7078, 0.7362, 0.7737, 0.7910, 0.8210, 0.8310, 0.8645, 0.8868, 0.9756, 1.1452, 1.8041, 3.1231}
                        ,{1.000, 0.4437, 0.4542, 0.4752, 0.4991, 0.5265, 0.5653, 0.6141, 0.6386, 0.6712, 0.6862, 0.7122, 0.7209, 0.7500, 0.7693, 0.8463, 0.9935, 1.5651, 2.7093}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0130, 0.0065, 0.0032, 0.0022, 0.0011, 0.0007, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004}
                        ,{0.389, 0.0424, 0.0421, 0.0415, 0.0410, 0.0404, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0406, 0.0424, 0.0424}
                        ,{0.555, 0.0616, 0.0612, 0.0603, 0.0595, 0.0587, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0590, 0.0616, 0.0616}
                        ,{0.850, 0.1033, 0.1026, 0.1012, 0.0998, 0.0984, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0990, 0.1033, 0.1033}
                        ,{0.900, 0.1343, 0.1334, 0.1316, 0.1298, 0.1280, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1287, 0.1343, 0.1343}
                        ,{0.950, 0.1859, 0.1847, 0.1822, 0.1797, 0.1772, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1782, 0.1859, 0.1859}
                        ,{1.000, 0.2685, 0.2667, 0.2631, 0.2595, 0.2559, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2573, 0.2685, 0.2685}
                        };
        };

        class SimpleRotor02 {
            //IDENTITY
            type             = "main";
            position         = "rear";   //TANDEM ONLY
            direction        = "cw";
            damageRole       = "tailRotor";
            //PLACEMENT
            pivot[]          = {-0.003, -7.769, 2.237};
            rotation[]       = {1.50, 0.00, 0.00};
            mastLength       = 0.290;     //m
            //DRIVE
            gearRatio        = 66.960;
            torqueTau        = 0.10;      //s
            //BLADE
            numBlades        = 3;
            bladeRadius      = 9.145;     //m
            bladeChord       = 0.641;     //m
            bladeMass        = 159.000;   //kg
            //AERO
            coneAngle        = 12.0;      //deg at full collective
            flapBackRollMax  = 15.0;      //deg per unit advance ratio
            flapBackPitchMax = 9.0;
            gndEffValue      = 1.225;
            reacTqScalar     = 0.50;
            //MAIN ONLY
            autoTorque       = 80.0;
            rollFlapMin      = -12.0;     //deg
            rollFlapMid      =   0.0;
            rollFlapMax      =  12.0;
            rollLiftCoef     = 0.102;
            //CONVENTIONAL ONLY
            pitchFlapMin     = 0.0;
            pitchFlapMid     = 0.0;
            pitchFlapMax     = 0.0;
            pitchLiftCoef    = 0.0;
            //TANDEM ONLY
            tandemPitchLiftCoef = 0.686;
            tandemYawLiftCoef   = 1.8;
            lctTime             = 12.0;    //s
            lctSchedule[] = {
                        {"PA", 0, 5000, 10000, 15000, 20000}
                        ,{0, -3.250, -3.250, -2.700, -1.850, -1.150}
                        ,{40, -2.940, -3.060, -3.150, -3.250, -3.250}
                        ,{45, -2.675, -2.830, -2.955, -3.093, -3.250}
                        ,{50, -2.410, -2.600, -2.760, -2.925, -3.120}
                        ,{55, -2.145, -2.370, -2.565, -2.758, -2.960}
                        ,{60, -1.880, -2.140, -2.370, -2.590, -2.800}
                        ,{65, -1.535, -1.840, -2.115, -2.380, -2.620}
                        ,{70, -1.190, -1.540, -1.860, -2.170, -2.440}
                        ,{75, -0.795, -1.200, -1.570, -1.925, -2.240}
                        ,{80, -0.400, -0.860, -1.280, -1.680, -2.040}
                        ,{85, 0.050, -0.475, -0.950, -1.405, -1.810}
                        ,{90, 0.500, -0.090, -0.620, -1.130, -1.580}
                        ,{95, 0.995, 0.340, -0.255, -0.820, -1.325}
                        ,{100, 1.490, 0.770, 0.110, -0.510, -1.070}
                        ,{105, 1.585, 0.785, 0.050, -0.640, -1.260}
                        ,{110, 1.680, 0.800, -0.010, -0.770, -1.450}
                        ,{115, 1.840, 0.870, -0.030, -0.865, -1.615}
                        ,{120, 2.000, 0.940, -0.050, -0.960, -1.780}
                        ,{125, 2.240, 1.070, -0.015, -1.010, -2.120}
                        ,{130, 2.480, 1.200, 0.020, -1.060, -2.460}
                        ,{135, 2.810, 1.405, 0.110, -1.075, -2.765}
                        ,{140, 3.140, 1.610, 0.200, -1.090, -3.070}
                        ,{145, 3.565, 1.895, 0.355, -1.050, -3.250}
                        ,{150, 3.990, 2.180, 0.510, -1.010, -3.250}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0629, 0.0658, 0.0691, 0.0729, 0.0782, 0.0850, 0.0884, 0.0929, 0.0950, 0.0986, 0.0998, 0.1038, 0.1065, 0.1171, 0.1375, 0.2166, 0.3749}
                        ,{0.850, 0.5792, 0.5930, 0.6204, 0.6516, 0.6873, 0.7380, 0.8016, 0.8337, 0.8762, 0.8958, 0.9298, 0.9411, 0.9791, 1.0043, 1.1048, 1.2970, 2.0432, 3.5370}
                        ,{0.900, 0.5543, 0.5675, 0.5937, 0.6236, 0.6577, 0.7063, 0.7672, 0.7979, 0.8385, 0.8573, 0.8898, 0.9006, 0.9370, 0.9611, 1.0573, 1.2412, 1.9553, 3.3849}
                        ,{0.950, 0.5114, 0.5236, 0.5478, 0.5754, 0.6069, 0.6517, 0.7078, 0.7362, 0.7737, 0.7910, 0.8210, 0.8310, 0.8645, 0.8868, 0.9756, 1.1452, 1.8041, 3.1231}
                        ,{1.000, 0.4437, 0.4542, 0.4752, 0.4991, 0.5265, 0.5653, 0.6141, 0.6386, 0.6712, 0.6862, 0.7122, 0.7209, 0.7500, 0.7693, 0.8463, 0.9935, 1.5651, 2.7093}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0130, 0.0065, 0.0032, 0.0022, 0.0011, 0.0007, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004, 0.0004}
                        ,{0.389, 0.0424, 0.0421, 0.0415, 0.0410, 0.0404, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0403, 0.0406, 0.0424, 0.0424}
                        ,{0.555, 0.0616, 0.0612, 0.0603, 0.0595, 0.0587, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0590, 0.0616, 0.0616}
                        ,{0.850, 0.1033, 0.1026, 0.1012, 0.0998, 0.0984, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0981, 0.0990, 0.1033, 0.1033}
                        ,{0.900, 0.1343, 0.1334, 0.1316, 0.1298, 0.1280, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1276, 0.1287, 0.1343, 0.1343}
                        ,{0.950, 0.1859, 0.1847, 0.1822, 0.1797, 0.1772, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1766, 0.1782, 0.1859, 0.1859}
                        ,{1.000, 0.2685, 0.2667, 0.2631, 0.2595, 0.2559, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2551, 0.2573, 0.2685, 0.2685}
                        };
        };
    };
