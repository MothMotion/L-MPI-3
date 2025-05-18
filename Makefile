CC = mpicc
CCFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
LSF_DIR = lsf

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LSF = $(wildcard $(LSF_DIR)/*.lsf)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p obj
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

bsubload: $(TARGET)
	for lsf_script in $(LSF) ; do \
		bsub < $$lsf_script ; \
	done
