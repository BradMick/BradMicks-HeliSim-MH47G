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
    nrLimits[]      = {0.98, 1.02, 1.05, 1.10};

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
                        ,{40, -0.080, 1.080, 2.100, 2.950, 3.650}
                        ,{45, 0.055, 1.215, 2.235, 3.085, 3.785}
                        ,{50, 0.190, 1.350, 2.370, 3.220, 3.920}
                        ,{55, 0.325, 1.485, 2.505, 3.355, 4.000}
                        ,{60, 0.460, 1.620, 2.640, 3.490, 4.000}
                        ,{65, 0.680, 1.840, 2.860, 3.710, 4.000}
                        ,{70, 0.900, 2.060, 3.080, 3.930, 4.000}
                        ,{75, 1.170, 2.330, 3.350, 4.000, 4.000}
                        ,{80, 1.440, 2.600, 3.620, 4.000, 4.000}
                        ,{85, 1.755, 2.915, 3.935, 4.000, 4.000}
                        ,{90, 2.070, 3.230, 4.000, 4.000, 4.000}
                        ,{95, 2.440, 3.600, 4.000, 4.000, 4.000}
                        ,{100, 2.810, 3.970, 4.000, 4.000, 4.000}
                        ,{105, 2.775, 3.935, 4.000, 4.000, 4.000}
                        ,{110, 2.740, 3.900, 4.000, 4.000, 4.000}
                        ,{115, 2.775, 3.935, 4.000, 4.000, 4.000}
                        ,{120, 2.810, 3.970, 4.000, 4.000, 4.000}
                        ,{125, 2.920, 4.000, 4.000, 4.000, 4.000}
                        ,{130, 3.030, 4.000, 4.000, 4.000, 4.000}
                        ,{135, 3.225, 4.000, 4.000, 4.000, 4.000}
                        ,{140, 3.420, 4.000, 4.000, 4.000, 4.000}
                        ,{145, 3.725, 4.000, 4.000, 4.000, 4.000}
                        ,{150, 4.000, 4.000, 4.000, 4.000, 4.000}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0629, 0.0659, 0.0693, 0.0732, 0.0787, 0.0855, 0.0890, 0.0936, 0.0957, 0.0993, 0.1005, 0.1045, 0.1071, 0.1176, 0.1376, 0.2148, 0.3695}
                        ,{0.850, 0.5792, 0.5937, 0.6218, 0.6539, 0.6905, 0.7420, 0.8066, 0.8394, 0.8826, 0.9025, 0.9365, 0.9477, 0.9857, 1.0101, 1.1095, 1.2978, 2.0267, 3.4860}
                        ,{0.900, 0.5543, 0.5682, 0.5951, 0.6257, 0.6608, 0.7101, 0.7719, 0.8033, 0.8446, 0.8637, 0.8963, 0.9070, 0.9433, 0.9667, 1.0618, 1.2420, 1.9396, 3.3361}
                        ,{0.950, 0.5114, 0.5242, 0.5491, 0.5774, 0.6097, 0.6552, 0.7123, 0.7412, 0.7793, 0.7969, 0.8270, 0.8369, 0.8704, 0.8920, 0.9797, 1.1460, 1.7896, 3.0781}
                        ,{1.000, 0.4437, 0.4548, 0.4763, 0.5009, 0.5289, 0.5684, 0.6179, 0.6430, 0.6760, 0.6913, 0.7174, 0.7260, 0.7551, 0.7738, 0.8499, 0.9941, 1.5525, 2.6703}
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
                        ,{40, -2.610, -1.440, -0.400, 0.450, 1.150}
                        ,{45, -2.360, -1.190, -0.150, 0.700, 1.400}
                        ,{50, -2.110, -0.940, 0.100, 0.950, 1.650}
                        ,{55, -1.860, -0.690, 0.350, 1.200, 1.900}
                        ,{60, -1.610, -0.440, 0.600, 1.450, 2.150}
                        ,{65, -1.275, -0.105, 0.935, 1.785, 2.485}
                        ,{70, -0.940, 0.230, 1.270, 2.120, 2.820}
                        ,{75, -0.555, 0.615, 1.655, 2.505, 3.205}
                        ,{80, -0.170, 1.000, 2.040, 2.890, 3.590}
                        ,{85, 0.260, 1.430, 2.470, 3.320, 4.000}
                        ,{90, 0.690, 1.860, 2.900, 3.750, 4.000}
                        ,{95, 1.175, 2.345, 3.385, 4.000, 4.000}
                        ,{100, 1.660, 2.830, 3.870, 4.000, 4.000}
                        ,{105, 1.740, 2.910, 3.950, 4.000, 4.000}
                        ,{110, 1.820, 2.990, 4.000, 4.000, 4.000}
                        ,{115, 1.970, 3.140, 4.000, 4.000, 4.000}
                        ,{120, 2.120, 3.290, 4.000, 4.000, 4.000}
                        ,{125, 2.345, 3.515, 4.000, 4.000, 4.000}
                        ,{130, 2.570, 3.740, 4.000, 4.000, 4.000}
                        ,{135, 2.880, 4.000, 4.000, 4.000, 4.000}
                        ,{140, 3.190, 4.000, 4.000, 4.000, 4.000}
                        ,{145, 3.610, 4.000, 4.000, 4.000, 4.000}
                        ,{150, 4.000, 4.000, 4.000, 4.000, 4.000}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0629, 0.0659, 0.0693, 0.0732, 0.0787, 0.0855, 0.0890, 0.0936, 0.0957, 0.0993, 0.1005, 0.1045, 0.1071, 0.1176, 0.1376, 0.2148, 0.3695}
                        ,{0.850, 0.5792, 0.5937, 0.6218, 0.6539, 0.6905, 0.7420, 0.8066, 0.8394, 0.8826, 0.9025, 0.9365, 0.9477, 0.9857, 1.0101, 1.1095, 1.2978, 2.0267, 3.4860}
                        ,{0.900, 0.5543, 0.5682, 0.5951, 0.6257, 0.6608, 0.7101, 0.7719, 0.8033, 0.8446, 0.8637, 0.8963, 0.9070, 0.9433, 0.9667, 1.0618, 1.2420, 1.9396, 3.3361}
                        ,{0.950, 0.5114, 0.5242, 0.5491, 0.5774, 0.6097, 0.6552, 0.7123, 0.7412, 0.7793, 0.7969, 0.8270, 0.8369, 0.8704, 0.8920, 0.9797, 1.1460, 1.7896, 3.0781}
                        ,{1.000, 0.4437, 0.4548, 0.4763, 0.5009, 0.5289, 0.5684, 0.6179, 0.6430, 0.6760, 0.6913, 0.7174, 0.7260, 0.7551, 0.7738, 0.8499, 0.9941, 1.5525, 2.6703}
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
