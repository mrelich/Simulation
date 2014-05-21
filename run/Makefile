SHELL := /bin/bash

RCXX=$(shell root-config --cflags)
RLIB=$(shell root-config --libs)

CXX		= g++
CFLAGS		= -pipe -g \
-D __SKIP_CLASS_DEF__ \
-I.. \
-Wall -Wextra -Winit-self -Wcast-align -Wno-comment -Wno-ignored-qualifiers \
-O2 -march=native -mfpmath=sse -fPIC \
-Wl,--no-as-needed

#---- Paths ----#
inc = ../include
src = ../src

#---- Links ----#
links = -I$(inc)

CXXFLAGS	= $(CFLAGS) $(RCXX) -lTreePlayer
LDFLAGS		= -lm -L. $(RLIB)

#---- Packages Dependencies ----#
Targets = mix treeMake

all: Makefile $(Targets)

obj/%.so: $(src)/%.cxx
	$(CXX) -c $< -o $@ $(SOFLAGS) $(CXXFLAGS) $(links)

#---- ROOT Objects ----#
obj/Particle_Dict.cxx: $(inc)/Particle.h $(inc)/LinkDefPart.h
	rootcint -f $@ -c -I$(inc) $+
obj/Particle_Dict.so: obj/Particle_Dict.cxx $(inc)/Particle.h
	$(CXX) -c $< -o $@ $(SOFLAGS) $(CXXFLAGS) -Os -g1 -I$(inc)
obj/Event_Dict.cxx: $(inc)/Event.h $(inc)/LinkDefEvent.h
	rootcint -f $@ -c -I$(inc) $+
obj/Event_Dict.so: obj/Event_Dict.cxx $(inc)/Event.h
	$(CXX) -c $< -o $@ $(SOFLAGS) $(CXXFLAGS) -Os -g1 -I$(inc)



#---- Additional Objects ----#
#obj/Particle.so:	$(inc)/Particle.h
obj/FileReader.so:	$(inc)/FileReader.h
obj/Mixer.so:		$(inc)/Mixer.h
obj/Mix.so:		$(src)/Mix.cxx
obj/TreeMaker.so:	$(inc)/TreeMaker.h

#---- Analysis Code ----#
#readTest: 			\
#	obj/Particle.so		\
#	obj/FileReader.so	
#	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)

mix:	 			\
	obj/Particle_Dict.so	\
	obj/FileReader.so	\
	obj/Mixer.so		\
	obj/Event_Dict.so	\
	obj/Mix.so
	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)

treeMake:			\
	obj/Particle_Dict.so	\
	obj/Event_Dict.so	\
	obj/FileReader.so	\
	obj/TreeMaker.so
	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)


clean:
	rm -f $(Targets)
	rm -f obj/*.so
	rm -f obj/*.so
	rm -f obj/*.cxx
	rm -f obj/*.h
