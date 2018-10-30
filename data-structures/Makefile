#RD3 10.12.2014
include ../Makefile.header

MODULE = utils
CFILE_ROOTS = scheduler task uuid pq queue srt_list dlist slist barr dyn_vec foo circ_buf stack vsm fsm
CXXFILE_ROOTS =

# for .h files that don't have a .c or test*.c file:
STAND_ALONE_H_FILES= #
STAND_ALONE_CXXH_FILES =
#STAND_ALONE_H_FILES=global_constants.h

# PROJ_LIBS is stuff we wrote that can be debugged and have a *.dbg version
PROJ_LIBS = -l$(MODULE)
# can be expanded as follows:
#PROJ_LIBS = -l$(MODULE) -lwatchdog -lsomeotherthingwewrote

# LIBS is the regular LIBS var of all LIBS we need to link with
# can be expanded as follows:
LIBS = -lm -lpthread


include ../Makefile.trailer

# My own executable can be compiled like this:
# debug: watchdog
# release: watchdog.dbg
#watchdog: watchdog.c $(LIB_NAME)
#       $(CC) $(CFLAGS) $(RELEASE_FLAGS) $< $(LDFLAGS) $(LIBS) -o$(@)
#
#watchdog.dbg: watchdog.c $(DBG_LIB_NAME)
#       $(CC) $(CFLAGS) $(DEBUG_FLAGS) $< $(LDFLAGS) $(DBG_LIBS) -o$(@)



# DO NOT DELETE
