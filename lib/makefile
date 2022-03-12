src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
lib = $(patsubst ./src/%.cpp, ./lib%.so, $(src))
shared_src = $(wildcard ../shared/src/*.cpp)
shared_obj = $(patsubst ../shared/src/%.cpp, ../shared/obj/%.o, $(shared_src))

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_S), Linux)
    CXX = g++
endif

ifeq ($(UNAME_S), Darwin)
    CXX = clang++
endif

INC = -I../inc -I../shared/inc -I./inc
ifeq ($(UNAME_M), x86_64)
	STD = -std=c++17 -ltbb
endif
ifeq ($(UNAME_M), arm64)
	STD = -std=c++17
endif
ALL: $(lib)

$(lib): ./lib%.so: ./obj/%.o $(shared_obj)
	$(CXX) -shared $< $(shared_obj) -o $@ -fPIC $(STD) 

$(shared_obj): ../shared/obj/%.o: ../shared/src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC $(STD) 

$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC $(STD) 

clean:
	rm -rf $(obj) $(lib) $(shared_obj)
