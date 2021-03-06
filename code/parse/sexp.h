/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

#ifndef _SEXP_H
#define _SEXP_H

#include "globalincs/pstypes.h"    // for NULL
#include <string>
#include "boost/unordered_map.hpp"

struct ship_subsys;
struct ship;

// bumped to 30 by Goober5000
#define    OPERATOR_LENGTH    30  // if this ever exceeds TOKEN_LENGTH, let JasonH know!
#define    TOKEN_LENGTH        32

/*
#ifdef FS2_DEMO
	#define	MAX_SEXP_NODES	1600
#else
	#define	MAX_SEXP_NODES	4000			// Reduced from 2000 to 1200 by MK on 4/1/98.
											// Most used nodes is 698 in sm1-10a.  Sandeep thinks that's the most complex mission.
											// AL 2-4-98: upped to 1600, btm03 ran out of sexps, since campaign took a bunch
											// DA 12/15 bumped up to 2000 - Dan ran out
											// DaveB 9/02/99 bumped to 2200
											// Goober5000 01/20/2004 bumped to 3000
											// WMCoolmon 06/15/2004 bumped to 3500
											// Goober5000 04/14/2005 bumped to 4000 for WCS
											// Goober5000 04/17/2005 reduced to 3000, now that we solved the root problem
											// taylor 03/11/2006 bumped to 4000, it's going dynamic soon so it should be ok to leave it this high
											//                                   until then.
											// Goober5000 10/8/2006 made dynamic :)
#endif
*/

#define MAX_SEXP_VARIABLES 100

#define    MAX_SEXP_TEXT    2000
#define    MAX_OPERATORS    1024  // Yes, this is used, but not by the Sexp code.

// Operator argument formats (data types of an argument)
#define    OPF_NONE                1        // argument cannot exist at this position if it's this
#define    OPF_NULL                2        // no value.  Can still be used for type matching, however
#define    OPF_BOOL                3
#define    OPF_NUMBER                4
#define    OPF_SHIP                5
#define    OPF_WING                6
#define    OPF_SUBSYSTEM            7
#define    OPF_POINT                8        // either a 3d point in space, or a waypoint name
#define    OPF_IFF                    9
#define    OPF_AI_GOAL                10        // special to match ai goals
#define    OPF_DOCKER_POINT        11        // docking point on docker ship
#define    OPF_DOCKEE_POINT        12        // docking point on dockee ship
#define    OPF_MESSAGE                13        // the name (id) of a message in Messages[] array
#define    OPF_WHO_FROM            14        // who sent the message -- doesn't necessarily have to be a ship!!!
#define    OPF_PRIORITY            15        // priority for messages
#define    OPF_WAYPOINT_PATH        16        // name of a waypoint
#define    OPF_POSITIVE            17        // positive number or zero
#define    OPF_MISSION_NAME        18        // name of a mission for various mission related things
#define    OPF_SHIP_POINT            19        // a waypoint or a ship
#define    OPF_GOAL_NAME            20        // name of goal (or maybe event?) from a mission
#define    OPF_SHIP_WING            21        // either a ship or wing name (they don't conflict)
#define    OPF_SHIP_WING_POINT        22        // name of a ship, wing, or a point
#define    OPF_SHIP_TYPE            23        // type of ship (fighter/bomber/etc)
#define    OPF_KEYPRESS            24        // a default key
#define    OPF_EVENT_NAME            25        // name of an event
#define    OPF_AI_ORDER            26        // a squadmsg order player can give to a ship
#define    OPF_SKILL_LEVEL            27        // current skill level of the game
#define    OPF_MEDAL_NAME            28        // name of medals
#define    OPF_WEAPON_NAME            29        // name of a weapon
#define    OPF_SHIP_CLASS_NAME        30        // name of a ship class
#define    OPF_HUD_GAUGE_NAME        31        // name of HUD gauge
#define    OPF_HUGE_WEAPON            32        // name of a secondary bomb type weapon
#define    OPF_SHIP_NOT_PLAYER        33        // a ship, but not a player ship
#define    OPF_JUMP_NODE_NAME        34        // name of a jump node
#define    OPF_VARIABLE_NAME        35        // variable name
#define    OPF_AMBIGUOUS            36        // type used with variable
#define    OPF_AWACS_SUBSYSTEM        37        // an awacs subsystem
#define OPF_CARGO                38        // Goober5000 - a cargo string (currently used for set-cargo and is-cargo)
#define OPF_AI_CLASS            39        // Goober5000 - an AI class
#define OPF_SUPPORT_SHIP_CLASS    40        // Goober5000 - a support ship class
#define OPF_ARRIVAL_LOCATION    41        // Goober5000 - a ship arrival location
#define OPF_ARRIVAL_ANCHOR_ALL    42        // Goober5000 - all of a ship's possible arrival anchors
#define OPF_DEPARTURE_LOCATION    43        // Goober5000 - a ship departure location
#define OPF_SHIP_WITH_BAY        44        // Goober5000 - a ship with a fighter bay
#define OPF_SOUNDTRACK_NAME        45        // Goober5000 - the name of a music soundtrack
#define OPF_INTEL_NAME            46        // Goober5000 - the name of an intel entry in species.tbl
#define OPF_STRING                47        // Goober5000 - any old string
#define OPF_ROTATING_SUBSYSTEM    48        // Goober5000 - a rotating subsystem
#define OPF_NAV_POINT            49        // Kazan	  - a Nav Point name
#define OPF_SSM_CLASS            50        // Goober5000 - an SSM class
#define OPF_FLEXIBLE_ARGUMENT    51        // Goober5000 - special to match for when-argument
#define OPF_ANYTHING            52        // Goober5000 - anything goes
#define OPF_SKYBOX_MODEL_NAME    53        // taylor - changing skybox model
#define OPF_SHIP_OR_NONE        54        // Goober5000 - an "optional" ship argument
#define OPF_BACKGROUND_BITMAP    55        // phreak - name of a background bitmap
#define OPF_SUN_BITMAP            56        // phreak - name of a background bitmap
#define OPF_NEBULA_STORM_TYPE    57        // phreak - name a nebula storm
#define OPF_NEBULA_POOF            58        // phreak - name of a nebula poof
#define OPF_TURRET_TARGET_ORDER    59        // WMC - name of a turret target type (see aiturret.cpp)
#define OPF_SUBSYSTEM_OR_NONE    60        // Goober5000 - an "optional" subsystem argument
#define OPF_PERSONA                61        // Karajorma - name of a persona
#define OPF_SUBSYS_OR_GENERIC    62        // Karajorma - a subsystem or a generic name (like engine) which covers all subsystems of that type
#define OPF_SHIP_WING_POINT_OR_NONE    63    // WMC - Ship, wing, point or none
#define OPF_ORDER_RECIPIENT        64        // Karajorma - since orders can go to All Fighters as well as a ship or wing
#define OPF_SHIP_WING_TEAM        65        // Karajorma - Ship, wing or an IFF
#define OPF_SUBSYSTEM_TYPE        66        // Goober5000 - a generic subsystem type (navigation, engines, etc.) rather than a specific subsystem
#define OPF_POST_EFFECT            67        // Hery - type of post-processing effect
#define OPF_TARGET_PRIORITIES    68        // FUBAR - Target priority groups
#define OPF_ARMOR_TYPES            69        // FUBAR - Armor type or <none>
#define OPF_HUD_ELEMENT            71        // A magic name of a specific HUD element

