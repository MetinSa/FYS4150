CC := c++

SRCDIR := src
BUILDDIR := build
TARGET := run.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CPPFLAGS := -O3 -std=c++17
LIB := -L lib -larmadillo -llapack -lblas
INC := -I include

$(TARGET):			$(OBJECTS)
					@echo " Linking..."
					$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.$(SRCEXT)
					@mkdir -p $(BUILDDIR)
					$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

clean:
					@echo " Cleaning..."; 
					$(RM) $(OBJECTS) $(TARGET)
					
cleantest:
					@echo " Cleaning..."; 
					$(RM) -r test.x


# Tests
test.x:
					$(CC) $(CPPFLAGS) test/test.cpp $(INC) $(LIB) -o test.x


.PHONY: clean