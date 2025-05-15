---
layout: default
title: Version 4.0
domain: Projects
subject: Student Log
---

# 7/27/2022
Experimented with Python more on my own. Decided to chip away at a new studentlog.py program!

---

# 7/28/2022
Played with Python some more. I’m finding it is way too easy to create a student log program. 😅 Maybe my C student log is more complex than necessary as well.

---

# 7/29/2022
I’m getting the hang of this language (Python)! Of course, there’s a lot to learn, but I feel less lost in general. Wrote writeRoster and readRoster functions; I’m working on exportStudents.

---

# 8/17/2022
(Abandoned the Python version) For better or worse, I decided to rebuild this program with SQLite3. I got the SQLite3 API to integrate with my C file, and I adapted the Makefile from studentlog3.0 to include it. I’m currently in the process of designing my student_base table. A question I have: can I use SQLite3 to store the assignment log, or do I still need separate txt files for that? [LATER] Things are coming together! My program can now load a student into my students array (although I need to alter the callback function because it fails when I try to store multiple students in the array), and it can add new students to the database.

---

# 8/18/2022
I had several moments of wanting to give up on this project, but I pushed through and discovered some of my errors! Using the sqlite3 API for C/C++ is proving challenging; I’m slowly figuring it out. I know have a better understanding of what an API is, and I have a good idea of how function pointers and callback functions work!

Was able to put all my header files in a subdirectory - I had to alter my includes and my Makefile to follow the new path; I included my new in_out.h file in this. Lastly, I cleaned up main.c by outsourcing more of the code to the tools.c source file.

---

# 8/19/2022
Really cleaned up the main.c file by moving the code into neatly organized functions for each menu. Added a delete_student function, which modifies the day to -1 so that the student doesn’t show up in the line up. I need to add end_date appending and an option for permanent deletion, which would completely destroy all records of the student. I need to improve the way date and time are stored in the database. Also, I think I’ve decided to store student assignment logs in the database itself; I think I’ll have to create another table that links to the student_base table. Question: do I need to allocate all 20 elements for the student array each time or can I allocate just what’s needed?

---

# 8/20/2022
Added end_date appending to my delete_student function. Added permanent deletion option by prepending ‘-d’ to the name of student to be deleted. Designing another table:
 
```
CREATE TABLE assignments (
  assignment_id INTEGER PRIMARY KEY
  student_id INTEGER,
  date TEXT,
  name TEXT,
  assignment TEXT);
```

I got caught up with my date function, which I ultimately decided to scrap! I’ll get back to the new table next time.

---

# 8/21/2022
Improved add_student function; now it displays a menu of choices for time and instrument, greatly simplifying the input process. Added system(“clear”) so that the program executes more cleanly in the console. Tried to get the callback function to read in the student_id (even made my own str to int function), but I kept getting errors - I think it’s due to conflicting data types. Just realized that my new time format might not display properly with SQLite ORDER BY statement.

---

# 8/23/2022
Made everything regarding the “time” column work smoothly; decided not to use the student_id to communicate between menus and tables - only student “name” is really needed (If in the future I had two students with the exact same name, the “student_id” would be more significant); added the student menu complete with “assign” and “view assignments” operations (deployed my own input function, get_var_text, here!); implemented a second callback function to handle assignments info (could maybe use a 3rd for fetching student_id, but not a priority); UP NEXT: update textwrap() and add to in_out.h for use in formatting assignment output; write a program to automatically transfer student and assignment info from individual student files in the students folder; add error handling for faulty input, etc; and possibly design callback function to fetch student_id like I initially wanted.

Follow up: fixed textWrap(); tried to get the transfer program to work, but no success yet - I’m close though!

---

# 8/24/2022
After much toil and lucubration, I got my transfer program to work; now I’ll be able to load all the assignment data from each student file into a sql file quite rapidly. I still have to enter the filenames manually, which is cumbersome, but I’ve saved a tremendous amount of time by not having to write each INSERT statement over and over!

