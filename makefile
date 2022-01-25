src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))

inc_path = ./inc
myArgs = -Wall -ldl
CXX = g++

ALL: TaskChecker 

TaskChecker: $(obj)
	$(CXX) $^ -o $@ $(myArgs)
$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ -I $(inc_path)

clean:
	rm -rf $(obj) TaskChecker 

.PHONY: ALL clean