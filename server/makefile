src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

inc_path = ./inc
myArgs = -Wall -g -ldl
CXX = gcc

ALL: server 

server: $(obj)
	$(CXX) $^ -o $@ $(myArgs)
$(obj): ./obj/%.o: ./src/%.c
	$(CXX) -c $< -o $@ -I $(inc_path)

clean:
	rm -rf $(obj) server

.PHONY: ALL clean