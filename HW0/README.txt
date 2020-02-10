HW0: Galaxy Explorers   -
Ian Jackson             -
-------------------------

Goal: Benchmark Python code for a video game and improve performance in C++.

PART ONE: Benchmarking in Python

I chose the following benchmark parameters using a lowest variance criteria from repeated measurements. By modifying the script update_locations.py, I was able to save the results from repeated measurements of different numbers of iterations (that finished within reasonable time) into a csv file. Then, using calculate_var.py, I was able to find the lowest variance of the randomly seeded data and use that to find the most statistically stable number of iterations. I chose vector size using the example given in the homework instructions. This experimentation resulted in the following benchmark parameters:

Vector Size        Iterations
4                  10000000
16                 500000
64                 50000
256                2000
1024               2000
4096               5000
16384              150
65536              150
262144             30
1048576            7
4194304            N/A [Multiple Crashes]

The .dat file of times (averaged using calculate_mean.py) resulting from this testing is in the repo's main branch (meancalc_python.dat) and the .csv files created from the repeated measurements for each vector size is in the supplementary folder. The resulting plot is in the 'plots' folder, saved as python_plot.png.

_______________________________________________________________

PART TWO: Porting to C++

For this section of the homework, I ported the code over from Python to C++, and found that the ported code ran around 3-6 times faster that the original. This is an improvement but is by no means ideal. I kept the vector size and number of iterations the same as I used in the testing for Python in order to make the comparison more straightforward. I didn't find any need to change anything in terms of actual function from the original code. 

The .dat of times (averaged using the .cc file) resulting from this testing is in the repo's main branch (meancalc_cpp.dat). The resulting plot is saved as cpp_plot.png, and a plot comparing the two is saved as cpp_python_comparison.png.

_______________________________________________________________

PART THREE: C++ Variable Type Comparison

For this section, I changed the types of the contents of vectors for coordinates and velocity, and compared them to the double-type I originally used in the first round of C++ testing. Having a user-defined type, objects_vector, made this pretty straightforward. For the sake of time, I only tested half of the numbers that I did for original testing going from 4 to 1048576 but by 2^4 rather than 2^2. The result of this testing is saved in separate .dat files, titled by their data type.

double: (tested in part two)

float: I noticed that the mean times were, on average, very slightly above those I found when using doubles, but not in every individual case.

int8_t: When using this data type, I noticed that the mean times were slightly less than those I found for float and double, making this the fastest thus far.

int16_t: This data type was marginally slower than the previous three used for testing.

int32_t: Just looking at the results from testing, this data type was also, on average, slower than the others used for testing.

int64_t: Finally, this data type overlapped some with the others, leaning on the slower slide of the spectrum.

Finally, for better visualization, I plotted the data from this testing using gnuplot (data_type_comparison.png). This provided a slightly more quantitatively understandable representation than the above qualitative report.

Looking at the plot, there's a great deal of overlap, but int8_t seems to take the cake for fastest time, especially when it comes to larger powers of 2.
________________________________________________________________

PART FOUR: Memory Use

Using the time function native to Linux, I can report the following real, user, and sys times calculated by the machine for a vector size of 1048576 and 7 iterations.


Python: real (2m12.047s), user (2m11.354s), sys(0m0.576s)
C++: real (0m38.300s), user (0m37.699s), sys (0m0.584s)

From the times listed above, it is clear that the real time and user time utilized by Python is much greater (by roughly 3.5 times) than the C++ time. Sys, however, is roughly the same between the two, which may call to the larger factor that makes Python take so much more memory: the overhead from its interpreter.

_________________________________________________________________

Bugs/Issues:

    - Adding the suggested optimization tag (-o3) raised the error: 

    /usr/bin/ld: a.out: _ZSt4cout: invalid version 3 (max 0)
    a.out: error adding symbols: Bad value
    collect2: error: ld returned 1 exit status

    I didn't have time to look into this, but I assume that this    meant that the -o tag I used was sufficient.


    - Potential improvements can be made to the code in later versions, such as:
    
        1. More memory testing - my machine wasn't recognizing the -v tag for verbosity in output and so I missed out on some key information about the runtime. But for the sake of time, I couldn't look into this.

__________________________________________________________________
