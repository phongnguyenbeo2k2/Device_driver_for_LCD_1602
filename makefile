CC :=gcc

.PHONY: run
run: build
	@./bin/main

.PHONY: build
build: ./bin/main 

./bin/main: ./output/main.o ./output/i2c-lcd.o
	@$(CC) $^ -o $@
./output/main.o: ./source/main.c
	@$(CC) -c $< -o $@ -I ./include

./output/i2c-lcd.o: ./source/i2c-lcd.c
	@$(CC) -c $< -o $@ -I ./include 

.PHONY: clean
clean:
	@rm -f ./bin/* ./output/*