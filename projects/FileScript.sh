#!/bin/sh

# Copyright © 2020  Philip Lindh
# All rights reserved

ChangeExtension()
{
    echo "Do not include any * or ."
    read -p "Change file extension from: " fileFrom
    read -p "Change file extension to: " fileTo
    
    find . -name "*.${fileFrom}"|while read file; do
        echo "Changing contents of "${file}"...";
        mv "$file" "${file%.*}.${fileTo}"; 
    done

    echo "Done."
}

ChangeFileContent()
{
    read -p "Directory: " currentDir
    read -p 'Change all occurances of: ' fromExt
    read -p 'Replace with: ' toExt
    
    for file in $currentDir; do
        echo "Changing contents of $currentFile..."; 
        sed -i "s/"${fromExt}"/"${toExt}"/g" $currentFile;
    done
    
    echo "Done."
}

AddAuthor()
{
    author="// Copyright © 2020  Philip Lindh \n// All rights reserved\n"
    
    find . -name "*.h"|while read file; do
        echo "Changing contents of "${file}"...";
        sed -i "1i${author}" $file
    done
    
    find . -name "*.cpp"|while read file; do
        echo "Changing contents of "${file}"...";
        sed -i "1i${author}" $file
    done
  
    echo "Done."
}

echo "1: Change file-extension"
echo "2: Change the contents of a file"
echo "3: Add Author Trademark"

read -p ">> " option

if [ $option = "1" ] 
then
    ChangeExtension
    exit 0
elif [ $option = "2" ]
then
    ChangeFileContent
    exit 0
elif [ $option = "3" ]
then
    AddAuthor
    exit 0
else
    echo "Failed to recognize your input, please use numbers."
fi
