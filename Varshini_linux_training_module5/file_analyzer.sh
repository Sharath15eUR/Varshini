#!/bin/bash

# ERROR LOG
ERROR_LOG="errors.log"

# KEYWORD SEARCH IN FILE
search_in_file() {
  local file="$1"
  local keyword="$2"

  # FILE CHECK
  if [ -f "$file" ]; then
  	# KEYWORD CHECK
  	if grep -q "$keyword" "$file"; then
      		echo "Found keyword '$keyword' in file: $file"
    	else
      		echo "Keyword '$keyword' not found in file: $file"
    	fi
  # FILE NOT FOUND
  else
    	echo "Error: File '$file' not found." | tee -a "$ERROR_LOG"
  fi
}


# RECURSIVE SEARCH
search_files_recursive() {
  # DIRECTORY AND KEYWORD TO SEARCH
  local dir="$1"
  local keyword="$2"

  # ITERATION THROUGH DIRECTORY
  for file in "$dir"/*; do
        # DIRECTORY CHECK
    	if [ -d "$file" ]; then
        	search_files_recursive "$file" "$keyword"
        #FILE CHECK
    	elif [ -f "$file" ]; then
      		# KEYWORD SEARCH
      		search_in_file "$file" "$keyword"
    	fi
  done
}


# HELP MENU
display_help() {
  cat <<-EOF
Usage: $0 [options]

Options:
  -d <directory>  Directory to search recursively.
  -k <keyword>    Keyword to search in files.
  -f <file>       File to search directly.
  --help          Display this help menu.
EOF
}

# KEYWORD VALIDATION FUNCTION
valid_keyword() {
  [[ "$1" =~ ^[a-zA-Z0-9_]+$ ]]
}

# PARSING COMMAND ARGUMENTS
while getopts "d:k:f:" opt; do
  case "$opt" in
    d)
      directory="$OPTARG"
      ;;
    k)
      keyword="$OPTARG"
      ;;
    f)
      file="$OPTARG"
      ;;
    *)
      display_help
      exit 1
      ;;
  esac
done

# HELP FLAG HANDLING
if [[ "$1" == "--help" ]]; then
  display_help
  exit 0
fi

# NO. OF COMMAND LINE ARGUMENTS CHECK
if [[ -z "$keyword" ]]; then
  echo "Error: Keyword must not be empty." | tee -a "$ERROR_LOG"
  exit 1
fi

# KEYWORD CHECK
if ! valid_keyword "$keyword"; then
  echo "Error: Invalid keyword. Please provide a valid alphanumeric keyword." | tee -a "$ERROR_LOG"
  exit 1
fi

# CHECKING INPUT DIRECTORY AND FILE ENTRY
if [[ -z "$directory" && -z "$file" ]]; then
  echo "Error: You must provide either a directory or a file to search." | tee -a "$ERROR_LOG"
  exit 1
fi

# DIRECTORY SEARCH
if [[ -n "$directory" ]]; then
        #DIRECTORY CHECK
  	if [ -d "$directory" ]; then
    		echo "Searching for keyword '$keyword' recursively in directory: $directory"
    		search_files_recursive "$directory" "$keyword"
  	else
    		echo "Error: Directory '$directory' does not exist." | tee -a "$ERROR_LOG"
    		exit 1
  	fi
fi

# SPECIFIC FILE SEARCH
if [[ -n "$file" ]]; then
  search_in_file "$file" "$keyword"
fi

# SUMMARY
echo "Script executed with the following parameters:"
echo "Directory: $directory"
echo "Keyword: $keyword"
echo "File: $file"
echo "Exit status: $?"

	

