CXX := g++

SRC_DIR 	:= src
BUILD_DIR 	:= build
INCLUDE_DIR := include

CXX_FLAGS 	:= -msse4.2 -mavx2 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SRC_FILES	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES   := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
# OBJ_FILES	:= $(wildcard $(BUILD_DIR)/*.o)

TARGET		:= hash_table.out

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/*.h
	$(CXX) -c $(CXX_FLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o *.out

#  & nasm -f elf64 $(SRC_DIR)/CRC32.s -o $(BUILD_DIR)/CRC32.o
