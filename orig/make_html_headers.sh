#!/bin/bash

# Directory containing HTML files
directory="$HOME/git/www"

# Expand the directory path and store files in an array
html_files=($directory/*.html)

# Check if array is empty
if [ ${#html_files[@]} -eq 0 ]; then
    echo "No HTML files found in $directory."
    exit 1
fi

# Loop through all .html files in the specified directory
for file in "${html_files[@]}"; do
    # Construct new file name by replacing .html with .h
    new_file="${file%.html}.h"
    # Use mv to rename the file
    mv "$file" "$new_file"
done

echo "All .html files have been renamed to .h files."

