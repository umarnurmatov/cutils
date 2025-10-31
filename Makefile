BUILD_DIR    := build
SRC_DIR      := src
TEST_DIR     := test
INCLUDE_DIRS := include
LOG_DIR      := log
LIBRARY      := libcutils.a

-include $(SRC_DIR)/sources.make
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# COMPILER CONFIG
CC := g++

CPPFLAGS_DEBUG := -D _DEBUG -ggdb3 

CPPFLAGS_ASAN := -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CPPFLAGS_WARNINGS := -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -Wlarger-than=8192 -Werror=vla -Wstack-usage=8192 

CPPFLAGS := -MMD -MP $(addprefix -I,$(INCLUDE_DIRS)) $(addprefix -I,$(LIBCUTILS_INCLUDE_PATH)) -std=c++17 -O0 $(CPPFLAGS_WARNINGS) $(CPPFLAGS_ASAN) $(CPPFLAGS_DEBUG)

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
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LOG_DIR)

-include $(DEPS)
