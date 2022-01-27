src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
lib = $(patsubst ./src/%.cpp, ./lib%.so, $(src))
shared_src = $(wildcard ../shared/src/*.cpp)
shared_obj = $(patsubst ../shared/src/%.cpp, ../shared/obj/%.o, $(shared_src))

INC = -I../inc -I../shared/inc -I./inc 
CXX = g++

ALL: $(lib)

$(lib): $(obj) $(shared_obj)
	$(CXX) -shared $(obj) $(shared_obj) -o $@ -fPIC

$(shared_obj): ../shared/obj/%.o: ../shared/src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC

$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC

clean:
	rm -rf $(obj) $(lib) $(shared_obj)