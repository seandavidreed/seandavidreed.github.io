---
layout: default
title: Version 3.0
domain: Projects
subject: Student Log
---

## 6/2/2022
Started working on my own program, Student Log, which will hopefully become sophisticated enough to actually aid me in my current job! I want a more streamlined way to store and look up information.

---

## 6/3/2022
Was banging my head against a wall trying to figure out why my delete node function was not working. Turns out I needed to pass not the head pointer to the function, but a pointer to the head pointer (pointer to pointer, double reference). This boggled my mind at first, but reading online, I found the reason: if we want to make a permanent change (one that endures when the function call is finished) to a pointer being passed into a function, we must instead pass a reference to the pointer! This is the exact same rule as when passing a variable; in other words, it’s the classic “pass by value vs. pass by address” situation.

---

## 6/4/2022
Worked on this one more during my breaks at work. It’s difficult to keep track of all the features I’ve added; I’ve got so much momentum in this project. 😅 Generally, I found myself debugging, improving the code I’d already written, and adding the select student feature, which allows me to zoom in on one student and view their information. I also added a time stamp feature to the addStudent function: now I will easily know the exact date that the student started lessons. This evening, I added a file handling feature: now when I exit the program all the information I entered into the linked list is exported to individual files for each student. If the file already exists, the programs merely appends the information.

---

## 6/5/2022
Debugging, creating a text wrapping feature for the assign item in the student struct. Success! To do: add a function that reads from student files based on which weekday I select. Do I need to add a “weekday” item to the student struct, or should I create a separate “roster” file that keeps track of what days I have certain students?

---

## 6/6/2022
Created insertStudent function to add students at different parts of the list.

---

## 6/7/2022
Did some debugging (still more to do - having trouble with scanf in selectStudent function), wrote a new function, exportRoster, which sends all students in the list to a txt file named after the day on which their lessons are scheduled. LoadRoster needs to be written next, so I don’t have to re-input students every day with addStudent function. I can tell I need to rethink several aspects of my file handling: I need the exported info to retain its structure - I think I need to export to binary instead of text. I also need to read the article about how to write structs to file. Phew! Lots to do.

Installed Chocolatey using an elevated/admin command prompt in Powershell. I need to learn what Chocolatey is capable of! I used it to install make (choco install make). Now, I can write Makefiles in my atom text editor to make compiling my programs more streamlined! [How to Install and Use Make in Windows](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows)

Jacob Sorber: how to use make in 60 seconds; compiling c programs with multiple files
A COMPILER IS A TOOLCHAIN
Successfully implemented a Makefile for my studentlog program. I have a lot to learn about build systems! After jumping through countless hoops, I turned on the Linux subsystem (Ubuntu) for Windows. It’s hard to remember what I did!

---

## 6/8/2022 
BIG NEWS: I finished my program today!!! I can now use my student log at work. I was able to make a function that exports the linked list to a file and another function that retrieves the list from file and reloads it into a linked list! I was pretty shocked when this worked! Now I simply need to debug the program as I use it.

---

## 6/9/2022
Some debugging of my student log. I needed to clear the ASSIGN array in my NODE struct whenever I want to assign new homework so that the new assignment will completely overwrite the old assignment.

Made the menu easier to interface with: using numbers to select the day desired rather than typing in the day. I need to find a way to do that with selecting students.

I’m mostly working on debugging now, implementing some error handling to make sure that inputs don’t make the program crash. I looked up ways to flush standard input and found that you can create a simple function to flush the input buffer after every scanf statement.

---

## 6/10/2022
Improved the selectStudent function; now I simply enter the number associated with the student to select them! I also updated the exportStudents function; now all the student files are saved neatly in a students folder.

---

## 6/14/2022
made some simple updates - now when a student is selected, a submenu pops up which allows the user to Assign Homework, Set Attendance, Open Student File (I’ve yet to write this feature), and Return to Main Menu. I wrote a function specifically to display this menu. It might not be the most elegant implementation! Later, I possibly want to make the text wrapping feature into a function.

---

