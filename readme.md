#Author
Leonandro Valério Barbosa Gurgel

#Intro
In this project **List** i implement a punch of functions of the std::list, with a double linked list, you will have below a little instructions about how to compile and run the tests.


#compiling

1. `cd llist`: enters into the main project directory.

2. `mkdir build`: this creates a new directory in which the compilation output will be stored, including the executable.

3. `cd build`: just moves into the directory created in the step above.

4. `cmake -G "Unix Makefiles" ..`: asks cmake to create the Makefile based on the script found in `CMakeLists.txt`, one level up.

5. `make`: triggers the compiling process and create the run_tests target.


#Tests
After compiling process you will have an executable `run_tests`, this target have a lot of tests to checking how you class works. For run the tests, you just have to execute the `run_tests` like any executable, with the command `./run_tests`. remenber, you target has been buildt in the build folder, execute in this directory.
