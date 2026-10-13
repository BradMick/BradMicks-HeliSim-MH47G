/////////////////////////////////////////////////////////////////////////////////////////////
// Rotors - Simple //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//AIRCRAFT
//  controlScheme       - "conventional" (default), "tandem", "coaxial", "tiltrotor" or "compound".
//  numSimpleRotors     - number of SimpleRotorNN classes.
//  nrLimits[]          - Nr {normal low, normal high, high rotor, maximum}.
//  drivetrainDrag      - drivetrain drag torque, fraction of one engine's 100% torque.
//
//EVERY ROTOR
//  type                - "main", "tail", "propeller" or "proprotor".
//  position            - "front", "rear", "left", "right", "top" or "bottom"; multi-rotor schemes.
//  direction           - "ccw" or "cw", from above.
//  damageRole          - hitpoint role that destroys it.
//  pivot[]             - hub {right, forward, up} m, Arma model frame.
//  rotation[]          - disc {pitch, roll, yaw} deg.
//  mastLength          - m, pivot to hub.
//  gearRatio           - rotor to engine shaft.
//  torqueTau           - s, torque filter.
//  numBlades, bladeRadius m, bladeChord m, bladeMass kg per blade.
//  coneAngle           - deg at full collective.
//  flapBackRollMax / flapBackPitchMax - deg of flap-back at advance ratio 1.0.
//  gndEffValue         - thrust multiplier on the ground.
//  reacTqScalar        - share of rotor torque that yaws the airframe.
//  liftCoefTable[] / dragCoefTable[] - rows collective (main) or pedal (tail), columns m/s.
//  controlMap[]        - optional, shapes the control between table rows.
//
//MAIN ONLY
//  autoTorque          - autorotation driving torque per m/s of descent.
//  rollFlapMin/Mid/Max - deg, lateral disc tilt.
//  rollLiftCoef        - lateral cyclic blade lift change.
//
//CONVENTIONAL ONLY
//  pitchFlapMin/Mid/Max, pitchLiftCoef - as roll, fore/aft.
//
//TANDEM ONLY
//  tandemPitchLiftCoef - blade lift change at full fore/aft stick.
//  tandemYawLiftCoef   - pedal blade lift change; the discs tilt through rollFlap.
//  lctSchedule[]       - mast tilt deg, + forward; rows kt, columns pressure altitude ft.
//  lctTime             - s, LCT full stroke.
//
//TAIL ONLY - pedal is the table key; cyclic fields 0.

    controlScheme   = "tandem";
    numSimpleRotors = 2;
    nrLimits[]      = {0.97, 1.01, 1.06, 1.11};
    drivetrainDrag  = 0.144;

    class SimpleRotors {
        class SimpleRotor01 {
            //IDENTITY
            type             = "main";
            position         = "front";
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
                        ,{0,  -1.200, -1.200, -0.200,  0.650,  1.350}
                        ,{40, -0.410, -0.540, -0.650, -0.760, -0.940}
                        ,{60,  0.190, -0.080, -0.330, -0.550, -0.760}
                        ,{80,  1.210,  0.740,  0.300, -0.100, -0.460}
                        ,{100, 2.640,  1.910,  1.230,  0.610,  0.050}
                        ,{120, 2.690,  1.620,  0.610, -0.300, -1.120}
                        ,{140, 3.370,  1.830,  0.400, -0.890, -1.200}
                        ,{150, 3.990,  2.170,  0.480, -1.040, -1.200}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0632, 0.0672, 0.0720, 0.0778, 0.0858, 0.0963, 0.1011, 0.1072, 0.1086, 0.1118, 0.1103, 0.1123, 0.1109, 0.1185, 0.1382, 0.2167, 0.3739}
                        ,{0.850, 0.5792, 0.5963, 0.6342, 0.6793, 0.7341, 0.8098, 0.9088, 0.9533, 1.0113, 1.0245, 1.0544, 1.0410, 1.0596, 1.0463, 1.1180, 1.3041, 2.0447, 3.5274}
                        ,{0.900, 0.5543, 0.5706, 0.6069, 0.6501, 0.7025, 0.7750, 0.8698, 0.9123, 0.9678, 0.9805, 1.0091, 0.9962, 1.0141, 1.0013, 1.0699, 1.2480, 1.9568, 3.3758}
                        ,{0.950, 0.5114, 0.5265, 0.5600, 0.5998, 0.6482, 0.7151, 0.8025, 0.8418, 0.8930, 0.9047, 0.9311, 0.9192, 0.9357, 0.9239, 0.9872, 1.1515, 1.8055, 3.1147}
                        ,{1.000, 0.4437, 0.4568, 0.4858, 0.5203, 0.5623, 0.6203, 0.6962, 0.7302, 0.7746, 0.7848, 0.8077, 0.7974, 0.8117, 0.8015, 0.8564, 0.9989, 1.5663, 2.7020}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0031, 0.0016, 0.0008, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001}
                        ,{0.389, 0.0325, 0.0323, 0.0319, 0.0315, 0.0310, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0312, 0.0325, 0.0325}
                        ,{0.555, 0.0517, 0.0514, 0.0507, 0.0500, 0.0493, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0496, 0.0517, 0.0517}
                        ,{0.850, 0.0934, 0.0928, 0.0916, 0.0903, 0.0891, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0895, 0.0934, 0.0934}
                        ,{0.900, 0.1215, 0.1207, 0.1190, 0.1174, 0.1158, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1164, 0.1215, 0.1215}
                        ,{0.950, 0.1682, 0.1671, 0.1648, 0.1625, 0.1603, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1612, 0.1682, 0.1682}
                        ,{1.000, 0.2429, 0.2413, 0.2380, 0.2348, 0.2315, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2328, 0.2429, 0.2429}
                        };
        };

        class SimpleRotor02 {
            //IDENTITY
            type             = "main";
            position         = "rear";
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
                        ,{60, -1.880, -2.140, -2.370, -2.590, -2.800}
                        ,{80, -0.400, -0.860, -1.280, -1.680, -2.040}
                        ,{100, 1.490, 0.770, 0.110, -0.510, -1.070}
                        ,{120, 2.000, 0.940, -0.050, -0.960, -1.780}
                        ,{140, 3.140, 1.610, 0.200, -1.090, -3.070}
                        ,{150, 3.990, 2.180, 0.510, -1.010, -3.250}
                        };
            //TABLES
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0614, 0.0632, 0.0672, 0.0720, 0.0778, 0.0858, 0.0963, 0.1011, 0.1072, 0.1086, 0.1118, 0.1103, 0.1123, 0.1109, 0.1185, 0.1382, 0.2167, 0.3739}
                        ,{0.850, 0.5792, 0.5963, 0.6342, 0.6793, 0.7341, 0.8098, 0.9088, 0.9533, 1.0113, 1.0245, 1.0544, 1.0410, 1.0596, 1.0463, 1.1180, 1.3041, 2.0447, 3.5274}
                        ,{0.900, 0.5543, 0.5706, 0.6069, 0.6501, 0.7025, 0.7750, 0.8698, 0.9123, 0.9678, 0.9805, 1.0091, 0.9962, 1.0141, 1.0013, 1.0699, 1.2480, 1.9568, 3.3758}
                        ,{0.950, 0.5114, 0.5265, 0.5600, 0.5998, 0.6482, 0.7151, 0.8025, 0.8418, 0.8930, 0.9047, 0.9311, 0.9192, 0.9357, 0.9239, 0.9872, 1.1515, 1.8055, 3.1147}
                        ,{1.000, 0.4437, 0.4568, 0.4858, 0.5203, 0.5623, 0.6203, 0.6962, 0.7302, 0.7746, 0.7848, 0.8077, 0.7974, 0.8117, 0.8015, 0.8564, 0.9989, 1.5663, 2.7020}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0031, 0.0016, 0.0008, 0.0005, 0.0003, 0.0002, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001}
                        ,{0.389, 0.0325, 0.0323, 0.0319, 0.0315, 0.0310, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0309, 0.0312, 0.0325, 0.0325}
                        ,{0.555, 0.0517, 0.0514, 0.0507, 0.0500, 0.0493, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0492, 0.0496, 0.0517, 0.0517}
                        ,{0.850, 0.0934, 0.0928, 0.0916, 0.0903, 0.0891, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0888, 0.0895, 0.0934, 0.0934}
                        ,{0.900, 0.1215, 0.1207, 0.1190, 0.1174, 0.1158, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1154, 0.1164, 0.1215, 0.1215}
                        ,{0.950, 0.1682, 0.1671, 0.1648, 0.1625, 0.1603, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1598, 0.1612, 0.1682, 0.1682}
                        ,{1.000, 0.2429, 0.2413, 0.2380, 0.2348, 0.2315, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2308, 0.2328, 0.2429, 0.2429}
                        };
        };
    };
