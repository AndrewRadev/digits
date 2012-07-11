CC=cc $(CFLAGS)
CXX=g++ $(CFLAGS)
CFLAGS=-g -O2 -Wall -Wextra -I./src -I./lib -rdynamic $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.cpp src/*.cpp lib/**/*.cpp lib/*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.cpp,%,$(TEST_SRC))

TARGET=libdigits.a

# The Target Build
all: $(TARGET) bin/grayscale

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

bin/grayscale: $(TARGET)
	$(CXX) $(LIBS) -o bin/grayscale tests/grayscale.cpp $(TARGET)

bin/threshold: $(TARGET)
	$(CXX) $(LIBS) -o bin/threshold tests/threshold.cpp $(TARGET)

bin/convolution: $(TARGET)
	$(CXX) $(LIBS) -o bin/convolution tests/convolution.cpp $(TARGET)

bin/invert: $(TARGET)
	$(CXX) $(LIBS) -o bin/invert tests/invert.cpp $(TARGET)

bin/scale: $(TARGET)
	$(CXX) $(LIBS) -o bin/scale tests/scale.cpp $(TARGET)

bin/rotate: $(TARGET)
	$(CXX) $(LIBS) -o bin/rotate tests/rotate.cpp $(TARGET)

bin/trim: $(TARGET)
	$(CXX) $(LIBS) -o bin/trim tests/trim.cpp $(TARGET)

bin/overlap: $(TARGET)
	$(CXX) $(LIBS) -o bin/overlap tests/overlap.cpp $(TARGET)

bin/main: $(TARGET)
	$(CXX) $(LIBS) -o bin/main main.cpp $(TARGET)

run: bin/grayscale bin/threshold bin/convolution bin/invert bin/scale bin/rotate bin/trim bin/overlap bin/squeeze_match bin/main
	./bin/main experiments/example_rotated.bmp

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

build:
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|strpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions
	@egrep $(BADFUNCS) $(SOURCES) || true
