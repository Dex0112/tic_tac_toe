CC = gcc
CFLAGS = -lSDL2 -lSDL2_image
TARGET = run
SRCS = main.c tic_tac_toe.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

