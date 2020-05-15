 #! /bin/bash

# Modo de uso:
# $ ./script.sh <directorio> <salida>
#
# <directorio> Es la ruta al directorio con las imágenes que se desean procesar.
#              IMPORTANTE: La ruta no debe terminar en /
#
# <salida>     Nombre del archivo de salida. Contendrá una tabla con los
#              vectores de características de cada una de las imágenes
#              procesadas.
#
# Ejemplo:
#
# $ ./script ~/tesis/texturas data.txt

# Obtenemos una lista de las imágenes PNG del directorio especificado como
# argumento a este script. Si no se especifica ningún argumento se asume que es
# el directorio de trabajo.

LIST=$(ls $1/*.png)

# Ahora iteramos sobre los archivos de la lista, y procesamos uno a la vez. El
# programa prog es el que escribiste en C++, recibe como entrada el nombre de un
# archivo PNG y escribe en stdout una línea de texto con el vector de
# características calculado:

#prog = ./featurevector

touch $2  # crea el archivo de salida
for file in $LIST ; do
   ./featurevector $file >> $2
done

# Nota: El doble >> indica que la salida del programa se agregue al final del
# archivo especificado en $2. Si se usa > se sobreescribe el archivo cada vez,
# que no es lo que se desea.

