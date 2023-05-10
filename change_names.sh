#!/bin/bash

for file in *; do
    old_name=$(basename "$file")
    new_name="${old_name/Лаба /Lab-}"
    mv "$old_name" "$new_name"
done

ls