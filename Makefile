test: thread.cpp barrier.cpp
	g++ -o test thread.cpp barrier.cpp -lm -lpthread -lrt
clean:
	rm test
