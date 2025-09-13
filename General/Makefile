########################################################################
# ECE5504 .... Add your project details here
########################################################################

CC := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump

# Define flags for Hwacha support
CFLAGS := -O2 -std=gnu11 -Wall -specs=htif_nano.specs -march=rv64gc

# Target for compiling dnn
.PHONY: dnn dfs heat
dnn: dnn.riscv
dfs: dfs.riscv
heat: heat.riscv

# Define rules for compiling .c files into .riscv binaries
.PRECIOUS: %.riscv
%.riscv: %.c trap.c
	$(CC) $(CFLAGS) -DSIZE=32 -o $@ $< trap.c -lm $(LDFLAGS)

# Clean target to remove compiled files
.PHONY: clean
clean:
	rm -f -- *.riscv *.o *.dump

# Disable built-in suffix rules
.SUFFIXES: