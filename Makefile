MKCWD=mkdir -p $(@D)

CC ?= gcc

SANITIZERS = 			\
	-fsanitize=address 	\
	-fsanitize=undefined

CFLAGS = 			\
		-Os 		\
		-g 		 	\
		-std=c2x	\
		-pedantic	\
		-Wpedantic	\
		-Isrc/      \
		-Werror 	\
		-Wextra 	\
		-Wall 		\
		-Wundef 	\
		-Wshadow 	\
		-Wvla		\
		-I./src		\
		$(SANITIZERS)

LDFLAGS=$(SANITIZERS)

PROJECT_NAME = myelisp
BUILD_DIR = build
SRC_DIR = src

CFILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
DFILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(CFILES))
OFILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))

OUTPUT = $(PROJECT_NAME)


$(OUTPUT): $(OFILES)
	@$(MKCWD)
	@echo " LD [ $@ ] $<"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKCWD)
	@echo " CC [ $@ ] $<"
	@$(CC) $(CFLAGS) -MMD -MP $< -c -o $@ 

run: $(OUTPUT)
	@$(OUTPUT)

all: $(OUTPUT)

clean:
	@rm -rf build/

.PHONY: clean all run

-include $(DFILES)