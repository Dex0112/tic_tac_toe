CC = gcc
CFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET = run
SRCS = main.c utils.c tic_tac_toe.c game.c main_menu.c button.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

