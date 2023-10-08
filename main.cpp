#include <iostream>
#include "SynchronizationHW.h"

int main()
{
    ThreadSafeQueue queue;
    queue.push(new TestCommand);
    queue.push(new TestCommand);
    queue.push(new TestCommand);
    queue.push(new TestCommand);
    queue.push(new TestCommand);
    queue.push(new TestCommand);

    StartThreadCommand startThread(&queue);

    queue.push(new HardStopCommand(startThread.currentThread));

    startThread.execute();

    std::thread* mainThread = startThread.currentThread;

    while (mainThread != NULL)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}