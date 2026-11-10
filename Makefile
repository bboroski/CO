CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
CPPFLAGS ?= -Iinclude
BUILD_DIR := .build
TEST_BIN := $(BUILD_DIR)/test_runtime
COMPAT_TEST := $(BUILD_DIR)/test_compat
PIPELINE_TEST := $(BUILD_DIR)/test_pipeline

.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): src/runtime.c tests/test_runtime.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_runtime.c -o $@

$(COMPAT_TEST): src/runtime.c tests/test_compat.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_compat.c -o $@


$(PIPELINE_TEST): src/pipeline.c tests/test_pipeline.c include/co/pipeline.h include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/pipeline.c tests/test_pipeline.c -o $@

test: $(TEST_BIN) $(COMPAT_TEST) $(PIPELINE_TEST)
	./$(TEST_BIN)
	./$(COMPAT_TEST)
	./$(PIPELINE_TEST)

clean:
	rm -rf $(BUILD_DIR)
