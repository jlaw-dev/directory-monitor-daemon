# Jonathan Lawrence
# CS3377.501
# jml160230@utdallas.edu
# Makefile for program5

# Variables
CURDIR = /home/013/j/jm/jml160230/CS3377UNIX/program5

# C++ flags
CXX = g++
CPPFLAGS = -Wall -I $(CURDIR)/install/include

# Linker flags
LFLAGS = -Wall -static

# Library flags
LDFLAGS = -L $(CURDIR)/install/lib
LIBS = -lrudeconfig

PROJECTNAME = CS3377.Program5.DaemonLibs

EXEC = program5

OBJS = InotifyFunctions.o loggingFunctions.o parseCommandLine.o parseConfigFile.o processControl.o program5.o signalHandling.o

######################################################################

all: $(EXEC)

cleanExec: 
	rm -f $(OBJS) *~ \#*
clean:
	rm -f $(OBJS) $(EXEC) *~ \#*

$(EXEC): $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
