CXX = gcc
CC = $(CXX)
CFLAGS = -Wall -Wextra -std=c99 -lpthread -lm -g -DDEBUG

SRC_FILES = $(wildcard src/*.c) $(wildcard src/**/*.c)
TST_FILES = $(wildcard test/*.c) $(wildcard test/**/*.c) $(wildcard test/**/**/*.c)
TO_TEST_FILES = $(filter-out src/main.c, $(SRC_FILES))

OBJECTS = $(SRC_FILES:%.c=%.o)
OBJECTS_TO_TEST = $(TO_TEST_FILES:%.c=%.o)
OBJECTS_TEST = $(TST_FILES:%.c=%.o)
TARGET = polyregress
TARGET_TEST = polyregress_test

.PHONY: all
	all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJECTS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)

.PHONY: trace
trace:
	valgrind --tool=drd --show-stack-usage=yes ./$(TARGET)

.PHONY: profile
profile:
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./$(TARGET)

.PHONY: debug
debug:
	gdb ./$(TARGET)

.PHONY: doc
doc:
	doxygen doc/polygress.conf

.PHONY: cleandoc
cleandoc:
	rm -rf doc/html

.PHONY: check
check:
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem ./src -I ./src

.PHONY: test
test:$(OBJECTS_TEST) 
	$(CXX) $(OBJECTS_TO_TEST) $(OBJECTS_TEST) $(CFLAGS) -lcunit -o $(TARGET_TEST)

.PHONY: cleantest
cleantest:
	rm -rf $(TARGET_TEST) $(OBJECTS_TEST)	
	