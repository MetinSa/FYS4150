CC := c++

SRCDIR := src
BUILDDIR := build
TARGET := run.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)" )
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INCLUDES := $(shell find $(SRCDIR) -type f -name "*.h" )
CPPFLAGS := -O3 -std=c++17
LIB := -larmadillo -llapack -lblas

TESTDIR := test
TESTSOURCES := $(shell find $(TESTDIR) -type f -name "*.$(SRCEXT)" )
FUNCSOURCES := $(shell find $(SRCDIR) -type f \( -name "*.$(SRCEXT)" ! -name "main.cpp" \))
TESTEXEC := $(patsubst $(TESTDIR)/%,$(TESTDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.x))
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(TESTDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))
FUNCOBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(FUNCSOURCES:.$(SRCEXT)=.o))

$(TARGET):			$(OBJECTS)
					@echo " Linking..."
					$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.$(SRCEXT) $(INCLUDES)
					@mkdir -p $(BUILDDIR)
					$(CC) $(CPPFLAGS) -c -o $@ $<
					

# Cleaning		
.PHONY: clean
clean:
					@echo " Cleaning..."; 
					$(RM) $(OBJECTS)
		

