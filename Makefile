SRC_DIR = src/

main : $(SRC_DIR)main.cc $(SRC_DIR)turing_machine.cc
	g++ $(SRC_DIR)main.cc -o main

clean:
	rm -rf *.o main