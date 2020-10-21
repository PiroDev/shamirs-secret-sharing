CXX := g++
LFLAGS := -lboost_system
OBJDIR := out
BINDIR := bin
SRCDIR := src
INCDIR := include

OBJECTS := $(OBJDIR)/main.o $(OBJDIR)/crypto_functions.o $(OBJDIR)/input_output.o

CXX_FLAGS := -std=c++17 -Wall -Werror -pedantic -Wextra
CPP_FLAGS := -I$(INCDIR)

ifeq ($(mode), debug)
	CXX_FLAGS += -g3
	CXX_FLAGS += -ggdb
endif

ifeq ($(mode), release)
	CXX_FLAGS += -DNDEBUG -g0
endif

$(BINDIR)/secret.exe : $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) $^ -o $@ $(LFLAGS) 

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp 
	mkdir -p $(OBJDIR)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -rf bin out
