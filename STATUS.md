# MH-47G - status

Where the pack is, what is settled, and what is next. Updated after every task.

Started 2026-10-11 on HeliSim Core `d7ed678` (1.3.0.0). Built from the Bo 105 pack
(`E:\bmkhs_bo105`, `94a97c2`), following Core's `docs/AIRCRAFT_GUIDE.md`.

This update builds the pack AND tandem rotor control in Core. Every Core change goes on Core's
`release/1.4.0` branch (HeliSim 1.4.0.0), published.

Repo: https://github.com/BradMick/BradMicks-HeliSim-MH47G (public, `master`). First commit
`8b4cd95` - tasks 1 and 3.

**Nothing since `7bbf9ff` (pack) / `65a28df` (Core) is committed.** The user commits when they
decide to, usually after flying it - do not prompt for it.

## Where it is

| # | Work | State |
|---|---|---|
| 1 | Pack scaffold from the Bo 105, renamed, Bo 105 values as `TODO(MH47G)` placeholders | **Done** - `8b4cd95` |
| 2 | Tandem rotor control in Core, MH-47G declared a tandem | **Done**, flying - uncommitted |
| 3 | Fuselage and wings from the MH-47G's `fm.p3d` | **Done** - `8b4cd95` |
| 4 | The Bo 105's dev tools made Core's | **Done** - Core `57b888d` |
| 5 | Place fuselage, rotor hubs, CoM on the model (nudge) | **Done** - uncommitted |
| 6 | Rotor tables fitted from the user's performance data | **Done** - uncommitted; 160 kt open |
| 7 | Control authority: pitch and yaw to match roll | **Built** 2026-10-12 - tandem lift terms; to fly |

## Task 7 - tandem pitch and yaw as their own lift terms (2026-10-12, Core uncommitted)

User agreed (names theirs): pitch and yaw stop going through collective and roll.

- `fn_simpleRotorControl.sqf` `TANDEM`: roll and collective conventional; returns two more outputs
  - `tandemPitch` = sign x stick, `tandemYaw` = -sign x pedal (front -1, rear +1).
- `fn_simpleRotor.sqf`: `tandemPitch x tandemPitchLiftCoef` joins the cyclic lift-coefficient
  terms (every blade). Pedal is lateral cyclic on each rotor, opposite ways (user's model):
  `tandemYaw` tilts the disc through the `rollFlap*` range, on top of roll's tilt, and
  `tandemYaw x cos psi x tandemYawLiftCoef` is its blade-pitch lift change, as `rollLiftCoef` is
  roll's. Lift lines stay perpendicular to the flapped blade. (A first version made yaw a
  sideways lift component with no disc tilt - NOT the user's model, removed; the user had not
  approved that mechanism - see memory.) Drag is still keyed on the lever's collective, so
  stick and pedal do not move torque (was +11-12% at full stick).
- Flight 2026-10-12 07:00 (onset rate build-up): roll 386, pitch 151, yaw 24.5 deg/s^2. User: roll -10%, pitch to match roll, yaw +25% -> `rollLiftCoef` 0.102, `tandemPitchLiftCoef` 0.575, `tandemYawLiftCoef` 0.344 (rig at 0.45 coll: roll 260 kNm, pitch 1.87 MNm, yaw 197 kNm; torque unchanged).
  torque +0.0 (was 61 / 79 kNm through `yawRollMix`).
- `fn_simpleRotorVariables.sqf`: `tandemPitchLiftCoef`, `tandemYawLiftCoef` replace
  `pitchCollMix`, `yawRollMix`. Rig ported (`forces.py`, `airframe.py`); Bo 105 output identical.
