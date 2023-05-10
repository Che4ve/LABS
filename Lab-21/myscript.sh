#!/bin/bash

read -ra PARAM <<< "$1"
parameter_name=$(echo "${PARAM[*]}" | cut -d'=' -f 1)

if [ "$parameter_name" = "-files" ]; then
    FILES=$(echo "${PARAM[*]}" | cut -d'=' -f 2)
fi

read -r -p "Do you want to add a new file to delete? (y/n): " new_prm_required
IFS=','
while [ "$new_prm_required" = "y" ]; do
    read -r -p "Enter file name: " file_name
    FILES+=("$file_name")
    echo "Resized parameter list: ${FILES[*]}"
    read -r -p "Add more? (y/n): " new_prm_required
done

if [ -z "${FILES[*]}" ]; then
    echo "No files to delete. Exiting..."
    IFS=
    exit 0
fi

echo -e "\nI am going to help you delete the files"
read -r -p "Proceed? (y/n) " permission
if [ "${permission}" = "y" ]; then
    echo -e "\nEnter the minimum amount of blocks a file must content: "
    read -r min_blocks
    if [[ -n "$min_blocks" && "$min_blocks" =~ ^[0-9]+$ ]]; then
        for file in ${FILES[@]}; do
            if ! [ -e "$file" ]; then 
                echo "($file) Fail: file does not exist"
                continue
            fi
            file_blocks=$(stat -f "%b" "$file")   
            if [ "$file_blocks" -ge "$min_blocks" ]; then
                echo "($file) Success: deleting file... (size: $file_blocks blocks)"
                #rm -f "$file"
            else
                echo "($file) Skip: file size is less than $min_blocks blocks"
            fi
        done
        IFS=
        exit 0
    fi
    echo "Error: number of blocks is in invalid range"
    IFS=
    exit 0
elif [ "${permission}" = "n" ]; then
    IFS=
    exit 0
fi
IFS=
exit 0