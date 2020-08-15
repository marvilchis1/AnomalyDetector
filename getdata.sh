# Database text name
ORIGIN_DIR=$1
DATABASE_NAME=$2

for directory in ${ORIGIN_DIR}/*
do
    if [ -d "$directory" ]
    then
      # Get basename
      dirname=$directory
      shopt -s extglob           # enable +(...) glob syntax
      basename=${dirname%%+(/)}    # trim however many trailing slashes exist
      basename=${basename##*/}       # remove everything before the last / that still remains
      #printf '%s\n' "$basename"

      # Apply featurevector
      echo $directory
      LIST=$(ls $directory/*.png)
      touch "dataclass${basename}.txt"
      for file in $LIST ; do
        echo "$(./featurevector $file) $basename" >> "dataclass${basename}.txt"
      done

    fi
done

cat dataclass*.txt > $2
cat $2 | sort -R > "s${2}"
rm dataclass*.txt