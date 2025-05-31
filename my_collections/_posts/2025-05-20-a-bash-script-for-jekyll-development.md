---
layout: post
title: A Bash Script for Jekyll Development
author: Sean David Reed
date: 2025-05-20
category: Bash
---

I'm a fan of the static site generator [Jekyll](https://jekyllrb.com). It can do as much or as little as you want it to do, simply providing the directory structure or organizing your content all the way to the look and feel with templates. Personally, I only wanted Jekyll for its organization, integration with GitHub Pages, and built-in support for markdown and the [Liquid](https://shopify.github.io/liquid/) templating language. Everything else was up to me, the HTML, CSS, JavaScript, and little additions like LaTeX support and the [darkmode.js](https://darkmodejs.learn.uno/) widget (really cool and not that little).

I'll be modifying the layout and content of this site for the foreseeable future, so I needed a convenient way to open my development environment and gets things running quickly. I like to use Vim as much as possible for things; it makes me feel like I know something about computers. I'll outline the steps I take to start developing.

## Steps

1. Open a terminal and navigate to my jekyll website directory.
2. `git pull` to make sure there aren't changes I pushed from another machine.
3. `tmux new -s jekyll` to open a new terminal session within the current session.
4. `bundle exec jekyll serve` to serve my website via localhost.
5. **Ctrl+B D** to detach from the virtual terminal.
6. Open firefox and navigate to **http://127.0.0.1:4000**.
7. Return to the terminal and open the files I need to edit in Vim.

After following this routine perhaps over 100 times, I decided a bash script was in order. [Here's the full script](/files/bash_scripts/jekyll-bash-script.html) with personal directories redacted; I'll also break down what I wrote.

## Script Breakdown

Error handling for when the user inputs more than one argument.

```
if [[ $2 ]];then

	echo "Too many arguments. Usage: jek [ start | stop ]"
	return 1
fi
```

Error handling for when the user inputs less than one argument.

```
if [[ $1 == "" ]];then

	echo "Too few arguments. Usage: jek [ start | stop ]"
	return 1
fi
```

Inside the third if statement block, the condition for starting development.

- Make sure everything is up to date

    ```
    cd ~/path/to/jekyll/website/dir/

    git pull
    ```

- Open new virtual terminal with terminal multiplexor without entering it. From the parent terminal, send a command to the virtual terminal to start the local jekyll server.

    ```
    tmux new -d -s jekyll
    tmux send-keys -t jekyll "bundle exec jekyll serve" ENTER
    ```

- Launch firefox in the background, open a tab with **localhost**, and send any stdout messages into oblivion.

    ```
    firefox & > /dev/null

    sleep 5

    firefox http://localhost:4000 & disown > /dev/null

    ls

    return 0
    ```

The condition for stopping development.

```
if [[ $1 == "stop" ]];then
	
	tmux kill-session -t jekyll
	tmux ls
	echo "Stopped."
	return 0
fi
```

Error handling for invalid arguments, anything other than "start" or "stop".

```
echo "Invalid argument. Usage: jek [ start | stop ]"

return 1
```

## Why Return Instead of Exit?

Ordinarily, when a bash script needs to terminate early, an *exit* statement is used. Scripts run in a separate process, so exiting a script means *exiting* that process to return to the shell that called it. 

My script needs to change my directory to that of the jekyll website. If I run it as a script, the directory change won't persist when the script ends and the separate process terminates. To get around this, I created an alias that calls the script as a shell function by prepending a dot. That way, it won't create a separate process.

```
echo "alias jek='. ~/path/to/script'" >> ~/.bashrc
```

In my case, I keep a separate file **~/.bash_aliases** that links to the **~/.bashrc** file.

Since my script runs as a shell function, if I used *exit* statements, the whole shell would close. Instead, I used *return* statements, which only affect the running of the shell function.

## That's It

Initially, the script was much simpler, but I added in the error handling and messages for posterity. I'm always happy to find an excuse to write a bash script!
