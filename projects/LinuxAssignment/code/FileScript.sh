#!/bin/sh

# Copyright © 2020  Philip Lindh
# All rights reserved

# Changes file extension
ChangeExtension()
{
    echo "Do not include any * or ."
    read -p "Change file extension from: " fileFrom
    read -p "Change file extension to: " fileTo
    
    for file in *.${fileFrom}; do 
        mv "$file" "${file%.*}.${fileTo}"; 
    done
    
    echo "Done."
}

ChangeFileContent()
{
    read -p "File: " currentFile
    read -p 'Change all occurances of: ' fromExt
    read -p 'Replace with: ' toExt
    
    
    echo "Changing contents of $currentFile..."; 
    sed -i "s/"${fromExt}"/"${toExt}"/g" $currentFile
    
    echo "Done."
}

echo "1: Change file-extension"
echo "2: Change the contents of a file"

read option

if [ $option = "1" ] 
then
    ChangeExtension
    exit 0
elif [ $option = "2" ]
then
    ChangeFileContent
    exit 0
else
    echo "Failed to recognize your input, please use numbers."
fi
