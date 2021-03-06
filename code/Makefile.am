## code/Makefile.am for fs2_open
##
## $Id: Makefile.am,v 1.31.2.10 2007-11-22 04:52:12 taylor Exp $


EXTRA_DIST =	\
	freespace2/app_icon.ico	\
	freespace2/freespace.rc	\
	freespace2/freespaceresource.h	\
	freespace2/goal_com.bmp	\
	freespace2/goal_fail.bmp	\
	freespace2/goal_inc.bmp	\
	freespace2/goal_none.bmp	\
	freespace2/goal_ord.bmp	\
	sound/phrases.xml

# D_ variants are defaults and should always be used
# FS2_ variants are for game building and wxFRED
AM_CXXFLAGS = @D_CFLAGS@ @FS2_CXXFLAGS@ -I../lua
AM_LDFLAGS = @D_LDFLAGS@ @FS2_LDFLAGS@

noinst_LIBRARIES = libcode.a
noinst_PROGRAMS = @FS2_BINARY@

EXTRA_PROGRAMS = fs2_open_r fs2_open_d

###############################################################################
##
## Begin CORE library
##

FS2_SOURCES =	\
	ai/ai.cpp	\
	ai/ai.h	\
	ai/aibig.cpp	\
	ai/aibig.h	\
	ai/aicode.cpp	\
	ai/aigoals.cpp	\
	ai/aigoals.h	\
	ai/aiinternal.h	\
	ai/ailocal.h	\
	ai/aiturret.cpp	\
	ai/ai_profiles.cpp	\
	ai/ai_profiles.h	\
	anim/animplay.cpp	\
	anim/animplay.h	\
	anim/packunpack.cpp	\
	anim/packunpack.h	\
	asteroid/asteroid.cpp	\
	asteroid/asteroid.h	\
	autopilot/autopilot.cpp	\
	autopilot/autopilot.h	\
	bmpman/bm_internal.h	\
	bmpman/bmpman.cpp	\
	bmpman/bmpman.h	\
	camera/camera.cpp	\
	camera/camera.h	\
	cfile/cfile.cpp	\
	cfile/cfile.h	\
	cfile/cfilearchive.cpp	\
	cfile/cfilearchive.h	\
	cfile/cfilelist.cpp	\
	cfile/cfilesystem.cpp	\
	cfile/cfilesystem.h	\
	cmdline/cmdline.cpp	\
	cmdline/cmdline.h	\
	cmeasure/cmeasure.cpp	\
	cmeasure/cmeasure.h	\
	controlconfig/controlsconfig.cpp	\
	controlconfig/controlsconfig.h	\
	controlconfig/controlsconfigcommon.cpp	\
	cutscene/cutscenes.cpp	\
	cutscene/cutscenes.h	\
	cutscene/decoder16.cpp	\
	cutscene/decoder8.cpp	\
	cutscene/movie.cpp	\
	cutscene/movie.h	\
	cutscene/mve_audio.cpp	\
	cutscene/mvelib.cpp	\
	cutscene/mvelib.h	\
	cutscene/mveplayer.cpp	\
	cutscene/oggplayer.cpp	\
	cutscene/oggplayer.h	\
	cutscene/OggReader.cpp	\
	cutscene/OggReader.h	\
	ddsutils/ddsutils.cpp	\
	ddsutils/ddsutils.h	\
	debris/debris.cpp	\
	debris/debris.h	\
	debugconsole/console.cpp	\
	debugconsole/dbugfile.h	\
	debugconsole/timerbar.cpp	\
	debugconsole/timerbar.h	\
	decals/decals.cpp	\
	decals/decals.h	\
	demo/demo.cpp	\
	demo/demo.h	\
	exceptionhandler/exceptionhandler.cpp	\
	exceptionhandler/exceptionhandler.h	\
	external_dll/externalcode.h		\
	external_dll/trackirglobal.cpp	\
	external_dll/trackirglobal.h	\
	fireball/fireballs.cpp	\
	fireball/fireballs.h	\
	fireball/warpineffect.cpp	\
	fs2netd/fs2netd_client.cpp	\
	fs2netd/fs2netd_client.h	\
	fs2netd/tcp_client.cpp	\
	fs2netd/tcp_client.h	\
	fs2netd/tcp_socket.cpp	\
	fs2netd/tcp_socket.h	\
	fs2netd/protocol.h	\
	gamehelp/contexthelp.cpp	\
	gamehelp/contexthelp.h	\
	gamehelp/gameplayhelp.cpp	\
	gamehelp/gameplayhelp.h	\
	gamesequence/gamesequence.cpp	\
	gamesequence/gamesequence.h	\
	globalincs/alphacolors.cpp	\
	globalincs/alphacolors.h	\
	globalincs/crypt.cpp	\
	globalincs/crypt.h	\
	globalincs/def_files.cpp	\
	globalincs/def_files.h	\
	globalincs/globals.h	\
	globalincs/linklist.h	\
	globalincs/pstypes.h	\
	globalincs/safe_strings.cpp	\
	globalincs/safe_strings.h	\
	globalincs/safe_strings_test.cpp	\
	globalincs/systemvars.cpp	\
	globalincs/systemvars.h	\
	globalincs/version.cpp	\
	globalincs/version.h	\
	graphics/2d.cpp	\
	graphics/2d.h	\
	graphics/font.cpp	\
	graphics/font.h	\
	graphics/generic.cpp	\
	graphics/generic.h	\
	graphics/grbatch.cpp	\
	graphics/grbatch.h	\
	graphics/grinternal.h	\
	graphics/gropengl.cpp	\
	graphics/gropengl.h	\
	graphics/gropenglbmpman.cpp	\
	graphics/gropenglbmpman.h	\
	graphics/gropengldraw.cpp	\
	graphics/gropengldraw.h	\
	graphics/gropenglextension.cpp	\
	graphics/gropenglextension.h	\
	graphics/gropengllight.cpp	\
	graphics/gropengllight.h	\
	graphics/gropenglpostprocessing.cpp	\
	graphics/gropenglpostprocessing.h	\
	graphics/gropenglshader.cpp	\
	graphics/gropenglshader.h	\
	graphics/gropenglstate.cpp	\
	graphics/gropenglstate.h	\
	graphics/gropengltexture.cpp	\
	graphics/gropengltexture.h	\
	graphics/gropengltnl.cpp	\
	graphics/gropengltnl.h	\
	graphics/grstub.cpp	\
	graphics/grstub.h	\
	graphics/line.h	\
	graphics/tmapper.h	\
	hud/hud.cpp	\
	hud/hud.h	\
	hud/hudartillery.cpp	\
	hud/hudartillery.h	\
	hud/hudbrackets.cpp	\
	hud/hudbrackets.h	\
	hud/hudconfig.cpp	\
	hud/hudconfig.h	\
	hud/hudescort.cpp	\
	hud/hudescort.h	\
	hud/hudets.cpp	\
	hud/hudets.h	\
	hud/hudgauges.h	\
	hud/hudlock.cpp	\
	hud/hudlock.h	\
	hud/hudmessage.cpp	\
	hud/hudmessage.h	\
	hud/hudnavigation.cpp	\
	hud/hudnavigation.h	\
	hud/hudobserver.cpp	\
	hud/hudobserver.h	\
	hud/hudparse.cpp	\
	hud/hudparse.h	\
	hud/hudresource.h	\
	hud/hudreticle.cpp	\
	hud/hudreticle.h	\
	hud/hudshield.cpp	\
	hud/hudshield.h	\
	hud/hudsquadmsg.cpp	\
	hud/hudsquadmsg.h	\
	hud/hudtarget.cpp	\
	hud/hudtarget.h	\
	hud/hudtargetbox.cpp	\
	hud/hudtargetbox.h	\
	hud/hudwingmanstatus.cpp	\
	hud/hudwingmanstatus.h	\
	iff_defs/iff_defs.cpp	\
	iff_defs/iff_defs.h	\
	inetfile/cftp.cpp	\
	inetfile/cftp.h	\
	inetfile/chttpget.cpp	\
	inetfile/chttpget.h	\
	inetfile/inetgetfile.cpp	\
	inetfile/inetgetfile.h	\
	io/key.cpp	\
	io/key.h	\
	io/keycontrol.cpp	\
	io/keycontrol.h	\
	io/mouse.cpp	\
	io/mouse.h	\
	io/timer.cpp	\
	io/timer.h	\
	jpgutils/jpgutils.cpp	\
	jpgutils/jpgutils.h	\
	jumpnode/jumpnode.cpp	\
	jumpnode/jumpnode.h	\
	lab/lab.cpp	\
	lab/lab.h	\
	lab/wmcgui.cpp	\
	lab/wmcgui.h	\
	lighting/lighting.cpp	\
	lighting/lighting.h	\
	localization/fhash.cpp	\
	localization/fhash.h	\
	localization/localize.cpp	\
	localization/localize.h	\
	math/fix.cpp	\
	math/fix.h	\
	math/floating.cpp	\
	math/floating.h	\
	math/fvi.cpp	\
	math/fvi.h	\
	math/spline.cpp	\
	math/spline.h	\
	math/staticrand.cpp	\
	math/staticrand.h	\
	math/vecmat.cpp	\
	math/vecmat.h	\
	menuui/barracks.cpp	\
	menuui/barracks.h	\
	menuui/credits.cpp	\
	menuui/credits.h	\
	menuui/fishtank.cpp	\
	menuui/fishtank.h	\
	menuui/mainhallmenu.cpp	\
	menuui/mainhallmenu.h	\
	menuui/mainhalltemp.cpp	\
	menuui/mainhalltemp.h	\
	menuui/optionsmenu.cpp	\
	menuui/optionsmenu.h	\
	menuui/optionsmenumulti.cpp	\
	menuui/optionsmenumulti.h	\
	menuui/playermenu.cpp	\
	menuui/playermenu.h	\
	menuui/readyroom.cpp	\
	menuui/readyroom.h	\
	menuui/snazzyui.cpp	\
	menuui/snazzyui.h	\
	menuui/techmenu.cpp	\
	menuui/techmenu.h	\
	menuui/trainingmenu.cpp	\
	menuui/trainingmenu.h	\
	mission/missionbriefcommon.cpp	\
	mission/missionbriefcommon.h	\
	mission/missioncampaign.cpp	\
	mission/missioncampaign.h	\
	mission/missiongoals.cpp	\
	mission/missiongoals.h	\
	mission/missiongrid.cpp	\
	mission/missiongrid.h	\
	mission/missionhotkey.cpp	\
	mission/missionhotkey.h	\
	mission/missionload.cpp	\
	mission/missionload.h	\
	mission/missionlog.cpp	\
	mission/missionlog.h	\
	mission/missionmessage.cpp	\
	mission/missionmessage.h	\
	mission/missionparse.cpp	\
	mission/missionparse.h	\
	mission/missiontraining.cpp	\
	mission/missiontraining.h	\
	missionui/chatbox.cpp	\
	missionui/chatbox.h	\
	missionui/fictionviewer.cpp	\
	missionui/fictionviewer.h	\
	missionui/missionbrief.cpp	\
	missionui/missionbrief.h	\
	missionui/missioncmdbrief.cpp	\
	missionui/missioncmdbrief.h	\
	missionui/missiondebrief.cpp	\
	missionui/missiondebrief.h	\
	missionui/missionloopbrief.cpp	\
	missionui/missionloopbrief.h	\
	missionui/missionpause.cpp	\
	missionui/missionpause.h	\
	missionui/missionrecommend.cpp	\
	missionui/missionrecommend.h	\
	missionui/missionscreencommon.cpp	\
	missionui/missionscreencommon.h	\
	missionui/missionshipchoice.cpp	\
	missionui/missionshipchoice.h	\
	missionui/missionstats.cpp	\
	missionui/missionstats.h	\
	missionui/missionweaponchoice.cpp	\
	missionui/missionweaponchoice.h	\
	missionui/redalert.cpp	\
	missionui/redalert.h	\
	model/model.h	\
	model/modelanim.cpp	\
	model/modelanim.h	\
	model/modelcollide.cpp	\
	model/modelinterp.cpp	\
	model/modelsinc.h	\
	model/modeloctant.cpp	\
	model/modelread.cpp	\
	nebula/neb.cpp	\
	nebula/neb.h	\
	nebula/neblightning.cpp	\
	nebula/neblightning.h	\
	network/chat_api.cpp	\
	network/chat_api.h	\
	network/multi.cpp	\
	network/multi.h	\
	network/multilag.cpp	\
	network/multilag.h	\
	network/multimsgs.cpp	\
	network/multimsgs.h	\
	network/multiteamselect.cpp	\
	network/multiteamselect.h	\
	network/multiui.cpp	\
	network/multiui.h	\
	network/multiutil.cpp	\
	network/multiutil.h	\
	network/multi_campaign.cpp	\
	network/multi_campaign.h	\
	network/multi_data.cpp	\
	network/multi_data.h	\
	network/multi_dogfight.cpp	\
	network/multi_dogfight.h	\
	network/multi_endgame.cpp	\
	network/multi_endgame.h	\
	network/multi_ingame.cpp	\
	network/multi_ingame.h	\
	network/multi_kick.cpp	\
	network/multi_kick.h	\
	network/multi_log.cpp	\
	network/multi_log.h	\
	network/multi_obj.cpp	\
	network/multi_obj.h	\
	network/multi_observer.cpp	\
	network/multi_observer.h	\
	network/multi_oo.h	\
	network/multi_options.cpp	\
	network/multi_options.h	\
	network/multi_pause.cpp	\
	network/multi_pause.h	\
	network/multi_pinfo.cpp	\
	network/multi_pinfo.h	\
	network/multi_ping.cpp	\
	network/multi_ping.h	\
	network/multi_pmsg.cpp	\
	network/multi_pmsg.h	\
	network/multi_pxo.cpp	\
	network/multi_pxo.h	\
	network/multi_rate.cpp	\
	network/multi_rate.h	\
	network/multi_respawn.cpp	\
	network/multi_respawn.h	\
	network/multi_sexp.cpp	\
	network/multi_sexp.h	\
	network/multi_team.cpp	\
	network/multi_team.h	\
	network/multi_update.h	\
	network/multi_voice.cpp	\
	network/multi_voice.h	\
	network/multi_xfer.cpp	\
	network/multi_xfer.h	\
	network/psnet.cpp	\
	network/psnet.h	\
	network/psnet2.cpp	\
	network/psnet2.h	\
	network/stand_gui.cpp	\
	network/stand_gui-unix.cpp	\
	network/stand_gui.h	\
	object/collidedebrisship.cpp	\
	object/collidedebrisweapon.cpp	\
	object/collideshipship.cpp	\
	object/collideshipweapon.cpp	\
	object/collideweaponweapon.cpp	\
	object/deadobjectdock.cpp	\
	object/deadobjectdock.h	\
	object/objcollide.cpp	\
	object/objcollide.h	\
	object/objectdock.cpp	\
	object/objectdock.h	\
	object/object.cpp	\
	object/object.h	\
	object/objectshield.cpp	\
	object/objectshield.h	\
	object/objectsort.cpp	\
	object/parseobjectdock.cpp	\
	object/parseobjectdock.h	\
	object/waypoint.cpp	\
	object/waypoint.h	\
	observer/observer.cpp	\
	observer/observer.h	\
	palman/palman.cpp	\
	palman/palman.h	\
	parse/encrypt.cpp	\
	parse/encrypt.h	\
	parse/lua.cpp	\
	parse/lua.h	\
	parse/parselo.cpp	\
	parse/parselo.h	\
	parse/scripting.cpp	\
	parse/scripting.h	\
	parse/sexp.cpp	\
	parse/sexp.h	\
	particle/particle.cpp	\
	particle/particle.h	\
	pcxutils/pcxutils.cpp	\
	pcxutils/pcxutils.h	\
	pngutils/pngutils.cpp	\
	pngutils/pngutils.h	\
	physics/physics.cpp	\
	physics/physics.h	\
	playerman/managepilot.cpp	\
	playerman/managepilot.h	\
	playerman/player.h	\
	playerman/playercontrol.cpp	\
	popup/popup.cpp	\
	popup/popup.h	\
	popup/popupdead.cpp	\
	popup/popupdead.h	\
	radar/radar.cpp	\
	radar/radar.h	\
	radar/radarorb.cpp	\
	radar/radarorb.h	\
	radar/radarsetup.cpp	\
	radar/radarsetup.h	\
	render/3d.h	\
	render/3dclipper.cpp	\
	render/3ddraw.cpp	\
	render/3dinternal.h	\
	render/3dlaser.cpp	\
	render/3dmath.cpp	\
	render/3dsetup.cpp	\
 	render/Frustum.cpp	\
	ship/afterburner.cpp	\
	ship/afterburner.h	\
	ship/awacs.cpp	\
	ship/awacs.h	\
	ship/shield.cpp	\
	ship/ship.cpp	\
	ship/ship.h	\
	ship/shipcontrails.cpp	\
	ship/shipcontrails.h	\
	ship/shipfx.cpp	\
	ship/shipfx.h	\
	ship/shiphit.cpp	\
	ship/shiphit.h	\
	ship/subsysdamage.h	\
	species_defs/species_defs.cpp	\
	species_defs/species_defs.h	\
	starfield/nebula.cpp	\
	starfield/nebula.h	\
	starfield/starfield.cpp	\
	starfield/starfield.h	\
	starfield/supernova.cpp	\
	starfield/supernova.h	\
	stats/medals.cpp	\
	stats/medals.h	\
	stats/scoring.cpp	\
	stats/scoring.h	\
	stats/stats.cpp	\
	stats/stats.h	\
	tgautils/tgautils.cpp	\
	tgautils/tgautils.h	\
	ui/button.cpp	\
	ui/checkbox.cpp	\
	ui/gadget.cpp	\
	ui/icon.cpp	\
	ui/inputbox.cpp	\
	ui/keytrap.cpp	\
	ui/listbox.cpp	\
	ui/radio.cpp	\
	ui/scroll.cpp	\
	ui/slider.cpp	\
	ui/slider2.cpp	\
	ui/ui.h	\
	ui/uidefs.h	\
	ui/uidraw.cpp	\
	ui/uimouse.cpp	\
	ui/window.cpp	\
	weapon/beam.cpp	\
	weapon/beam.h	\
	weapon/corkscrew.cpp	\
	weapon/corkscrew.h	\
	weapon/emp.cpp	\
	weapon/emp.h	\
	weapon/flak.cpp	\
	weapon/flak.h	\
	weapon/muzzleflash.cpp	\
	weapon/muzzleflash.h	\
	weapon/shockwave.cpp	\
	weapon/shockwave.h	\
	weapon/swarm.cpp	\
	weapon/swarm.h	\
	weapon/trails.cpp	\
	weapon/trails.h	\
	weapon/weapons.cpp	\
	weapon/weapon.h

