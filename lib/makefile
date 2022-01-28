src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
lib = $(patsubst ./src/%.cpp, ./lib%.so, $(src))
shared_src = $(wildcard ../shared/src/*.cpp)
shared_obj = $(patsubst ../shared/src/%.cpp, ../shared/obj/%.o, $(shared_src))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CXX = g++
endif

ifeq ($(UNAME_S), Drawin)
    CXX = clang++
endif

INC = -I../inc -I../shared/inc -I./inc 
STD = -std=c++11

ALL: $(lib)

$(lib): ./lib%.so: ./obj/%.o $(shared_obj)
	$(CXX) -shared $< $(shared_obj) -o $@ -fPIC $(STD) 

$(shared_obj): ../shared/obj/%.o: ../shared/src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC $(STD) 

$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC $(STD) 

clean:
	rm -rf $(obj) $(lib) $(shared_obj)
