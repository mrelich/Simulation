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
Targets = ana

all: Makefile $(Targets)

obj/%.so:
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
obj/DataPoints.so:	$(src)/DataPoints.cxx
#obj/Detector.so:	$(inc)/Detector.h
obj/Detectors.so:	$(src)/Detectors.cxx
obj/Dim3.so:		$(src)/Dim3.cxx
obj/Mixer.so:		$(src)/Mixer.cxx
obj/SaveOutput.so:	$(src)/SaveOutput.cxx
obj/Analyze.so:		$(src)/Analyze.cxx
obj/Ana.so:		../main/Ana.cxx


ana:	 			\
	obj/Particle_Dict.so	\
	obj/Event_Dict.so	\
	obj/DataPoints.so	\
	obj/Detectors.so	\
	obj/Dim3.so		\
	obj/Mixer.so		\
	obj/SaveOutput.so	\
	obj/Analyze.so		\
	obj/Ana.so
	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)

clean:
	rm -f $(Targets)
	rm -f obj/*.so
	rm -f obj/*.so
	rm -f obj/*.cxx
	rm -f obj/*.h
