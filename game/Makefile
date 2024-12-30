CC = gcc
LDFLAGS = -lglfw -lGL -lleif -lclipboard -lm -lxcb
SRCS = main.c tetromino.c board.c
OBJS = $(SRCS:.c=.o)
TARGET = tetris

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

