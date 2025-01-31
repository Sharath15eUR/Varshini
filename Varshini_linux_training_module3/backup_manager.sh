#!/bin/bash

# COMMAND-LINE ARGUMENTS AND QUOTING
# CHECKING THE INPUT REQUIREMENTS
if [ "$#" -ne 3 ]; then
	echo "Please, Enter the source directory, destination directory an the file format"
	exit 1
fi

# VARIABLE ASSIGNMENT
SOURCE=$1
BACKUP=$2
FILEFORMAT=$3

# SOURCE DIRECTORY CHECK
if [ ! -d "$SOURCE" ]; then
	echo "Source directory not found"
	exit 1
fi

# BACKUP DIRECTORY CHECK
if [ ! -d "$BACKUP" ]; then
	echo "Backup directory not found. Creation of directory for backup"
	mkdir -p "$BACKUP"
	if [ ! -d "$BACKUP" ]; then
		echo "Backup directory creation failed"
		exit 1	
        fi
fi

# GLOBBING
# FILES EXTRACTION FROM SOURCE DIRECTORY TO BACKUP
BACKUP_FILES=($SOURCE/*$FILEFORMAT)
echo "Backup files ${BACKUP_FILES[@]}"

# CHECKING FILES EXISTENCE
if [ ${#BACKUP_FILES[@]} -eq 1 ]; then
	echo "No files are inside source directory $SOURCE with this extension $FILEFORMAT"
	exit 1
fi

# EXPORT STATEMENTS
# GLOBAL VARIABLE SETUP FOR BACKUPCOUNT AND TOTALSIZE OF THE FILE
export BACKUP_COUNT=0
TOTAL_SIZE=0

# ARRAY OPERATIONS AND CONDITIONAL EXECUTION
# BACKUP FILE SETUP
for file in "${BACKUP_FILES[@]}"; do

	# FILE EXISTENCE IN THE DIRECTORY
	if [ -f "$file" ]; then
		NAME=$(basename "$file")
		SIZE=$(stat -c %s "$file")
		FILE_TO_BACKUP="$BACKUP/$NAME"
		
		# PRINT THE DETAILS OF THE FILES TO BACKUP
		echo ""
		echo "Name:$NAME Size:$SIZE File to be backup:$FILE_TO_BACKUP"
		
		# CHECKING THE DIRECTORY
		if [ -f "$FILE_TO_BACKUP" ]; then
			SOURCE_TIME=$(stat -c %Y "$file")
			BACKUP_TIME=$(stat -c %Y "$FILE_TO_BACKUP")
			if [ "$SOURCE_TIME" -le "$BACKUP_TIME" ]; then
				echo "Backup already exists"
				continue
			fi
		fi
		
		# FILE BACKUP
		cp "$file" "$BACKUP"
		if [ $? -eq 0 ]; then
			export BACKUP_COUNT=$((BACKUP_COUNT +1))
			TOTAL_SIZE=$((TOTAL_SIZE+SIZE))
		else
			echo "Backup failed $NAME"
		fi			
	fi
done

# CHECKING THE FILE BACKUP
if [ "$BACKUP_COUNT" -eq 0 ]; then
	echo ""
	echo "No files were backedup"
	exit 1
fi

# REPORT GENERATION
REPORT="./Backupreport.log"

echo "" > "$REPORT"
echo "Backup Summary Report" >> "$REPORT"
echo "" >> "$REPORT"
echo "Total files processed: $BACKUP_COUNT" >> "$REPORT"
echo "Total size of files backed up: $TOTAL_SIZE" >> "$REPORT"
echo "Source directory: $SOURCE" >> "$REPORT"
echo "Backup directory: $BACKUP" >> "$REPORT"


# PRINTING THE REPORT
cat "$REPORT"

exit 0
