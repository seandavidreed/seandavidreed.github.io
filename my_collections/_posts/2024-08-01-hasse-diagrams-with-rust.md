---
layout: post
title: Hasse Diagrams with Rust
author: Sean David Reed
date: 2024-08-01
category: Mathematics
---

While studying Chapter 0 of the book [Introductory Discrete Mathematics](https://www.goodreads.com/book/show/641871.Introductory_Discrete_Mathematics) in my spare time, I decided to write a program that could generate a [Hasse Diagram](https://en.wikipedia.org/wiki/Hasse_diagram) from a partially-ordered set. I wrote this entry after my first big breakthrough with the program design. In another post, I'll show what I was missing in this implementation.

[The rest of this entry was originally written April 18, 2024]

I called it [Hasse Diagram Generator](https://github.com/seandavidreed/hasse-diagram-generator). I started it as an excuse to learn Rust and also to get a deeper understanding of Partially-Ordered Sets and Hasse Diagrams. I've learned a TON about Rust in the process! I feel comfortable with the syntax now, but I still get tripped up with the concept of ownership from time to time.

Near the beginning of this month, I had a breakthrough in the implementation of my Hasse Diagram Generator. Below is the barely-intelligible white-boarding process I went through to arrive there.

![](/images/2024-08-01-post/hasse_diagram_algo.jpg)

At this point in the development process, I had designed rudimentary structs and impl blocks that could take user input, store it as a set, and finally prompt the user to build a relation out of it. Moreover, I had learned how to use Rusts [imageproc](https://docs.rs/imageproc/latest/imageproc/) crate to draw circles, text, and lines on a blank JPEG image. The most crucial step, that of actually building the Hasse diagram from the data provided, had yet to be implemented.

My main concern was figuring out in what order to draw the vertices so as to preserve the upward orientation, an important feature of the Hasse Diagram. I needed to make some simple algorithm that could accomplish this task. It occurred to me that given any partially-order set, the minimal elements would always need to be drawn first at the base of the diagram. Using the definition of a minimal element,

$u$ is a minimal element if $\forall x \in S,\ (x,u) \in R \implies x = u$,

I wrote a method that could extract the minimal elements from a given instance of the Relation struct I designed. Then, I figured I could create a procedure out of finding minimal elements. Here's what I came up with:

1. Find minimal elements and array them as vertices horizontally on the image above the most recently drawn vertices if they exist.

2. Remove all ordered pairs from Relation that have a minimal element as the left element $(min,\ x)$.

3. Repeat steps 1 and 2 until there are no pairs left in the Relation.

I proved to myself that all Hasse Diagrams could be thus drawn and I was ecstatic! However, I quickly realized this implementation did not account for the connections between vertices. I needed a way keep track of the connections. At first, I thought of using a `HashMap` I called `tree_map`, which I wrote on the board, but I found that wouldn't work.

I decided to pull a strategy from the *graph* implementation playbook, the *Adjacency Matrix*. What I built is essentially the same concept. Since Rust didn't have an easy way to initialize a 2d-array like C, `int array[][10]`, I made a `Matrix` struct that used a basic vector initialized to some value `row * col` where row acts as a *stride* to scale `col` and index the proper location in the vector, simulating two dimensions.

When the user inputs the set elements and builds a relation, a `Relation` struct is instantiated which contains the matrix: every ordered pair is represented with the first element as the row index and the second element as the column index. The actual value stored is a boolean to tell the program whether or not the given pair exists in the relation.

With the `Matrix` data structure, the algorithm had everything it needed:

1. Find minimal elements. To check if an element is minimal, simply find its column and iterate downward across the rows looking for a `true` value at any row index other than that which matches the column index (partially-ordered sets are reflexive, so they will always contain pairs with duplicate elements). If any other `true` value is found, the given element is not minimal. In this way, all minimal elements are found and returned.

    1. Draw the minimum elements as the next layer from the bottom of the image.  
    2. Iterate through `previous_min_elts`, indexing the matrix, to see which elements in the previous layer the current minimum elements connect to. Draw lines between the adjacent elements.  
    3. Save a copy of the minimal elements as previous_min_elts.

2. Remove the minimum elements from the matrix by indexing from the `row` and setting the value at every `col` index to false.
3. Repeat steps 1 and 2 until all values in the matrix are false.

Done! What I stumbled upon while work-shopping with the whiteboard evolved into the final implementation outlined above, which works wonderfully! Here's a screenshot of the CLI app in action with the resulting image:

![](/images/2024-08-01-post/result.png)
