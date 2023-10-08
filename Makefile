all:
	g++ -std=c++17 SynchronizationHW.h -o SynchronizationHW
	g++ -std=c++17 SynchronizationHW.cpp -o SynchronizationHW
	g++ -std=c++17 ./Test/SyncronizationTest/SyncronizationTest.cpp -o SyncronizationTest

test:
	chmod +x SynchronizationHW
	./Test/SyncronizationTest/SyncronizationTest

clean:
	$(RM) SynchronizationHW SyncronizationTest