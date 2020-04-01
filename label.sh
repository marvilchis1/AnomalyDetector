#! /bin/bash

# modo de uso: label.sh <file> <label>
#
# <file>  Nombre del archivo con los datos (vectores) a etiquetar
# <label> Etiqueta que se le agregará a cada vector.
#
# Ejemplo:
#
# $ ./label.sh data.txt 1

touch aux.txt
while read LINE ; do
   echo $LINE $2 >> aux.txt
done < $1

tail -n+1 aux.txt > $1
rm aux.txt