Follow up: added a feature that lets me iterate through each student file automatically! Now, I just have to troubleshoot a few things.

---

# 8/25/2022
Still can’t figure out how to get VS Code to see the GTK libraries I installed. I updated the include path, but I’m not sure I did it right. I’d really like to implement a primitive GUI for my studentlog4.0 app.

TO-DO add error checking; replace student array with linked list (to help with insertion and deletion) - this will be a significant task, but I think it will improve the program overall!

# 8/26/2022
Decided not to implement a linked list; instead, I created a hash function that takes the student lesson time and convert it into an index for the student array - do it’s a quasi hash table. Now I can easily insert and remove from the array, and I reduced how many times I have to deallocated the array (the cost is that I have to search through the array more). I still can’t figure out why my delete_student function won’t remove the student from the student array.

---

# 8/27/2022
I figured out what was going wrong with my delete_student function: in the strcmp() function, I was comparing the wrong string. 🤬 It took me so long to catch it because I was following a red herring with the extern keyword and with variable scope, thinking the problem resided with the student array being somehow invisible to the delete_student function. Of course, the problem was much simpler.

Made use of the return codes from SQLITE3_EXEC, so now I can print “empty” when the function doesn’t find any data.

Wrote a simple program to transfer student data to the student_base table in the database. Not all the dates reformat properly yet - I might just manually correct the faulty ones. UPDATE: corrected the dates and inserted the data into the database.

TODO add error handling for user errors; and general debugging!

---

# 8/29/2022
Improved the way the initial menu and main menu functions take the user’s selection and added error handling. TODO: more debugging; add more error handling; and spruce up the display of each menu, i.e. adding labels to each menu (WEDNESDAY).

---

# 8/30/2022
Added an option to cancel when assigning, adding, and deleting; added weekday labels to main menu; and finally, I decided to implement the program at work today! I think it’s debugged enough that it will work for all general purposes - I will add things like assignment deletion later. TODO make the most recent assignment display by default and rename the view assignments to view all assignments.

---

# 8/31/2022
Improved the look of the code by wrapping the long sprintf query statements.

---

# 9/7/2022
Found a bug - date(‘now’) sets the date according to UTC time, so my lesson times after 5pm were registering as the next day. I had to change the function to date(‘now’, ‘localtime’).

---

# 9/21/2022
Quickly debugged the program - when a new student is created, the date will display correctly according to local time.

---

# 10/6/2022
Added create database feature that creates a database with the requisite tables if none exists in the program directory. I used sqlite3_open_v2 to check for the existence of a database. It works because this function takes two extra parameters: one that more precisely specifies what to do with the database once opened (I passed in SQLITE_OPEN_READONLY, which throws an error if no database exists, voila!) and one that I don’t really understand - it dictates what VFS module to use based on what operating system you’re running. I pushed all the changes to my repository!

---

# 10/7/2022
Tried to implement a function that allows the user to restore archived students, a feature that I do need. However, I found that the changes would be more complex than I thought, and I wasn’t up for the task today. Plus I find that there is probably an easier way to implement such a feature. I executed two git commands, git reset —hard AND git clean -fxd, which reverted my local project folder back to the previous commit, effectively “undoing” my uncommitted changes.

---

# 11/16/2022
Made some simple changes to the directory.
```
Git rm —cached studentlog.db // to remove the db from tracked files
```

I ran the same command for a few other files. Finally, I added a .gitignore file to make sure that the database file and any object files are never tracked.

---

# 11/30/2022
I watched a video about WebAssembly, and now my interest is piqued. I have very limited understanding at the most, but I know I can use it to compile my C code for the web browser. One main tool for this is Emscripten, which I run into before when I was searching for ways to create a gui for my studentlog app. Just for fun, I tried compiling my studentlog3.0 app with Emscripten. After some finagling, I was able to get it to compile without any errors, but the program still wouldn’t run properly in the browser. Oh well, I’ll try again soon! Here’s the video: [WebAssembly](https://youtu.be/3sU557ZKjUs)
