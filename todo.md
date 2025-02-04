#TODO

- Implement trading view apis.
- Add progress bar lol.
- Optimize the data parsing process.
- Optimize the trade sell execution.
- Allow to edit trades.
- Figure out a way to test this program.
- Make it so the simulation is branchless
- There's a bug where the code would sometime segfault because of the detached thread reading the file data, seems like it's fixed by stoping the main thread from reading the 2 thread data but idk. Read more about multithreading and a thread's memory when detached.
- Seperate balanced that's locked in a trade and make sure that each trade is accessing balance that is not locked in a trade.

Simple file I/0 benchmarking:

- Reading with fscanf(): 45.97 seconds worth of data read per second -- forgot to remove data from the buffer after it's used, so it just supa slowed down the reading process. fixed now
- Still fscanf() but without the bug: 8.4k klines per sec. -> good enough? takes 10s to finnish 1 day.
