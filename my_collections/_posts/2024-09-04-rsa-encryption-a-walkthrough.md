---
layout: post
title: RSA Encryption - A Walkthrough
author: Sean David Reed
---

<a href="https://github.com/seandavidreed/RSA_demo"><button type="button">RSA Python Code</button></a>

## Introduction

I’ve written this walkthrough in an effort to understand the RSA encryption algorithm (Rivest, Shamir, Adleman). I started with some basic research, sifting through valuable sources and code snippets at GeeksForGeeks, Stack Overflow, and elsewhere. That led to [my own implementation of the algorithm in Python](https://github.com/seandavidreed/RSA_demo), and finally, this walkthrough, covering the mathematics involved. I learned a lot throughout the process, and now I can reasonably say I understand the algorithm at a basic level. I still have more to learn about the *Rabin Miller Primality Test*, but that will be for another time. What follows is a step by step explanation of all that the RSA algorithm entails.

## What we need to achieve.

The basic mechanism of the RSA algorithm is actually really simple. The complexity arises when we try to find the inputs that make it all work, which is what we’ll discuss. However, I first want to take stock of what we need for the algorithm and what it does.

We need a set of two keys, a public key and a private key. Each key will be a pair of numbers with one number as the exponent and the other as the modulus. The numbers of the public key are typically denoted $(e,\ n)$ and of the private key $(d,\ n)$, where e is for *encryption* and d for *decryption*. To encrypt a message, in our example a single value $M$, we must raise it to the power of $e$ and reduce the result modulo $n$ to get our encrypted message $E$.

$$
M^e \bmod{n} = E 
$$

To reverse this procedure, we use the private key to raise the encrypted value to the power of $d$ and reduce the result modulo $n$.

E^d \bmod{n} = M 

This is the basis of what’s happening in the RSA algorithm, but the fact that we have found functions that can undo each other using different inputs is the bit of mathematical wizardry that needs explaining. We need to know how to get our numbers $e,\ d,\ n$ such that these two simple calculations work.

## Select two random prime numbers.

To begin, we need to select two random prime numbers, and ideally, they should be quite large. The article [How to generate Large Prime numbers for RSA Algorithm](https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/) from GeeksForGeeks outlines the steps for us. They are, broadly, as follows:

1. Generate a large random number, `prime_candidate`, using a pseudo-random number generator.
2. Use *Sieve of Eratosthenes*: Iterate through a list of the first several hundred prime numbers checking if any are divisors of `prime_candidate`. If a divisor is found, prime_candidate is not prime $\rightarrow$ return to step 1. Otherwise, proceed.
3. Perform the *Rabin Miller Primality Test* $i$ times. *Rabin Miller* is a probabilistic procedure, so the more successful tests we run, the higher the probability `prime_candidate` is prime. If all $i$ tests are successful, assume `prime_candidate` is prime with a high degree of confidence.

We use a probabilistic procedure for step 3 because we’re dealing with such large numbers. If a deterministic procedure were used instead, it would require far too many computing resources.

For this example, we will let our random prime numbers be $p = 1231$ and $q = 131$. Next, we need to multiply them to get $n$, which will be our modulus:

$$
n = p \cdot q = 1231 \cdot 131 = \mathbf{161261} 
$$

## Compute Euler’s Totient Function.

Euler’s Totient Function computes for some value of $n$ the quantity of positive integers that are both less than $n$ and coprime with $n$. As a small example, we will calculate $\phi(24)$:

$$
\begin{aligned}
&\text{Let } C = \{x \in \mathbb{Z}^{+}: x \perp 24\} \\
&C = \{5, 7, 9, 11, 13, 17, 19, 23\} \\ 
&\phi(24) = |C| = 8
\end{aligned}
$$ 

For our example, we pass the product of our randomly selected prime numbers, $p$ and $q$, into the Totient function $\phi(pq)$, and because of its multiplicative property, we can simply calculate $\phi(p) \cdot \phi(q)$ instead. Even better, when we pass any prime number $r$ to the Totient function, it will always yield $r - 1$.

Let’s unpack that. For two numbers to be coprime, they must have no factors in common other than $1$. A prime number $r$ by definition only has two factors, $1$ and $r$. As such, no positive number less than $r$ can have any factors in common with $r$, so there are exactly $r - 1$ coprime positive integers. This is the result found by the Totient function.

Therefore, when we want to calculate $\phi(pq)$, we can simply calculate $(p-1)(q-1)$. Expressed summarily,

$$
\phi(n) = \phi(pq) = \phi(p) \cdot \phi(q) = (p-1)(q-1)
$$ 

And for our numbers,

$$
\begin{aligned}
&\phi(161261) = \phi(1231 \cdot 131) \\ 
&=> \phi(1231) \cdot \phi(131) = (1230)(130) = \mathbf{159900}
\end{aligned}
$$ 

## Select the Public Key exponent.

We need to select our Public Key exponent, $e$, such that it is coprime with $\phi(n)$ and $1 <= e < \phi(n)$. The selection of $e$ can be random, but $e = 65537$ is commonly used. We can get away with using a predictable prime number for $e$ for two reasons: it will be known by all parties involved anyway since it’s public, and the numbers that really must remain hidden are $p$ and $q$, but more on that later. We now have our Public Key.

$$
public\ key = (e,\ n) = \mathbf{(65537, 161261)}
$$ 

## Compute the Private Key exponent.

To compute the Private key exponent, $d$, we must use the *Extended Euclidean Algorithm* to find the [Modular Multiplicative Inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of $e$, which will be worked out below. We need to use $\phi(n) = 159900$ and $e = 65537$ to find $d$. Ultimately, the following formula must be solved for $d$: $d \cdot e \equiv 1\ (\bmod{\phi(n)})$. We can solve it with the [Extended Euclidean Algorithm](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html) worked out below.

### Step 1 – Euclidean Algorithm

$$
\begin{aligned}
&159900 = 65537(2) + 28826 \\ 
&65537 = 28826(2) + 7885 \\ 
&28826 = 7885(3) + 5171 \\ 
&7885 = 5171(1) + 2714 \\
&5171 = 2714(1) + 2457 \\
&2714 = 2457(1) + 257 \\
&2457 = 257(9) + 144 \\
&257 = 144(1) + 113 \\
&144 = 113(1) + 31 \\
&113 = 31(3) + 20 \\
&31 = 20(1) + 11 \\
&20 = 11(1) + 9 \\
&11 = 9(1) + 2 \\
&9 = 2(4) + 1 \\
&2 = 1(2) + 0 \\ 
\end{aligned}
$$

### Step 2 – Modular Multiplicative Inverse Calculation

$$
\begin{aligned}
&1 = 9(1) + 2(-4) \\
&1 = 9(1) + (11 + 9(-1))(-4) \\
&1 = 11(-4) + 9(5) \\
&1 = 11(-4) + (20 + 11(-1))(5) \\
&1 = 20(5) + 11(-9) \\
&1 = 20(5) + (31 + 20(-1))(-9) \\
&1 = 31(-9) + 20(14) \\
&1 = 31(-9) + (113 + 31(-3))(14) \\
&1 = 113(14) + 31(-51) \\
&1 = 113(14) + (144 + 113(-1))(-51) \\
&1 = 144(-51) + 113(65) \\
&1 = 144(-51) + (257 + 144(-1))(65) \\
&1 = 257(65) + 144(-116) \\
&1 = 257(65) + (2457 + 257(-9))(-116) \\
&1 = 2457(-116) + 257(1109) \\
&1 = 2457(-116) + (2714 + 2457(-1))(1109) \\
&1 = 2714(1109) + 2457(-1225) \\
&1 = 2714(1109) + (5171 + 2714(-1))(-1225) \\
&1 = 5171(-1225) + 2714(2334) \\
&1 = 5171(-1225) + (7885 + 5171(-1))(2334) \\
&1 = 7885(2334) + 5171(-3559) \\
&1 = 7885(2334) + (28826 + 7885(-3))(-3559) \\
&1 = 28826(-3559) + 7885(13011) \\
&1 = 28826(-3559) + (65537 + 28826(-2))(13011) \\
&1 = 65537(13011) + 28826(-29581) \\
&1 = 65537(13011) + (159900 + 65537(-2))(-29581) \\
&1 = 159900(-29581) + 65537(72173) \\ \\ 
&d = 72173 \bmod{159900} = \mathbf{72173}  
\end{aligned}
$$

After that arduous calculation, we have our Private Key.

$$
private\ key = (d,\ n) = \mathbf{(72173, 161261)} 
$$

## Encrypt and decrypt a message.

We want to keep things simple for this demonstration. Let our message be a single character, $message =\ 'B'$. When expressed as its ASCII code, our message is $message = 66$. To encrypt our character, we must raise it to the power of $e$ and then reduce the result $\bmod{\ \phi(n)$}. Thus, we encrypt our message.

$$
66^{65537} \bmod{161261} = \mathbf{107400} 
$$

And we can turn right around and decrypt it.

$$
107400^{72173} \bmod{161261} = 66 = \mathbf{'B'} 
$$

## Conclusion

Great! We’ve successfully encrypted and decrypted our very simple message. How does this calculation protect the information from prying eyes? Let’s look take a closer look. If you’re an attacker trying to decrypt $107400$, the only bit of information you’re missing is $d = 72173$, the Private Key exponent.

In this basic example, if would not be difficult to mount a brute-force attack, simply trying one private key exponent after another until you reached the relatively-small number $72173$.

$$
(1,\ 161261),\ (2,\ 161261),\ ...,\ (72173, 161261) 
$$

$72173$ can be represented with 32 bits, and its on the small end as far as 32-bit integers go. Let’s suppose you have a computer with a pretty fast clock speed at 4 GHz. For ease of demonstration, let’s say each guess, i.e. $(12389,\ 161261)$, in our brute-force attack takes our CPU 1 instruction cycle. Given that the CPU can run 4 billion cycles per second (4 GHz), our computer will guess the correct Private Key exponent in

$$
\frac{72173}{4000000000} \approx 0.000018 \text{ seconds}
$$

Awesome. Even if we use the largest 32-bit number available, $4294967296$, our encryption will be cracked in barely more than 1 second.

$$
\frac{4294967296}{4000000000} \approx 1.07 \text{ seconds}
$$

In practice, The *National Institute of Science and Technology* recommends a minimum key length of 2048 bits. We don’t even need to select a 2048-bit number to illustrate the forthcoming point. Let’s select the largest possible 64-bit integer, $2^{64} = 18446744073709551616$. Our computer will guess the correct Private Key exponent in

$$
\frac{18446744073709551616}{4000000000} \approx 4.6 \text{ billion seconds} \approx 146 \text{ years} 
$$

No one has that kind of time. If the largest 128-bit integer were used, our computer would guess the correct Private Key exponent in approximately

$$
2.698 \times 10^{21} \text{ years}
$$

You get the idea. Ok, but how did we get our Private Key exponent in the first place? We solved for the Modular Multiplicative Inverse: $d \cdot e \equiv 1\ (\bmod\ \phi(pq))$. The randomly-selected numbers $p$ and $q$ are, like $d$, secret numbers.

If you, as the attacker, want to get $d$ by calculating the *Modular Multiplicative Inverse*, you would have to find $p$ and $q$. In practice, these numbers will themselves be very large. If you want to carry out a brute-force attack, you would, in the worst case, have to try every combination of two prime factors of $n$, and this gets you back into the realm of trillions of trillions of years.

It’s beyond the scope of this post to consider some of the viable attacks on RSA that have emerged throughout the years, or *will* emerge with the advent of quantum computing. For now, we’ve developed a sense of why RSA works in ordinary circumstances.
