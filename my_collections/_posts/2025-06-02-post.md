---
layout: post
title: Tetration and Iterated Log
author: Sean David Reed
date: 2025-06-02
category: Mathematics
---

## Introduction
I wrote this bit about an obscure mathematical concept, _Tetration_, in January 2024. At the time, I was taking an online course called [Algorithms for Searching, Sorting, and Indexing](https://coursera.org/share/88d8b9b89089006c432068246a24022c) offered by University of Colorado Boulder, and we were covering _Iterated Logarithms_.

Now, I don't consider myself extraordinarily gifted at Mathematics, but I do find it very engaging whenever I have the pleasure of studying it. It's a common experience for me to so engrossed in a concept I'm learning about that I have dreams about it or wake up in the middle of the night with a eureka moment.

Prior to all this, I had watched some arbitrary recommendation on my YouTube homepage, <a target="_blank" href="https://www.youtube.com/watch?v=Ea1_1aVfwl4">Why you didn't learn tetration in school</a>, which turned out to be pretty cool, so I had this disconnected concept called _Tetration_ rattling around in my brain. 


## The Thoughts from January 2024
I was lying in bed unable to sleep last night because I kept thinking about algorithms. Once my brain gets started on a topic like that it's hard to stop it! I was thinking about how the logarithm is simply recursive division carried out until the quotient is less than or equal to 1; the number of recursions needed to do this is the answer to the logarithm:

$$
\begin{aligned}
    log_2{16} \rightarrow 16 \div 2 &= 8 & & \#1 \\
    8 \div 2 &= 4 & & \#2 \\
    4 \div 2 &= 2 & & \#3 \\
    2 \div 2 &= 1 & & \#4 \\
\end{aligned}
$$

$$
log_2{16} = 4
$$

This conception has helped me tremendously in making the damn things more intuitive. Further, I used the same form to understand the iterated log, which is recursively taking the log of a number. I'll show this in a moment.

Then, I thought what is the analog to all this with multiplication? It was a question to which I already knew the answer: exponentiation is recursively multiplying with the same multiplier. Logarithmic and exponential functions are inverse to one another. Finally, I asked, what is inverse to iterated log? The answer hit me almost immediately! I thought back to a YouTube video I watched about an abstruse mathematical concept called *Tetration*, <a target="_blank" href="https://www.youtube.com/watch?v=Ea1_1aVfwl4">Why you didn't learn tetration in school</a>. *Tetration* is the inverse of the iterated log! Here's a precise formulation:

$$
\begin{aligned}
    &\text{let } f(n)=\displaystyle{}^n2 \leftarrow \text{ tetration} \\
    &\text{let } g(n) = \lg^*n \leftarrow \text{ iterated log} \\
    &\text{then } \forall n > 0,\ f(n) = g^{-1}(n) \text{ and } g(n) = f^{-1}(n)
\end{aligned}
$$

Suppose I calculate $f(4) = \displaystyle{}^4{2}$:

$$
\displaystyle{}^4{2} = \underbrace{2^{2^{2^2}}}_{n=4} = 65536
$$ 

We find that $f(4) = 65536$. Let's provide that output as input to $g(n)$, so $g(65536) = \lg^*65536$. The iterated log function is defined using a recurrent equation: 

$$
\lg^*(n) := 
    \begin{cases}
        0 & \text{if }n \leq 1\\
        1 + \lg^*(\lg n) & \text{if }n > 1
    \end{cases}
$$

Here is the calculation carried out:

$$
\begin{aligned}
   1. & & \lg(65536)&= 16 \\
   2. & & \lg(16)&= 4 \\
   3. & & \lg(4)&= 2 \\
   4. & &  \lg(2)&= 1
\end{aligned} 
$$

The function ran $4$ times, so $g(65536) = 4$. This is pretty good evidence that $f(n)$ and $g(n)$ are inverses of each other, and they are indeed inverses, but I won't formally prove it here.

I began thinking about the recursive definitions of all basic arithmetical operations. I'll show only the ones that ultimately pertain to _tetration_ and _iterated log_:

Division (integer division for simplicity):

$$
divide(a,\ b) :=
    \begin{cases}
        0 & if\ a = 0\\
        1 + divide(a - b,\ b) & if\ a \geq 1
    \end{cases}
$$

Logarithm:

$$
log(b,\ n) :=
    \begin{cases}
        1 & if\ n \leq 1\\
        n \div log(b,\ n - b) & if\ n > 1
    \end{cases}
$$

Iterated Logarithm:

$$
\lg^*(n) := 
    \begin{cases}
        0 & \text{if }n \leq 1\\
        1 + \lg^*(\lg n) & \text{if }n > 1
    \end{cases}
$$

Multiplication:

$$
multiply(a,\ b) := 
    \begin{cases}
        0 & if\ b = 0\\
        a + multiply(a,\ b - 1) & if\ b \geq 1
    \end{cases}
$$

Exponentiation:

$$
power(b,\ p) :=
    \begin{cases}
        1 & if\ p = 0\\
        b \times power(b,\ p-1) & if\ p \geq 1
    \end{cases}
$$

Tetration:

$$
tetrate(t,\ b) := 
    \begin{cases}
        0 & if\ t = 0\\
        b^{tetrate(t-1,\ b)} & if\ t > 1
    \end{cases}
$$

## Conclusion
That's all! This was a fun exercise in discovering correlations and in rendering equations with LaTeX.
