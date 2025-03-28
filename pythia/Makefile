# Define variables for the compiler and flags
CXX = g++
CXXFLAGS = -O2 -std=c++11 -I/Users/magnussellebjerg/Software/pythia8313/include `root-config --cflags`
LDFLAGS = -L/Users/magnussellebjerg/Software/pythia8313/lib -Wl,-rpath,/Users/magnussellebjerg/Software/pythia8313/lib -lpythia8  `root-config --libs`

# Path to your source code
SRC = /Users/magnussellebjerg/BA/pythia/createData.C
# The name of the final executable
TARGET = runScript

# 'all' is a special target that builds the entire project.
all: $(TARGET)

# This rule tells make how to build the executable.
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# The 'clean' target removes the compiled executable.
clean:
	rm -f $(TARGET)