// Operand return types
#define    OPR_NUMBER                1    // returns number
#define    OPR_BOOL                2    // returns true/false value
#define    OPR_NULL                3    // doesn't return a value
#define    OPR_AI_GOAL                4    // is an ai operator (doesn't really return a value, but used for type matching)
#define    OPR_POSITIVE            5    // returns a non-negative number
#define    OPR_STRING                6    // not really a return type, but used for type matching.
#define    OPR_AMBIGUOUS            7    // not really a return type, but used for type matching.
#define OPR_FLEXIBLE_ARGUMENT    8    // Goober5000 - is an argument operator (doesn't really return a value, but used for type matching)

#define    OP_INSERT_FLAG            0x8000
#define    OP_REPLACE_FLAG            0x4000
#define    OP_NONCAMPAIGN_FLAG        0x2000
#define    OP_CAMPAIGN_ONLY_FLAG    0x1000

// if we ever have more than 1024 (!)
// total sexps, we're going to have to
// figure out a different way of
// distinguishing between sexp identifier
// and sexp array index
#define    FIRST_OP                0x0400

// IMPORTANT: because of the way
// categories work, no category can
// have more than 256 sexps (mapped
// to 00 through ff) otherwise
// they'll overlap their category)
#define    OP_CATEGORY_OBJECTIVE    0x0400
#define    OP_CATEGORY_TIME        0x0500
#define    OP_CATEGORY_LOGICAL        0x0600
#define    OP_CATEGORY_ARITHMETIC    0x0700
#define    OP_CATEGORY_STATUS        0x0800
#define    OP_CATEGORY_CHANGE        0x0900
#define    OP_CATEGORY_CONDITIONAL    0x0a00
#define    OP_CATEGORY_AI            0x0b00  // used for AI goals
#define    OP_CATEGORY_TRAINING    0x0c00
#define    OP_CATEGORY_UNLISTED    0x0d00
#define OP_CATEGORY_NAVPOINTS    0x0e00
#define    OP_CATEGORY_GOAL_EVENT    0x0f00    // final category can't be higher than 0x0f00,
// to avoid overlap with flags above

#define    OP_CATEGORY_MASK        0x0f00    // 0000111100000000b


// The debug category is obsolete, so
// I removed it.  It originally took the
// place of OP_CATEGORY_CONDITIONAL,
// which was bumped (along with all the
// lower categories) so that FIRST_OP
// could be 0x0400.  This allows for
// 1024 possible sexps, as opposed to
// the 768 possible if the categories
// had not been bumped.
/*
#define	OP_CATEGORY_DEBUG		0x0a00
*/

// New subcategories! :) -- Goober5000
// Adding more subcategories is possible with the new code.  All that needs to be done is
// to add a #define here (a number from 0x0000 to 0x00ff ORred with the category that it
// goes under), some appropriate case statements in get_subcategory() (in sexp.cpp) that
// will return the subcategory for each sexp that uses it, and the submenu name in the
// op_submenu[] array in sexp.cpp.
#define SUBCATEGORY_MASK                                    0x00ff
#define CHANGE_SUBCATEGORY_MESSAGING_AND_MISSION_GOALS        (0x0000 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_AI_AND_IFF                        (0x0001 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SUBSYSTEMS_AND_CARGO                (0x0002 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SHIP_STATUS                        (0x0003 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_BEAMS_AND_TURRETS                (0x0004 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MISSION_AND_CAMPAIGN                (0x0005 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SPECIAL                            (0x0006 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MODELS_AND_TEXTURES                (0x0007 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_COORDINATE_MANIPULATION            (0x0008    | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MUSIC_AND_SOUND                    (0x0009 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_HUD                                (0x000a | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_CUTSCENES                        (0x000b | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_JUMP_NODES                        (0x000c | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_BACKGROUND_AND_NEBULA            (0x000d | OP_CATEGORY_CHANGE)
#define STATUS_SUBCATEGORY_MULTIPLAYER_AND_MISSION_CONFIG    (0x000e | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_SHIELDS_ENGINES_AND_WEAPONS        (0x000f | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_CARGO                            (0x0010 | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_SHIP_STATUS                        (0x0011 | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_DAMAGE                            (0x0012 | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_DISTANCE_AND_COORDINATES            (0x0013 | OP_CATEGORY_STATUS)
#define STATUS_SUBCATEGORY_KILLS_AND_SCORING                (0x0014 | OP_CATEGORY_STATUS)


#define    OP_PLUS                                (0x0000 | OP_CATEGORY_ARITHMETIC)
#define    OP_MINUS                            (0x0001 | OP_CATEGORY_ARITHMETIC)
#define    OP_MOD                                (0x0002 | OP_CATEGORY_ARITHMETIC)
#define    OP_MUL                                (0x0003 | OP_CATEGORY_ARITHMETIC)
#define    OP_DIV                                (0x0004 | OP_CATEGORY_ARITHMETIC)
#define    OP_RAND                                (0x0005 | OP_CATEGORY_ARITHMETIC)
#define OP_ABS                                (0x0006    | OP_CATEGORY_ARITHMETIC)    // Goober5000
#define OP_MIN                                (0x0007    | OP_CATEGORY_ARITHMETIC)    // Goober5000
#define OP_MAX                                (0x0008    | OP_CATEGORY_ARITHMETIC)    // Goober5000
#define OP_AVG                                (0x0009    | OP_CATEGORY_ARITHMETIC)    // Goober5000
#define OP_RAND_MULTIPLE                    (0x000a | OP_CATEGORY_ARITHMETIC)    // Goober5000

#define    OP_TRUE                                (0x0000 | OP_CATEGORY_LOGICAL)
#define    OP_FALSE                            (0x0001 | OP_CATEGORY_LOGICAL)
#define    OP_AND                                (0x0002 | OP_CATEGORY_LOGICAL)
#define    OP_AND_IN_SEQUENCE                    (0x0003 | OP_CATEGORY_LOGICAL)
#define    OP_OR                                (0x0004 | OP_CATEGORY_LOGICAL)
#define    OP_EQUALS                            (0x0005 | OP_CATEGORY_LOGICAL)
#define    OP_GREATER_THAN                        (0x0006 | OP_CATEGORY_LOGICAL)
#define    OP_LESS_THAN                        (0x0007 | OP_CATEGORY_LOGICAL)
#define    OP_HAS_TIME_ELAPSED                    (0x0008 | OP_CATEGORY_LOGICAL | OP_NONCAMPAIGN_FLAG)
#define    OP_NOT                                (0x0009 | OP_CATEGORY_LOGICAL)
#define OP_STRING_EQUALS                    (0x000a | OP_CATEGORY_LOGICAL)
#define OP_STRING_GREATER_THAN                (0x000b | OP_CATEGORY_LOGICAL)
#define OP_STRING_LESS_THAN                    (0x000c | OP_CATEGORY_LOGICAL)

#define    OP_GOAL_INCOMPLETE                    (0x0000 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_GOAL_TRUE_DELAY                    (0x0001 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_GOAL_FALSE_DELAY                    (0x0002 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_EVENT_INCOMPLETE                    (0x0003 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_EVENT_TRUE_DELAY                    (0x0004 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_EVENT_FALSE_DELAY                (0x0005 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define    OP_PREVIOUS_EVENT_TRUE                (0x0006 | OP_CATEGORY_GOAL_EVENT)
#define    OP_PREVIOUS_EVENT_FALSE                (0x0007 | OP_CATEGORY_GOAL_EVENT)
#define    OP_PREVIOUS_GOAL_TRUE                (0x0009 | OP_CATEGORY_GOAL_EVENT)
#define    OP_PREVIOUS_GOAL_FALSE                (0x000a | OP_CATEGORY_GOAL_EVENT)

