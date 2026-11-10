CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
CPPFLAGS ?= -Iinclude
BUILD_DIR := .build
TEST_BIN := $(BUILD_DIR)/test_runtime
COMPAT_TEST := $(BUILD_DIR)/test_compat

.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): src/runtime.c tests/test_runtime.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_runtime.c -o $@

$(COMPAT_TEST): src/runtime.c tests/test_compat.c include/co/runtime.h include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_compat.c -o $@

test: $(TEST_BIN) $(COMPAT_TEST)
	./$(TEST_BIN)
	./$(COMPAT_TEST)

clean:
	rm -rf $(BUILD_DIR)
