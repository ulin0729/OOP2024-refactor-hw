# OOP 2024 Refactor Homework
## Problem
Judge Girl 10288. Rubik's cube

https://judgegirl.csie.org/problem/216/10288

## Versions
### v1: Original code on judge girl
Nothing to say, so awful.

### v2: Refactor with functions
Put the initialization, output and rotation parts inside seperate functions. This does not reduce the code overall, but the logic is clearer.

### v3: Refactor with structures
Make a structure called "Cube" which put the size and the array itself together. This way, we can know where to find the size of the cube instantly. And, when passing arguments to the functions, we can simply pass one argument instead of several ones. (I also dynamically allocate the memories for array to better support variant sizes of cubes.)

### v4: Refactor with vectors (Convert to C++)
In C++, we have a handy STL called "vector" that is basically a dynamic array. Also, vector can handle the construction and destruction on its own. So, I changed all arrays in previous vertion to vectors.

### v5: Merge two rotation functions using reference functions
The rotation functions modifies different part of the array, which is hard to merge the logic in C.

Specifically, `cube->arr[i][j][layer]` and `cube->arr[layer][i][j]`.

In C, we can easily write an helper function called `get_node()` that returns a value based on different type of rotation. The problem is that, it cannot be used as lvalue, which means we can't assign value to it. We may somehow write a function that returns a pointer to the value and modify the value. But it would be too complicate in practice.

In C++, we can simply make `get_node()` function returns a reference. And boom, everything works! `get_node(cube, type, i, j, layer) = temp[i][j];` is all we need to make it work in C++.

### v6: Refactor using class
When using structure, everything is accessible to any part of the code. What if I accidentally modify the vector inside `struct cube`? To avoid such circumstances, we can use class instead. I put the vector and a function (`get_node()`) that won't be used outside of the class in the private section and only expose the methods (rotate, print) in public section.

Now, everything is inside a class and the main function looks much better then ever.

### v7: Overly complicated but fun refactor using STLs. (C++23 only)

**This is just for fun.** I surveyed the features of modern C++ and found out that there are lots of things that I never heard of. Then, I use `cartesian_product_view()` and `iota_view{}` to eliminate the nested for loops which are intended to generate (i,j,k) tuples only. Ultimately turn the cyclomatic compleity number from 16 to 6 without using "&&, ||" hacks.

## Conclusion
I think OOP is really making writing code easier. My code has a better control flow and a clearer logic than the first version after the refactoring. 

However, I have a slightly different thought on "OOP can be applied to every programming language." 

I think having a good tool is essential in writing OOP codes. For example, I tried using C to write an OOP code (the file is in the repo too) and it turns out to be a big mess. Without native support on encapsulation, inheritance, polymorphism will severely damage the clarity of our codes.
