# CPP Module 09

## Table of Contents
- [Introduction](#introduction)
- [Exercises](#exercises)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [Notes](#notes)
- [License](#license)



## Introduction

This module is part of the **C++ Piscine** at [42 School](https://42.fr).  
It focuses on advanced usage of the Standard Template Library (STL), algorithms, and efficient handling of containers in C++98.

The goal is to strengthen understanding of templates, iterators, and algorithms while building custom containers or utilities that replicate STL behavior.



## Exercises

The module is divided into several exercises:

- **ex00 – Bitcoin Exchange**  
  Parse a CSV file with historical exchange rates and compute values based on an input file.  
  The focus is on file handling, parsing, and using associative containers (`std::map`).

- **ex01 – Reverse Polish Notation (RPN)**  
  Implement a calculator using Reverse Polish Notation.  
  Demonstrates stack operations and algorithmic evaluation.

- **ex02 – PmergeMe**  
  Implement a hybrid sorting algorithm (Ford-Johnson merge-insertion sort) that works with both `std::vector` and `std::deque`.  
  Emphasis on algorithm efficiency, benchmarking, and template programming.



## Requirements

- The project must be implemented in **C++98**.  
- Only the standard library is allowed.  
- Each exercise must compile with the provided `Makefile`.



## Compilation

Each exercise comes with its own `Makefile`. Typical usage:

```bash
make
./program input.txt
