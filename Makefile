CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
CPPFLAGS ?= -Iinclude
BUILD_DIR := .build
TEST_BIN := $(BUILD_DIR)/test_runtime
COMPAT_TEST := $(BUILD_DIR)/test_compat
PLATFORM_TEST := $(BUILD_DIR)/test_platform

.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): src/runtime.c tests/test_runtime.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_runtime.c -o $@

$(COMPAT_TEST): src/runtime.c tests/test_compat.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_compat.c -o $@


$(PLATFORM_TEST): src/platform.c tests/test_platform.c include/co/platform.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/platform.c tests/test_platform.c -o $@

test: $(TEST_BIN) $(COMPAT_TEST) $(PLATFORM_TEST)
	./$(TEST_BIN)
	./$(COMPAT_TEST)
	./$(PLATFORM_TEST)

clean:
	rm -rf $(BUILD_DIR)
