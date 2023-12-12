# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Informática Básica
#
# @author Fabián González Lence
# @date 13/09/2023
# @brief Makefile Template


CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++17 -Wall	 			 # The C++ compiler options (C++17, and warn all)
LDFLAGS =						         # The linker options (if any)

# The all target builds all of the programs handled by the makefile.
all: quickhull

# The quickhull target builds the quickhull executable.
quickhull: main.o point_set.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	rm *.o

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean

# The following rule is effectively built into make and
# therefore need not be explicitly specified:
# quickhull.o: quickhull.cc
#
	$(CXX) $(CXXFLAGS) -c $<

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -f quickhull *.o
	rm -rf *~ basura* b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;

push:
	git pull 
	git add . 
	git commit -m "Minor changes" 
	git push