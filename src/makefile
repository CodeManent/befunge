## Build flags for all targets
#
ifndef CXX
	CXX = g++-4.8
endif

CXXFLAGS += -g -pedantic -Wall -Werror -Wextra -std=c++11
CC       = $(CXX)
CFLAGS   = $(CXXFLAGS)
LDFLAGS +=
LF_ALL   +=
LL_ALL   +=

TARGET_BIN=befunge
BINDIR=../bin

# Used to colourise the output
RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m


###############################################################################
#compilation rules
$(BINDIR)/%.o: %.cpp $(BINDIR)/%.d
	@printf "$(RED)Compiling:$(NC) $<\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BINDIR)/%.o: %.cc $(BINDIR)/%.d
	@printf "$(RED)Compiling:$(NC) $<\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(BINDIR)/%.o: %.c $(BINDIR)/%.d
	@printf "$(RED)Compiling:$(NC) $<\n"
	@$(CC) $(CXXFLAGS)  -c -o $@ $<

###############################################################################
#Makefile driver creation rules
$(BINDIR)/%.d: %.c
	@$(CC) $(CXXFLAGS) $< -MM -MF $@ -MT '$(@:%.d=%.o)'

$(BINDIR)/%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MF $@ -MT '$(@:%.d=%.o)'

$(BINDIR)/%.d: %.cc
	@$(CXX) $(CXXFLAGS) $< -MM -MF $@ -MT '$(@:%.d=%.o)'

###############################################################################
# Standard things
.PHONY: all
all: $(TARGET_BIN)

###############################################################################
# The main source variable
SRC=

#Anything extra that should be deleted on clean
CLEAN=


###############################################################################
dir:=
include Rules.mk


###############################################################################
# The tree traversal has now been completed.
# We exctract the object/dependency file names from the soure names and compile
OBJS = $(SRC:%.cpp=$(BINDIR)/%.o)
DEPS = $(SRC:%.cpp=$(BINDIR)/%.d)

-include $(DEPS)

$(TARGET_BIN): $(OBJS)
	@printf "Building (linking) target bin: $(GREEN)$(TARGET_BIN)$(NC)\n"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


###############################################################################
.PHONY: clean
clean:
	$(RM) $(CLEAN) $(OBJS) $(DEPS) $(TARGET_BIN)

.PHONY: run
run: $(TARGET_BIN)
	./$(TARGET_BIN)

.PHONY: test
test: $(TARGET_BIN)
	./$(TARGET_BIN) --test

# Check the code using cppcheck.
.PHONY: check
check:
	cppcheck --enable=all -q .

