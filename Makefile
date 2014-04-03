CC = gcc
CFLAGS = -c -Wall -g
LDFLAGS = -g -lm -lglut -lGL -lGLU
SRC_DIR = SRC
INC_DIR = INC
OBJ_DIR = OBJ
BIN_DIR = BIN
SRC = $(wildcard SRC/*.c)
INC = $(addsuffix .o, $(basename $(subst ${SRC_DIR}, ${INC_DIR}, ${SRC})))
OBJ = $(addsuffix .o, $(basename $(subst ${SRC_DIR}, ${OBJ_DIR}, ${SRC})))
EXEC = commando418


all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(BIN_DIR)/$(EXEC) -Wall $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -o $@

clean :
	@rm -f $(OBJ)

mrproper : clean
	@rm -f $(BIN_DIR)/$(EXEC)
