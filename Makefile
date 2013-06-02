# Generic Makefile for compiling a simple executable.
#
#
CC := gcc
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall
LNFLAGS := -lncurses
TARGET := antares

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $(LNFLAGS) $^ -o $(TARGET)
	@mkdir -p dist
	@mv $(TARGET) dist/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)
	@rm -Rf dist

-include $(DEPS)

.PHONY: clean
