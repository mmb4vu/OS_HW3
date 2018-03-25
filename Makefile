test: sample.cpp barrier.cpp
	g++ -o test sample.cpp barrier.cpp -lm -lpthread -lrt
clean:
	rm test
