#include "pch.h"
#include "CppUnitTest.h"
#include "SynchronizationHW.h"
#include "SynchronizationHW.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SyncronizationTest
{
	TEST_CLASS(SyncronizationTest)
	{
	public:
		
		TEST_METHOD(StartingTest)
		{
            ThreadSafeQueue queue;
            queue.push(new TestCommand);

            StartThreadCommand startThread(&queue);

            startThread.execute();

			Assert::IsTrue(startThread.isRunning);
		}
	};
}
