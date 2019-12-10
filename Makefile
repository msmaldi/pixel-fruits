LIBS = `pkg-config --cflags --libs sdl2 SDL2_ttf SDL2_image`
CFLAGS += -flto -O3 -m64 -mtune=generic

SOURCE := src/keyboard.c src/fps_component.c src/game_core.c src/game_state.c src/player.c src/fruit.c src/observer.c src/main.c src/logf.c

OBJS = ${SOURCE:.c=.o}
EXECUTABLE := pixel-fruits

.PHONY: all
all: $(EXECUTABLE)

.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(OBJS)
	$(CC) -s $(CFLAGS) $^ $(LIBS) -o $@
