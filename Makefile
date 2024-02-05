CC := gcc
CFLAGS := -Wall -Werror -I./include -I./src
RELEASE_CFLAGS := -O3
DEBUG_CFLAGS := -ggdb

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/src/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET := $(BINDIR)/bf

.PHONY: all release debug info clean

all: release

release: CFLAGS += $(RELEASE_CFLAGS)
release: $(TARGET)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

info:
	@echo "Build Information:"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Release CFLAGS: $(RELEASE_CFLAGS)"
	@echo "Debug CFLAGS: $(DEBUG_CFLAGS)"
	@echo "SRCDIR: $(SRCDIR)"
	@echo "OBJDIR: $(OBJDIR)"
	@echo "BINDIR: $(BINDIR)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "TARGET: $(TARGET)"
	@echo "clang-format: clang-format --dump-config --style='{BasedOnStyle: Google, IndentWidth: 4, TabWidth: 4}'"
