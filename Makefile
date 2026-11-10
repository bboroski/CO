CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
CPPFLAGS ?= -Iinclude
BUILD_DIR := .build
TEST_BIN := $(BUILD_DIR)/test_runtime
COMPAT_TEST := $(BUILD_DIR)/test_compat
CONSENSUS_TEST := $(BUILD_DIR)/test_consensus

.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): src/runtime.c tests/test_runtime.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_runtime.c -o $@

$(COMPAT_TEST): src/runtime.c tests/test_compat.c include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/runtime.c tests/test_compat.c -o $@

$(CONSENSUS_TEST): src/consensus.c tests/test_consensus.c include/co/consensus.h include/co/runtime.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/consensus.c tests/test_consensus.c -o $@

test: $(TEST_BIN) $(COMPAT_TEST) $(CONSENSUS_TEST)
	./$(TEST_BIN)
	./$(COMPAT_TEST)
	./$(CONSENSUS_TEST)

clean:
	rm -rf $(BUILD_DIR)
