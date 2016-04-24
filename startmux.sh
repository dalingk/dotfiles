#!/bin/bash
session="piMux"
tmux has-session -t $session &> /dev/null
if [ $? != 0 ]; then
    tmux start-server
    tmux new-session -d -s $session	-n "Main"
    tmux select-pane -t 1
    tmux split-window -h -p 50
    tmux select-pane -t 2
    tmux split-window -v -p 50
    tmux new-window -t $session:2 -n "Website"
    tmux select-pane -t 1
    tmux split-window -h -p 50
    tmux select-pane -t 2
    tmux split-window -v -p 50
    tmux new-window -t $session:3 -n "Scratch"
    tmux select-window -t $session:1
    tmux attach-session -t $session
else
    echo "TMUX already running."
fi