#define    OP_IS_DESTROYED_DELAY                (0x0000 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_SUBSYSTEM_DESTROYED_DELAY        (0x0001 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_DISABLED_DELAY                (0x0002 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_DISARMED_DELAY                (0x0003 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_HAS_DOCKED_DELAY                    (0x0004 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_HAS_UNDOCKED_DELAY                (0x0005 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_HAS_ARRIVED_DELAY                (0x0006 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_HAS_DEPARTED_DELAY                (0x0007 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_WAYPOINTS_DONE_DELAY                (0x0008 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_SHIP_TYPE_DESTROYED                (0x0009 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_PERCENT_SHIPS_DEPARTED            (0x000a | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_PERCENT_SHIPS_DESTROYED            (0x000b | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_DEPART_NODE_DELAY                (0x000c | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define    OP_DESTROYED_DEPARTED_DELAY            (0x000d | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define OP_PERCENT_SHIPS_DISARMED            (0x000e | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PERCENT_SHIPS_DISABLED            (0x000f | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PERCENT_SHIPS_ARRIVED            (0x0010 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)    // FUBAR-BDHR
#define    OP_WAS_DESTROYED_BY_DELAY            (0x0011 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)  // KeldorKatarn

#define    OP_TIME_SHIP_DESTROYED                (0x0000 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_SHIP_ARRIVED                (0x0001 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_SHIP_DEPARTED                (0x0002 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_WING_DESTROYED                (0x0003 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_WING_ARRIVED                (0x0004 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_WING_DEPARTED                (0x0005 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_MISSION_TIME                        (0x0006 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_DOCKED                        (0x0007 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define    OP_TIME_UNDOCKED                    (0x0008 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)

#define    OP_SHIELDS_LEFT                        (0x0000 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_HITS_LEFT                        (0x0001 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_HITS_LEFT_SUBSYSTEM                (0x0002 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // deprecated
#define    OP_SIM_HITS_LEFT                    (0x0003 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_DISTANCE                            (0x0004 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_DISTANCE_SUBSYSTEM                (0x0005 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define    OP_LAST_ORDER_TIME                    (0x0006 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_NUM_PLAYERS                        (0x0007 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_SKILL_LEVEL_AT_LEAST                (0x0008 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_WAS_PROMOTION_GRANTED            (0x0009 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_WAS_MEDAL_GRANTED                (0x000a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_CARGO_KNOWN_DELAY                (0x000b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_CAP_SUBSYS_CARGO_KNOWN_DELAY        (0x000c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_HAS_BEEN_TAGGED_DELAY            (0x000d | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_TAGGED                        (0x000e | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_NUM_KILLS                        (0x000f | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)

#define    OP_NUM_TYPE_KILLS                    (0x0010 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_NUM_CLASS_KILLS                    (0x0011 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define OP_SHIELD_RECHARGE_PCT                (0x0012 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define OP_ENGINE_RECHARGE_PCT                (0x0013 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define OP_WEAPON_RECHARGE_PCT                (0x0014 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_SHIELD_QUAD_LOW                    (0x0015 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_SECONDARY_AMMO_PCT                (0x0016 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_SECONDARY_SELECTED            (0x0017 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_PRIMARY_SELECTED                (0x0018 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_SPECIAL_WARP_DISTANCE            (0x0019 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_IS_SHIP_VISIBLE                    (0x001a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define    OP_TEAM_SCORE                        (0x001b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define OP_PRIMARY_AMMO_PCT                    (0x001c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_SHIP_STEALTHY                    (0x001d | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_CARGO                            (0x001e | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_FRIENDLY_STEALTH_VISIBLE        (0x001f | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000

#define OP_GET_OBJECT_X                        (0x0020    | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_GET_OBJECT_Y                        (0x0021    | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_GET_OBJECT_Z                        (0x0022    | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_AI_CLASS                        (0x0023 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_SHIP_TYPE                        (0x0024 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_IS_SHIP_CLASS                    (0x0025    | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_NUM_SHIPS_IN_BATTLE                (0x0026 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // phreak
#define OP_CURRENT_SPEED                    (0x0027 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // WMCoolmon
#define OP_IS_IFF                            (0x0028 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_NUM_WITHIN_BOX                    (0x0029 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // WMCoolmon
#define OP_SCRIPT_EVAL_NUM                    (0x002a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // WMCoolmon
#define OP_SCRIPT_EVAL_STRING                (0x002b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // WMCoolmon
#define OP_NUM_SHIPS_IN_WING                (0x002c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)    // Karajorma
#define OP_GET_PRIMARY_AMMO                    (0x002d | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_GET_SECONDARY_AMMO                (0x002e | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define    OP_NUM_ASSISTS                        (0x002f | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma

#define    OP_SHIP_SCORE                        (0x0030 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define    OP_SHIP_DEATHS                        (0x0031 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define    OP_RESPAWNS_LEFT                    (0x0032 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define    OP_IS_PLAYER                        (0x0033 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_GET_DAMAGE_CAUSED                (0x0034 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_AFTERBURNER_LEFT                    (0x0035 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_WEAPON_ENERGY_LEFT                (0x0036 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_PRIMARY_FIRED_SINCE                (0x0037 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SECONDARY_FIRED_SINCE            (0x0038 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_CUTSCENES_GET_FOV                (0x0039 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Echelon9
#define OP_GET_THROTTLE_SPEED                (0x003a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_HITS_LEFT_SUBSYSTEM_GENERIC        (0x003b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_HITS_LEFT_SUBSYSTEM_SPECIFIC        (0x003c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG) // Goober5000


// conditional sexpressions
#define OP_WHEN                                (0x0000 | OP_CATEGORY_CONDITIONAL)
#define OP_WHEN_ARGUMENT                    (0x0001 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_EVERY_TIME                        (0x0002 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_EVERY_TIME_ARGUMENT                (0x0003 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_ANY_OF                            (0x0004 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_EVERY_OF                            (0x0005 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_RANDOM_OF                        (0x0006 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_NUMBER_OF                        (0x0007 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_INVALIDATE_ARGUMENT                (0x0008 | OP_CATEGORY_CONDITIONAL)    // Goober5000
#define OP_RANDOM_MULTIPLE_OF                (0x0009 | OP_CATEGORY_CONDITIONAL)    // Karajorma
#define OP_IN_SEQUENCE                        (0x000a | OP_CATEGORY_CONDITIONAL)    // Karajorma
#define OP_VALIDATE_ARGUMENT                (0x000b | OP_CATEGORY_CONDITIONAL)    // Karajorma
#define OP_DO_FOR_VALID_ARGUMENTS            (0x000c | OP_CATEGORY_CONDITIONAL)    // Karajorma


// sexpressions with side-effects
#define OP_CHANGE_IFF                        (0x0000 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_REPAIR_SUBSYSTEM                    (0x0001 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SABOTAGE_SUBSYSTEM                (0x0002 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_SUBSYSTEM_STRNGTH            (0x0003 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_PROTECT_SHIP                        (0x0004 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_MESSAGE                        (0x0005 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SELF_DESTRUCT                    (0x0006 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CLEAR_GOALS                        (0x0007 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_GOAL                            (0x0008 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_REMOVE_GOAL                        (0x0009 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_INVALIDATE_GOAL                    (0x000a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_VALIDATE_GOAL                    (0x000b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_RANDOM_MESSAGE                (0x000c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TRANSFER_CARGO                    (0x000d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_EXCHANGE_CARGO                    (0x000e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_UNPROTECT_SHIP                    (0x000f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)

