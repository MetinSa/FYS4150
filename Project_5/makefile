CC := mpic++

SRCDIR := src
BUILDDIR := build
TARGET := run.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTSOURCES := $(shell find src -type f \( -name "*.cpp" ! -name "main.cpp" \))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CPPFLAGS := -O3 -std=c++17
LIB := -larmadillo -llapack -lblas
INC := -I include

$(TARGET):			$(OBJECTS)
					@echo " Linking..."
					$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.$(SRCEXT)
					@mkdir -p $(BUILDDIR)
					$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<
					

# Cleaning		
.PHONY: clean
clean:
					@echo " Cleaning..."; 
					$(RM) $(OBJECTS)
		

