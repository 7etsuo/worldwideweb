#!/bin/bash

# Directory containing HTML files
directory="$HOME/git/www"

# Loop through all .html files in the specified directory
for file in "$directory"/*.html; do
    # Use sed to delete any lines containing < and >
    sed -i '/<.*>/d' "$file"
done

echo "Lines containing HTML tags have been removed from all files."

