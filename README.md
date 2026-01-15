# LeetCode Solutions (C++)

Repository of my LeetCode solutions written in C++.

## Build and run

### Windows

#### Prerequisites

* CMake 4.2.1
* LLVM clang++ 21.1.8 (target: x86_64-pc-windows-msvc)
* C++23 compiler (set in CMakeLists.txt)
* Windows: VS Build Tools (MSVC toolchain) for linking then targetings *-windows-msvc

#### Commands (PowerShell)

Build a specific solution:

```powershell
.\build.bat 2.TwoPointer\5-LongestPalindromicSubstring\solution.cpp
```

Build with coverage artifacts (written to the same folder):

```powershell
.\build.bat 2.TwoPointer\5-LongestPalindromicSubstring\solution.cpp cov
```

### Linux (TODO)

#### Prerequisites

* CMake
* C++23 (clang++)
* Ninja or Make

#### Commands 

```
TODO: 
  -build.sh or equivalent CMake commands.
```

## Organization

Solutions are grouped by pattern/category (folder prefix):

* `#.PATTERN_FOLDER\#-PROBLEM_FOLDER\solution.cpp`

## Testing

Using Catch2 Testing Suite, test cases are built into each solution.cpp and automatically run. Outputs are generated in terminal.

Alternatively run the following to output .txt:
```powershell
.\#.PATTERN_FOLDER\#-PROBLEM_FOLDER\solution.exe > test_log.txt 2>&1
```

## Patterns & Notes So far
* [Notes Template](0.Notes/0-Template.md)
* Hash Map (`std::unordered_map`)
* Two Pointers

  * Manacher’s Algorithm (palindromic substring)
* Sliding Window
* Binary Search / Partition
* Dynamic Programming