## 6/15/2022
Commented more of my functions; for new students, the program writes date start at top of file if it is empty; when I remove a student, an end date is appended to their file; added the open student file functionality (not portable - relies on powershell commands - in the future, I’ll need a cleaner option); created the textWrap function to clean up my selectStudent function; finally, I used the pre-processor directive #define to create a PATH constant and a WRAP constant - the path allows a user to specify the path at which student files will be stored and retrieved, and the wrap allows a user to specify the formatting for the assign member of each struct node.

---

## 6/17/2022
Been trying to find GUI building tools for my student log. I don’t want to be confined to the shell to interact with my program! So far I’ve gotten dizzy trying to figure out how to build the following tools: IUP, GTK, QT, and WxWidgets. I think I may have settling on WxWidgets since I found a great build tutorial video on YouTube (channel: javidx9). WHY IS IT SO HARD TO INSTALL THIS STUFF.

---

## 6/18/2022
I want to run Valgrind on my program, but I have to be in a Linux environment to do it, so I learned how to make Bash the default shell for Atom, then I had to install gcc for Linux to compile my program, and then I thought I had to change the path and in my environment variables window, but I didn’t. Success! However, compiling and running the program with bash, I notice that when I read the roster from the .bin file created by the studentlog.exe (compiled in powershell), the data is corrupted. 

Read up on linked list serialization. I noticed I’m writing the node pointers to file in my writeRoster function - perhaps that adds to the issue. I know I could improve my program by making every string format exactly alike - then I could use the same criterion to write each to file.

---

# 6/20/2022
Worked on my writeRoster and readRoster functions on my Linux PC.

---

## 6/21/2022
With all the changes I’ve made while compiling in bash, I wanted to compare the new and old versions of studentlog. I wrote a program called filecomp.c and it didn’t work. Then I wrote pretty much the exact same program, calling it test.c, and it worked. So I went through the filecomp.c program line by line until it was identical to test.c, and it still didn’t work! Only once I deleted filecomp.c, created a new file with the same name, and copied test.c contents into it did it work. 🤯 Anyhow, I think I’m going to leave my student log be for now - it works as I need it to - it makes sense that it doesn’t work when I run the program in bash and it was compiled in powershell. I don’t need to fix that.

---

## 6/23/2022
Added a Display Expanded feature, so the user can now expand the list to show all the information contained in each student node for the current roster.

Watched the first episode of The Triumph of the Nerds documentary - generally very informative! I’m anxious to learn all I can about the history and hardware of computers.

Learned that Program Files (x86) is a folder in a 64bit system where 32bit programs are stored. x86 refers to a particular kind of processor- 386, 486, 586, etc.

---

## 6/25/2022
Tried to work out a method to increase the struct node size without messing up the data. I have a potential solution, a function that can transfer the data from one node to another node with the changed formatting. I implemented this, but it doesn’t work perfectly yet. As I type this, I’m thinking of another way to do this that involves fewer steps: I could modify the readRoster function to pull the data into the original node then copy it into the new node, thereby making two linked lists at the same time, one with the updated formatting. Of course! I need to rewrite the whole program to accommodate the new struct size, and then create a back door for the old format to be loaded in, reformatting it in the process!

---

## 6/28/2022
Made progress with the linked list transfer concept - I’m able to take the old roster, load it into a linked list of old nodes, and then transfer the data from each node into a modified node in a new linked list. From there, I’ll be able to update the roster with the new nodes, and then I won’t have to load old nodes anymore. I’m still having a bug: the last student in the roster never makes it into the linked list, and I need to find out why.

---

## 6/29/2022
Woohoo! Fixed the issue with the last student not printing! Like a chump, I was freeing the last node in the linked list in my transfer function, so the penultimate node wound up pointing to a random address that held garbage values! I fixed that, and then I changed the function so it would load the nodes in the correct order. Everything is now running smoothly, and I think I’m ready to implement the update in my official studentlog!

---

## 7/20/2022
I forgot to export the students from yesterday, so I did it when I opened my computer this morning. As I suspected, the wrong date was written to the student files. To make sure this issue didn’t happen again, I edited my program so that the current date is retrieved at the beginning of runtime and is passed to functions as needed.