#define OP_GOOD_REARM_TIME                    (0x0010 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BAD_REARM_TIME                    (0x0011 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GRANT_PROMOTION                    (0x0012 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GRANT_MEDAL                        (0x0013 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ALLOW_SHIP                        (0x0014 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ALLOW_WEAPON                        (0x0015 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GOOD_SECONDARY_TIME                (0x0016 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_BROKEN                        (0x0017 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_NOT_BROKEN                    (0x0018 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_NEVER                        (0x0019 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_ALLOWED                        (0x001a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_INVISIBLE                    (0x001b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VISIBLE                        (0x001c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_INVULNERABLE                (0x001d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VULNERABLE                    (0x001e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_RED_ALERT                        (0x001f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)

#define OP_TECH_ADD_SHIP                    (0x0020 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TECH_ADD_WEAPON                    (0x0021 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_END_CAMPAIGN                        (0x0022 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_JETTISON_CARGO                    (0x0023 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_MODIFY_VARIABLE                    (0X0024 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_NOP                                (0x0025 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FIRE                        (0x0026 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FREE                        (0x0027 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FREE_ALL                    (0x0028 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_LOCK                        (0x0029 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_LOCK_ALL                    (0x002a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_PROTECT_SHIP                (0x002b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_UNPROTECT_SHIP                (0x002c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_FREE                        (0x002d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_FREE_ALL                    (0x002e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_LOCK                        (0x002f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)

#define OP_TURRET_LOCK_ALL                    (0x0030 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_REMOVE_ESCORT                (0x0031 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_AWACS_SET_RADIUS                    (0x0032 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_MESSAGE_LIST                (0x0033 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CAP_WAYPOINT_SPEED                (0x0034 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_GUARDIAN                    (0x0035 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_NO_GUARDIAN                    (0x0036 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_TAGGED_ONLY_ALL            (0x0037 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_TAGGED_CLEAR_ALL            (0x0038 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SUBSYS_SET_RANDOM                (0x0039 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SUPERNOVA_START                    (0x003a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CARGO_NO_DEPLETE                    (0x003b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_SPECIAL_WARPOUT_NAME            (0X003c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VANISH                        (0X003d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIELDS_ON                        (0x003e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Sesquipedalian
#define OP_SHIELDS_OFF                        (0x003f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Sesquipedalian

#define OP_CHANGE_AI_LEVEL                    (0x0040 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Sesquipedalian
#define OP_END_MISSION                        (0x0041 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //-Sesquipedalian. replaces end-mission-delay, which did nothing
#define OP_SET_SCANNED                        (0x0042 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_UNSCANNED                    (0x0043    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_STEALTHY                    (0x0044    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_UNSTEALTHY                    (0x0045    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_CARGO                        (0x0046    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_CHANGE_AI_CLASS                    (0x0047 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_FRIENDLY_STEALTH_INVISIBLE        (0x0048    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_FRIENDLY_STEALTH_VISIBLE            (0x0049    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_DAMAGED_ESCORT_LIST                (0x004a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_DAMAGED_ESCORT_LIST_ALL            (0x004b    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_VAPORIZE                    (0x004c    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_NO_VAPORIZE                    (0x004d    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_COLLIDE_INVISIBLE                (0x004e    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_DONT_COLLIDE_INVISIBLE            (0x004f    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000

#define OP_PRIMITIVE_SENSORS_SET_RANGE        (0x0050    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_CHANGE_SHIP_CLASS                (0x0051    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SCRIPT_EVAL                        (0x0052 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_SET_SUPPORT_SHIP                    (0x0053 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_DEACTIVATE_GLOW_POINTS            (0x0054    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_ACTIVATE_GLOW_POINTS                (0x0055    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_DEACTIVATE_GLOW_MAPS                (0x0056    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_ACTIVATE_GLOW_MAPS                (0x0057    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_DEACTIVATE_GLOW_POINT_BANK        (0x0058    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_ACTIVATE_GLOW_POINT_BANK            (0x0059    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Bobboau
#define OP_CHANGE_SOUNDTRACK                (0x005a    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_TECH_ADD_INTEL                    (0x005b    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_TECH_RESET_TO_DEFAULT            (0x005c    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_EXPLOSION_EFFECT                    (0x005d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_WARP_EFFECT                        (0x005e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_OBJECT_FACING                (0x005f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000

#define OP_SET_OBJECT_FACING_OBJECT            (0x0060 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_OBJECT_POSITION                (0x0061    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PLAY_SOUND_FROM_TABLE            (0x0062    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PLAY_SOUND_FROM_FILE                (0x0063    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_CLOSE_SOUND_FROM_FILE            (0x0064 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_HUD_DISABLE                        (0x0065    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_KAMIKAZE                            (0x0066 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Sesquipedalian
#define OP_NOT_KAMIKAZE                        (0x0067 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //-Sesquipedalian
#define OP_TURRET_TAGGED_SPECIFIC            (0x0068 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_TURRET_TAGGED_CLEAR_SPECIFIC        (0x0069 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_LOCK_ROTATING_SUBSYSTEM            (0x006a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_FREE_ROTATING_SUBSYSTEM            (0x006b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_REVERSE_ROTATING_SUBSYSTEM        (0x006c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_ROTATING_SUBSYS_SET_TURN_TIME    (0x006d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PLAYER_USE_AI                    (0x006e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_PLAYER_NOT_USE_AI                (0x006f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000

#define OP_HUD_DISABLE_EXCEPT_MESSAGES        (0x0070 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_FORCE_JUMP                        (0x0071 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_HUD_SET_TEXT                        (0x0072 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_HUD_SET_TEXT_NUM                    (0x0073 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_HUD_SET_COORDS                    (0x0074 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_HUD_SET_FRAME                    (0x0075 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_HUD_SET_COLOR                    (0x0076 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //WMC
#define OP_HUD_SET_MAX_TARGETING_RANGE        (0x0077 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_SHIP_TAG                            (0x0078 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_SHIP_UNTAG                        (0x0079 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_SHIP_CHANGE_ALT_NAME                (0x007a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SCRAMBLE_MESSAGES                (0x007b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // phreak
#define OP_UNSCRAMBLE_MESSAGES                (0x007c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // phreak
#define OP_CUTSCENES_SET_CUTSCENE_BARS        (0x007d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_UNSET_CUTSCENE_BARS    (0x007e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_FADE_IN                (0x007f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC

#define OP_CUTSCENES_FADE_OUT                (0x0080 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_CAMERA_POSITION    (0x0081 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_CAMERA_FACING        (0x0082 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_CAMERA_FACING_OBJECT    (0x0083 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_CAMERA_ROTATION    (0x0084 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_FOV                (0x0085 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_RESET_FOV                (0x0086 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_RESET_CAMERA            (0x0087 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SHOW_SUBTITLE            (0x0088 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC / deprecated
#define OP_CUTSCENES_SET_TIME_COMPRESSION    (0x0089 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_RESET_TIME_COMPRESSION    (0x008a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_FORCE_PERSPECTIVE        (0x008b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_JUMP_NODE_SET_JUMPNODE_NAME        (0x008c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_JUMP_NODE_SET_JUMPNODE_COLOR        (0x008d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_JUMP_NODE_SET_JUMPNODE_MODEL        (0x008e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_JUMP_NODE_SHOW_JUMPNODE            (0x008f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC

