---
layout: default
title: Version 5.0
domain: Projects
subject: Student Log
---

# 12/20/2022
My Udemy Course has me into C all over again. I started writing another iteration of the studentlog, though I’m not fully committed to it. If I stick with it, I hope to make it extremely lightweight with minimal time and space complexity. I won’t use a relational database. Instead, I’ll use the good old text file. As I was experimenting with fscanf() for reading the cache csv file, I learned about scanners, which work with the scanf functions and allow us to tell scanf how far to read and when to stop.

---

## 12/21/2022
I was reminded how much I love working with C, so I started working on student-log again. This time around, I decided to push my work to a public repository! I'm trying to make this one as efficient and simple as possible. I can really feel the influence of The Art of Clean Code: I feel a strong desire to write tight, elegant code. I can give a rough idea of my progress by displaying my student.h file:

```
#ifndef __STUDENT_H_
#define __STUDENT_H_

typedef struct student {
    char name[25];
    int day;
    char time[8];
    char start[11];
    char end[11];
    char instrument[10];
    int hash_offset; // going for the linear probing approach this time
    char *assignment;
    struct student *next;
} student;

extern const int TABLE_SIZE; // excited to get more understanding of "extern"

int hasher(char *str);
void initialize_table(student *table[]);
int file_to_table(FILE *cache, student *table[]);
void display_table(student *table[]);
void display_menu(student *table[]);
void consume(FILE *stream);
void destroy_table(student *table[]);

#endif
```

# 12/22/2022
I worked on this more than I should have today. I need to let myself take more breaks. Several of my edits to the code were successful: I implemented a matrix of pointers-to-struct (I also intuited how I might create a pointer to a matrix of pointers), and I added linked list functionality to each bucket in the matrix. However, I struggled to get the while loop in file_to_matrix (formerly file_to_table) to work right. A big reason for that was my erroneous use of feof():

```
// incorrect code
while (!feof(file)) {
    // do stuff
}
```

## 12/23/2022
I wanted to shriek last night: I couldn't for the life of me figure out how to make this program work. Here were the steps I took to fix it:

- Replace `while(!feof(file))` with `while((c = fgetc) != EOF)`
- Load file one character at a time into buffer.
- Parse buffer using sscanf() and scansets, terminating the read at newline character
- Add iterator pointer to any function that manipulated the matrix since it is passed by reference. The iterator moves through the linked list while the matrix pointer is preserved.
- Add newline character to the end of the file.

All these things together fixed my program. Now I need a good break.

---

# 12/30/2022
I altered the file_to_matrix() function so that the student structs are now read from a binary file. That way storing them is much simpler! I also added file_to_matrix(), which writes them to a binary file in the first place, and add_student(), which adds a student to the matrix.

---

# 3/9/2023
I thought I was done with this one too, but I needed the `edit_student()` function so many times that I broke down and added it tonight. Next, I want to tidy up the codebase even further and to add a feature that allows the user to reinstate deleted students. 
