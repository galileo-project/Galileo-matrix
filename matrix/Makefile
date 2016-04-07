AR_TARGET      = libmatrix.a
TEST_TARGET    = test.out
CC             = gcc
AR             = ar
ARFLAGS        = -crv
CFLAGS         = -I src -std=c99
AR_CFILES      = $(notdir $(wildcard ./src/*.c))
TEST_CFILES    = $(notdir $(wildcard ./test/*.c))
AR_OBJS        = $(patsubst %.c, %.o, $(AR_CFILES))
TEST_OBJS      = $(patsubst %.c, %.o, $(TEST_CFILES))
INCLUDE_FILES  = $(wildcard ./src/*.h)
INCLUDE_DIR    = /usr/local/include
INSTALL_DIR    = /usr/local/lib

VPATH          = src:test

$(AR_TARGET): $(AR_OBJS)
	@echo compile archive target
	$(AR) $(ARFLAGS) $@ $?
    
.PHONY: test
test: $(TEST_OBJS) $(AR_TARGET)
	@echo compile test target
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)

.PHONY: install
install: $(AR_TARGET) $(INCLUDE_FILES)
	@echo installing $(AR_TARGET) to $(INSTALL_DIR) ...
	cp $(AR_TARGET) $(INSTALL_DIR)
	cp -r $(INCLUDE_FILES) $(INCLUDE_DIR)

$(AR_OBJS):   $(AR_CFILES)
$(TEST_OBJS): $(TEST_CFILES)

.PHONY: clean
clean:
	-rm -rf $(TEST_OBJS) $(AR_OBJS) $(TEST_TARGET) $(AR_TARGET) 