#define OP_JUMP_NODE_HIDE_JUMPNODE            (0x0090 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_SHIP_GUARDIAN_THRESHOLD            (0x0091 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_SUBSYS_GUARDIAN_THRESHOLD    (0x0092 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_SKYBOX_MODEL                    (0x0093 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // taylor
#define OP_SHIP_CREATE                        (0X0094 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WEAPON_CREATE                    (0x0095    | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_OBJECT_SPEED_X                (0X0096 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_OBJECT_SPEED_Y                (0X0097 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_OBJECT_SPEED_Z                (0X0098 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_MISSION_SET_NEBULA                (0x0099 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_BACKGROUND_BITMAP            (0x009a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_REMOVE_BACKGROUND_BITMAP            (0x009b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_SUN_BITMAP                    (0x009c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_REMOVE_SUN_BITMAP                (0x009d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_NEBULA_CHANGE_STORM                (0x009e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_NEBULA_TOGGLE_POOF                (0x009f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)

#define OP_TURRET_CHANGE_WEAPON                (0x00a0 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_SET_TARGET_ORDER            (0x00a1 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_TURRET_TARGET_ORDER            (0x00a2 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_PRIMARY_AMMO                    (0x00a3 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_SECONDARY_AMMO                (0x00a4 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SHIP_BOMB_TARGETABLE                (0x00a5 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //WMC
#define OP_SHIP_BOMB_UNTARGETABLE            (0x00a6 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    //WMC
#define OP_SHIP_SUBSYS_TARGETABLE            (0x00a7 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SHIP_SUBSYS_UNTARGETABLE            (0x00a8 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_DEATH_MESSAGE                (0x00a9 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_SET_PRIMARY_WEAPON                (0x00aa | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_SECONDARY_WEAPON                (0x00ab | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_DISABLE_BUILTIN_MESSAGES            (0x00ac | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_ENABLE_BUILTIN_MESSAGES            (0x00ad | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_LOCK_PRIMARY_WEAPON                (0x00ae | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_UNLOCK_PRIMARY_WEAPON            (0x00af | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma

#define OP_LOCK_SECONDARY_WEAPON            (0x00b0 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_UNLOCK_SECONDARY_WEAPON            (0x00b1 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_CAMERA_SHUDDER                (0x00b2 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_ALLOW_TREASON                    (0x00b3 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SHIP_COPY_DAMAGE                    (0x00b4 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_CHANGE_SUBSYSTEM_NAME            (0x00b5 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Karajorma
#define OP_SET_PERSONA                        (0x00b6 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_CHANGE_PLAYER_SCORE                (0x00b7 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_CHANGE_TEAM_SCORE                (0x00b8 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_CUTSCENES_SET_CAMERA_FOV            (0x00b9 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // WMC
#define OP_CUTSCENES_SET_CAMERA                (0x00ba | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // WMC
#define OP_CUTSCENES_SET_CAMERA_HOST        (0x00bb | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // WMC
#define OP_CUTSCENES_SET_CAMERA_TARGET        (0x00bc | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // WMC
#define OP_LOCK_AFTERBURNER                    (0x00bd | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_UNLOCK_AFTERBURNER                (0x00bf | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn

#define OP_SET_RESPAWNS                        (0x00c0 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_AFTERBURNER_ENERGY            (0x00c1 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_WEAPON_ENERGY                (0x00c2 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_SHIELD_ENERGY                (0x00c3 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_SET_AMBIENT_LIGHT                (0x00c4 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Karajorma
#define OP_CHANGE_IFF_COLOR                    (0x00c5 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_TURRET_SUBSYS_TARGET_DISABLE        (0x00c6 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_TURRET_SUBSYS_TARGET_ENABLE        (0x00c7 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_REMOVE_WEAPONS                    (0x00c8 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_SHIP_MANEUVER                    (0x00c9 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_SHIP_ROT_MANEUVER                (0x00ca | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_SHIP_LAT_MANEUVER                (0x00cb | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Wanderer
#define OP_GET_VARIABLE_BY_INDEX            (0x00cc | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_SET_VARIABLE_BY_INDEX            (0x00cd | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Goober5000
#define OP_SET_POST_EFFECT                    (0x00ce | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // Hery
#define OP_TURRET_SET_OPTIMUM_RANGE            (0x00cf | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // FUBAR

#define OP_TURRET_SET_DIRECTION_PREFERENCE    (0x00d0 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // FUBAR
#define OP_TURRET_SET_TARGET_PRIORITIES        (0x00d1 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // FUBAR
#define OP_SET_ARMOR_TYPE                    (0x00d2 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // FUBAR
#define OP_CUTSCENES_SHOW_SUBTITLE_TEXT        (0x00d3 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_CUTSCENES_SHOW_SUBTITLE_IMAGE    (0x00d4 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)    // Goober5000
#define OP_MISSION_SET_SUBSPACE                (0x00d5 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_HUD_DISPLAY_GAUGE                (0x00d6 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TRIGGER_ARRIVAL_TRACK            (0x00d7 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_SET_SCANNABLE                    (0x00d8 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_HIDE_SHIP_NAME                    (0x00d9 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_FORCE_BATTLE_MUSIC                (0x00da | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_LOCK_CONTROLS                    (0x00db | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_SET_FORWARD_DECELERATION            (0x00dc | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn
#define OP_ALLOW_DYNAMIC_GOALS                (0x00dd | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) // KeldorKatarn

/* made obsolete by Goober5000
// debugging sexpressions
#define	OP_INT3									(0x0000 | OP_CATEGORY_DEBUG)
*/

// defined for AI goals
#define OP_AI_CHASE                            (0x0000 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DOCK                            (0x0001 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_UNDOCK                        (0x0002 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WARP_OUT                        (0x0003 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WAYPOINTS                        (0x0004 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WAYPOINTS_ONCE                (0x0005 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DESTROY_SUBSYS                (0x0006 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DISABLE_SHIP                    (0x0007 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DISARM_SHIP                    (0x0008 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_GUARD                            (0x0009 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_CHASE_ANY                        (0x000a | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_EVADE_SHIP                    (0x000b | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_STAY_NEAR_SHIP                (0x000c | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_KEEP_SAFE_DISTANCE            (0x000d | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_IGNORE                        (0x000e | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_STAY_STILL                    (0x000f | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_PLAY_DEAD                        (0x0010 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_IGNORE_NEW                    (0x0011 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)    // Goober5000

#define OP_GOALS_ID                            (0x0000 | OP_CATEGORY_UNLISTED)
#define OP_NEXT_MISSION                        (0x0001 | OP_CATEGORY_UNLISTED)        // used in campaign files for branching
#define OP_IS_DESTROYED                        (0x0002 | OP_CATEGORY_UNLISTED)
#define OP_IS_SUBSYSTEM_DESTROYED            (0x0003 | OP_CATEGORY_UNLISTED)
#define OP_IS_DISABLED                        (0x0004 | OP_CATEGORY_UNLISTED)
#define OP_IS_DISARMED                        (0x0005 | OP_CATEGORY_UNLISTED)
#define OP_HAS_DOCKED                        (0x0006 | OP_CATEGORY_UNLISTED)
#define OP_HAS_UNDOCKED                        (0x0007 | OP_CATEGORY_UNLISTED)
#define OP_HAS_ARRIVED                        (0x0008 | OP_CATEGORY_UNLISTED)
#define OP_HAS_DEPARTED                        (0x0009 | OP_CATEGORY_UNLISTED)
#define OP_WAYPOINTS_DONE                    (0x000a | OP_CATEGORY_UNLISTED)
#define OP_ADD_SHIP_GOAL                    (0x000b | OP_CATEGORY_UNLISTED)
#define OP_CLEAR_SHIP_GOALS                    (0x000c | OP_CATEGORY_UNLISTED)
#define OP_ADD_WING_GOAL                    (0x000d | OP_CATEGORY_UNLISTED)
#define OP_CLEAR_WING_GOALS                    (0x000e | OP_CATEGORY_UNLISTED)
#define OP_AI_CHASE_WING                    (0x000f | OP_CATEGORY_UNLISTED)
#define OP_AI_GUARD_WING                    (0x0010 | OP_CATEGORY_UNLISTED)
#define OP_EVENT_TRUE                        (0x0011 | OP_CATEGORY_UNLISTED)
#define OP_EVENT_FALSE                        (0x0012 | OP_CATEGORY_UNLISTED)
#define OP_PREVIOUS_GOAL_INCOMPLETE            (0x0013 | OP_CATEGORY_UNLISTED)
#define OP_PREVIOUS_EVENT_INCOMPLETE        (0x0014 | OP_CATEGORY_UNLISTED)
#define OP_AI_WARP                            (0x0015 | OP_CATEGORY_UNLISTED)
#define OP_IS_CARGO_KNOWN                    (0x0016 | OP_CATEGORY_UNLISTED)
#define OP_COND                                (0x0017 | OP_CATEGORY_UNLISTED)
#define OP_END_OF_CAMPAIGN                    (0x0018 | OP_CATEGORY_UNLISTED)
#define OP_WAS_DESTROYED_BY                    (0x0019 | OP_CATEGORY_UNLISTED)

