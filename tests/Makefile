default: test

CPPFLAGS=-I. -I../.. -DBOOST_TEST_DYN_LINK=1
LDFLAGS=-lboost_unit_test_framework

TESTS=auto_matrix_tests
TEST_DEPS=$(TESTS:=.d)
TEST_STAMPS=$(patsubst %,.%.stamp,$(TESTS))

-include $(TEST_DEPS)

$(TESTS): %: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LD_FLAGS) $(ARCH_FLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@ -MMD -MP

$(TEST_STAMPS): .%.stamp: %
	./$^ $(TEST_PARAMS) 2>&1 | tee $@

build-tests: $(TESTS)

run-tests: $(TEST_STAMPS)

reset-tests:
	rm -f $(TEST_STAMPS) || true

test: build-tests run-tests

clean:
	rm -f $(TESTS) || true
	rm -f $(TEST_DEPS) || true
	rm -f $(TEST_STAMPS) || true

.PHONY: build-tests run-tests reset-tests test clean
