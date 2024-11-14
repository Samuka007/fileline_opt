all: bin/filelines_gen bin/filelines

filelines_gen: src/filelines_gen.cpp src/find_most_freq.h
	g++ src/filelines_gen.cpp -o bin/filelines_gen -O2
filelines: bin/filelines.o bin/find_most_freq.o bin/filelines_baseline.o
	g++ bin/filelines.o bin/find_most_freq.o bin/filelines_baseline.o -mavx2 -O2 -o bin/filelines
bin/filelines.o: src/filelines.cpp src/find_most_freq.h
	g++ -mavx2 src/filelines.cpp -c -O2 -o bin/filelines.o
bin/find_most_freq.o: src/find_most_freq.cpp src/find_most_freq.h
	g++ src/find_most_freq.cpp -c -O2 -o bin/find_most_freq.o
bin/filelines_baseline.o: src/filelines_baseline.cpp src/filelines_baseline.h
	g++ -mavx2 src/filelines_baseline.cpp -c -O2 -o bin/filelines_baseline.o