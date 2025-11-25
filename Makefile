CC = g++
CXXFLAGS = -std=c++20 -I./main -Wall -MMD -MP
APPNAME = Calculator

SRCDIR = main/src
APPDIR = app
OBJDIR = $(APPDIR)/src
EXT = .cpp

SRC = $(shell find $(SRCDIR) -name "*$(EXT)")
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
DEP = $(patsubst $(SRCDIR)/%.cpp, $(APPDIR)/%.d, $(SRC))

all: $(APPNAME)

$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@
	mv $(OBJDIR)/$*.d $(APPDIR)/$*.d

-include $(DEP)

.PHONY: clean
clean:
	rm -rf $(APPDIR) $(APPNAME)
