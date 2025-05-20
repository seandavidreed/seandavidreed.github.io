#!/bin/bash
# 2025-05-19
# A simple script to help me setup my vim development environment for jekyll

if [[ $2 ]];then

	echo "Too many arguments. Usage: jek [ start | stop ]"
	return 1
fi

if [[ $1 == "" ]];then

	echo "Too few arguments. Usage: jek [ start | stop ]"
	return 1
fi

if [[ $1 == "start" ]];then

	cd ~/path/to/jekyll/website/dir/

	git pull

	tmux new -d -s jekyll
	tmux send-keys -t jekyll "bundle exec jekyll serve" ENTER

	firefox & > /dev/null

	sleep 5

	firefox http://localhost:4000 & disown > /dev/null

	ls

	return 0
fi

if [[ $1 == "stop" ]];then
	
	tmux kill-session -t jekyll
	tmux ls
	echo "Stopped."
	return 0
fi

echo "Invalid argument. Usage: jek [ start | stop ]"

return 1
