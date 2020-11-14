/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/




#include "object/object.h"
#include "render/3d.h"
#include "mission/missionparse.h"
#include "nebula/neb.h"
#include "ship/ship.h"
#include "render/Frustum.h"



typedef struct sorted_obj
{
	object* obj;					// a pointer to the original object
	float z, min_z, max_z;	// The object's z values relative to viewer
} sorted_obj;

int Num_sorted_objects = 0;
sorted_obj Sorted_objects[MAX_OBJECTS];
int Object_sort_order[MAX_OBJECTS];


// Used to (fairly) quicky find the 8 extreme
// points around an object.
vec3d check_offsets[8] =
{
	{
		{
			{
				-1.0f,
				-1.0f,
				-1.0f
			}
		}
	},
	{
		{
			{
				-1.0f,
				-1.0f,
				1.0f
			}
		}
	},
	{
		{
			{
				-1.0f,
				1.0f,
				-1.0f
			}
		}
	},
	{
		{
			{
				-1.0f,
				1.0f,
				1.0f
			}
		}
	},
	{
		{
			{
				1.0f,
				-1.0f,
				-1.0f
			}
		}
	},
	{
		{
			{
				1.0f,
				-1.0f,
				1.0f
			}
		}
	},
	{
		{
			{
				1.0f,
				1.0f,
				-1.0f
			}
		}
	},
	{
		{
			{
				1.0f,
				1.0f,
				1.0f
			}
		}
	}
};

extern int G3_user_clip;
extern vec3d G3_user_clip_normal;
extern vec3d G3_user_clip_point;

// See if an object is in the view cone.
// Returns:
// 0 if object isn't in the view cone
// 1 if object is in cone 
// This routine could possibly be optimized.  Right now, for an
// offscreen object, it has to rotate 8 points to determine it's
// offscreen.  Not the best considering we're looking at a sphere.
bool obj_in_view_cone(Frustum* frustum, object* objp)
{
	bool behindUserPlane = false;

	if (G3_user_clip)
	{
		behindUserPlane = frustum->sphereBehindPlane(&objp->pos,
			objp->radius, &G3_user_clip_point, &G3_user_clip_normal);
	}

	return !behindUserPlane && frustum->sphereInFrustum(&objp->pos, objp->radius);
}

//int obj_in_view_cone( object * objp )
//{
//	int i;
//	vec3d tmp,pt; 
//	ubyte codes;
//
//// Use this to hack out player for testing.
//// if ( objp == Player_obj ) return 0;
//
//// OLD INCORRECT CODE!!!
////	g3_rotate_vector(&tmp,&objp->pos);
////	codes=g3_code_vector_radius(&tmp, objp->radius);
////	if ( !codes )	{
////		return 1;		// center is in, so return 1
////	}
////	return 0;
//
//// This I commented out because it will quickly out for
//// objects in the center, but cause one more rotation
//// for objects outside the center.  So I figured it
//// would be best to slow down objects inside by a bit
//// and not penalize the offscreen ones, which require
//// 8 rotatations to throw out.
////	g3_rotate_vector(&tmp,&objp->pos);
////	codes=g3_code_vector(&tmp);
////	if ( !codes )	{
////		//mprintf(( "Center is in, so render it\n" ));
////		return 1;		// center is in, so return 1
////	}
//
//	// Center isn't in... are other points?
//
//	ubyte and_codes = 0xff;
//
//	for (i=0; i<8; i++ )	{
//		vm_vec_scale_add( &pt, &objp->pos, &check_offsets[i], objp->radius );
//		codes=g3_rotate_vector(&tmp,&pt);
//		if ( !codes )	{
//			//mprintf(( "A point is inside, so render it.\n" ));
//			return 1;		// this point is in, so return 1
//		}
//		and_codes &= codes;
//	}
//
//	if (and_codes)	{
//		//mprintf(( "All points offscreen, so don't render it.\n" ));
//		return 0;	//all points off screen
//	}
//
//	//mprintf(( "All points inside, so render it, but doesn't need clipping.\n" ));
//	return 1;	
//}


