# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.

# All Targets

all: hello


# Tool invocations

# Executable "hello" depends on the files hello.o and run.o.


hello: clean bin/main.o 
	
	g++ -o bin/main bin/main.o bin/Facility.o bin/Settlement.o bin/SelectionPolicy.o
	
	./bin/main

# Depends on the source and header files

bin/main.o: src/main.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp


# Depends on the source and header files

# : 

#     g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o  


#Clean the build directory

clean:

	rm -f bin/*