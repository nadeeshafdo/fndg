CC ?= gcc
VERSION = $(shell git describe --tags --always --dirty 2>/dev/null || echo "v1.0.0")
CFLAGS = -I./src -MMD -Wall -Wextra -O3 -s -std=c11 -D_DEFAULT_SOURCE -DVERSION=\"$(VERSION)\"

ifeq ($(OS),Windows_NT)
    EXE = .exe
else
    EXE =
endif

TARGET = build/fndg$(EXE)
PREFIX = /usr/local

SRCS = src/main.c src/search.c src/traverse.c
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

install: $(TARGET)
	install -d $(PREFIX)/bin
	install -m 755 $(TARGET) $(PREFIX)/bin/fndg$(EXE)

uninstall:
	rm -f $(PREFIX)/bin/fndg$(EXE)

clean:
	rm -rf build

-include $(DEPS)

.PHONY: all install uninstall clean build
