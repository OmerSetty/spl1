# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.

# All Targets

all: hello


# Tool invocations

# Executable "hello" depends on the files hello.o and run.o.


hello: clean bin/main.o 
	
	g++ -o bin/main bin/main.o bin/Facility.o bin/Settlement.o bin/SelectionPolicy.o bin/Plan.o bin/Simulation.o bin/Auxiliary.o bin/Action.o
	
	./bin/main /workspaces/Skeleton/config_file.txt

	# valgrind -s --leak-check=full --show-reachable=yes ./bin/main /workspaces/Skeleton/config_file.txt

# Depends on the source and header files

bin/main.o: src/main.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Plan.o src/Plan.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp


# Depends on the source and header files

# : 

#     g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o  


#Clean the build directory

clean:

	rm -f bin/*