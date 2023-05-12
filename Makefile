# Define the compiler
CC = gcc

# Define compiler flags
CFLAGS = -Wall -Werror -g -std=c99

# Define source and object file directories
SRCDIR = src
OBJDIR = obj

# Define source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Define the output executable
EXEC = program

# Define the build target
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Define the object file targets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Define the obj directory creation
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Define the clean target
clean:
	rm -rf $(OBJDIR) $(EXEC)

.PHONY: clean
