#!/usr/bin/make -f
default: test

TESTS=auto_matrix_members offset_op step_op limit_op
TEST_OBJECTS=$(TESTS:=.o)
TEST_DEPS=$(TESTS:=.d)
RM ?= rm -f

CPPFLAGS=-I. -I../.. -DBOOST_TEST_DYN_LINK=1
CXXFLAGS=-g -Wall
LDFLAGS=-lboost_unit_test_framework

-include test_runner.d $(TEST_DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LD_FLAGS) $(ARCH_FLAGS) $< $(LOADLIBES) $(LDLIBS) -c -o $@ -MMD -MP

test_runner: test_runner.o $(TEST_OBJECTS)

test_output: test_runner
	./$^ `cat test_params 2>/dev/null` 2>&1 | tee $@ || true

reset-tests:
	$(RM) test_output || true

test:
	@$(MAKE) reset-tests
	@$(MAKE) test_output

clean:
	$(RM) test_output test_runner test_runner.o $(TEST_OBJECTS) || true

.PHONY: default reset-tests test clean
