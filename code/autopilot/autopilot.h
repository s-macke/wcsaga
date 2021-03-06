// Autopilot.h
// Derek Meek
// 4-30-2004



#if !defined(_AUTOPILOT_H_)
#define _AUTOPILOT_H_

#include "globalincs/pstypes.h"
#include <map>

// milliseconds between updates
#define NPS_TICKRATE    125

#define MAX_NAVPOINTS    8

#define NP_WAYPOINT        0x0001 // Nav Point is bound to the poistion of a single node of a waypoint path
#define NP_SHIP            0x0002 // Nav Point is bound to the poisiton of a certain ship
#define NP_HIDDEN        0x0004 // Nav Point doesn't show on map and isn't selectable
#define NP_NOACCESS        0x0008 // Nav Point isn't selectable
#define NP_VISITED        0x0100 // Whether we've been within 1,000 meters of this waypoint

#define NP_NOSELECT        ( NP_HIDDEN | NP_NOACCESS )
#define NP_VALIDTYPE    ( NP_WAYPOINT | NP_SHIP )

struct NavPoint {
    char NavName[32];
    int flags;

    void *target_obj;
    int waypoint_num; //only used when flags & NP_WAYPOINT

    vec3d *GetPosition();

    char *GetInteralName();
};


#define NP_NUM_MESSAGES 6
#define NP_MSG_FAIL_NOSEL        0
#define NP_MSG_FAIL_GLIDING        1
#define NP_MSG_FAIL_TOCLOSE        2
#define NP_MSG_FAIL_HOSTILES    3
#define NP_MSG_MISC_LINKED        4
#define NP_MSG_FAIL_HAZARD        5

struct NavMessage {
    char message[256];
    char filename[256]; // can be ""
};

extern bool AutoPilotEngaged;
extern int CurrentNav;
extern NavPoint Navs[MAX_NAVPOINTS];
extern NavMessage NavMsgs[NP_NUM_MESSAGES];
extern int LockAPConv;
extern std::map<int, int> autopilot_wings;

// Cycles through the NavPoint List
bool Sel_NextNav();

// Selects the specified nav point if valid and selectable.
// Has no effect otherwise.
void SelectNav(char *nav);

void SelectNav(int nav);

// Un-select the currently selected nav point.
// Has no effect if no nav point is selected.
void UnSelectNav();


// Tell us is autopilot is allow
// This needs:
//        * Nav point selected
//        * No enemies within 5,000 meters
//        * Destination > 1,000 meters away
bool CanAutopilot(bool send_msg = false);

bool CanAutopilotPos(vec3d targetPos);

// Engages autopilot
// This does:
//        * Control switched from player to AI
//        * Time compression to 32x
//        * Tell AI to fly to targetted Nav Point (for all nav-status wings/ships)
//		  * Sets max waypoint speed to the best-speed of the slowest ship tagged
void StartAutopilot();

// Checks if autopilot should automatically die
// Returns true if:
//         * Targetted waypoint < 1,000 meters away
//         * Enemy < 5,000 meters
bool Autopilot_AutoDiable();

// Disengages autopilot
// this does:
//         * Time compression to 1x
//         * Delete AI nav goal
//         * Control switched from AI to player
void EndAutoPilot();


// Checks for changes every NPS_TICKRATE milliseconds
// Checks:
//			* if we've gotten close enough to a nav point for it to be counted as "Visited"
//			* If we're current AutoNavigating it checks if we need to autodisengage
void NavSystem_Do();


// Inits the Nav System
void NavSystem_Init();

// parse autopilot.tbl
void parse_autopilot_table(char *filename);

// Finds a Nav point by name
int FindNav(char *Nav);

// Set A Nav point to "ZERO"
void ZeroNav(int i);

// Removes a Nav
bool DelNavPoint(char *Nav);

bool DelNavPoint(int nav);

// adds a Nav
bool AddNav_Ship(char *Nav, char *TargetName, int flags);

bool AddNav_Waypoint(char *Nav, char *WP_Path, int node, int flags);

//Change Flags
bool Nav_Alt_Flags(char *Nav, int flags);

// Sexp Accessors
bool Nav_Set_Flag(char *Nav, int flag);

bool Nav_UnSet_Flag(char *Nav, int flag);

bool Nav_Set_Hidden(char *Nav);

bool Nav_Set_NoAccess(char *Nav);

bool Nav_Set_Visited(char *Nav);

bool Nav_UnSet_Hidden(char *Nav);

bool Nav_UnSet_NoAccess(char *Nav);

bool Nav_UnSet_Visited(char *Nav);

// Useful functions
unsigned int DistanceTo(char *nav);

unsigned int DistanceTo(int nav);

bool IsVisited(char *nav);

bool IsVisited(int nav);

void send_autopilot_msg(char *msg, char *snd = NULL);

void send_autopilot_msgID(int msgid);

#endif

