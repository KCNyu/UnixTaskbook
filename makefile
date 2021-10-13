src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

inc_path = ./inc
myArgs = -Wall -g
CXX = gcc

ALL: TaskChecker 

TaskChecker: $(obj)
	$(CXX) $^ -o $@ $(myArgs)
$(obj): ./obj/%.o: ./src/%.c
	$(CXX) -c $< -o $@ $(myArgs) -I $(inc_path)

clean:
	rm -rf $(obj) TaskChecker 

.PHONY: ALL clean