SDIR := src
BUILD_DIR := build
MAIN_FILE := MiniDuckSimulator

SRC := $(shell find $(SDIR) -name "*.java")
CLASS := $(patsubst $(SDIR)/%.java,$(BUILD_DIR)/%.class,$(SRC))

JAVAC := javac
JAVA := java

all: compile

compile: $(CLASS)

$(CLASS): $(SRC) | $(BUILD_DIR)
	$(JAVAC) -d $(BUILD_DIR) $(SDIR)/*.java

run: compile
	@cd $(BUILD_DIR) && $(JAVA) $(MAIN_FILE)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
re: clean
	$(MAKE) compile
