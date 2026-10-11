# MH-47G - status

Where the pack is, what is settled, and what is next. Updated after every task.

Started 2026-10-11 on HeliSim Core `d7ed678` (1.3.0.0). Built from the Bo 105 pack
(`E:\bmkhs_bo105`, `94a97c2`), following Core's `docs/AIRCRAFT_GUIDE.md`.

This update builds the pack AND tandem rotor control in Core.

## Where it is

| # | Work | State |
|---|---|---|
| 1 | Pack scaffold from the Bo 105, renamed, Bo 105 values as `TODO(MH47G)` placeholders | **Done** 2026-10-11 - `hemtt check` clean, not committed |
| 2 | Tandem rotor control in Core - design | **Open** - waiting on the two questions below |
| 3 | Fuselage and wings from the MH-47G's `fm.p3d` (`fm_generateAeroSurfacePoints.py`) | **Done** 2026-10-11 - written, `hemtt check` clean, not committed |

### Task 3 - fm.p3d

- Model: 180 points, 46 faces, 46 selections. `fuselageTop` up 15 quads, `fuselageSide` right
  12, `fuselageFront` forward 19. No wing surfaces, so `helisim_wings.hpp` declares none (the Bo 105
  placeholder stabiliser and fins are gone with the regeneration).
- First build: `fuselageTop07` held a duplicate face - fixed in the model.
- `fuselageFront06/09/16/19` are triangles (the engine fronts). User: "a quad can also be a
  triangle with 1 duplicated point." Core change, NOT committed: `python/tools/fm_generateAeroSurfacePoints.py`
  takes a 3-sided face as a quad with its last corner repeated; `docs/AIRCRAFT_GUIDE.md` (step 2
  and the error table) says so. Checked first: Core's panel normal is the diagonals' cross product
  and `fn_mathGetArea` (Brahmagupta) becomes Heron's with a zero edge - both exact for a triangle.
- Fuselage drag tables, airfoil: the generator's defaults - not fitted.

## Where it is going

Tandem control in Core, then the MH-47G declared as a tandem. Open questions:

1. **Where the tandem routing is declared** - on each rotor class (how pitch and pedal feed that
   rotor's collective and lateral cyclic), in an extended `ControlMixing` (cyclic sources, a
   per-rotor target, and running in casual), or another way.
2. **What is in this update** - pedal to differential lateral cyclic and fore/aft cyclic to
   differential collective, the minimum to fly; and whether longitudinal cyclic trim (both discs
   tilted fore/aft on an airspeed schedule) is in it too.

Whatever goes into Core's `fn_simpleRotor*` is ported to the rig (`python/dev/airframe.py`) in the
same change - the rig is a 1:1 port of Core's force path.

## Why tandem control is Core work

`fn_simpleRotorControl.sqf:34-43`: every `main` rotor gets the same collective, pitch and roll,
and only a `tail` rotor reads the pedal. Two `main` rotors would have:

- **no yaw control** - the pedal reaches nothing;
- **pitch from each disc's own cyclic only** - no differential collective;
- roll and collective working, and the two rotors' torques cancelling (`ccw` + `cw`).

`simpleRotor.hpp:37` says "a tandem is a declaration, not a code change" - the code does not
support that yet.

`ControlMixing` (`fn_fmcControlMixing.sqf`), the closest existing system, does not fit as it is:
it runs in REALISTIC only, its sources are collective and pedal only, and its output goes to every
rotor alike.

## Settled

- Pack at `E:\bmkhs_mh47g`, the Bo 105's naming: project prefix `bmkhs_mh47g`, PBO prefix
  `bmkhs_mh47g_helisim`, functions `bmkhs_mh47g_helisim_fnc_*`. Version 0.1.0.0.
- `bmkhsBaseClass = "PGS_Chinook_Base"` - it must cover both Block 1 and Block 2.
- Every placeholder value is the Bo 105's, marked `TODO(MH47G)`.

## The airframe in game

From the console dump, 2026-10-11:

- Mod: Pegasus Systems MH-47G Block 1 & 2, workshop 3805899171, `PGS_MH47G.pbo` (obfuscated -
  not opened).
- `configSourceAddonList PGS_MH47G_Block_1` gives `PGS_Hooker_Core` and `PGS_MH47G_Block_1` -
  both are in `requiredAddons`, so the pack loads after each.
- Classes: `PGS_Chinook_Base : Helicopter_Base_H` (scope 0), `PGS_MH47G_Block_1 : PGS_Chinook_Base`
  (scope 2), `PGS_MH47G_Block_2 : PGS_MH47G_Block_1` (scope 2).
- Only `PGS_Chinook_Base` declares the force coefficients (`liftForceCoef`,
  `cyclicForwardForceCoef`, `cyclicAsideForceCoef`, `backRotorForceCoef`), so `BMKHS_FM_OVERRIDE`
  sits on the base alone - no per-variant override like the Bo 105's.

## Placeholders still to replace

Every `TODO(MH47G)` in the pack:

| File | Still the Bo 105's |
|---|---|
| `helisim_engine.hpp` | the Allison 250-C20B - the MH-47G's engine goes here |
| `helisim_rotor.hpp` | the blade element rotors |
| `helisim_simpleRotor.hpp` | a main and a tail rotor - the tandem replaces them |
| `helisim_mass.hpp` | mass, balance, seats, the HOT stations and stores |
| `helisim_fuel.hpp` | the supply and main tanks |
| `helisim_fuselage.hpp` | the drag tables are the generator's defaults - the geometry is the MH-47G's own |
| `helisim_flightControls.hpp` | the FMC and auto-pedal gains |
| `README.md` | the Core version it needs - the release that carries tandem control |

## Scaffold notes (task 1)

- Not copied from the Bo 105: `fm.p3d` (its geometry; the MH-47G needs its own), `tools/`,
  `docs/BO105_FM.md`, `releases/`.
- Deleted as dead in the copy: the `BO105_SWOOPER` seat block (`helisim_mass.hpp`) and the
  `BO105_VARIANT` list (`cfgVehicles.hpp`).
- Vendored `include/bmkhs_helisim/fmOverride.hpp` from Core 1.3.0.0 (identical to the Bo 105's
  1.2.1.0 copy).