// nav point sexps
#define OP_NAV_IS_VISITED                    (0x0000 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_DISTANCE                        (0x0001 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_ADD_WAYPOINT                    (0x0002 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_ADD_SHIP                        (0x0003 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_DEL                            (0x0004 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_HIDE                            (0x0005 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_RESTRICT                        (0x0006 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_UNHIDE                        (0x0007 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_UNRESTRICT                    (0x0008 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_SET_VISITED                    (0x0009 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_SET_CARRY                    (0x000a | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_UNSET_CARRY                    (0x000b | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_UNSET_VISITED                (0x000c | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_SET_NEEDSLINK                (0x000d | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_UNSET_NEEDSLINK                (0x000e | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_ISLINKED                        (0x000f | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_USECINEMATICS                (0x0010 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_USEAP                        (0x0011 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // Kazan
#define OP_NAV_SELECT                        (0x0012 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // KeldorKatarn
#define OP_NAV_UNSELECT                        (0x0013 | OP_CATEGORY_NAVPOINTS | OP_NONCAMPAIGN_FLAG)    // KeldorKatarn

// training sexps
#define OP_KEY_PRESSED                        (0x0000 | OP_CATEGORY_TRAINING)
#define OP_KEY_RESET                        (0x0001 | OP_CATEGORY_TRAINING)
#define OP_TARGETED                            (0x0002 | OP_CATEGORY_TRAINING)
#define OP_SPEED                            (0x0003 | OP_CATEGORY_TRAINING)
#define OP_FACING                            (0x0004 | OP_CATEGORY_TRAINING)
#define OP_ORDER                            (0x0005 | OP_CATEGORY_TRAINING)
#define OP_WAYPOINT_MISSED                    (0x0006 | OP_CATEGORY_TRAINING)
#define OP_PATH_FLOWN                        (0x0007 | OP_CATEGORY_TRAINING)
#define OP_WAYPOINT_TWICE                    (0x0008 | OP_CATEGORY_TRAINING)
#define OP_TRAINING_MSG                        (0x0009 | OP_CATEGORY_TRAINING)
#define OP_FLASH_HUD_GAUGE                    (0x000a | OP_CATEGORY_TRAINING)
#define OP_SPECIAL_CHECK                    (0x000b | OP_CATEGORY_TRAINING)
#define OP_SECONDARIES_DEPLETED                (0x000c | OP_CATEGORY_TRAINING)
#define OP_FACING2                            (0x000d | OP_CATEGORY_TRAINING)
#define OP_PRIMARIES_DEPLETED                (0x000e | OP_CATEGORY_TRAINING)    // Goober5000
#define OP_MISSILE_LOCKED                    (0x000f | OP_CATEGORY_TRAINING)    // Sesquipedalian
#define OP_SET_TRAINING_CONTEXT_FLY_PATH    (0x0010 | OP_CATEGORY_TRAINING)
#define OP_SET_TRAINING_CONTEXT_SPEED        (0x0011 | OP_CATEGORY_TRAINING)
#define OP_KEY_RESET_MULTIPLE                (0x0012 | OP_CATEGORY_TRAINING)    // Goober5000
#define OP_STRING_TO_INT                    (0x0013 | OP_CATEGORY_TRAINING) // Karajorma
#define OP_RESET_ORDERS                        (0x0014 | OP_CATEGORY_TRAINING) // Karajorma
#define OP_QUERY_ORDERS                        (0x0015 | OP_CATEGORY_TRAINING) // Karajorma
#define OP_MATCHING_SPEED                    (0x0016 | OP_CATEGORY_TRAINING) // KeldorKatarn

// defines for string constants
#define SEXP_HULL_STRING            "Hull"
#define SEXP_SIM_HULL_STRING        "Simulated Hull"
#define SEXP_ALL_ENGINES_STRING        "<all engines>"
#define SEXP_ALL_TURRETS_STRING        "<all turrets>"
#define SEXP_ARGUMENT_STRING        "<argument>"
#define SEXP_NONE_STRING            "<none>"
#define SEXP_SHIELD_STRING            "Shields"

// macros for accessing sexpression atoms
#define CAR(n)        ((n < 0) ? -1 : Sexp_nodes[n].first)
#define CDR(n)        ((n < 0) ? -1 : Sexp_nodes[n].rest)
#define CADR(n)        CAR(CDR(n))

// #define CTEXT(n)	(Sexp_nodes[n].text)
char *CTEXT(int n);

// added by Goober5000
#define CDDR(n)        CDR(CDR(n))
#define CDDDR(n)    CDR(CDDR(n))
#define CDDDDR(n)    CDR(CDDDR(n))
#define CDDDDDR(n)    CDR(CDDDDR(n))
#define CADDR(n)    CAR(CDDR(n))
#define CADDDR(n)    CAR(CDDDR(n))
#define CADDDDR(n)    CAR(CDDDDR(n))
#define CADDDDDR(n)    CAR(CDDDDDR(n))

#define REF_TYPE_SHIP        1
#define REF_TYPE_WING        2
#define REF_TYPE_PLAYER        3
#define REF_TYPE_WAYPOINT    4
#define REF_TYPE_PATH        5    // waypoint path

#define SRC_SHIP_ARRIVAL    0x10000
#define SRC_SHIP_DEPARTURE    0x20000
#define SRC_WING_ARRIVAL    0x30000
#define SRC_WING_DEPARTURE    0x40000
#define SRC_EVENT                0x50000
#define SRC_MISSION_GOAL    0x60000
#define SRC_SHIP_ORDER        0x70000
#define SRC_WING_ORDER        0x80000
#define SRC_DEBRIEFING        0x90000
#define SRC_BRIEFING            0xa0000
#define SRC_UNKNOWN            0xffff0000
#define SRC_MASK                0xffff0000
#define SRC_DATA_MASK        0xffff

#define SEXP_MODE_GENERAL    0
#define SEXP_MODE_CAMPAIGN    1

// defines for type field of sexp nodes.  The actual type of the node will be stored in the lower
// two bytes of the field.  The upper two bytes will be used for flags (bleah...)
// Be sure not to conflict with type field of sexp_variable
#define SEXP_NOT_USED        0
#define SEXP_LIST                1
#define SEXP_ATOM                2

// flags for sexpressions -- masked onto the end of the type field
#define SEXP_FLAG_PERSISTENT                (1<<31)        // should this sexp node be persistant across missions
#define SEXP_FLAG_VARIABLE                    (1<<30)

