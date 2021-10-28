src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))
lib = $(patsubst ./src/%.c, ./lib%.so, $(src))

inc_path = ./inc
CXX = gcc

ALL: $(lib)

$(lib): ./lib%.so: ./obj/%.o
	$(CXX) -shared $< -o $@ -fPIC
$(obj): ./obj/%.o: ./src/%.c
	$(CXX) -c $< -o $@ -I ./inc -fPIC
clean:
	rm -rf $(obj) $(lib)