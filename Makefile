CXX = g++
CXXFLAGS = -Wextra -Werror -Wall -I./include

TARGET = gameboy.out

src =	$(wildcard *.cpp) \
		$(wildcard src/*.cpp)

obj = $(src:.cpp=.o)

$(TARGET) : $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)