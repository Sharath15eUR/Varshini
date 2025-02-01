#!/bin/bash

if [ "$#" -le 0 ]; then
	echo "Expecting input file"
	exit 1
fi

# INPUT FILE TO BE TRAVERSED
input="$1"

# OUTPUT FILE
output="output.txt"
> "$output"

# TRAVERSING THROUGH EACH LINE IN THE FILE
while IFS= read -r line; do
	if echo "$line" | grep -qE '\"frame\.time\"|\"wlan\.fc\.type\"|\"wlan\.fc\.subtype\"'; then
		echo "$line" | sed 's/^[[:space:]]*//' >> "$output"
  	fi
done < "$input"
