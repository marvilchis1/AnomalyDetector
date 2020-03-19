#! /bin/bash

FILES=$(ls *tiff | sed ' s/.tiff//')


#for item in $FILES ; do
#    echo $item
#done

for item in $FILES ; do
    #Imprime en pantalla
    echo 'transform '$item'.tiff --> '$item'.png'
    #2> /dev/null quita el mensaje de writing file
    #jpegtopnm $item'.tiff' 2> /dev/null | pnmtopng > $item'.png'
    convert $item.tiff $item.png
done


#LIST='0 1 2 3 4 5 6 7 8 9'
#Intera sobre una lista de elementos separados por espacios
#for i in $LIST ; do
#    echo "Mensaje $i"
#done

#echo $FILES
