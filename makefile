src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
shared_src = $(wildcard ./shared/src/*.cpp)
shared_obj = $(patsubst ./shared/src/%.cpp, ./shared/obj/%.o, $(shared_src))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CXX = g++
endif

ifeq ($(UNAME_S), Drawin)
    CXX = clang++
endif
myArgs = -Wall -ldl
INC = -I./shared/inc -I./inc 
STD = -std=c++11

ALL: taskchecker 

taskchecker: $(shared_obj) $(obj) 
	$(CXX) $^ -o $@ $(myArgs) $(STD)

$(shared_obj): ./shared/obj/%.o: ./shared/src/%.cpp
	$(CXX) -c $< -o $@ $(INC) $(STD)

$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC) $(STD)

clean:
	rm -rf $(obj) $(shared_obj) TaskChecker 

.PHONY: ALL clean
