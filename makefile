# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.

# All Targets

all: hello


# Tool invocations

# Executable "hello" depends on the files hello.o and run.o.


hello: clean bin/main.o 

	

	

	g++ -o bin/main bin/main.o

	
	./bin/main
	


# Depends on the source and header files

bin/main.o: src/main.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp


# Depends on the source and header files

# : 

#     g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o  


#Clean the build directory

clean:

	rm -f bin/*