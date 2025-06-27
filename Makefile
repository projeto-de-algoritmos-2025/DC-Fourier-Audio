help:
	@echo "build: compiles the project"
	@echo "clean: deletes all binaries and objects"
	@echo "To start the program, run ./bin/bin"

build:
	@g++ src/*.cpp src/dr_libs-master/*.c -std=c++11 -I/usr/include/python3.11 -lpython3.11 -o bin/bin

clean:
	@rm -rf bin/* 

run:
	@aplay $(FILE)
	@./bin/bin $(FILE)