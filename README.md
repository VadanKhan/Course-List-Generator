# Course List Generator

This program reads course data from a file, filters and sorts the courses based on user inputs, and then prints the sorted course list along with some statistics.

UID: 10823198

## How to Run

1. Compile the program.
2. Run the program.

## User Inputs

The program asks for three inputs from the user:

1. The name of the datafile to extract. If you want to use the default datafile 'courselist.dat', enter '-d'.
2. The sort specifier, which can be 'id' or 'name'. This determines whether the output data is sorted by course id or course name.
3. An integer (0, 1, 2, 3, or 4). If you enter 0, the program will print all courses. If you enter 1, 2, 3, or 4, the program will print courses of the corresponding level.

## Output

The program prints the following:

1. The sorted course list. Each line of the course list contains the course id and the course name.
2. The mean of the marks for the selected courses.
3. The population error of the marks for the selected courses.

## Code Structure

The code consists of several functions:

- `read_data`: Reads course data from a file.
- `calculate_mean_and_std_dev`: Calculates the mean, standard deviation, and mean standard deviation of a vector of values.
- `compareByID` and `compareByName`: Comparators for sorting courses by id and name.
- `course_list_generator`: Filters and sorts courses based on user inputs, and then generates the course list and some statistics.
- `get_user_inputs`: Gets inputs from the user.
- `main`: The main function of the program. It calls the other functions and controls the flow of the program.

# Tips on checking compilation

Note: only command-line compilation works on Windows, unless you install MinGW's makefile.exe. For mac, you have to make sure that when you write "which g++" you don't get "clang" in your output - if you do, you should edit the Makefile so that the g++-11 is the one you installed with brew.

If you want to compile your code in the same way the demonstrators will compile it to check it, you can just write "make" in the console.
This will use a the combination of the `make` command with a `Makefile` file that you will see in the same folder. In this case, doing this which in this case will run the following command:

`g++-11 assignment-2.cpp -o assignment-2.o -std=gnu++17`

The std=gnu++17 makes sure that the compiler you're using locally (which you should have installed following the instructions on the Quickstart guide on Blackboard/Git) picks up the same version of the C++ standards as the computers in the lab.

This command will produce the following file in the same directory you're running on:

`g++-11 assignment-2.cpp -o assignment-2.o -std=gnu++17`

Which you can then execute in a terminal using:

`./assignment-2.o`

You can find out more about Makefiles [here](https://www.gnu.org/software/make/manual/html_node/Introduction.html) or [in this simple starter guide](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/) but we won't cover these in the course.
