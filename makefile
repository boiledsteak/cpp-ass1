# Makefile

# Compiler and flags
CC = g++
CFLAGS = -std=c++11

# Source files
SRCS = assdraft1.cpp converters.cpp
HEADERS = constructors.h converters.h

# Output file
TARGET = ass.app

# Build rule
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)