BUILD_DIR    := build
SRC_DIR      := src
TEST_DIR     := test
INCLUDE_DIRS := include
LOG_DIR      := log
LIBRARY      := libcutils.a

-include $(SRC_DIR)/sources.make
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# LIBS

CXX_LIBS := -ldl

# COMPILER CONFIG
CC := gcc

CXXFLAGS_DEBUG := -D _DEBUG -ggdb3 -O1

CXXFLAGS_ASAN := -fcheck-new -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CXXFLAGS_RELEASE := -DNDEBUG -O2 -march=native

ifeq "$(TARGET)" "Release"
CXXFLAGS_TARGET := $(CXXFLAGS_RELEASE)
else
CXXFLAGS_TARGET := $(CXXFLAGS_DEBUG) $(CXXFLAGS_ASAN)
endif

CXXFLAGS_WARNINGS := -Wall -Wextra -Waggressive-loop-optimizations -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-varargs -Wstack-protector -Wlarger-than=8192 -Werror=vla -Wstack-usage=8192 

CXX_DEFINES = -D_POSIX_C_SOURCE=202405L -D_GNU_SOURCE

CXXFLAGS := -MMD -MP -std=c11 $(addprefix -I,$(INCLUDE_DIRS)) $(addprefix -I,$(LIBCUTILS_INCLUDE_PATH)) $(CXX_DEFINES) $(CXXFLAGS_WARNINGS) $(CXXFLAGS_ASAN) $(CXXFLAGS_DEBUG)

.PHONY: all
all: $(BUILD_DIR)/$(LIBRARY)

# LIBRARY
$(BUILD_DIR)/$(LIBRARY): $(OBJS)
	@echo -n Archiving $@...
	@ar rcs $@ $(OBJS) 
	@echo done

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Building $@...
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CXXFLAGS) -c $< -o $@ $(CXX_LIBS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LOG_DIR)

-include $(DEPS)
