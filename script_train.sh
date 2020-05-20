 #! /bin/bash

# Modo de uso:
# $ ./script_train.sh <directorio> <salida>
#
# <directorio> Es la ruta al directorio en donde esta la base de datos con los vectores de caracteristicas
#
# <salida>     Nombre del archivo de salida. Contendrá una tabla con los vectores de las clases promedio
#
# Ejemplo:
# $ ./script_train ~/tesis/texturas data.txt

# Obtenemos una lista de las imágenes PNG del directorio especificado como
# argumento a este script. Si no se especifica ningún argumento se asume que es
# el directorio de trabajo.

#LIST=$(ls $1/*.png)

touch $2  # crea el archivo de salida
#for file in $LIST ; do
./train $file >> $2
#done

# Nota: El doble >> indica que la salida del programa se agregue al final del
# archivo especificado en $2. Si se usa > se sobreescribe el archivo cada vez,
# que no es lo que se desea.

