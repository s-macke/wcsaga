/*
 * Created by Ian "Goober5000" Warfield for the FreeSpace2 Source Code Project.
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 */



#ifndef _DEAD_OBJECT_DOCK_H
#define _DEAD_OBJECT_DOCK_H

#include "globalincs/globals.h"
#include "objectdock.h"


// get the first object in objp's dock list
object *dock_get_first_dead_docked_object(object *objp);

// add objp1 and objp2 to each others' dock lists; currently only called by ai_deathroll_start
void dock_dead_dock_objects(object *objp1, int dockpoint1, object *objp2, int dockpoint2);

// remove objp1 and objp2 from each others' dock lists; currently only called by do_dying_undock_physics
void dock_dead_undock_objects(object *objp1, object *objp2);

#endif    // _DEAD_OBJECT_DOCK_H
