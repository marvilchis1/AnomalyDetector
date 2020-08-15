#!/bin/bash

# Takes directory entries specified and renames them using the pattern provided.

i=1
for directory in $1/*
do
    if [ -d "$directory" ]
    then
      echo $directory
      mv "${directory}" "${i}" || echo 'Could not rename '"$directory"''
      ((++i))
    fi
done