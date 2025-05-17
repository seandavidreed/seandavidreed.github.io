---
layout: default
title: Bare Metal C
domain: Courses
subject: Bare Metal C
---

# 9/20/2022
I finally got started in this book! I read the intro and got started in chapter 1, downloading the STM32 System Workbench IDE Installer (I’ve yet to install it) and writing a hello world program. Of course a lot of this is review, but I appreciate reading a bit more about Makefiles, compiler flags, and bash commands. The next section covers how the compiler works.
   - Tried to install the STM32 System Workbench IDE to no avail. I eventually found that I needed the latest version of Java SE Runtime Environment, so I downloaded it and still had no success.

---

# 9/21/2022
After searching forums online, I found that most likely the installation failed because I had two versions of Java installed on my machine. I uninstalled both versions and then installed Java afresh. Finally I was able to install and open System Workbench!
   - I finished reading through Chapter 1. There were some excellent bits about the inner workings of the compiler, the importance of reading SOME assembly code to make sure the compiler isn’t taking too many liberties with our code, and how Makefiles and flags work. Very helpful!

---

# 9/29/2022
Worked through a bit of chapter 2, learning how to use STM32 Eclipse IDE. I created and compiled a hello world program as part of the exploration - the takeaway is the basic difference between Debug and Release configurations. Debug is not optimized, but easy to debug while Release is highly-optimized and difficult to debug.

---

# 9/30/2022
Bare Metal C: tried to use the GNU debugger (GDB) as the book instructed, but I kept getting an error message since GDB is often not auto-installed on Windows. At this URL — rpg.hamsterrepublic.com/ohrrpgce/GDB_on_Windows — I was able to find the answer. I went into the MinGW (Minimalist GNU for Windows) Installation Manager, and scheduled the GDB packages for installation. Voila! LATER: I tested out the debugger, stepping over a line of code, and where the book said I should see “!!! Hello World !!!” output, I saw nothing. I wondered if the GDB I installed was the wrong version, and I eventually found myself trying to reinstall a GCC package I downloaded directly from GNU’s site (I couldn’t figure out how to install it!). I’ll probably stick with MinGW. Still gotta figure out why I’m not getting output from GDB!

---

# 10/1/2022
Bare Metal C: puzzled over the lack of console output from the debugger. I saw some things online that suggested this issue is common when running the Eclipse IDE on a Windows machine, so I decided to just move on in the book.

---

# 10/2/2022
Worked on answering all the questions at the end of chapter two. Chapter three finally let’s me use the Nucleo microcontroller!

I bought a multimeter for my breadboard circuit exploits!

---

# 11/17/2022
I went ahead and installed STM32 System Workbench for Linux. I really would like to get more into this book - once I finish my inventory manager, I think I’ll do that.

---

# 11/19/2022
Refreshed on some of the content in chapter 1.

Read and followed along in Chapter 3 until page 44. I learned about the Hardware Abstraction Layer (HAL), general purpose input/output (GPIO), and the various other components on the Nucleo development board.

Wrote the led blinking program, and I tweaked it a little to get the led to blink twice rapidly before going off for a longer interval.

---

# 1/3/2023
I went through the earlier part of Chapter 3 and refreshed myself; key terms are HAL (Hardware Abstraction Layer) and GPIO (General Purpose Input Output). Since I had already written the demo program last time, I simply reviewed it to make sure I understood every part of it. I’m pleased that this book goes so in depth on the build process, compiling and linking. It’s possible that I will breeze through some parts of this book since it is geared toward beginner C programmers, but I know there will be many new concepts scattered throughout.

---

# 1/8/2023
I finished chapter 4. The main takeaways were from exploring the files created by the IDE at the creation of the project and from using GDB, the debugger. This chapter helped me appreciate just how much goes on under the hood, all the preliminary steps and initializations that must occur just so I can write my tiny LED-blinking program. HAL\_init() caught my attention the most since it has a catalog of hardware architectures from which it initializes the hardware with the appropriate data. If you can’t tell, I don’t fully understand it yet!

---

# 1/9/2023
Began working in chapter 4. The first part of the chapter is mainly about data types, so it is just review. Later in the chapter, I see that we’ll be getting to some content that should fill in some knowledge gaps for me.

---

# 1/11/2023
I read a little more of chapter 4, and it was mostly review again. This is becoming a bit of a trend with my classes. Perhaps I need to be less of a completionist and know when to skim. I’m fine with being a completionist with the C++20 Masterclass, but with this book, I ought to start skimming ahead to content that is new.

