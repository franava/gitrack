#!/bin/bash

get_mad(){
	echo "No params passed to this instance of execute"
	exit 1 
}

print_repo_into_log(){
	echo "##################" 
	echo "Repo: $1" 
}

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ]
then
	get_mad
fi

BASE_FOLDER=INSTALL_PATH_FOLDER
COMP_FOLDER=$BASE_FOLDER/components
LOG_FOLDER=$BASE_FOLDER/logs
REPO=$1
FOLD=$COMP_FOLDER/$2
LOG=$LOG_FOLDER/$3

cd $BASE_FOLDER

if [ -d "$FOLD" ]
then
	cd $FOLD
	print_repo_into_log $2 2>&1 | tee -a $LOG
	if [ "$4" == "t" ]
	then
		echo "tracking all branches on repo"
		git branch -r | grep -v '\->' | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g" | while read remote; do git branch --track "${remote#origin/}" "$remote"; done
	fi
	git pull --all --tags 2>&1 | tee -a $LOG
else
	cd $COMP_FOLDER
	print_repo_into_log $2 2>&1 | tee -a $LOG
	git clone --recurse-submodules $REPO 2>&1 | tee -a $LOG
fi

cd $BASE_FOLDER 

