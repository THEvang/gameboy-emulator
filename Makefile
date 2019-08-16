CXX = g++
CXXFLAGS = -Wextra -Werror -Wall -I./include -I./include/glad 
LDLIBS = -lSDL2

TARGET = gameboy.out

src =	$(wildcard *.cpp) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.c)

obj = $(src:.cpp=.o)

$(TARGET) : $(obj)
	$(CXX) -o $@ $^ $(LDLIBS)


.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)