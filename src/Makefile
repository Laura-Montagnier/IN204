CFLAGS = -g `sdl2-config --cflags` -Wall
LDFLAGS = `sdl2-config --libs`  -lSDL2_ttf -lSDL2_mixer
PROG = ray_tracer
CXX = g++
OBJS = init.o graphics.o main.o

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
%.o: %.cpp %.hpp defs.hpp
	$(CXX) $(CFLAGS) -c $<

# linking the program
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LDFLAGS)

# cleaning everything that can be automatically recreated with "make"
clean:
	rm $(PROG) *.o