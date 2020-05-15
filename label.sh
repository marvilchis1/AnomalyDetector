#! /bin/bash

while read LINE ; do
   echo "$LINE $2"
done < $1

