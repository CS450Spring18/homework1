#include <iostream>
#include <chrono>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void syscall()
{
    auto start = chrono::system_clock::now(); // Start the clock - line 211 in s file
    getpid(); // Get pid() which is a system call - line 213 in s file
    auto end = chrono::system_clock::now(); // End clock - line 214 in s file
 
    chrono::duration<double> elapsed_seconds = end-start; // Calculate the time it took to run
    cout << "\nelapsed time for syscall:     " << elapsed_seconds.count() << "s\n\n"; // Print the time elapsed

}

void myfunction()
{
    auto start = chrono::system_clock::now(); // Start the clock
    // Trying this as an empty function
    auto end = chrono::system_clock::now(); // End clock
 
    chrono::duration<double> elapsed_seconds = end-start; // Calculate the time it took to run
    cout << "\nelapsed time for my function: " << elapsed_seconds.count() << "s"; // Print the time elapsed
}
 
int main()
{
    myfunction(); // Call function that does not do anything but start and stop timer
    syscall(); // Call function that does a syscall ( getpid() )
}


/*
Using gettimeofday is provided by the kernel but put
into the user memory space. So there is no need to really
use an int x80 since we don't need to make a call to the kernel.
It has to:
    1. make the call to the function
    2. start the timer
    3. do something like a syscall
    4. end the timer
    5. calculate the time elapsed
    6. print out the time it took to run the syscall

The performance from myfunction() to syscall()
is about 4x faster on average. Sometimes it will only be
2x as fast. Sometimes the syscall() is faster.
*/