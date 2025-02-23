#!/bin/bash

rev1="$1"
rev2="$2"

svn_dir="$3"

# Extract the name of the directory from the given SVN path
dir=${svn_dir%/}
dir="${dir##*/}"

# Initialize a new empty Git repository with the extracted directory name
git init "$dir"

cd "$dir"

# Iterate through all the revisions from $rev1 to $rev2
for r in $(seq $rev1 $rev2); do

    # Check if the given SVN revision exists
    svn log -q -r "$r" "$svn_dir"
    if [ $? == "1" ]; then
        # If the revision doesn't exist, skip to the next one
        continue
    fi

    # Export the content of the SVN directory at the specific revision
    rm -rf *  # Clear the current directory to avoid residual files
    svn export --force -q "$svn_dir" -r "$r" "./"

    # Extract the commit message for the given revision from SVN
    msg="$(svn log -r $r $svn_dir | tail -n +4 | head -n -2)"

    # Add all the exported files to the Git staging area and commit them
    git add "./**/*"
    git commit -m "$msg"

done

