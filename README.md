# LeetCode Study Guide - C++ Implementation

A comprehensive C++ study guide covering essential data structures and algorithms for technical interviews and competitive programming.

## 🚀 Features

- **Complete Data Structures**: Trees, Heaps, Graphs, Arrays, and more
- **Algorithm Patterns**: DFS, BFS, Dynamic Programming, Two Pointers, etc.
- **Comprehensive Tests**: 48+ unit tests with Google Test framework
- **Modern C++**: C++17 standard with smart pointers and RAII
- **CMake Build System**: Cross-platform build support
- **Detailed Documentation**: Extensive comments and complexity analysis

## 📁 Project Structure

```
├── include/                    # Header files
│   └── leetcode_study_guide/
│       └── data_structures/    # Data structure implementations
├── src/                        # Source files
├── tests/                      # Unit tests
├── docs/                       # Documentation
├── CMakeLists.txt             # CMake configuration
└── README.md                  # This file
```

## 🛠️ Build Instructions

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+)
- CMake 3.16+
- Google Test library

### Ubuntu/WSL2
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake libgtest-dev

# Build project
mkdir build && cd build
cmake ..
make

# Run tests
./run_tests
# or
make test
```

## 🧪 Testing

The project includes comprehensive unit tests:

```bash
# Run all tests
./build/run_tests

# Run specific test suites
./build/run_tests --gtest_filter="*Tree*"
./build/run_tests --gtest_filter="*Heap*"
./build/run_tests --gtest_filter="*Graph*"
```

## 📚 Covered Topics

### Data Structures
- [x] Binary Trees & Binary Search Trees
- [x] Heaps (Min/Max) & Priority Queues
- [x] Graphs (Directed/Undirected, Weighted)
- [x] Tries (Prefix Trees)
- [ ] Arrays & Dynamic Arrays
- [ ] Linked Lists
- [ ] Stacks & Queues

### Algorithms
- [x] Tree Traversals (DFS, BFS, Inorder, Preorder, Postorder)
- [x] Graph Algorithms (DFS, BFS, Shortest Path)
- [x] Heap Operations & Heap Sort
- [ ] Sorting Algorithms
- [ ] Dynamic Programming
- [ ] Two Pointers & Sliding Window

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🎯 Roadmap

- [ ] Complete array and linked list implementations
- [ ] Add more algorithm patterns
- [ ] Performance benchmarks
- [ ] Interactive examples
- [ ] LeetCode problem mappings

## 📞 Contact

terrense - slamshenxin@gmail.com

Project Link: [https://github.com/terrense/leetcode-study-guide](https://github.com/terrense/leetcode-study-guide)