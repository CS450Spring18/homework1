#include <iostream>
#include <chrono>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

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

void timeofday()
{
    auto start = chrono::system_clock::now(); // Start the clock
    struct timeval begin;
    gettimeofday(&begin, NULL);
    auto end = chrono::system_clock::now(); // End clock
 
    chrono::duration<double> elapsed_seconds = end-start; // Calculate the time it took to run
    cout << "\nelapsed time for gettimeofday: " << elapsed_seconds.count() << "s\n"; // Print the time elapsed
}
 
int main()
{
    myfunction(); // Call function that does not do anything but start and stop timer
    syscall(); // Call function that does a syscall ( getpid() )
    timeofday();
}