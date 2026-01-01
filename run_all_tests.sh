#!/bin/bash

echo "=== LeetCode Study Guide - Running All Tests ==="
echo

# Compile and run all tests
echo "1. Running Common Tests..."
g++ ../tests/test_common.cpp ../src/common.cpp -I../include -lgtest -lgtest_main -pthread -o test_common
./test_common
echo

echo "2. Running Problem Tests..."
g++ ../tests/test_problem.cpp ../src/problem.cpp ../src/solution.cpp ../src/common.cpp -I../include -lgtest -lgtest_main -pthread -o test_problem
./test_problem
echo

echo "3. Running Solution Tests..."
g++ ../tests/test_solution.cpp ../src/solution.cpp ../src/common.cpp -I../include -lgtest -lgtest_main -pthread -o test_solution
./test_solution
echo

echo "4. Running Array Tests..."
g++ ../tests/array_test.cpp -I../include -lgtest -lgtest_main -pthread -o array_test
./array_test
echo

echo "=== All Tests Completed ==="