// sexp variable definitions
#define SEXP_VARIABLE_CHAR                    ('@')
// defines for type field of sexp_variable.  Be sure not to conflict with type field of sexp_node
#define SEXP_VARIABLE_NUMBER                (1<<4)    //	(0x0010)
#define SEXP_VARIABLE_STRING                (1<<5)    //	(0x0020)
#define SEXP_VARIABLE_UNKNOWN                (1<<6)    //	(0x0040)
#define SEXP_VARIABLE_NOT_USED                (1<<7)    //	(0x0080)

#define SEXP_VARIABLE_BLOCK                    (1<<0)    //	(0x0001)
/*
#define SEXP_VARIABLE_BLOCK_EXP				(1<<1)	//	(0x0002)
#define SEXP_VARIABLE_BLOCK_HIT				(1<<2)	//	(0x0004)
*/
#define SEXP_VARIABLE_PLAYER_PERSISTENT        (1<<3)    //	(0x0008)

// Goober5000 - hopefully this should work and not conflict with anything
#define SEXP_VARIABLE_CAMPAIGN_PERSISTENT    (1<<29)    //	(0x0100)
//Karajorma
#define SEXP_VARIABLE_NETWORK                (1<<28)

#define BLOCK_EXP_SIZE                    6
#define INNER_RAD                            0
#define OUTER_RAD                            1
#define DAMAGE                                2
#define BLAST                                3
#define PROPAGATE                            4
#define SHOCK_SPEED                        5

#define BLOCK_HIT_SIZE                    2
#define SHIELD_STRENGTH                    0
#define HULL_STRENGTH                    1


#define SEXP_VARIABLE_SET                (0x0100)
#define SEXP_VARIABLE_MODIFIED        (0x0200)

#define SEXP_TYPE_MASK(t)    (t & 0x00ff)
#define SEXP_NODE_TYPE(n)    (Sexp_nodes[n].type & 0x00ff)

// defines for subtypes of atoms
#define SEXP_ATOM_LIST            0
#define SEXP_ATOM_OPERATOR        1
#define SEXP_ATOM_NUMBER        2
#define SEXP_ATOM_STRING        3

// defines to short circuit evaluation when possible. Also used when goals can't
// be satisfied yet because ship (or wing) hasn't been created yet.

#define SEXP_TRUE            1
#define SEXP_FALSE            0
// Goober5000: changed these to unlikely values, because now we have sexps using negative numbers
// KeldorKatarn: Goober.. someday I'll kill you for being too stupid to live...
// This is a hack and stays a hack. And a bad one at that.
// At least now the numbers are REALLY unlikely. sigh...
// This would have to be done differntly entirely. One cannot use integer error codes on numbers that can
// have the full integer range. But it's too late to clean up this mess now...
#define SEXP_KNOWN_FALSE    -2147483647    //-1
#define SEXP_KNOWN_TRUE        -2147483646    //-2
#define SEXP_UNKNOWN        -2147483645    //-3
#define SEXP_NAN            -2147483644    //-4	// not a number -- used when ships/wing part of boolean and haven't arrived yet
#define SEXP_NAN_FOREVER    -2147483643    //-5	// not a number and will never change -- used to falsify boolean sexpressions
#define SEXP_CANT_EVAL        -2147483642    //-6	// can't evaluate yet for whatever reason (acts like false)
#define SEXP_NUM_EVAL        -2147483641    //-7	// already completed an arithmetic operation and result is stored

// defines for check_sexp_syntax
#define SEXP_CHECK_NONOP_ARGS            -1            // non-operator has arguments
#define SEXP_CHECK_OP_EXPECTED        -2            // operator expected, but found data instead
#define SEXP_CHECK_UNKNOWN_OP            -3            // unrecognized operator
#define SEXP_CHECK_TYPE_MISMATCH        -4            // return type or data type mismatch
#define SEXP_CHECK_BAD_ARG_COUNT        -5            // argument count in incorrect
#define SEXP_CHECK_UNKNOWN_TYPE        -6            // unrecognized return type of data type

#define SEXP_CHECK_INVALID_NUM                    -101        // number is not valid
#define SEXP_CHECK_INVALID_SHIP                    -102        // invalid ship name
#define SEXP_CHECK_INVALID_WING                    -103        // invalid wing name
#define SEXP_CHECK_INVALID_SUBSYS                -104        // invalid subsystem
#define SEXP_CHECK_INVALID_IFF                    -105        // invalid iff string
#define SEXP_CHECK_INVALID_POINT                    -106        // invalid point
#define SEXP_CHECK_NEGATIVE_NUM                    -107        // negative number wasn't allowed
#define SEXP_CHECK_INVALID_SHIP_WING            -108    // invalid ship/wing
#define SEXP_CHECK_INVALID_SHIP_TYPE            -109    // invalid ship type
#define SEXP_CHECK_UNKNOWN_MESSAGE                -110    // invalid message
#define SEXP_CHECK_INVALID_PRIORITY                -111    // invalid priority for a message
#define SEXP_CHECK_INVALID_MISSION_NAME        -112    // invalid mission name
#define SEXP_CHECK_INVALID_GOAL_NAME            -113    // invalid goal name
#define SEXP_CHECK_INVALID_LEVEL                    -114    // mission level too high in campaign
#define SEXP_CHECK_INVALID_MSG_SOURCE            -115    // invalid 'who-from' for a message being sent
#define SEXP_CHECK_INVALID_DOCKER_POINT        -116
#define SEXP_CHECK_INVALID_DOCKEE_POINT        -117
#define SEXP_CHECK_ORDER_NOT_ALLOWED            -118    // ship goal (order) isn't allowed for given ship
#define SEXP_CHECK_DOCKING_NOT_ALLOWED            -119
#define SEXP_CHECK_NUM_RANGE_INVALID            -120
#define SEXP_CHECK_INVALID_EVENT_NAME            -121
#define SEXP_CHECK_INVALID_SKILL_LEVEL            -122
#define SEXP_CHECK_INVALID_MEDAL_NAME            -123
#define SEXP_CHECK_INVALID_WEAPON_NAME            -124
#define SEXP_CHECK_INVALID_SHIP_CLASS_NAME    -125
#define SEXP_CHECK_INVALID_GAUGE_NAME            -126
#define SEXP_CHECK_INVALID_JUMP_NODE            -127
#define SEXP_CHECK_INVALID_VARIABLE                -128
#define SEXP_CHECK_INVALID_AI_CLASS                -129
#define SEXP_CHECK_UNKNOWN_ERROR                -130
#define SEXP_CHECK_INVALID_SUPPORT_SHIP_CLASS    -131
#define SEXP_CHECK_INVALID_SHIP_WITH_BAY        -132
#define SEXP_CHECK_INVALID_ARRIVAL_LOCATION        -133
#define SEXP_CHECK_INVALID_DEPARTURE_LOCATION    -134
#define SEXP_CHECK_INVALID_ARRIVAL_ANCHOR_ALL    -135
#define SEXP_CHECK_INVALID_SOUNDTRACK_NAME        -136
#define SEXP_CHECK_INVALID_INTEL_NAME            -137
#define SEXP_CHECK_INVALID_SKYBOX_NAME            -138
#define SEXP_CHECK_INVALID_PERSONA_NAME            -139
#define SEXP_CHECK_INVALID_VARIABLE_TYPE        -140
#define SEXP_CHECK_INVALID_SUBSYS_TYPE            -141
#define SEXP_CHECK_INVALID_HUD_ELEMENT            -143

