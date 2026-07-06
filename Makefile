CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -g -fexec-charset=UTF-8
INCLUDES = -Iinclude -Itests

SRC_DIR  = src
TEST_DIR  = tests
BUILD_DIR = build

CORE_SRCS = $(wildcard $(SRC_DIR)/*.c)
CORE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(CORE_SRCS))

MAIN_OBJ      = $(BUILD_DIR)/src/main.o
CORE_LIB_OBJS = $(filter-out $(MAIN_OBJ),$(CORE_OBJS))

TEST_SRCS   = $(filter-out $(TEST_DIR)/testing.c,$(wildcard $(TEST_DIR)/*.c))
TEST_OBJS   = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/tests/%.o,$(TEST_SRCS))
TESTING_OBJ = $(BUILD_DIR)/tests/testing.o

TEST_NAMES   = test_utils test_poly_funcs
TEST_TARGETS = $(addprefix $(BUILD_DIR)/,$(TEST_NAMES))

TARGET = $(BUILD_DIR)/app

.PHONY: all run test clean dirs test-utils test-poly test-all show

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)/src $(BUILD_DIR)/tests

$(TARGET): $(CORE_LIB_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/test_utils: $(BUILD_DIR)/tests/test_utils.o $(CORE_LIB_OBJS) $(TESTING_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(BUILD_DIR)/test_poly_funcs: $(BUILD_DIR)/tests/test_poly_funcs.o $(CORE_LIB_OBJS) $(TESTING_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

test-utils: $(BUILD_DIR)/test_utils
	@echo
	@echo "ТЕСТЫ UTILS"
	@./$(BUILD_DIR)/test_utils

test-poly: $(BUILD_DIR)/test_poly_funcs
	@echo
	@echo "ТЕСТЫ POLY_FUNCS"
	@./$(BUILD_DIR)/test_poly_funcs

test-all: $(TEST_TARGETS)
	@echo
	@echo "ЗАПУСК ВСЕХ ТЕСТОВ"
	@echo
	@./$(BUILD_DIR)/test_utils
	@echo
	@./$(BUILD_DIR)/test_poly_funcs
	@echo "ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ"

tests: test-all

run: all
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	@echo "Очистка завершена"

-include $(CORE_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)