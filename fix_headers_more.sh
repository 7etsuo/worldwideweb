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
    # Use sed to remove the specific string from each file
    sed -i 's/End of declaration module//g' "$file"
done

echo "The string 'End of declaration module' has been removed from all files."

