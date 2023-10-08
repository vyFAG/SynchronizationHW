#pragma once

#include <queue>
#include <iostream>
#include <mutex>
#include <chrono>

class BaseException : public std::exception
{
public:
    explicit BaseException(const char* message)
        : exceptionMsg(message) {}

    explicit BaseException(const std::string& message)
        : exceptionMsg(message) {}

    virtual ~BaseException() noexcept {}

    virtual const char* what() const noexcept
    {
        return exceptionMsg.c_str();
    }

    virtual const std::string getMsg() const noexcept
    {
        return exceptionMsg;
    }

protected:
    std::string exceptionMsg;
};



class ICommand
{
public:
    ICommand();

    virtual void execute() = 0;
protected:
    std::string commandType;
};



class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    void pop();
    void push(ICommand* newCommand);
    ICommand* front();
    int size();

private:
    std::queue<ICommand*> commandQueue;
};



class StartThreadCommand : public ICommand
{
public:
    StartThreadCommand(ThreadSafeQueue* setCommandsQueue);

    void execute();

    std::thread* currentThread = nullptr;

    bool isRunning = false;

private:
    ThreadSafeQueue* commandsQueue;
};



class TestCommand : public ICommand
{
public:
    TestCommand();

    void execute();
};



class HardStopCommand : public ICommand
{
public:
    HardStopCommand(std::thread* setCurrentThread);

    void execute();

private:
    std::thread* currentThread;
};



class SoftStopCommand : public ICommand
{
public:
    SoftStopCommand();

    void execute();
};