#define TRAINING_CONTEXT_SPEED        (1<<0)
#define TRAINING_CONTEXT_FLY_PATH    (1<<1)

// numbers used in special_training_check() function
#define SPECIAL_CHECK_TRAINING_FAILURE    2000

typedef struct sexp_ai_goal_link {
    int ai_goal;
    int op_code;
} sexp_ai_goal_link;

typedef struct sexp_oper {
    char *text;
    int value;
    int min, max;
} sexp_oper;

typedef struct sexp_node {
    char text[TOKEN_LENGTH];
    int op_index;                // the index in the Operators array for the operator at this node (or -1 if not an operator)
    int type;                        // atom, list, or not used
    int subtype;                    // type of atom or list?
    int first;                    // if first parameter is sexp, index into Sexp_nodes
    int rest;                        // index into Sexp_nodes of rest of parameters
    int value;                    // known to be true, known to be false, or not known
    int flags;                    // Goober5000
} sexp_node;

// Goober5000
#define SNF_ARGUMENT_VALID        (1<<0)
#define SNF_ARGUMENT_SELECT        (1<<1)
#define SNF_DEFAULT_VALUE        SNF_ARGUMENT_VALID

typedef struct sexp_variable {
    int type;
    char text[TOKEN_LENGTH];
    char variable_name[TOKEN_LENGTH];
} sexp_variable;

// Goober5000 - adapted from sexp_list_item in Sexp_tree.h
class arg_item {
public:
    char *text;
    arg_item *next;
    int nesting_level;

    arg_item()
            : text(NULL),
              next(NULL) {}

    void add_data(char *str);

    void expunge();

    int empty();

    arg_item *get_next();

    void clear_nesting_level();
};


// next define used to eventually mark a directive as satisfied even though there may be more
// waves for a wing.  bascially a hack for the directives display.
#define DIRECTIVE_WING_ZERO        -999

// Goober5000 - it's dynamic now
//extern sexp_node Sexp_nodes[MAX_SEXP_NODES];

extern int Num_sexp_nodes;
extern sexp_node *Sexp_nodes;

extern sexp_variable Sexp_variables[MAX_SEXP_VARIABLES];
extern sexp_variable Block_variables[MAX_SEXP_VARIABLES];

extern sexp_oper Operators[];
extern int Num_operators;
extern int Locked_sexp_true, Locked_sexp_false;
extern int Directive_count;
extern int Sexp_useful_number;  // a variable to pass useful info in from external modules
extern char *Sexp_string;
extern int Training_context;
extern int Training_context_speed_min;
extern int Training_context_speed_max;
extern int Training_context_speed_set;
extern int Training_context_speed_timestamp;
extern int Training_context_path;
extern int Training_context_goal_waypoint;
extern int Training_context_at_waypoint;
extern float Training_context_distance;
extern int Players_target;
extern int Players_mlocked;
extern ship_subsys *Players_targeted_subsys;
extern int Players_target_timestamp;
extern int Players_mlocked_timestamp;
extern int Sexp_clipboard;  // used by Fred

extern SCP_vector<int> Current_sexp_operator;

extern void init_sexp();

extern int alloc_sexp(char *text, int type, int subtype, int first, int rest);

extern int find_free_sexp();

extern int free_one_sexp(int num);

extern int free_sexp(int num);

extern int free_sexp2(int num);

extern int dup_sexp_chain(int node);

extern int cmp_sexp_chains(int node1, int node2);

extern int find_sexp_list(int num);

extern int find_parent_operator(int num);

extern int is_sexp_top_level(int node);

// Goober5000 - renamed these to be more clear, to prevent bugs :p
extern int get_operator_index(char *token);

extern int get_operator_const(char *token);

extern int check_sexp_syntax(int node, int return_type = OPR_BOOL, int recursive = 0, int *bad_node = 0/*NULL*/,
                             int mode = 0);

extern int get_sexp_main(void);    //	Returns start node
extern int run_sexp(const char *sexpression); // debug and lua sexps
extern int stuff_sexp_variable_list();

extern int eval_sexp(int cur_node, int referenced_node = -1);

extern int is_sexp_true(int cur_node, int referenced_node = -1);

extern int query_operator_return_type(int op);

extern int query_operator_argument_type(int op, int argnum);

extern void update_sexp_references(char *old_name, char *new_name);

extern void update_sexp_references(char *old_name, char *new_name, int format);

extern int query_referenced_in_sexp(int mode, char *name, int *node);

extern int verify_vector(char *text);

extern void skip_white(char **str);

extern int validate_float(char **str);

extern int build_sexp_string(int cur_node, int level, int mode, int max_len);

extern int sexp_query_type_match(int opf, int opr);

extern char *sexp_error_message(int num);

extern int count_free_sexp_nodes();

// Goober5000
void do_action_for_each_special_argument(int cur_node);

int special_argument_appears_in_sexp_tree(int node);

int special_argument_appears_in_sexp_list(int node);

// functions to change the attributes of an sexpression tree to persistent or not persistent
extern void sexp_unmark_persistent(int n);

extern void sexp_mark_persistent(int n);

extern int waypoint_lookup(char *name);

extern int verify_sexp_tree(int node);

extern int query_sexp_ai_goal_valid(int sexp_ai_goal, int ship);

int query_node_in_sexp(int node, int sexp);

void flush_sexp_tree(int node);

// sexp_variable
void sexp_modify_variable(char *text, int index, bool sexp_callback = true);

int get_index_sexp_variable_from_node(int node);

int get_index_sexp_variable_name(const char *temp_name);

int get_index_sexp_variable_name_special(const char *text);    // Goober5000
bool sexp_replace_variable_names_with_values(char *text, int max_len);    // Goober5000
int get_nth_variable_index(int nth, int variable_type);    // Karajorma
int sexp_variable_count();

int sexp_campaign_persistent_variable_count();    // Goober5000
int sexp_variable_typed_count(int sexp_variables_index, int variable_type); // Karajorma
void sexp_variable_delete(int index);

void sexp_variable_sort();

void sexp_fred_modify_variable(const char *text, const char *var_name, int index, int type);

int sexp_add_variable(const char *text, const char *var_name, int type, int index = -1);

bool generate_special_explosion_block_variables();

int num_block_variables();

bool has_special_explosion_block_index(ship *shipp, int *index);

// Karajorma
void set_primary_ammo(int ship_index, int requested_bank, int requested_ammo, int rearm_limit = -1, bool update = true);

void
set_secondary_ammo(int ship_index, int requested_bank, int requested_ammo, int rearm_limit = -1, bool update = true);


// menu and category stuff
extern int get_subcategory(int sexp_id);

// Goober5000
extern void sexp_music_close();

// Goober5000
extern int Knossos_warp_ani_used;

//WMC - moved here from FRED
typedef struct sexp_help_struct {
    int id;
    char *help;
} sexp_help_struct;

extern sexp_help_struct Sexp_help[];

typedef struct op_menu_struct {
    char *name;
    int id;
} op_menu_struct;

extern op_menu_struct op_menu[];
extern op_menu_struct op_submenu[];

extern int Num_sexp_help;
extern int Num_op_menus;
extern int Num_submenus;

//WMC
//Outputs sexp.html file
bool output_sexps(char *filepath);


void multi_sexp_eval();

/** Global state variables for the hud-display-gauge sexp.
They all should be named Sexp_hud_display_*;
They all should follow the following symantics for the value of the
variable:
=0	don't show
=1	show until canceled
>1	timestamp when gauge should stop showing (set zero when expired)
\sa sexp_hud_display_warpout
*/
extern int Sexp_hud_display_warpout;

#endif
