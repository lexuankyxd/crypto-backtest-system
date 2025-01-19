#TODO

- Optimize the data parsing process.
- Optimize the trade sell execution.
- Allow to edit trades.
- Figure out a way to test this program.
- Make it so the simulation is branchless
- There's a bug where the code would sometime segfault because of the detached thread reading the file data, seems like it's fixed by stoping the main thread from reading the 2 thread data but idk. Read more about multithreading and a thread's memory when detached.

Simple file I/0 benchmarking(100 mins worth of data):

- Reading with fscanf(): 45.97 seconds worth of data read per second
- Reading
