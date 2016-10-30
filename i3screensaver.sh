#!/bin/bash
IMAGE=/tmp/i3lock.png
import -window root $IMAGE
convert $IMAGE -blur "2x8" $IMAGE
i3lock -i $IMAGE
rm $IMAGE
