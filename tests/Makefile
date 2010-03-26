#!/usr/bin/make -f
default: test

TESTS=auto_matrix_members offset step limit
TEST_OBJECTS=$(TESTS:=.o)
TEST_DEPS=$(patsubst %,.%.d,$(TESTS))
RM ?= rm -f

CPPFLAGS=-I. -I../.. -DBOOST_TEST_DYN_LINK=1
CXXFLAGS=-g -Wall
LDFLAGS=-lboost_unit_test_framework

-include .test_runner.d $(TEST_DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LD_FLAGS) $(ARCH_FLAGS) $< $(LOADLIBES) $(LDLIBS) -c -o $@ -MMD -MP -MF .$*.d

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

reallyclean: clean
	$(RM) $(TEST_DEPS)

.PHONY: default reset-tests test clean
