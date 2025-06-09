##fadinujedat062@gmail.com
# ========== Compiler & Flags ==========
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# ========== Files ==========
MAIN_SRC = main.cpp
DEMO_SRC = Demo.cpp
TEST_SRC = tests.cpp
HEADERS = MyContainer.hpp

MAIN_EXEC = main
DEMO_EXEC = demo
TEST_EXEC = run_tests

# ========== Targets ==========

all: $(MAIN_EXEC) $(DEMO_EXEC)

$(MAIN_EXEC): $(MAIN_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_SRC)

$(DEMO_EXEC): $(DEMO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMO_SRC)

$(TEST_EXEC): $(TEST_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC)

test: $(TEST_EXEC)
	./$(TEST_EXEC) --success --no-skip --reporters=console

valgrind: $(MAIN_EXEC)
	valgrind --leak-check=full ./$(MAIN_EXEC)

clean:
	rm -f $(MAIN_EXEC) $(DEMO_EXEC) $(TEST_EXEC)