## conditional includes follow:

## joystic support sources
if FS2_OS_WIN32
JOY_SOURCES =	\
	io/joy.cpp	\
	io/joy.h	\
	io/joy_ff.cpp	\
	io/joy_ff.h	\
	io/sw_error.hpp	\
	io/sw_force.h	\
	io/sw_guid.hpp	\
	io/swff_lib.cpp
endif

if FS2_OS_UNIX
JOY_SOURCES =	\
	io/joy.h	\
	io/joy_ff.h	\
	io/joy-unix.cpp
endif

## sound support sources
if FS2_SOUND
SOUND_SOURCES =	\
	gamesnd/eventmusic.cpp	\
	gamesnd/eventmusic.h	\
	gamesnd/gamesnd.cpp	\
	gamesnd/gamesnd.h	\
	object/objectsnd.cpp	\
	object/objectsnd.h	\
	sound/ogg/ogg.cpp	\
	sound/ogg/ogg.h	\
	sound/audiostr-openal.cpp	\
	sound/audiostr.cpp	\
	sound/audiostr.h	\
	sound/acm-openal.cpp	\
	sound/acm.h	\
	sound/ds.cpp	\
	sound/ds.h	\
	sound/ds3d.cpp	\
	sound/ds3d.h	\
	sound/dscap.cpp	\
	sound/dscap.h	\
	sound/rbaudio.cpp	\
	sound/rbaudio.h	\
	sound/rtvoice.cpp	\
	sound/rtvoice.h	\
	sound/sound.cpp	\
	sound/sound.h	\
	vcodec/codec1.cpp	\
	vcodec/codec1.h	\
	sound/fsspeech.cpp	\
	sound/fsspeech.h	\
	sound/speech.cpp	\
	sound/speech.h	\
	sound/voicerec.cpp	\
	sound/voicerec.h
