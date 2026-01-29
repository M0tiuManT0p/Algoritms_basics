CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm
TARGET = main.exe
SRCS = main.c PercolationStats.c percolation.c dynamic_connectivity.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)