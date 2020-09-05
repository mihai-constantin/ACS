CXX=g++
CXX_FLAGS=-O2 -g -std=c++11

all: gpu_hashtable

gpu_hashtable: gpu_hashtable.cu test_map.cpp gpu_hashtable.hpp
	nvcc $(CXX_FLAGS) gpu_hashtable.cu -o gpu_hashtable

std_hashtable: std_hashtable.cpp test_map.cpp
	$(CXX) $(CXX_FLAGS) -lm std_hashtable.cpp -o std_hashtable

clean:
	rm -f gpu_hashtable std_hashtable
