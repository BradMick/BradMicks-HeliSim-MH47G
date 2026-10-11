class CfgPatches
{
    class bmkhs_mh47g_helisim
    {
        units[] = {};
        author = "BradMick";
        weapons[] = {};
        requiredVersion = 2.10;
        //HeliSim Core, and both PGS addons that edit the Chinook classes - this pack modifies
        //them, so it must load after each.
        requiredAddons[] = {"bmkhs_helisim", "PGS_Hooker_Core", "PGS_MH47G_Block_1"};
        //The airframe this pack drives. The MH-47G Block 1 and Block 2 both inherit from it.
        bmkhsBaseClass   = "PGS_Chinook_Base";
        #include "version.hpp"
    };
};

#include "CfgFunctions.hpp"
#include "config\CfgEventHandlers.hpp"
#include "config\cfgVehicles.hpp"
