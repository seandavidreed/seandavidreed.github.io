---
layout: post
title: Static vs. Dynamic Arrays
author: Sean David Reed
---
## What is an Array?

An array is one of the simplest data structures available to the programmer. It stores elements of a given data type, e.g. int, float, char, contiguously in memory, that is, in a sequence with each element directly adjacent to the next.

Many explanations of arrays use the C language to demonstrate how they work. I’ll use Rust, mainly because I’m trying to get better at it! Let’s declare an array of five 32-bit integers in Rust.

```
let arr: [5, i32] = [1, 2, 33, 4, 7];
```

This declaration allocates 20 contiguous bytes of memory since we have five 32-bit integers and 32 bits is 4 bytes. We should expect our memory to look something like below.

Note the memory addresses are in hexadecimal, which is the standard way to represent them. For ease of explanation, I’ll convert them to decimal.

```
0x64 == 100
0x68 == 104
0x6C == 108
0x70 == 112
0x74 == 116
```

The address numbers I selected are pretty small; we should expect to see much larger numbers in practice, but I want to keep things simple. Each address is 4 bytes apart since each one marks the start of a 32-bit integer.

The utility of the array comes from its contiguity. When we want to access an element of the array, we simply index into the array, for example `arr[3] -> 4`. This is possible because of pointer arithmetic, where the index provided designates how far we want to move from the starting address, in this case 0x64 or 100. By providing the index 3, we are saying we want to move 3 lengths of 4 bytes, the size of an element, from our starting address, 100, to the destination address 12 bytes away, 112 or 0x70, where our data `arr[3] -> 4` resides.

No matter how far away our target address is from the starting address, we only ever have to do one calculation to retrieve it.

```
target_address = start_address + index * data_size
```

Therefore, this simple and powerful lookup procedure only ever takes constant time `O(1)`.
## Static Arrays

So far, what we’ve been examining is the static array, which is generally what is meant when the term array is used. It is one block of contiguous space in memory with definite bounds, the starting and ending addresses. Its strength is its simplicity, and when the number of required elements to be stored is known ahead of time, it is typically the best choice of storage.

The simplicity of the static array can also be its weakness, however. Suppose you don’t know ahead of time how many elements will need to be stored in your array, so you declare an array to have some arbitrary size and you plan to simply add more addresses to the end the array if you reach capacity.

There’s a problem. When an array is allocated, the contiguous block of memory is allocated all at once. This is the only way to ensure that the space is indeed contiguous, an attribute we found is necessary for our linear time O(1) indexing. Our program must look for an empty space in memory that is at least the size of our array. Once allocated, there’s no telling whether there’s data stored at addresses near to, but separate from, our array. If we were somehow able to add more addresses to the end of our array to accommodate more elements, we might accidentally overwrite data that belongs to a different variable or even a different program or process. Therefore, most programming languages won’t let us do such a thing by default.

In a moment, we’ll see how this dilemma can be solved with the dynamic array, but before we go there, let’s look at an implementation of a static array. We’ll print both the elements and their addresses in memory to see if it matches up with our expectation of contiguity.

```
fn unsafe_print(array: &mut [i32]) {
    let my_num_ptr: *mut i32 = &mut array[0];
    unsafe {
        for i in 0..array.len() {
            println!(
                "{:?} {:?}", 
                my_num_ptr.add(i), 
                *my_num_ptr.add(i)
            );
        }
    }
}

fn main() {
    let mut my_array: [i32; 5] = [1,2,33,4,7];
    unsafe_print(&mut my_array);
}
```

When I run this in my terminal, I get the following results.

Plainly, the first 8 digits of the addresses are identical, so we can analyze the final four digits and see if they are indeed 4 bytes apart.

```
0x7ff4 == 32756
0x7ff8 == 32760
0x7ffc == 32764
0x8000 == 32768
0x8004 == 32772
```

As expected!
## Dynamic Arrays

Let’s review the problem we encountered with static arrays. We have 20 contiguous bytes of memory allocated for our array, but in the course of our programs runtime, a new element needs to be added such that no other element is overwritten. We need our array to accommodate 24 bytes of data. However, we cannot simply extend the array by adding available addresses to the end of it. Such a procedure would very possibly overwrite and corrupt data that belongs to a different variable in our program or in a different program altogether.

Instead, we have to allocate a new array of a larger size and copy our elements into it. This resize operation is a more expensive since it requires us to visit all n elements in our array of size n. It will take linear time `O(n)` to achieve this. The resize operation is what differentiates the dynamic array from the static array.

