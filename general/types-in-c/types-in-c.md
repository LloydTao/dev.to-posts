Types in C: The void (\*(\*[])())()

## Introduction

### Program Memory

One of the C language's superpowers is its low-level memory management.

You've likely manipulated memory before. Most languages allow you to pass variables by reference (i.e. its memory address) as well as by value (i.e. a copy is made so that there are no side effects).

![Pass by Reference vs. Pass by Value Analogy](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/types-in-c/pass-by-reference-vs-pass-by-value.gif)

C gives developers a standard low-level interface to program memory on both the heap and the stack. 

An important part of this interface is **pointer** types. 

### Pointers

Put simply, a pointer is a variable that stores a memory address to another variable. 

Since a pointer is a variable, we can have a pointer to a pointer. And a pointer to a pointer to a pointer. And so on, and forever. See this diagram for reference:

![Pointer to a Pointer to a Pointer to a Variable](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/types-in-c/pointers-to-pointers.jpg)

---

## The void (\*(\*[])())()

### "What?"

Using the awesome converter at [cdecl.org](https://cdecl.org/?q=void+%28*%28*foo%5B%5D%29%28%29%29%28%29), we can see what this type declaration really means.

![Conversion with cdecl](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/types-in-c/cdecl.png)

Let's work backwards to understand what's going on.

### Breakdown
```
         foo            -- foo
         foo[]          -- is an array
        *foo[]          -- of pointers
       (*foo[])()       -- to functions
      *(*foo[])()       -- returning pointers
     (*(*foo[])())()    -- to functions
void (*(*foo[])())();   -- returning void
```

Now that we understand the individual components, let's create it!

### Function returning Void

A function that doesn't return anything (i.e. a procedure) is a void function.

For this, we'll define a function that prints "Apple!".

```c
void apple() {
    printf("Apple!\n");
}
```

### Pointer to a Function returning Void

This is simple. It's a pointer to the function that we just declared.

```c
&apple;
```

### Function returning a Pointer to a Function returning Void

We need a function that returns `&apple`. The hard part here is the type signature. 

```c
void (*pointer_to_apple())() {
    return &apple;
}
```

One mistake [I made](https://www.reddit.com/r/C_Programming/comments/gq171w/pointer_to_function_returning_void_vs_pointer_to/) initially was declaring this as `void *pointer_to_apple()`. This would be incorrectly returning a `Pointer to Void`, as opposed to a `Pointer to a Function returning Void`.

You may wish to look at the syntax of [Function Pointers](https://www.geeksforgeeks.org/function-pointer-in-c/) in order to understand this better.

### Pointer to a Function returning a Pointer to a Function returning Void

This is simple again. It's a pointer to this new function.

```c
&pointer_to_apple;
```

### Array of Pointers to Functions returning a Pointer to a Function returning Void

The final step, and an easy one at that. Pretending we defined two similar sets of functions and pointers, we can an array of these new pointers.

```c
{
    &pointer_to_apple,
    &pointer_to_banana,
    &pointer_to_cherry
};
```

Let's define a variable with this array. 

Our variable **foo** is an array of of type `void (*(*[])())()` with a size of **3**.
```c
void (*(*foo[3])())() = {
    &pointer_to_apple,
    &pointer_to_banana,
    &pointer_to_cherry
};
```

### Using this Array

We can now iterate through the array to print our various fruits.

The only boilerplate here is getting the size of a `void (*(*[])())()`. *This is standard for iterating through arrays in C, as using the sizeof operator to determine the size of arrays is [error prone](https://wiki.sei.cmu.edu/confluence/display/c/ARR01-C.+Do+not+apply+the+sizeof+operator+to+a+pointer+when+taking+the+size+of+an+array)*.

```c 
size_t n = sizeof(foo)/sizeof(foo[0]);
```

We can now iterate through the array. As each element is effectively a pointer to a function returning a pointer to a function, we use `foo[i]()()`, which calls each function pointed to.

```c
for (int i = 0; i < n; ++i) {
    foo[i]()();
}
```

Let's check the output.

```
>>> Apple!
>>> Banana!
>>> Cherry!
>>> 
>>> Process finished with exit code 0
```

Success!

### Example Code

You can check this code out in my [GitHub repository](https://github.com/LloydTao/dev.to-posts/blob/master/general/types-in-c/main.c).

```c
#include <stdio.h>

void apple() {
    printf("Apple!\n");
}

void banana() {
    printf("Banana!\n");
}

void cherry() {
    printf("Cherry!\n");
}

void (*pointer_to_apple())() {
    printf("Getting pointer to apple.\n");
    return &apple;
}

void (*pointer_to_banana())() {
    printf("Getting pointer to banana.\n");
    return &banana;
}

void (*pointer_to_cherry())() {
    printf("Getting pointer to cherry.\n");
    return &cherry;
}

int main() {
    void (*(*foo[3])())() = {
            &pointer_to_apple,
            &pointer_to_banana,
            &pointer_to_cherry
    };
    size_t n = sizeof(foo) / sizeof(foo[0]);
    for (int i = 0; i < n; ++i) {
        foo[i]()();
    }
    return 0;
}
```

---

Hey, guys! Thank you for reading. I hope that you enjoyed this.

Keep up to date with me:

- DEV: https://dev.to/tao/
- Twitter: https://twitter.com/LloydTao
- GitHub: https://github.com/LloydTao
- LinkedIn: https://www.linkedin.com/in/LloydTao/

Catch you around!