// Sorts all the objects by Z and renders them
extern int Fred_active;
extern int Cmdline_nohtl;
void obj_render_all(void (*render_function)(object* objp), bool* draw_viewer_last)
{
	object* objp;
	int i, j, incr;
	float fog_near, fog_far;
#ifdef DYN_CLIP_DIST
	float closest_obj = Max_draw_distance;
	float farthest_obj = Min_draw_distance;
#endif

	objp = Objects;
	Num_sorted_objects = 0;
	Frustum frustum(Proj_fov, gr_screen.clip_aspect, Min_draw_distance, Max_draw_distance, &Eye_position, &Eye_matrix);
	for (i = 0; i <= Highest_object_index; i++, objp++)
	{
		if ((objp->type != OBJ_NONE) && (objp->flags & OF_RENDERS))
		{
			objp->flags &= ~OF_WAS_RENDERED;

			if (obj_in_view_cone(&frustum, objp))
			{
				sorted_obj* osp = &Sorted_objects[Num_sorted_objects];
				Object_sort_order[Num_sorted_objects] = Num_sorted_objects;
				Num_sorted_objects++;

				osp->obj = objp;
				vec3d to_obj;
				vm_vec_sub(&to_obj, &objp->pos, &Eye_position);
				osp->z = vm_vec_dot(&Eye_matrix.vec.fvec, &to_obj);
				/*
								if ( objp->type == OBJ_SHOCKWAVE )
									osp->z -= 2*objp->radius;
				*/
				// Make warp in effect draw after any ship in it
				if (objp->type == OBJ_FIREBALL)
				{
					//if ( fireball_is_warp(objp) )	{
					osp->z -= 2 * objp->radius;
					//}
				}

				osp->min_z = osp->z - objp->radius;
				osp->max_z = osp->z + objp->radius;
#ifdef DYN_CLIP_DIST
				if(objp != Viewer_obj)
				{
					if(osp->min_z < closest_obj)
						closest_obj = osp->min_z;
					if(osp->max_z > farthest_obj)
						farthest_obj = osp->max_z;
				}
#endif
			}
		}
	}

	if (!Num_sorted_objects)
		return;

#ifdef DYN_CLIP_DIST
	if (!Cmdline_nohtl)
	{
		if(closest_obj < Min_draw_distance)
			closest_obj = Min_draw_distance;
		if(farthest_obj > Max_draw_distance)
			farthest_obj = Max_draw_distance;

		gr_set_proj_matrix(Proj_fov, gr_screen.clip_aspect, closest_obj, farthest_obj);
		gr_set_view_matrix(&Eye_position, &Eye_matrix);
	}
#endif


	// Sort them by their maximum z value
	if (Num_sorted_objects > 1)
	{
		incr = Num_sorted_objects / 2;
		while (incr > 0)
		{
			for (i = incr; i < Num_sorted_objects; i++)
			{
				j = i - incr;
				while (j >= 0)
				{
					// compare element j and j+incr
					if ((Sorted_objects[Object_sort_order[j]].max_z < Sorted_objects[Object_sort_order[j +
						 incr]].max_z))
					{
						// If not in correct order, them swap 'em
						int tmp;
						tmp = Object_sort_order[j];
						Object_sort_order[j] = Object_sort_order[j + incr];
						Object_sort_order[j + incr] = tmp;
						j -= incr;
					}
					else
					{
						break;
					}
				}
			}
			incr = incr / 2;
		}
	}

	gr_zbuffer_set(GR_ZBUFF_FULL);

	// now draw them
	for (i = 0; i < Num_sorted_objects; i++)
	{
		sorted_obj* os = &Sorted_objects[Object_sort_order[i]];
		os->obj->flags |= OF_WAS_RENDERED;
		//This is for ship cockpits. Bobb, feel free to optimize this any way you see fit
		if (os->obj == Viewer_obj
			&& os->obj->type == OBJ_SHIP
			&& (!Viewer_mode || (Viewer_mode & VM_PADLOCK_ANY) || (Viewer_mode & VM_OTHER_SHIP) || (Viewer_mode &
																									VM_TRACK))
			&& (Ship_info[Ships[os->obj->instance].ship_info_index].flags2 & SIF2_SHOW_SHIP_MODEL))
		{
			(*draw_viewer_last) = true;
			continue;
		}

		// if we're fullneb, fire up the fog - this also generates a fog table
		if ((The_mission.flags & MISSION_FLAG_FULLNEB) && (Neb2_render_mode != NEB2_RENDER_NONE) && !Fred_running)
		{
			// get the fog values
			neb2_get_fog_values(&fog_near, &fog_far, os->obj);

			// only reset fog if the fog mode has changed - since regenerating a fog table takes
			// a bit of time
			if ((fog_near != gr_screen.fog_near) || (fog_far != gr_screen.fog_far))
			{
				gr_fog_set(GR_FOGMODE_FOG, gr_screen.current_fog_color.red, gr_screen.current_fog_color.green,
					gr_screen.current_fog_color.blue, fog_near, fog_far);
			}

			// maybe skip rendering an object because its obscured by the nebula
			if (neb2_skip_render(os->obj, os->z))
			{
				continue;
			}
		}

		(*render_function)(os->obj);
	}

	//WMC - draw maneuvering thrusters
	extern void batch_render_man_thrusters();
	batch_render_man_thrusters();

	// if we're fullneb, switch off the fog effet
	if ((The_mission.flags & MISSION_FLAG_FULLNEB) && (Neb2_render_mode != NEB2_RENDER_NONE))
	{
		gr_fog_set(GR_FOGMODE_NONE, 0, 0, 0);
	}

	//	if(!Cmdline_nohtl)gr_set_lighting(false,false);
	// lasers have to be drawn without fog! - taylor
	batch_render_lasers();

	/*	Show spheres where wingmen should be flying
		{
			extern void render_wing_phantoms_all();
			render_wing_phantoms_all();
		}
		*/
}

