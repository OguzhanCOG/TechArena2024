# Compiler and tools
CC=/usr/bin/clang-16
CXX=/usr/bin/clang++-16
LD=/usr/bin/ld.lld-16

# Include directories
INCLUDES=$(TECHARENA24_TASK2_DIR)/common/install/include
COMMON_INCLUDES=$(TECHARENA24_TASK2_DIR)/common
SYSROOT=$(TECHARENA24_TASK2_DIR)/common/install
LIBS=$(TECHARENA24_TASK2_DIR)/common/install/lib
DYN_INSTR_COUNT_DIR=$(TECHARENA24_TASK2_DIR)/common/DynamicInstructionCounting

# Flags
CXXFLAGS=--sysroot $(SYSROOT) -nostdlib -nostdinc++ -nostdlib++     -isystem $(INCLUDES)/c++/v1/ -isystem $(INCLUDES)/x86_64-pc-linux-musl/c++/v1     -isystem $(COMMON_INCLUDES)     -fPIC     -fuse-ld=$(LD) -Wno-unused-command-line-argument     -D _LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION

LDFLAGS=--sysroot $(SYSROOT) -nostdlib -nostdinc++ -nostdlib++     -L $(LIBS) -Wl,--rpath,$(LIBS) -L $(LIBS)/x86_64-pc-linux-musl     -Wl,-rpath,$(LIBS)/x86_64-pc-linux-musl     -L $(DYN_INSTR_COUNT_DIR) -Wl,--rpath,$(DYN_INSTR_COUNT_DIR)     -latomic -lc++ -lc -lc++abi -lunwind -lDynamicInstructionCounting_API     -lboost_program_options     -fuse-ld=$(LD) -Wno-unused-command-line-argument

CXXFLAGS += -fpass-plugin=$(DYN_INSTR_COUNT_DIR)/libDynamicInstructionCounting.so

SRC_FILES := $(wildcard ./*.cpp)
OBJ_FILES := $(patsubst ./%.cpp,./%.o,$(SRC_FILES))

# Build target
all: $(OBJ_FILES)
    $(CC) $(LDFLAGS) $^ -shared -o libTask12HybridPredictionAlgorithm.so

./%.o: ./%.cpp
    $(CC) -c $(CXXFLAGS) -o $@ $<

clean:
    rm -rf *.o libTask12HybridPredictionAlgorithm.so
