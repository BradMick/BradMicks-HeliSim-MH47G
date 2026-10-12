/* ----------------------------------------------------------------------------
Function: bmkhs_mh47g_helisim_fnc_setup

Description:
    Initialises HeliSim Core for the MH-47G and hands it this aircraft's
    configuration. Called once per aircraft at init.

Parameters:
    _heli - The helicopter [Object]

Returns:
    Nothing
---------------------------------------------------------------------------- */
params ["_heli"];

//Once per aircraft. The pack's own init EH is what fires this.
if (_heli getVariable ["bmkhs_initialised", false]) exitWith {};

[_heli] call bmkhs_fnc_coreInit;
[_heli, configOf _heli >> "BMKHS_HeliSim"] call bmkhs_fnc_coreConfig;

//No main-to-main transfer; the aux tanks feed their own side's main.
_heli setVariable ["bmkhs_xferMode", "OFF"];
{ _heli setVariable [_x + "XferOn", true] } forEach ["bmkhs_leftFwdAuxTank", "bmkhs_rightFwdAuxTank", "bmkhs_leftAftAuxTank", "bmkhs_rightAftAuxTank"];
