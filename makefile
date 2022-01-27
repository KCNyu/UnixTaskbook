src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
shared_src = $(wildcard ./shared/src/*.cpp)
shared_obj = $(patsubst ./shared/src/%.cpp, ./shared/obj/%.o, $(shared_src))

myArgs = -Wall -ldl
CXX = g++
INC = -I./shared/inc -I./inc 

ALL: TaskChecker 

TaskChecker: $(shared_obj) $(obj) 
	$(CXX) $^ -o $@ $(myArgs)

$(shared_obj): ./shared/obj/%.o: ./shared/src/%.cpp
	$(CXX) -c $< -o $@ $(INC)

$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC)

clean:
	rm -rf $(obj) $(shared_obj) TaskChecker 

.PHONY: ALL clean