The section Standard Integers in chapter 4 was actually very enlightening. The C standard only defines the integral types relative to each other (short is smaller than int is smaller than long). However, on some system, int is 2 bytes, and on others, it's 4 bytes (more common). To deal with this unpredictability, fixed-width data types were added with the stdint.h library (int32\_t). These guarantee a specific width (conditional compilation). However, we can still run into something called argument promotion, which is where a data type like int8\_t is promoted to int32\_t to accomodate a value which cannot be stored in the smaller width. In embedded programming, we don't want data types being manipulated under the hood. We want total control of their width, so that our program runs exactly as intended. Thus, it's better that the value overflow than get promoted.

---

# 1/12/2023
I definitely spoke too soon with yesterdays first entry for this book. I'm learning some awesome things now. Chapter 4, starting from Shorthand Operators, started to challenge me: it seems to explain that increment and decrement operators should only be used on their own lines of code, not like this `while (arr[++i]);`. This seems to be perfectly legal C; I'll have to investigate further. Then, we got into Memory-Mapped I/O Registers Using Bit Operations. Here the book introduced us to bitwise operators. I copied down the program on pages 73-74, and It found it probably the most elucidating part of the chapter. Finally, I answered all the questions at the end of the chapter. For question 2b, I found that I needed to clear any values that might be present in the parity bits before reassigning them to a different value:  

```
// clear Parity  
ledRegister &= ~Parity; // Parity is 0b00001100  
// set Parity to 2  
ledRegister |= 0b00001000;  
```

---

# 1/14/2023
Today was a light day, but I did manage to get a little study in. I read quickly through the first 6 pages of chapter 5 since it was entirely review. It was all about loop and conditional statements. I stopped just before the section entitled "Using the Button"; I'm fairly certain this section will provide me with new material to digest.

---

# 1/15/2023
Completed chapter five today, though I've yet to solve all the problems at the end. Here are the main takeaways from Chapter Five starting from the section entitled "Using the Button":

