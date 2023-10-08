#include "SynchronizationHW.h"

ICommand::ICommand()
{
    
}



StartThreadCommand::StartThreadCommand(ThreadSafeQueue* setCommandsQueue)
{
    commandsQueue = setCommandsQueue;
}


void StartThreadCommand::execute()
{
    commandType = "StartThreadCommand";

    currentThread = new std::thread(
        [](ThreadSafeQueue* commandsQueue)
        {
            while (true)
            {
                if (commandsQueue->size() < 0)
                {
                    while (true)
                    {
                        if (commandsQueue->size() > 0)
                        {
                            break;
                        }

                        else
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }
                    }

                    continue;
                }

                try
                {
                    ICommand* command = commandsQueue->front();

                    command->execute();
                }

                catch (BaseException*)
                {
                    // Handle exception
                }

                commandsQueue->pop();
            }
        }, commandsQueue);

    currentThread->detach();
    isRunning = true;
}



TestCommand::TestCommand()
{
    commandType = "TestCommand";
}



void TestCommand::execute()
{
    std::cout << "test\n";
}



HardStopCommand::HardStopCommand(std::thread* setCurrentThread)
{
    commandType = "HardStopCommand";

    currentThread = setCurrentThread;
}



void HardStopCommand::execute()
{
    //std::terminate();
    currentThread = nullptr;

    delete currentThread;
}



ThreadSafeQueue::ThreadSafeQueue()
{
    
}



void ThreadSafeQueue::pop()
{
    std::mutex threadMutex;

    threadMutex.lock();

    if (0 < commandQueue.size())
    {
        commandQueue.pop();
    }

    threadMutex.unlock();
}


void ThreadSafeQueue::push(ICommand* newCommand)
{
    std::mutex threadMutex;

    threadMutex.lock();

    commandQueue.push(newCommand);

    threadMutex.unlock();
}



ICommand* ThreadSafeQueue::front()
{
    std::mutex threadMutex;

    threadMutex.lock();

    if (commandQueue.size() > 0)
    {
        ICommand* returningValue = commandQueue.front();

        threadMutex.unlock();

        return returningValue;
    }

    threadMutex.unlock();
}



int ThreadSafeQueue::size()
{
    std::mutex threadMutex;

    threadMutex.lock();

    if (commandQueue.size() > 0)
    {
        int returningValue = commandQueue.size();

        threadMutex.unlock();

        return returningValue;
    }

    threadMutex.unlock();
}
