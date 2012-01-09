#-----------------------------------------------------------------------------
# directory variables
#-----------------------------------------------------------------------------
BUILD = build
SRCDIRS = Harness Basic 

#-----------------------------------------------------------------------------
# source and object variables
#-----------------------------------------------------------------------------
SOURCES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/src/*.cpp)) 
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

TESTSRC = $(wildcard Self/src/*.cpp)
TESTOBJ = $(patsubst %.cpp, %.o, $(TESTSRC))

#----------------------------------------------------------------------------- # compile and link flags #-----------------------------------------------------------------------------
DEBUG= -ggdb
LINK = $(DEBUG) 
COMPILE = $(DEBUG)  -c -I. 
CHANGESET = $(strip $(shell git rev-parse HEAD 2> /dev/null))
ifneq  "$(CHANGESET)" ""
COMPILE += -DGIT_CHANGESET=\"$(CHANGESET)\"
endif

#-----------------------------------------------------------------------------
# Targets
#-----------------------------------------------------------------------------
help: TARGS = $(shell grep "^.PHONY" makefile | sed 's/.PHONY:\+//' | xargs -ifoo echo "\tfoo\n")
help:
	@echo "* object files are created next to the sources";\
	echo "* executables are created in the 'build' directory";\
	echo "Available targets:\n$(TARGS)";

.PHONY: UnitTest
UnitTest: $(BUILD)/UnitTest
$(BUILD)/UnitTest: $(BUILD) $(BUILD)/main.o  $(OBJECTS) $(TESTOBJ)
	g++ -o $(BUILD)/UnitTest $(LINK)  $(BUILD)/main.o $(OBJECTS) $(TESTOBJ)

$(BUILD)/main.o: main.cpp
	g++ $(COMPILE) -o $@ $<

$(TESTOBJ): %.o : %.cpp
	g++ $(COMPILE) -o $@ $<

$(OBJECTS) : %.o : %.cpp
	g++ $(COMPILE) -o $@ $<

$(BUILD):
	- mkdir $(BUILD)

.PHONY: clean
clean:
	- rm -fr $(OBJECTS) $(TESTOBJ) $(BUILD) test.json

.PHONY: run
run: $(BUILD)/UnitTest
	./$(BUILD)/UnitTest --json=test.json

.PHONY: runval
valrun: $(BUILD)/UnitTest
	valgrind --leak-check=full ./$(BUILD)/UnitTest --json=test.json
