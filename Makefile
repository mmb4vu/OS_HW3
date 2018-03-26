max: findMaxThreaded.cpp barrier.cpp
	g++ findMaxThreaded.cpp barrier.cpp -lm -lpthread -lrt -o max
clean:
	rm max
