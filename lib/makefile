src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))
lib = $(patsubst ./src/%.cpp, ./lib%.so, $(src))

INC = -I../inc -I./inc
CXX = g++

ALL: $(lib)

$(lib): ./lib%.so: ./obj/%.o
	$(CXX) -shared $< -o $@ -fPIC
$(obj): ./obj/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(INC) -fPIC
clean:
	rm -rf $(obj) $(lib)