endif

## Win32-specific sources
if FS2_OS_WIN32
WIN32_SOURCES =	\
	directx/vasync.h	\
	directx/vd3dtypes.h	\
	directx/vddraw.h	\
	directx/vdinput.h	\
	directx/vdplay.h	\
	directx/vdplobby.h	\
	directx/vdsetup.h	\
	directx/vdsound.h	\
	directx/vdvp.h	\
	globalincs/windebug.cpp	\
	graphics/gl/GLAUX.H	\
	graphics/gl/GLU.H	\
	graphics/gl/Gl.h	\
	graphics/gl/Glext.h	\
	graphics/gl/wglext.h	\
	osapi/monopub.h	\
	osapi/osapi.cpp	\
	osapi/osapi.h	\
	osapi/osregistry.cpp	\
	osapi/osregistry.h	\
	osapi/outwnd.cpp	\
	osapi/outwnd.h
endif

## Unix-specific sources
if FS2_OS_UNIX
UNIX_SOURCES =	\
	osapi/osapi_unix.cpp	\
	osapi/osapi.h	\
	osapi/osregistry_unix.cpp	\
	osapi/osregistry.h	\
	osapi/outwnd_unix.cpp	\
	osapi/outwnd.h	\
	windows_stub/stubs.cpp	\
	windows_stub/config.h
endif


## libcode.a
libcode_a_SOURCES = ${FS2_SOURCES} ${JOY_SOURCES} ${SOUND_SOURCES}	\
	${WIN32_SOURCES} ${UNIX_SOURCES}

##
## End CODE library
##
###############################################################################

###############################################################################
##
## Begin MAIN fs2 binary
##

FS2OPEN_SOURCES = \
	freespace2/freespace.cpp	\
	freespace2/freespace.h	\
	freespace2/levelpaging.cpp	\
	freespace2/levelpaging.h

fs2_open_d_SOURCES =	\
	${FS2OPEN_SOURCES}

fs2_open_r_SOURCES =	\
	${FS2OPEN_SOURCES}

fs2_open_d_LDADD = libcode.a ../libjpeg/libjpeg.a ../lua/liblua.a
fs2_open_r_LDADD = libcode.a ../libjpeg/libjpeg.a ../lua/liblua.a

##
## End MAIN binary
##
###############################################################################