- We were shown three types of input circuitry: pullup, pulldown, and floating. These all have to do with how current is directed before closing the circuit and how it is redirected after closing it.
- When analyzing the code in "The Break Statement" section, I noticed the static keyword and I wanted to refresh myself on its purpose. I found an [article](https://www.geeksforgeeks.org/static-variables-in-c/) on GeeksForGeeks that explains static allocation very well. From there I found another [article](https://www.geeksforgeeks.org/static-variables-in-c/) on the memory layout of C programs. I found the following image very helpful:

![the memory layout of a C program](/images/memoryLayoutC.jpg "Memory layout of a C Program")

BSS, the block of memory where static variables are stored, stands for "Block Starting Symbol". The static keyword causes a variable to be stored in the .bss segment of memory; furthermore, it can be used to make a variable global even if it is declared within some local scope.

---

# 1/16/2023
It took me far too long to solve chapter 5 problem 1; it's because I was trying to minimize the number of variables and use only two for loops, printing the product of their iterator variables. I completed the program, but I needed to use one initial for loop to set the column headers (X  0  1  2  3  ...).

I solved problem 2 much quicker and had a lot more fun! I enjoy anything that involves bitwise operations; it feels sneaky. For this problem, I had to write a program that could count the number of bits set to 1 in a 32-bit unsigned integer. I did it by running a for loop 32 times while ANDing the number against a 32-bit test value (0x80000000), only the most significant bit set to 1. If the result of the AND is equal to the test value itself, then a count variable is incremented. This is how I counted the number of bits.

I solved problem 3 this evening. I'm proud of my solution: I was able to make my program more user-friendly by using familiar musical jargon. All the user has to do is specify the TimeSignature and Tempo and then populate the uint8\_t array with the beats on which they want the light to flash.

---

# 1/17/2023
Solved problem 4, which asked me to write a program that blinks out "HELLO WORLD" in Morse Code on the Nucleo board LED. Once again, I took it a step further and gave the user the ability to easily change the message as they like. I did this by implementing a Morse Code alphabet matrix and a simple hash function. The user simply types their message into a string literal using only uppercase alpha chars and spaces. The program then interprets this at Morse Code.

Problem 5 tasked me with writing a program that computes the first 10 primes. I wrote a program that computes primes up to an upper bound of 0xFFFF (the maximum value as can be stored in uint16\_t). To reduce time complexity, I used an array that remembers the prime numbers we've already computed and uses only the necessary amount of them to compute the next prime in the sequence. Unfortunately, the space complexity had to increase for the time complexity to decrease; there may yet be a further way to optimize this code, but I'll leave it here for now.

---

# 1/18/2023
Solved problems 6 and 7. These were very easy, so I spent most of my time making them as clean looking as possible. Problem 7 asked me to write a program that prints only the vowels from a string. I'm pleased to say that after working with ASCII codes so much now, I was able to recall the codes for the vowels, both upper and lowercase, from memory.

---

# 1/24/2023
I read through Chapter six entirely this afternoon. It was on Arrays, Pointers, and Strings, all things I'm well familiar with. Nonetheless, I did have a few takeaways:

1. "The size of the pointer depends on the processor type, not the type of data being pointed to. On our STM32 processor, we have 32-bit addresses, so the pointer will be a 32-bit value.
2. When initializing a pointer, we specify the data type to which it points (uint32\_t *ptr). This does not do anything to the size of the pointer itself, but rather it indicates how the pointer is to be incremented in the case of pointer arithmetic, i.e. (ptr + 1) will move the pointer over by four bytes since a uint32\_t is four bytes in size. It will go from 0xFFE0 to 0xFFE4, for example.

I solved programming problems 1 through 3. Number 3 proved to be a most interesting challenge: "Write a program to scan an array for duplicate numbers that may occur anywhere in the array." The first solution that came to mind was brute-force, touching every element and testing it against every other element for a time complexity of O(n^2). For any sufficiently large array, this method is absurd. I thought of other solutions as well, but ultimately I realized that the best thing to do would be to sort the array beforehand. Naturally, I turned to merge sort. Loosely referencing an old implementation of mine, I wrote another mergesort algo, and in the process, I found that with a few tweaks the mergesort algorithm itself could count the number of duplicates while sorting the array. Here's what I wrote:

```
/*
 * duplicates2.c
 *
 *  Created on: Jan 24, 2023
 *      Author: seandavidreed
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define TYPE uint16_t
// ARRAY_SIZE cannot be a value larger than can be held
// by the fixed-width data type above
#define ARRAY_SIZE 1000


void initRandomArray(int *arr, int size) {
	srand(time(NULL));
	for (TYPE i = 0; i < size; ++i) {
		arr[i] = rand() % (int)pow(2.0, sizeof(TYPE) * 8.0);
	}
}

void mergeSort(int *arr, int *temp, int i, int j, int *count) {
	// base case
	if (i >= j) return;

	// recursive case
	int mid = (i + j) / 2;
	mergeSort(arr, temp, i, mid, count);
	mergeSort(arr, temp, mid + 1, j, count);

	int lptr = i;
	int rptr = mid + 1;
	int k;

	for (k = i; k <= j; ++k) {
		if (lptr == mid + 1) temp[k] = arr[rptr++];
		else if (rptr == j + 1) temp[k] = arr[lptr++];
		else if (arr[lptr] == arr[rptr]) {
			temp[k] = arr[lptr++];
			(*count)++;
		}
		else if (arr[lptr] < arr[rptr]) temp[k] = arr[lptr++];
		else temp[k] = arr[rptr++];
	}

	for (k = i; k <= j; ++k) {
		arr[k] = temp[k];
	}
}

void printArray(int *arr, int size) {
	for (TYPE i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int array[ARRAY_SIZE], temp[ARRAY_SIZE];
	int count = 0;

	initRandomArray(array, ARRAY_SIZE);
	printArray(array, ARRAY_SIZE);

	mergeSort(array, temp, 0, ARRAY_SIZE - 1, &count);
	printArray(array, ARRAY_SIZE);

	printf("Number of Duplicates: %d\n", count);

	return 0;
}
```

---

# 1/25/2023
Finished the last two problems in chapter 6, numbers 4 and 5. They were pretty easy. However, I ran into a snag on problem 5; I was trying to pass a char pointer as an argument to my `void capitalize(char *str)` function, which capitalizes the first character of every word beginning with a letter. The problem is when a string is declared like this `char *str = "This is a string.";`, the string is not mutable. I needed to instead declare it like so, `char str[] = "This is a string.";`. Though I've looked into this topic many times, I still find the terminology somewhat abstruse. However, the concept is intact. Here's a resource on the subject: [Character Strings in C](https://www.cs.uic.edu/~jbell/CourseNotes/C_Programming/CharacterStrings.html).

---

# 2/4/2023
I completed chapter 7, which was all about Local Variables and Procedures. The bits on local variables helped sharpen my understanding of static allocation, which occurs at compile time and is hard-coded into a programs binaries before it even runs. That is much clearer now. Using the GDB debugger in STM32 Workbench, we were able to observe function calls being added to the stack. This was especially interesting in the case of the recursive factorial function: I witnessed the stack grow to the necessary size to initiate the functions base case, and then shrink as each stack frame resolved and was destroyed. Tomorrow, I plan to do the practice problems.

---

# 2/5/2023
I Solved practice problem 3 in chapter 7. It was the classic recursive fibonacci function problem. I remember this being difficult to write the first time I tried it early last year, but now it was extremely easy; I just needed to refresh myself on the fibonacci sequence formula.

```
#include <stdio.h>
#include <stdlib.h>

unsigned int fibonacci (unsigned const int n) {
	// Base Case
	if (n == 1) return 0;
	else if (n == 2) return 1;

	// Recursive Case
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
	printf("%u\n", fibonacci(5));
	return 0;
}
```

### Exploring the Nucleo Board and STM32 Cube IDE On My Own!
My goal is to connect the PIR (Pyroelectric InfraRed) Motion Sensor I got from Adafruit to my Nucleo F030R8 development board.

1. First, I wanted to check the power pins on the development board to see if I needed to initialize them. I connected test leads to the 3V3 and GND pins and used my multimeter to read the voltage, which indeed was 3.3 volts.
2. Next, I consulted the Bare Metal C book, from which I refreshed myself on LED initialization:

	```
	LED2_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = LED2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_LedInit);
	```

	I placed this code inside the comments:

	```
	/* USER CODE BEGIN Init */
	/* USER CODE END Init */
	```

	found inside the main.c source file.
3. I needed to understand the `LED2_GPIO_CLK_ENABLE();` macro so I could ostensibly apply the same thing to my motion sensor peripheral. I highlighted the statement, and selected "search text" and "workspace". The search did not reveal anything I needed.
4. Explored the `stm32f0xx_hal_gpio.h`  library to find the preprocessor definitions for the GPIO pins. I'm using `GPIO_PIN_2`.
5. Explored the `stm32f0xx_hal_conf.h` library and found an include for `stm32f0xx_hal_rcc.h`. I found that "RCC" stands for Reset Clock Control." I thought maybe I could find out what the correct `CLK_ENABLE()` macro would be for my motion sensor - to no avail. I decided to guess that it would be called `PIN_2_GPIO_CLK_ENABLE();`.
6. When I tried to build the project, I found that

	```
	LED2_GPIO_CLK_ENABLE();
	PIN2_GPIO_CLK_ENABLE();
	LED2_PIN;
	LED2_GPIO_PORT;
	PIN2_GPIO_PORT;
	```
	were all flagged as implicit declarations. This means that there is a library that STM32 System Workbench includes by default and that STM32 Cube IDE does not. My next step is to retry everything back in System Workbench. I really just want to wrap my head around all this!
7. Found the solution! I copied all my code over to System Workbench and right away I noticed a library that was not included over at Cube IDE, `stm32f0xx_nucleo.h`. Opening this library, I found several aliases; for example. `GPIO_PIN_5` is aliased to `LED2_PIN`, and `GPIOA` is aliased to `LED2_GPIO_PORT`. `__HAL_RCC_GPIOA_CLK_ENABLE()` is aliased to `LED2_GPIO_CLK_ENABLE()`. As I looked through the different macros, I came across these ones:

	```
	#define NUCLEO_SPIx_SCK_GPIO_PORT                   GPIOA
	#define NUCLEO_SPIx_SCK_PIN                         GPIO_PIN_5
	#define NUCLEO_SPIx_SCK_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
	```
	Looking at the development board, I saw that pin 13 was also named `SCK`. I divined that I could connect my PIR Motion Sensor to this pin and use the macros above, and it worked! Here's a picture:

	![Connecting the PIR to Nucleo](/images/nucleo_pir.jpg)

---

# 2/7/2023
I'm in Chapter 8, which is on Complex Data Types (I can see that this chapter plus the next two will be quite important and will likely present new concepts). I read through the first part of this chapter regarding enums and a neat preprocessor trick that can be done with them. Here it is below for reference (I copied this from the book):

```
#define COLOR_LIST				\
	DEFINE_ITEM(COLOR_RED),		\
	DEFINE_ITEM(COLOR_BLUE),	\
	DEFINE_ITEM(COLOR_GREEN)

#define DEFINE_ITEM(X) X
enum colorType {
	COLOR_LIST
};
#undef DEFINE_ITEM

#define DEFINE_ITEM(X) #X
static const char* colorNames[] = {
	COLOR_LIST
};
#undef DEFINE_ITEM
```

After thinking through this process for a moment, it clicked, and I could see how useful it will be. I'll be working my way slowly through this chapter to absorb as much as I can.

---

# 2/8/2023
Chapter 8 new-to-me concepts in my own words:

1. The Enum data type is new to me, as outlined above.
2. The system architecture defines, among other things, the size of data that is to be passed along the address and data buses. In a 32-bit system, we essentially have a 32-lane superhighway for the data bus and a 32-lane superhighway for the address bus. Therefore, if we have a struct in memory that is 6 bytes in size, when the CPU performs a `fetch` from RAM, it will first fetch 4 bytes (32 bits) of the struct via the data bus, and then it will fetch the remaining 2 bytes along with 2 bytes of padding (32 bits in total) - this padding is defined by the compiler, which prepares the struct according to the system architecture.
3. When a structure is initialized, we can declare a struct name or a variable or both. If a struct is to be used only once, it makes sense to declare it with a variable and without a name:

	```
	struct {
		int dosage;
		int drug;
	} myPrescription;
	```
	I won't have to declare this struct in main since it is declared here. We can declare both a name and a variable:

	```
	struct prescription {
		int dosage;
		int drug;
	} myPrescription;
	```
4. In the unions section, the concept of Endianness is touched on (without being named). It is another facet of the system architecture and it defines how a `word` is stored, either from lowest-order to highest-order byte, as in little Endian, or vice versa, as in big Endian. Little Endian is the most common since it allows a given `word` to be read the same regardless of the number of bits read:


	0x13 will be stored 1300 0000 0000 0000 in a little endian, 64-bit machine. If the same value were read as 32-bit 1300 0000, it will still read 0x13.	

	The term Endianness is derived from Gulliver's Travels, in which there are two factions of Lilliputians, one which cracks hard-boiled eggs from the big end, and the other which cracks them from the little end.

I left off at Creating A Custom Type, which I will pick up perhaps tomorrow!

---

# 2/9/2023
I studied the design pattern found in the **Creating a Custom Type** section and I think it's pretty cool. I went ahead and replicated the program, adding my own touches, to fully understand the logic behind it. [Here](files/bare_metal_c/shapes.c) is the final product. I like the clever use of a union within a structure, which allows a structure to have a dynamic member. The addition of the enum is a nice touch too as it makes the code much more readable. It also allows the `drawShape()` function to recognize which shape is being passed in by checking the `enum shapeType type` member.

I wanted to practice with enums, but I found myself practicing with function pointers instead. I want to get a better grasp on their usage. Here's my silly little programs: [func_ptr.c](files/func_ptr/func_ptr.c).

---

# 2/13/2023
I found the **Structures and Embedded Programming** section informative. It mentioned the Small Computer System Interface (SCSI), which is a standardized way of transferring data to and from devices (Est. 1986). The standard uses a command block, which was only 6 bytes at first but is now 32, to specify the address and size of the data and the opcode of the operation to be performed on it. Following the `read10` standard, we made a command block using a struct:

```
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

struct read10 {
    uint8_t opCode; // Op code for read
    uint8_t flags; // Flag bits
    uint32_t lba; // Logical block address
    uint8_t group; // Command group
    uint16_t transferLength; // Length of the data to read
    uint8_t control; // Control bits, the NACA being the only one defined
};

int main() {
    printf(“%ul”, sizeof(struct read10));
    assert(sizeof(struct read10) == 10);
    return 0;
}
```

The printf statement yielded 16, and the assert statement terminated the program since 16 != 10. In the book’s example, the program yielded 12 bytes for the size of `struct read10`. In both cases, the compiler automatically pads the structure if any of the data are unaligned. For instance, the books example is from a 32-bit system, so the data in the struct will be read in that `word` size, which makes `uint32_t lba` unaligned since its address is not offset by 4 bytes from the address of `uint8_t opCode`. The compiler adds 2-bytes padding between ‘uint8_t flags` and `uint32_t lba` and the data is now aligned to the word size.

In my own example, I’m working with 64-bit system architecture, so the compiler did this:

```
struct read10 {
    uint8_t opCode;
    /* 3 bytes padding added */
    uint8_t flags;
    /* 3 bytes padding added */
    uint32_t lba;
    uint8_t group; 
    uint16_t transferLength;
    uint8_t control;
}; 
```

I have to say that, after looking through the assembly code, I was a little perplexed at the way the data was moved, but I think I got the gist of what went on in the code block above.

---

# 2/14/2023 [fraction.c](/files/bare_metal_c/fraction.c)
Wow, I had way too much fun with Problem 1 of Chapter 8, and I learned a ton. The problem is written as follows:

"Create a structure to hold a fraction. Then create procedures that add, subtract, multiply, and divide fractions. The fractions should be stored in normalized form. In other words, 2/4 should be stored as 1/2."

Designing the struct was easy enough. Things got interesting when I began working on the `fraction add(fraction *addend1, fraction *addend2)` function. The initial arithmetic on the numerators and denominators was fun to implement. I wanted the code to be syntactically sugary and tight; I'm happy with what I got. I quickly realized that the second step, reducing the fraction to its simplest form, would need to be repeated for each arithmetical function (add, subtract, multiply, divide), so I created a separate function, `void reduce(function *reduce)`. I couldn't find a better way to factor out the fraction besides using nested loops. I take half of the smaller term and iterate from 2 up to that number checking which divisors will leave no remainders. As long as a given divisor keeps dividing evenly, the function remains in an inner while loop.

Everything worked just fine until I needed to work with negative values; finding the smaller term becomes problematic because a negative number is always smaller than a positive number. What I really needed was the number that is closest to zero - I needed the absolute value. I didn't want to use the `math.h` library function, `abs()`. I thought about using bitwise operations with bitmasks. This proved to be the right idea, but I couldn't get the right implementation. I wanted one bitmask to both remove the sign from negative numbers and leave positive numbers unaffected. I caved and searched for the answer. These were the two sources I found: 

[Compute the Integer Absolute Value Without Branching](https://www.geeksforgeeks.org/compute-the-integer-absolute-value-abs-without-branching/)  
[Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs)  

At first, I was so baffled at how these functions worked:

```
int v;           // we want to find the absolute value of v
unsigned int r;  // the result goes here 
int const mask = v >> sizeof(int) * CHAR_BIT - 1;

r = (v ^ mask) - mask;
```

I presumed the mask to be equal to 0x1 by the end of the operation, so I didn't see how this worked, yet it did. [This page](https://learn.microsoft.com/en-us/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170) in the Right Shifts section cleared it up: when a right shift is performed on a negative integer, 1's are propagated to the right:

```
signed short int someValue = 0b1000000'00100000;
someValue >> 1;
// 0b11000000'00010000
someValue >> 4;
// 0b11111100'00000001
someValue >> 4;
// 0b11111111'11000000
```
This is reasonable since the right shift is supposed to reduce the magnitude of a value by half for each move. As more 1’s propagate, the negative value approaches 0. Apparently some processor architectures define a different behavior for right shifting negative integers, presumably causing the magnitude of the negative value to double with each right shift.

---

# 2/15/2023
- [car_struct.c](files/bare_metal_c/car_struct.c) - Wrote a program for problem 2, and I added more functionality than was required for the sake of practice. The main goal here was to implement a car struct that contains a union for two structs of vehicle types, electric and gas. In addition to completing this, I implemented the enum preprocessor trick outlined on [2/6/2023](#262023). Additionally, I added a color member to the struct that stores RGB values in a `uint32_t` type. For this member, I wrote functions that read and write from the member with bitwise or and shift operations. I had a lot of fun doing it!
- [acmeTrafficSignal.c](files/bare_metal/acmeTrafficSignal.c) - Worked on this one for a good while. I couldn't understand why the problem wanted me to organize the program the way it did (I did take some liberties, like using function pointers and adding my own functions). In the end, I decided to roll with it. It was good practice for enums, unions, and function pointers.

---

# 2/17/2023
I started in on Chapter 9, **Serial Output on the STM**. Before reading the majority of this chapter, I didn't really have an idea of serial I/O. Now I undertstand that serial I/O in a general sense is the pushing of bits in series in what's called a stream. I imagine that the opposite of serial would be parallel, sort of like in electric circuits. When a CPU fetches data from RAM, I imagine the data could be said to be received via the data bus in parallel; there are multiple lanes in the superhighway delivering the data in multiple streams. *Disclaimer: I might be making stuff up here. Really, I'm only trying to help myself conceptualize the process of Serial I/O*. For serial communication with a microcontroller, we have to access RX (receiver) and TX (transmitter) pins. In the case of the NUCLEO board, the TX and RX pins are already wired up for us, so we don't need to connect any additional jumper cables. 

I especially enjoyed reading the section **A Brief History of Serial Communications**, in which we are taken from the telegraph to the teletype to the computer. Through each advancement, serial communications technologies have remained relatively the same, except that they have increased in speed (baudrate, which is bits per second). In this section, there is a subsection, **Line Endings**, I found very interesting. Here's a direct quote:

--Begin Quote--  
&ensp;&ensp;*If you sent a character immediately after the carriage return, you'd get a blurred blob printed in the middle of the line as the printhead tried to print while moving.*

&ensp;&ensp;*The teletype people solved this issue by making the end of a line two characters. The first, the carriage return, moved the print head to position 1. The second, the line feed, moved the paper up one line. Since the line feed didn't print anything on the paper, the fact that is was done while the printhead was flying to the left didn't matter.*

&ensp;&ensp;*However, when computers came out, storage cost a lot of money (hundreds of dollars per byte), so storing two characters for an end of line was costly. The people who created Unix, the inspiration for Linux, decided to use the line feed (\n) character only. Apple decided to use the carriage return (\r) only, and Microsoft decided to use both the carriage return and the line feed (\r\n) for its line ending.*

&ensp;&ensp;*C automatically handles the different types of newlines in the system library, but only when you use the system library. If you are doing it yourself, ... you must write out the full end-of-line sequence (\r\n).*  
--End Quote--

More useful bits

- UART stands for *Universal Asynchronous Receiver-Transmitter*.
- USART stands for *Universal Synchronous/Asynchronous Receiver-Transmitter*.
- In synchronous serial communication, the transmitter continuously sends out characters even when idle to maintain the synchronization between the transmitter and receiver clocks.
- In asynchronous serial communication, the transmitter only sends characters when there is something to send. This form is used when it is reasonable to assume that the transmitter and receiver clocks can stay synchronized on their own.

---

# 2/18/2023
I finished up Chapter 9 today. At first I was a little displeased by the use of copy code to test out the USART, but my perspective changed when I got to the practice problems at the end of the chapter. These problems helped me to dig through the program and its included libraries and understand it better.

- For problem 2, I was charged with "...changing the configuration so that you send 7 data bits and even parity (instead of 8 data bits, no parity)." The first step was to understand the function of the parity bit. Parity in mathematics is the even/odd quality of a number. In embedded programmin, a parity bit is used for error-checking. The error-checking method is established as either even parity or odd parity. In the case of even parity, the parity bit is set to 1 whenever there is an odd number of 1's in the 7 data bits and it is set to 0 when there is an even number. This ensures that when the data frame is transmitted, it will have an even number of 1 bits. If when it is received there is an odd number of bits, the receiving register will know that the data has been corrupted and it won't accept it. Odd parity works the same way but opposite. 
    
	- Here's what I did to solve this problem: I went into the `void uart2_Init(void)` function and changed `uartHandle.Init.Parity = UART_PARITY_NONE` to `uartHandle.Init.Parity = UART_PARITY_EVEN`. I found the correct macro by right-clicking on `UART_PARITY_NONE` and selecting "Open Declaration". This change caused `Hello World!` to look something like this `Hello??orl?!`. The space, 'W', and 'd' all have an odd number of 1 bits, so they were modified and thrown out of the range of printable ASCII characters.

- Problem 3 was about adding flow control to thr program to allow the user to start and stop the printing of `Hello World!`. To solve this, I once again selectes some code `uartHandle.Init.HwFlwCtl = UART_HWCONTROL_NONE` and selected "Open Declaration". There I found the `UART_HWCONTROL_RTS_CTS` macro, which I deduced to be the value I needed.
- Problem 4 was certainly the most challenging, but with more browsing declarations and reading the [documentation](/documents/page605NucleoF030r8Docs.pdf) on character input, I was able to work out how to change the `myPutChar()` function into a semi-functional `myGetChar()` function. The main takeaway from the documentation was how to use the RDR and RXNE variables.

---

# 2/28/2023
I'm on Chapter 10, Interrupts. There is a lot of technical jargon in this section, and I've not even finished reading it! I read half the chapter and implemented the example program today. Here's my key takeaways:

- Polling and Interrupts are the two main methods for handling I/O. Polling is easy to understand and implement but suffers in efficiency; Interrupts are hard to understand and implement but are efficient. In my estimation, one is not ubiquitously better than the other. Rather, Polling is useful when a process is guaranteed to happen frequently. Interrupts are useful when a process is going to happen semi-infrequently. This is a gross simplification, but the general logic makes sense and helps reinforce the concept.
- Important Acronyms: 
  - TDR - Transmit Data Register
  - TSR - Transmit Shift Register
  - TXE - TDR Empty; IRQ - Interrupt Request
  - volatile - C keyword that tells the compiler that a variable may be changed
  - TXEIE - Transmit Interrupt Enable
  - UART and USART - (refresher) Universal Asynchronous Receiver-Transmitter; Universal Synchronous/Asynchronous Receiver/Transmitter

To really understand the USART protocol, I'll need to experiment with it directly. Once I finish the chapter, I will look up USART tutorials specifically for STM32 products.

---

# 3/1/2023
I finished Chapter 10 today. I didn't care for the second half of the chapter like I did the first. I found it difficult to follow, not because the material was too complex, though it certainly is complex, but because several things were glossed over that I think should have been clarified more. That's okay. I like this book as a whole and I have no problem consulting other resources to fill in any gaps. Before I continue to Chapter 11, I'm going to explore UART, polling, and interrupts more thoroughly.

[This article on the UART Protocol](https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html) is an excellent distillation. Much of it was review for me, but it also gave me some new mind maps to use when thinking about UART. I really want to get a firm grasp on serial communication. Here are some steps I can take:

- Implement my own STM32 program that sends and receives packets via UART on the Nucleo MCU.
- Find a device with an embedded system and see if I can connect to it via UART and read its log data.

---

# 3/4/2023
I started reading Chapter 11, which was on the Linker. It goes into great detail. I’ll likely need to read it more than once to fully grasp everything. The example program was the most helpful part:

```
/**
 * A program to demonstrate various types of variable
 * storage, so we can see what the linker does with them
 */
 int uninitializedGlobal; // section bss
 int initializedGlobal = 1; // section data
 int initializedToZero = 0; // section BSS
 
 // aString —- initialized variable (section bss)
 // “A string.” —- constant (section text)
 const char* aString = “A string.”; // String (pointing to read-only data)
 static int uninitializedModule = 2; // section bss
 static int initializedModule = 2; // section data
 
 int main() {
     int uninitializedLocal; // section stack
     int initializedLocal = 1234; // section stack
     
     static int uninitializedStatic; // section bss
     static int initializedStatic = 5678; // section data
     
     while (1)
         continue;
}
```

This helped clarify the three main sections, text, data, and bss.

---

# 3/8/2023
Finished chapter 11, but I chose not to complete the problems at the end. I will return to these problems, or ones like them, when I’ve had a chance to practice the concepts more. I’ve gotten a lot out of this book, but these latest chapters have had too much of a “knowledge dump” format for me. I want to have more opportunities to apply things.

---

# 3/9/2023
Read through chapter 12, which was all about the preprocessor. This elucidating chapter reminded me of the value this book has added to my learning process. Key takeaways:

- The #ifndef and #endif directives that encapsulate the declarations in a header file are called *sentinels*.
- The preprocessor does not understand C syntax; macros are merely word replacement machines. Despite this limitation, they can be used for complex purposes, but it is generally best practice to use macros in this only way if there is no better alternative, as with ordinary C code.
- Parameterized Macros can spoof the behavior of functions. The STM32 library occasionally uses them in this way.


---

# 3/24/2023
I finally got around to doing the practice problems for the final chapter in Part I. There were all about practicing writing macros with the preprocessor. Here are two of the macros I wrote:

```
#define SWAP(a, b)    \
    a ^= b;           \
    b ^= a;           \
    a ^= b;
```
and

```
#define islower(x)    \
    (x >= 97 && x <= 122) ? 1 : 0
``` 

Having completed Part I, I will probably move on from this book. Part II is all about C for big metal, a topic I’ve had my fill of for a while (most of Part II would be review). Perhaps I’ll browse through it in the future, but for now it’s on to the new!

