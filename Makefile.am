# Makefile.am for fs2_open (top level)
#
# This file uses GNU Automake to generate makefiles

SUBDIRS = code

EXTRA_DIST = FS2OpenSCPReadMe.doc

# D_ variants are defaults and should always be used
AM_CXXFLAGS = -I./code @D_CFLAGS@
AM_LDFLAGS = @D_LDFLAGS@

EXTRA_PROGRAMS = cryptstring

###############################################################################
##
## Begin utilitites
##

# cryptstring -- to encrypt strings that are used as cheat codes
cryptstring_SOURCES =	\
	code/cryptstring/cryptstring.cpp

# catch all to build utilitites
tools: cryptstring

# cleaning
clean-tools:
	-test -z "$(EXTRA_PROGRAMS)" || rm -f $(EXTRA_PROGRAMS)

##
## End utilitites
##
###############################################################################


# make sure we get this stuff cleaned up
clean-generic: clean-tools