- Pack: 0.25 / 0.20 - rig, full input: 815 kNm pitch, 677 kNm yaw, torque +0.0%. Matching roll by
  the logged rate-per-moment would need ~1.7 MNm pitch (each rotor's lift +/-170% of hover) and
  ~1.1 MNm yaw (side force 110% of hover lift) - not rotor forces. The rest of the gap is on the
  Arma side (how hard this model resists pitch and yaw) - not looked into yet.
- `helisim_simpleRotor.hpp` reorganised (user): the header lists every field under who reads it -
  AIRCRAFT / EVERY ROTOR / MAIN ONLY / CONVENTIONAL ONLY / TANDEM ONLY / TAIL ONLY - and each rotor
  groups its fields the same way. Values unchanged apart from the two mixes swapped for the
  two coefficients (checked field by field).
| 8 | Mass and balance: CG, datum, limits, seats, tanks | **Mostly done** 2026-10-12 from the `fm-p3d-update` fm.p3d - seats and stores still the Bo 105's |

## Task 8 - from the `fm-p3d-update` branch's fm.p3d (2026-10-12)

The user's branch (`origin/fm-p3d-update`, `8748754`) adds point selections to fm.p3d:
`referenceDatum`, `fwdCgLimit`/`aftCgLimit`, `fwd/aftRotorPivot`, `fwd/aftRotorMast` (2 points),
and six tanks (`left/right` `FwdAux`/`Main`/`AftAux` `Tank`). The 46 fuselage quads are
unchanged, so the placement on line 2 applies to all of it. The config below is worked from that
fm.p3d - **the branch is not merged into master yet**; the working tree's fm.p3d is the old one.

Frames: panels, wings, fuel arms, `fsDatum` and the CG limits are Object Builder positions (Core
subtracts `boundingCenter`); a rotor `pivot[]` is Arma's model frame, so it is placed AND less
`boundingCenter` `[0.00339, 1.63298, 3.00263]` (read in game - the Pegasus model's, not ours).

- `helisim_mass.hpp`: `fsDatum` 8.012; `fwdCgLimit` 0.145 (station 309.8 in), `aftCgLimit` -0.845
  (348.8 in); empty CG mid-way (user: "near the center") - station 8.362 m / 329.2 in, `emptyMom`
  93237.79; `comCorrection` vertical only `{0, 0, 1.724}` (the -2.25 m stand-in is gone);
  `casualModeCom` `{0, -1.983, -1.279}`. Full fuel, no crew: CG station ~8.225 m, inside the limits.
- `helisim_simpleRotor.hpp`: front pivot `{-0.003, 4.213, 1.191}`, mast 0.290, `rotation` -5.43
  (leans forward 6.9 deg in fm.p3d, less the placement's 1.5); rear `{-0.003, -7.769, 2.237}`,
  mast 0.290, `rotation` +1.50 (vertical in fm.p3d). Core's hub (pivot + mast) lands exactly on
  each mast top, within ~5 cm of the hubs nudged in game the day before.
- `helisim_fuel.hpp`: six tanks, user's capacities - mains 3750 lb (1701 kg), aux ~1700 lb
  (771.1 kg); 14,300 lb in all. Engine 1 draws from the left main, engine 2 the right; each aux
  tank (`role = "xfer"`) feeds its own side's main. `fn_setup.sqf`: XFER pump OFF, the four aux
  transfers ON. TODO: `lowFuelKg`, a crossfeed position, aux pumps as crew switches.
- Generator (Core): a selection with no faces is passed over (it used to stop at
  `referenceDatum`). With the branch's fm.p3d it writes the pack's panels unchanged.
- Not done: the generator reading these points itself (it could write all of the above) - the
  user's call.

## Paused 2026-10-11, late - pick up here

**Last flight (22:25 rpt, local Core build):** roll is right ("roll is perfect", user) at
~70-80 deg/s full input. Pitch ~22 deg/s, yaw ~3.5 deg/s. User: pitch and yaw must match roll.

**Open question to the user - do pitch and yaw need their own coefficients?** My answer, given:

- **Yaw - yes.** Pedal is added to each rotor's ROLL output (`yawRollMix`), so it runs through
  roll's own `rollLiftCoef` and `rollFlap*` and is capped by the roll output's +/-1 clamp. Roll is
  now right, so yaw cannot be raised there without moving roll. Proposed: a tandem yaw output with
  its own coefficients (e.g. `yawLiftCoef`, `yawFlapMin/Max`) that `fn_simpleRotor` applies the
  same way it applies roll's - Core change, needs the user's design.
- **Pitch - only by changing what pitch is.** `pitchCollMix` is already pitch's own knob, but it
  works through collective, the lift table's key, so it is capped by the table's 0.85 peak (at
  50,000 lb the rising rotor reaches the peak at 0.30). A direct differential lift term (like the
  cyclic terms) would have no cap, but torque would no longer follow, since the drag table is keyed
  on the same collective. User to choose: real differential collective (capped) or a lift term.
- Numbers (rig, current config, ~0.40 collective): full lateral 277 kNm roll; full stick 0.53 MNm
  pitch; full pedal 0.11 MNm yaw at `yawRollMix` 1.0. Game rate per moment: pitch ~6x and yaw
  ~4x slower than roll (the long fuselage - a real Chinook has the same imbalance). To match roll:
  pitch ~1.7 MNm, yaw ~1.1 MNm.
- `yawRollMix` is still 0.50 - raising it to 1.0 (the clamp) only doubles yaw.

**Mass and balance - asked the user for:** the empty-weight CG station; forward and aft CG
limits (stations, and whether they vary with weight); one or two known stations to tie the datum
to the model (the rotor hub stations ideally - the hubs are nudged on at model y 4.27 and -7.72);
fuel tank capacities and stations; which crew/cabin seats count (positions measured with Core's
`tools/seats.sqf`). With those, `fsDatum`, `emptyMom`, the CG limits, seats and tanks become the
MH-47G's, and `comCorrection` goes back to vertical only (the -2.25 m forward part is a stand-in).

**Gotcha:** one session loaded the Workshop `@BradMick's HeliSim` 1.3.0.0 instead of the local
Core build - pitch and yaw went dead (no `TANDEM`). Check the rpt's `bmkhs_helisim.pbo` line is
`C:\GitHub\BradMicks-HeliSim-Core\.hemttout\build\...`.

## Task 2 - tandem control (Core `release/1.4.0`)

The design (user): the CONTROL SCHEME decides how the controls reach the rotors -
conventional, tandem, coaxial, tilt rotor, compound. Rotor types are main, tail, propeller,
prop rotor. A rotor's place in its scheme is DECLARED (`position`: front, rear, left, right,
top, bottom), not inferred from `pivot[]`. Only the tandem is built; the other schemes' cases
are empty headers.

- `rotor.hpp`: the scheme and position constants.
- `fn_simpleRotorVariables.sqf`: `controlScheme` at aircraft level (conventional when not
  declared); per rotor `position` (-1 when not declared), `pitchCollMix`, `yawRollMix` (0).
- `fn_simpleRotorControl.sqf`: takes the rotor, switches on the scheme. `CONVENTIONAL` is the old
  code unchanged. `TANDEM`: pitch output 0; collective +/- `pitchCollMix` x pitch, roll +/-
  `yawRollMix` x pedal - forward stick takes collective off the front and puts it on the rear,
  right pedal tilts the front disc right and the rear left.
- `fn_simpleRotor.sqf` passes the rotor. Rig ported: `forces.py`, `airframe.py`.
- How the rotor makes force (read it before touching it): four blade points; each point's flap
  (coning + `flapLat cos psi` + `flapLon sin psi` + flapback) places the blade and tilts its lift
  vector; lift = table lift + the cyclic term (`rollOutput cos psi rollLiftCoef + pitchOutput sin
  psi pitchLiftCoef`); lift and drag go to `addForce` at each point. Cyclic = blade pitch change +
  disc tilt, together. In a tandem yaw the two rotors' roll moments cancel and the side forces
  (tilted lift, blade pitch included) make the yaw.
- Nothing breaks for other aircraft: Bo 105 rig output byte-identical; no pack on this machine
  (Bo 105, EC665, AH-64D, H-60, HeliSim) declares the new fields or includes `rotor.hpp`.
- Fine for a tandem: the transmission refers each rotor through its own gear ratio (rotor 0's
  feeds only a debug log); rotor effects read the first main rotor's Vne and blades.

## Task 6 - rotor tables and the pack's numbers

User's figures, sea level 15 C OGE unless noted:

- Engine T55-GA-714A: 4168 SHP continuous, 3108 kW, 15066 rpm, 100% TQ 1965 Nm. Rotor 225 rpm
  (`gearRatio` 66.96), 3 blades, 18.29 m diameter, 0.641 m chord, 159 kg blades. Empty 11,150 kg,
  max gross 24,494 kg (54,000 lb, user 2026-10-12; was 22,700).
- Hovers: 37,500 lb 62%, 50,000 lb 90% (80 ft OGE), and the structural limit line 50,000 lb 98% at
  5,000 ft 15 C. Flat pitch both engines FLY ~19% per engine. Power curve at 37,500 lb (kt:%):
  0:62 10:60 20:56 30:52 40:48 50:44 60:40 70:39 80:38 90:39 100:40 110:43 120:46 130:52 140:58
  150:68 160:80. Max endurance 79 kt, max range 148 kt. The chart stops at 50,000 lb.
- Fitted with `rotortables.py --peak-margin 1.20` (command in the comment above the tables). The
  5,000 ft point is flown at sea level as 59,901 lb 117.4% - the model's lift and torque both scale
  with density, so it is the same rotor state. Same tables on both rotors ("they are the same
  rotor").
- Result: 0-150 kt and all three hovers fit (50,000 lb at 0.554 collective); flat pitch 19.0%.
  **160 kt does not trim** - not pitch authority (`pitchCollMix` 0.60 changed nothing), not the
  250 kt airspeed clamp. Open. The fit's CG `{0, -1.659, -1.279}` is derived, not read in game -
  re-fit once mass and balance are real (`getCenterOfMass vehicle player`).
- Engines: the Allison 250-C20B gas model with `massFlow` and `maxFuelFlow` x9.93 (3108/313 kW) -
  same Ng/TGT/fuel-air behaviour at the T55's power. Rig at the 50,000 lb hover: Nr 100%, Ng
  0.957, TGT 792 C. A rough rescale, not the T55's own gas model.
- Roll (user): disc tilt symmetric +/-10.5 deg, `rollLiftCoef` 0.116 (roll -25% from the Bo 105's
  0.166). Pitch: `pitchFlap*`, `pitchLiftCoef` 0. Mixes: `pitchCollMix` 0.30, `yawRollMix` 0.50.
- Core rig fixes for a tandem (uncommitted): `airframe.py forces()` keyed rotors by type, so the
  rear main rotor overwrote the front in every trim - now type + position. `rotortables.py` fitted
  only the first main rotor - now every main rotor. New `--peak-margin` (default 1.001, other
  aircraft unchanged).

The rough rescale before the fit (Bo 105 tables x2.35 lift / x2.72 drag) is gone - superseded.

## Task 5 - placement (nudge)

- Fuselage + wings: `--forward 0.400 --down -2.050 --right 0.000 --pitch 1.500` (no turn),
  recorded on line 2 of both files and as `fmPlacement[]`.
- Hubs: front `{0.000, 4.270, 0.820}` with `rotation[] = {-5, 0, 0}`, rear `{0.000, -7.720,
  1.820}` (12 m apart; published 11.94).
- `comCorrection[] = {0.000, -2.250, 1.724}` - the forward part is a stand-in until task 8.
- `tools/fm_nudge.sqf` (Core): no comments anywhere - the Extended Debug Console on this machine
  fails on the first comment after the start of the pasted code. Numpad 5 copies every changed
  value at once; Numpad 7 cycles a mode - rotors move / rotate / mast, fuselage + wings move /
  rotate. Used in game 2026-10-11 - works.
- Generator: `--pitch/--roll/--yaw` rotate the fm.p3d about its own origin (turn, rotate, shift;
  `--add` adds the angles); writes `fmPlacement[]` into `helisim_fuselage.hpp` so the nudge
  rotates about the placed origin. No rotation regenerates the MH-47G and Bo 105 panels exactly.
- `docs/AIRCRAFT_GUIDE.md` (Core) updated for both.

## Task 4 - the tools (Core `release/1.4.0`, `57b888d`)

- `python/tools/fm_generateAeroSurfacePoints.py`, `tools/fm_nudge.sqf`, `tools/seats.sqf`,
  `tools/dump.sqf`, `python/dev/airflow_trim.py` moved from the Bo 105 into Core; they ship in
  Core's release file list (`.hemtt/project.toml` `[files]`).
- Bo 105 changes pushed to its `master`, `7509ecd`.

## Task 3 - fm.p3d

- Model: 180 points, 46 faces, 46 selections. `fuselageTop` up 15 quads, `fuselageSide` right
  12, `fuselageFront` forward 19. No wing surfaces.
- `fuselageFront06/09/16/19` are triangles (the engine fronts); the generator takes a 3-sided face
  as a quad with its last corner repeated (Core `57b888d`).
- Fuselage drag tables, airfoil: the generator's defaults - not fitted.

## Settled

- Pack at `C:\GitHub\BradMicks-HeliSim-MH47G`, Core at `C:\GitHub\BradMicks-HeliSim-Core`
  (`release/1.4.0`), other packs beside them in `C:\GitHub`. The Bo 105's naming: project prefix
  `bmkhs_mh47g`, PBO prefix `bmkhs_mh47g_helisim`, functions `bmkhs_mh47g_helisim_fnc_*`.
  Version 0.1.0.0.
- `bmkhsBaseClass = "PGS_Chinook_Base"` - it must cover both Block 1 and Block 2.
- Damage roles: front rotor `mainRotor` (HitHRotor), rear `tailRotor` (HitVRotor) - to confirm
  against the Pegasus model.
- Not in this update: longitudinal cyclic trim, and the other control schemes.
- Whatever goes into Core's `fn_simpleRotor*` is ported to the rig (`python/dev/airframe.py`) in
  the same change - the rig is a 1:1 port of Core's force path.

## The airframe in game

From the console dump, 2026-10-11:

- Mod: Pegasus Systems MH-47G Block 1 & 2, workshop 3805899171, `PGS_MH47G.pbo` (obfuscated -
  not opened).
- `configSourceAddonList PGS_MH47G_Block_1` gives `PGS_Hooker_Core` and `PGS_MH47G_Block_1` -
  both are in `requiredAddons`, so the pack loads after each.
- Classes: `PGS_Chinook_Base : Helicopter_Base_H` (scope 0), `PGS_MH47G_Block_1 : PGS_Chinook_Base`
  (scope 2), `PGS_MH47G_Block_2 : PGS_MH47G_Block_1` (scope 2).
- Only `PGS_Chinook_Base` declares the force coefficients, so `BMKHS_FM_OVERRIDE` sits on the base
  alone.
- `boundingCenter vehicle player` = `[0.003, 1.633, 3.003]`.

## Placeholders still to replace

Every `TODO(MH47G)` in the pack:

| File | Still a placeholder |
|---|---|
| `helisim_engine.hpp` | the gas model - the Allison 250-C20B's, rescaled x9.93 to the T55's 3108 kW |
| `helisim_rotor.hpp` | the blade element rotors |
| `helisim_simpleRotor.hpp` | the two mixes (task 7); `coneAngle`, flapback, `gndEffValue`, `reacTqScalar`, `autoTorque`, `mastLength`, `nrLimits`; the hitpoints; 160 kt in the tables |
| `helisim_mass.hpp` | turrets 7, 10, 11 (did not measure); the estimated kit masses |
| `helisim_fuel.hpp` | `lowFuelKg`, crossfeed, aux pumps as switches (tanks done - task 8) |
| `helisim_fuselage.hpp` | the drag tables are the generator's defaults - the geometry is the MH-47G's own |
| `helisim_flightControls.hpp` | the FMC and auto-pedal gains |
| `README.md` | the Core version it needs - the release that carries tandem control |

## Scaffold notes (task 1)

- Not copied from the Bo 105: `fm.p3d`, `tools/`, `docs/BO105_FM.md`, `releases/`.
- Deleted as dead in the copy: the `BO105_SWOOPER` seat block (`helisim_mass.hpp`) and the
  `BO105_VARIANT` list (`cfgVehicles.hpp`).
- Vendored `include/bmkhs_helisim/fmOverride.hpp` from Core 1.3.0.0.

### 2026-10-12 07:10 flight and `tandemYawFlap`

- 07:10 rpt (Core built 07:10:40 - the tilt + blade-pitch yaw): onset build-up roll 265, pitch
  222, yaw 20 deg/s^2; full pedal yaw settles flat at ~9.8 deg/s. The 07:00 flight's 25-35 deg/s
  matches the sideways-lift build (~680 kNm), so the "+25% yaw" was sized from the wrong
  baseline.
- Pitch to roll: `tandemPitchLiftCoef` 0.575 -> 0.686.
- `tandemYawFlap` (user's name, Core, approved): pedal's own disc tilt, deg at full pedal, added
  to lateral cyclic's (was pedal through the `rollFlap*` range). Pack 10.5 = unchanged behaviour.
  Rig yaw at full pedal, 0.45 coll (kNm), flap x `tandemYawLiftCoef`: 10.5 deg 197 / 376 / 512
  (0.344 / 1.0 / 1.5); 20 deg 284 / 459 / 592; 30 deg 369 / 536 / 663; 40 deg 444 / 601 / 720.
  Steady yaw rate looks proportional to moment: 197 kNm ~ 9.8 deg/s.
- 07:24 flight (tandemYawFlap 10.5): pitch and roll about even (user); yaw still ~10 deg/s. Set
  `tandemYawFlap` 40, `tandemYawLiftCoef` 1.5 - rig 720 kNm, ~36 deg/s expected.
- `tandemYawFlap` 15 (user: 12-15 deg is the most a blade flaps; 40 removed). Rig, floored-lift test in
  a scratch copy only: the down blade goes to -82 kN at coef 1.5; flooring main-rotor blade lift at 0
  gives +9-17% yaw (15 deg / 1.5: 551 -> 648 kNm). NOT built - waiting on the user: all main rotors
  or tandem only.
- Refactor (user): `fn_simpleRotorGetLiftCoefDelta.sqf` (Core, registered in cfgFunctions) - one
  blade's lift coefficient change from the controls, mixed per control scheme into a roll and a
  pitch part (tandem pitch is the pitch part); `fn_simpleRotor` adds the two. Same math; rig ported
  (`forces.simple_rotor_get_lift_coef_delta`), rig output identical for the MH-47G and Bo 105.
- User: no `tandemYawFlap` - pedal tilts through `rollFlap*` again (removed from Core, rig, pack). The
  lift-coefficient call is back inside the blade loop (it needs psi and the blade's table lift
  coefficient). TANDEM only: the pedal term never takes a blade's total lift coefficient below 0.
  Rig at full pedal, coef 1.5: yaw 503 / 532 / 582 kNm at 0.39 / 0.45 / 0.55 collective, no blade
  below 0 N; roll and pitch unchanged; Bo 105 identical.
- Floor tested in flight 07:49: right pedal rolled the aircraft (to -74 deg bank) - with fore/aft input
  (the attitude hold saturated) the floor clips the two rotors differently, so their +/-1 MNm roll
  moments stop cancelling; and it turns pedal into lift (+151 kN at full pedal). Its yaw gain
  (4-12%) IS that lift. REMOVED (user). `rollFlap*` now +/-12 deg (user).
- `ControlMixing` (Core): new target "collective" -> `bmkhs_mixCollOut`, added to the collective in
  `fn_simpleRotorControl` and `fn_rotorControl`; guide updated. Mixing still REALISTIC only.
  Proposed, NOT added: PedalToRoll {-1,0.141},{0,0},{1,-0.141}; PedalToCollective
  {-1,0.033},{0,0},{1,0.033} (rig, 0.46 coll, no floor).

### LCT (2026-10-12, Core uncommitted)

- User: in `fn_simpleRotorControl` (the tilt rotor will set mast pitch there too); actuators travel
  smoothly - full stroke in `lctTime` (12 s, user); casual and realistic alike; all altitudes.
- Core: `TANDEM` reads `lctSchedule` (2D grid, rows airspeed kt from `bmkhs_vel2D`, columns pressure
  altitude ft from `bmkhs_barAlt`), rate-limits the actuator (`lctPos`, full stroke `lctStroke` in
  `lctTime`), returns a sixth output, mast pitch = -LCT (extend tilts forward); `fn_simpleRotor`
  adds it to `rotation[]` pitch. Grid built only where a rotor declares one. Rig ported (schedule
  value, no clock). Other packs' rig output unchanged.
- Pack: grids digitised from the user's Chinook LCTA chart - front -1.2..+4 deg, 0.058 deg/kt;
  rear -3.25..+4 deg, 0.081 deg/kt; flat to 40 kt, lines for SL, 5k, 10k, 15k, 20k ft; rows 0 and
  40-150 kt every 5.
- `tandemYawLiftCoef` 1.8 (+20%, user).
- Tables refitted WITH the LCT (`rotortables.py --peak-margin 1.20 --cg 0 -1.983 -1.279 --bc 0.003
  1.633 3.003 --mr 148 --cruise-pitch -5 --cruise-kt 150`, same hovers and curve): every point
  0-160 kt and all hovers within 0.5% (160 kt now fits). Front fuselage drag 0.793 flat.
- Tuning target (user): level (0 deg) to 100 kt, then 1 deg nose low per 10 kt. Rig at 37,500 lb:
  -0.5..-1.9 deg to 100 kt, -2.2 / -2.6 / -3.2 / -4.0 / -5.0 / -7.1 at 110-160 kt. Above 120 kt
  within ~0.6 deg; below 100 kt ~1.6-1.9 deg nose low - open.
- LCT schedule tuned to the attitude target (user OK'd adjusting it): offsets added to both actuators,
  every altitude, clamped to the limits; 0 kt row untouched. Offsets (deg, + forward): 40 kt +1.76,
  60 +1.68, 70 +1.53, 80 +1.49, 90 +1.54, 100 +1.70, 110 +1.05, 120 +0.54, 130 +0.18, 140-150 0.
  Tables refitted each round (scratchpad lct_tune.py, 3 rounds). Rig at 37,500 lb: 0.00 deg 20-100 kt,
  -1/-2/-3/-4/-5 at 110-150 (+/-0.03), torque on the curve, fit OK; 160 kt -7.1 (both actuators at
  the +4 extend limit). Front fuselage drag 0.793.
- `lctTime` 12 s (user: full retract to full extend).
- Casual CoM (user: picks straight up, pure inputs): `casualModeCom[] = {-0.003, -1.721, -1.279}` - rig,
  casual (no flapback, no reaction torque, LCT at hover): zero pitch/roll/yaw moment with no input at
  every weight 12,000-22,680 kg (y does not move with weight; 0.5-1 kN aft from the masts' hover
  lean). Half inputs: roll leaks <1% into yaw, pitch is pure, pedal 4.7% into roll - the opposite
  side forces at different hub heights (1.48 / 2.53 m), a couple no CoM can remove; mixing is
  REALISTIC only, so casual keeps it.
- Seats (2026-10-12): measured with tools/seats.sqf (its in-block comment removed - same console
  problem as the nudge). 34 declared: pilot + turrets 0-6, 8, 9 at 100 kg (crew), cargo 0-23 at
  149.7 kg (330 lb, the UH-60 pack's troop mass, user). Turrets 7, 10, 11 did not measure - in the
  file commented out, TODO check in game. Full fuel + all crew + 24 troops: 22,229 kg, CG station
  318.5 in - every loading checked is inside the limits. The pack has no pylons (seats.sqf found
  none); the Bo 105 HOT stations and store are still declared.
- Weapons and ammo (UH-60 pack weights, user): Equipment keyed to the guns' hide sources (inherited
  from PGS_Chinook_Base - dump.sqf missed them, it lists only a class's own AnimationSources):
  Hide_M134_1/2 42.4 kg (39 gun + 3.4 mount), Hide_M240_1/2 15.9 kg (12.5 estimate + 3.4), at the
  gunner seats, installedPhase 0. emptyMass back to 11,150. Magazines: 4000rnd_65x39 and
  250rnd_762x51 at 0.0254 kg/rd, cmflare 0.25 kg/rd (arm an estimate). Full fuel + ammo + all crew
  + 24 troops: 22,832 kg, under the 24,494 kg max gross; CG inside.
- Other fitted kit, Equipment (user agreed the figures): AAR probe 228 kg (502 lb complete system,
  Army flight test, Chinook-type, airframe unconfirmed); armour 1,588 kg (US Army Chinook BPS
  ~3,500 lb, 2013) along the cabin; cargo door armour 35, dump pipe 4, door plug 20, window plugs
  4 x 6, skis 110 - estimates. Default kit (probe, armour, door armour, pipe, door plug) +2 pilots
  no fuel: 13,342 kg; + full fuel, ammo, all crew, 24 troops: 24,707 kg (213 kg over the 24,494 kg
  max gross); every CG inside the limits (312.8-317.3 in).
- Turret ammo (Core fix, user approved): fn_massUpdate read ammo with `magazinesAmmo`, which returns
  only the driver's ([-1]) magazines - in game the MH-47G showed only Laserbatteries, every door-gun
  belt only in `magazinesAllTurrets`. The UH-60 DAP counted because all its weapons are the pilot's;
  the Tiger because its guns are pylon stores (getPylonMagazines). Now reads `magazinesAllTurrets`
  (a superset - driver-only aircraft unchanged, pylon racks matched as before). Guide updated.
  No flare magazine is loaded on the MH-47G in game, so its flare entry reads 0.
- HOT stations and store removed (user) - numStations 0, numStores 0; the MH-47G has no pylons.

### 2026-10-12 afternoon

- Flown: casual pick-up fine. Pedal->collective mix paused (user).
- dump.sqf (Core, uncommitted): turrets, pylons, presets and animation sources via
  configProperties with inheritance - it missed inherited classes (the gun hide sources).
- Turrets 7, 10, 11: seats.sqf could not board them (hoist / hanging ramp seats) - lower the ramp,
  deploy the hoist and re-run seats.sqf.
- CG fit: a 37,500 lb loading with the default kit (empty + kit + guns + 2 pilots + ammo + 3,224 kg
  fuel) sits at station 313.3 in = Arma {0.014, -1.579, -1.279} (was -1.983). Refit + LCT tuned for
  ALL altitudes in scratchpad (lct_tune_all.py, cfg_tune_all): converged (<=0.01 deg; 20k ft
  130-150 kt short by 0.04-0.21). Copied to the pack 2026-10-12 (lctSchedule, lift/drag tables,
  front fuselage drag 0.808; pack engine and nrLimits kept). At altitude the tuned columns run AFT
  of the chart (20k ft 150 kt: -1.2 / -3.25 vs chart +4 / +4) - flight test.
- Engine limits from the TM (user): PTIT bands 816 (30 min) / 854 (10 min) / 899 (2.5 min) /
  932 (12 s) / 943; Ng 111%, ngMin 50%; Np 111.5%; TQ 100% dual / 123% single; oil 35-90 psi
  normal (full scale 90 psi); Nr {0.97, 1.01, 1.06, 1.11}. Written. Open (user): maxTgt / maxTgtSe
  limiter (suggested 899 / 932), maxNg / maxNp trips (maxNg scales the compressor map - leave for
  the T55 gas model), Ng-dependent oil minimums (Core has one), hydraulic pressures (no systems yet).
- Engine (2026-10-12): Ng-only limiting at 111% (ngLimitMax/Base 1.11, maxTgt 9999 - Core always runs a
  TGT limiter, so it is set out of reach); maxNg 1.12. Core fix: Ng was clamped at 1.1 in
  fn_gasTurbineCompressorTurbine (and the rig) - now the engine's maxNg (other packs all 1.10).
  Spec: pressure ratio 9.32 (T55-L-714A published), mass flow 13.199 kg/s (user). Compressor map by
  compressor_map.py from the 10-minute rating at its PTIT limit: 15 C, N1 1.110, T45 899, TQ 1.265 -
  lands exactly; fuelIdle 0.401 (superseded - see the idle rebuild below). airflowTable trimmed to the user's
  sea-level 10-minute torque curve (-40..+40 C): warm side exact; cold side fitted through noisy
  runs (max Ng settles 1.108-1.113). Open: max-power Ng overshoots the 1.11 book limit (0 s);
  hot-day max-power PTIT 910 (20 C) / 930 (30 C) / 947 (40 C) - past the 10-minute band and, at
  40 C, the 943 never-exceed.
- Overspeed trips (Core, user): Ng fly-weight trip is optional `ngOvrspdProt` (default maxNg, 0 = none -
  the T55, Bo 105 and Tiger engines have no fly weights); Np trip `npOvrspdProt` (falls back to the old
  `maxNp`, 0 = none) - trip check, engine display, rig, docs. Other packs resolve to their old trips.
  MH-47G: ngOvrspdProt 0, npOvrspdProt 1.175 (the Allison's value - T55 figure wanted).
- Full collective pull, SL 15 C, 37,500 lb, no Ng trip now: Ng hits the 1.12 ceiling then hunts 1.10-1.12
  round the 111% limit, torque swings 108-170%, Nr droops to ~57%. The Ng limiter only reacts once
  over the limit - proposed (awaiting design approval): make it anticipate the rate of approach.
- Np overspeed protection 114.8% (user - the T55's only trip). Ng 83% at 100% Np/Nr flat pitch (user).
- Ng limiter anticipator (Core + rig, user): the limiter acts on Ng 0.4 s ahead at its filtered rate
  (GT_NG_LEAD, GT_NG_RATE_TAU, bmkhs_engNgPrev/Rate). Full pull: Ng stops at 111.0%, no overshoot, no
  hunting (was 112% then +/-1% with torque 108-170%); Bo 105 at its limit: was Ng 104.4-105.6% /
  torque 106-126%, now 105.0% / 116.3% - same mean.
- Compressor map rebuilt: FLAT 15 C N1 0.830 T45 550 (assumed) TQ 0.19 + 10MIN 15 C 1.110 / 899 / 1.265 -
  both land. airflowTable re-trimmed: every FAT exact. SL 15 C: flat pitch Ng 83.0% TQ 19% PTIT 550;
  37,500 lb hover Ng 93.1% TQ 62% PTIT 798; 50,000 lb hover Ng 100.2% TQ 89.9% PTIT 867.
  Hot-day max-power PTIT: 919 (20 C), 958 (30 C), 995 (40 C) - kept (user): the T55 has no TGT limiter,
  so the pilot can pull past the limits and burn the engine; the book limits and damage handle it. A
  hot-day re-trim to put the curve at 899 C needed airflow x1.27-1.67 and gave 157-193% when pulled
  past - rejected.
- Ground idle (MH-47G display, user): Ng 55.3%, TQ 15-16%, PTIT 445, Np 50.6%, Nr 49%. In game the pack
  idled at Ng 71.0 / TQ 6 / PTIT 433 / Np-Nr 75; 45,500 lb hover at TQ 68% read PTIT 817 (30-min band).
  Core tool compressor_map.py: low-end pressure ratio now scales the T700's in log terms on the
  engine's own ratio (was a straight fraction - PR 0.55 at standstill, 1.5 at idle); a rating may
  give its own compressor efficiency (6th column). Map rebuilt from IDLE 15 C 0.553 / 445 / power
  0.0784 (15.5% at Np 50.6%) eff 0.70 + FLAT + 10MIN - all land. idleNg 0.553, fuelIdle 0.403,
  airflowTable re-trimmed (every FAT exact). Rig SL 15 C: idle Ng 55.3 PTIT 445 TQ 7.8 Np/Nr 64;
  TQ 69% PTIT 792 (was 819); 89% 841 (was 866); hot-day max PTIT 916 / 946 / 975.
  Open: idle Np/Nr 64% vs 49% and TQ 7.8% vs 15.5% - Core rotor drag goes as Nr^2 (19% at 100% gives
  4.6% at 49%); the real drivetrain loads ~3x that at idle. Needs a Core load term - user's design.
  helisim_engine.hpp comments cut to section headers and term descriptions.
