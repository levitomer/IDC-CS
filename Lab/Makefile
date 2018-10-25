# UTILS MAKEFILE

#VARS

#specify our compiler of choice
CC = gcc

#optional flags that we may wish to pass to our compiler.
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -O3
CFLAGS_DNDEBUG = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
VLGFLAGS =  -v --leak-check=yes --track-origins=yes

#.c files
SRCS = slist.c barr.c dyn_vec.c pq.c task.c circ_buf.c queue.c srt_list.c fsm.c uuid.c dlist.c scheduler.c stack.c vsm.c

TESTS = barr_test.c circ_buf_test.c dyn_vec_test.c queue_test.c srt_list_test.c task_scheduler_test.c barr_test.o dlist_test.c fsm_test.c slist_test.c stack_test.c vsm_test.c

#.o files
OBJS = $(SRCS:.c=.o)

#.h files
HEADERS = $(SRCS:.c=.h)

#programs name
PROGS = barr dlist slist stack dyn_vec pq scheduler circ_buf queue srt_list fsm vsm

# For cleaning
RM = /bin/rm -f

#END OF VARS

#make all: compiles all .c files, and creates a library using the "ar" command
all: libutils.a

libutils.a: $(OBJS)
	ar rcs libutils.a $(OBJS)

#make release: compile the files using DNDEBUG flag, and create a library
release: lib_utils_dndb.a $(PROGS)
	$(CC) $(CFLAGS_DNDEBUG) -o $(OBJS)

lib_utils_dndb.a: $(OBJS)
	ar rcs lib_utils_dndb.a $(SRCS)

#make include: create a symbolic link to .h files from current directory into the /include directory
include: 
	

#make libs: create a symbolyic link to .a files from current directory into /lib directory
libs:

#make test: create executable files and symbolic link to executables files from current directory into /bin directory
test: $(PROGS)
	$(CC) $(CFLAGS) -o $(PROGS) $(OBJS)

-include .depends
#make depend: create a file (.depends) with all the missing dependencies (automatically).
.depends :
	$(CC) -MM $(SRCS) > .depends

#This rule compiles any .c file into a .o file. The % in the target and dependencies will determine what files to compile through string matching. 
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

# PHONYs

# target: cleans all object (.o) files and executables created by makefile
.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGS)

#END OF PHONYs

#makedepend: automatically finds the dependencies for each object file, and adds them to the bottom of the makefile.
depend:
	makedepend -- $(CFLAGS) -- $(SRCS)

# END OF MAKEFILE

