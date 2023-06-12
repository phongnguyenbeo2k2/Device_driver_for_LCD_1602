PROJECT_NAME:= i2c-lcd
CC :=gcc
SRC_DIR:= source
INC_DIR:= include/ 
OBJ_DIR := output
BIN_DIR := bin

SRC:= $(wildcard $(SRC_DIR)/*.c)
OBJ:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXE:= $(BIN_DIR)/$(PROJECT_NAME)
.PHONY: run
run: build
	@ ./$(EXE)

.PHONY: build
build: $(EXE) 

$(EXE): $(OBJ)
	@ $(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) -c $< -o $@ -I $(INC_DIR)

.PHONY: clean
clean:
	@ rm -r ./bin/* ./output/*

test:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) -c $< -o $@ -I $(INC_DIR)