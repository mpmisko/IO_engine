CC=gcc
CFLAGS=-Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
RCFLAGS= -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -D_DEFAULT_SOURCE \
		-std=c99 -Werror -pedantic
RCLINKERFLAGS=`sdl2-config --libs --cflags` -lSDL2_image -lm -lSDL2_ttf
RENDERER_BUILD_DIR=./renderer_build_dir
RENDERER_FILES=$(addprefix src/,renderer_main.c $(addprefix game/,sprite.c utils.c game.c) \
			   utils/linked_list/linked_list.c) lib/io_lib.c
RENDERER_OBJECTS=$(RENDERER_FILES:%.c=$(RENDERER_BUILD_DIR)/%.o)
RENDERER_HEADERS=$(addprefix src/game/,utils.h game.h) lib/io_lib.h src/utils/linked_list/linked_list.h
RACER_EXECUTABLE=racergame

all: racer

racer: $(RACER_EXECUTABLE)

$(RACER_EXECUTABLE): $(RENDERER_OBJECTS) $(RENDERER_BUILD_DIR)/examples/racer.o
	@mkdir -p $(@D)
	$(CC) $(RCFLAGS) $^ -o $(RACER_EXECUTABLE) $(RCLINKERFLAGS)

$(RENDERER_BUILD_DIR)/%.o: %.c $(RENDERER_HEADERS)
	@mkdir -p $(@D)
	$(CC) $(RCFLAGS) -c $< -o $@

clean:
	rm -rf $(RENDERER_BUILD_DIR)
	rm -f $(RACER_EXECUTABLE)
