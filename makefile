CC = gcc

CFLAGS = -lglfw -lGL -lleif -lclipboard -lm -lxcb

TARGET = window

SRCS = window.c

OBJS = $(SRCS:.c=.o)

all = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@
