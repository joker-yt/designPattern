SRC=01_abstractfactory.cpp \
	05_singleton.cpp \
	20_state.cpp \
	23_visitor.cpp
EXE=$(subst .cpp,.bin,$(SRC))
CPPFLAGS=-std=c++11 -MMD -g

all: $(EXE)
-include $(DEPS)

.SUFFIXES:	.cpp .bin
.cpp.bin:
	g++ $< -o $@ $(CPPFLAGS)

clean:
	rm -fr *.bin *.gch *.d
