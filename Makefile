KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

MODULE_NAME := kernel_stack


SRC_DIR := src
LIB_DIR := lib
INC_DIR := inc
LIB_INC_DIR := $(LIB_DIR)/inc

BUILD_DIR := $(PWD)/build
BUILD_FILES += $(PWD)/*.ko
SOURCES := $(SRC_DIR)/*.c


CLANG_FORMAT_VER ?= 19
CLANG_FORMAT := clang-format-$(CLANG_FORMAT_VER)
CLANG_FORMAT_FLAGS += -i
FORMAT_FILES := $(SRC_DIR)/*.c $(LIB_DIR)/*.c \
	$(INC_DIR)/*.h $(LIB_INC_DIR)/*.h

$(shell mkdir -p $(BUILD_DIR))



kbuild:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
	mv $(BUILD_FILES) $(BUILD_DIR)

format:
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(FORMAT_FILES)

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
	rmdir $(BUILD_DIR)

check:
	checker/check.sh

.PHONY: kbuild format clean check