First, let’s look at an inefficient way to reallocate our array. Suppose we want to add the element 52 to our array at `arr[5]`, which exceeds the bounds of our array. We declare a 24 byte array which allocates a contiguous block at some other corner of memory and copy over our elements from the 20 byte array, which is then destroyed. We’ve successfully added a new element to our array, but we still find ourselves with an array at max capacity, which means we will have to perform this expensive copying operation `O(n)` the next time we need to add a new element. This is very inefficient. If we designed our dynamic array in this manner, the append operation will always take linear time `O(n)`.

To fix this, we need the size by which we increase the array to be proportional to the initial size instead of merely a constant. Every time our array is at max capacity and we want to append a new element, we will double the size of our array.

```
fn main() {
    let mut my_array: [i32; 5] = [1,2,33,4,7];
    let mut my_doubled_array: [i32; 10] = [0; 10];

    let mut i = 0;
    while i < 5 {
        my_doubled_array[i] = my_array[i];
        i += 1;
    }

    my_doubled_array[i] = 52;
    
    unsafe_print(&mut my_array);
    println!();
    unsafe_print(&mut my_doubled_array);
}
```

In the program output below, note that the addresses of `my_doubled_array` are completely separate from the addresses of `my_array`, just as expected.
## Amortized Analysis

Consider the static array for a moment. Appending a new element takes constant time O(1). It always takes only 1 operation to store 1 element. This is also true with dynamic arrays, but we have to consider an additional cost that occasionally occurs. Whenever we have to double the capacity of our array to make room for new elements, we must copy over all the previously stored elements into a new doubled array. This operation will cost O(n), where n is the size of the array that needs to be copied.

We know that the append operation takes `O(1)` time for static arrays; we want to know the time complexity of the append operation for dynamic arrays, taking the resize operation into consideration. I’ll put my cards on the table: it’s also going to be `O(1)`. And we can show this with amortized analysis.

Simply stated, our resize operation does not occur with every append operation, far from it. Instead, it occurs less and less frequently as more and more elements are appended. So to consider this cost, we will spread it out, that is amortize it, across the total number of append operations. We will be left with an amortized time complexity of `O(1)` for each append operation.

First, we’ll run the numbers with our example array of size 5 from before. Suppose in the course of appending 640 elements,the capacity of our array increased as below.

```
5 -> 10 -> 20 -> 40 -> 80 -> 160 -> 320 -> 640
```

We began with an array of size 5 which was empty, and over the course of the program, we performed 640 append operations. Only 7 of those append operations involved the `O(n)` resizing procedure! Let’s express that mathematically.

To get to an array of size 640, we repeatedly multiplied by 2, which is the process of exponentiation. To find out how many times we multiplied by 2, we can apply the inverse operation of exponentiation to 640, namely the logarithm.

```
\log_2{640} \approx 9.32
```

Not only is this number too high, but we need an integer. In our example, our array began at size 5, not 2 which the above calculation assumes. We need to subtract the number of times 2 is doubled to reach 5.

```
\log_2{640} - \log_2{5} = 7
```

In other words, we performed the resize operation 7 times over the course of appending 640 elements. Recall that the resize operation will cost O(n), where n is the size of the array that needs to be copied. Let’s add up all the operations.

```
\underbrace{640}_{appends} + \underbrace{5 + 10 + 20 + 40 + 80 + 160 + 320}_{elements\ copied\ during\ resizes} = 1275
```

Note that the total operations is nearly double that of the number of elements (n = 640) appended, so our time complexity is `O(2n)`. However, we want to amortize this cost across the total number of appends.

```
\frac{O(2n)}{n} = O(2) = O(1)
```

Every append operation has an amortized cost of O(1). Let’s formalize everything we did here.

```
\begin{aligned}  &amortized\ cost\ = (n + \displaystyle\sum_{i = 1}^{\log_2{n}} 2^{i-1}) / n \\  &amortized\ cost\ = \frac{O(2n)}{n} \\ &amortized\ cost\ = O(1) \end{aligned} 
```

The equation above applies to a more generic example where the arrays sizes are powers of 2. In our case, we start with size 5 and repeatedly double it from there, so our exact implementation looks like this.

```
\begin{aligned} &amortized\ cost\ = (n + \displaystyle5 \times \sum_{i = 1}^{\log_2{n}-\log_2{5}} 2^{i-1}) / n \\ &amortized\ cost\ = \frac{O(2n)}{n} \\ &amortized\ cost\ = O(1) \end{aligned} 
```

## Conclusion

The dynamic array is so commonly used that many programming languages have it implemented in their standard library. C++ has std::vector, Rust has std::vec, and Python has list, just to name a few. Each of these implementations involves increasing the size of the array by some factor between 1.25 and 2 whenever the array reaches max capacity.
