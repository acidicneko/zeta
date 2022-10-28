#!/bin/bash

LOC="$HOME"/.config/zeta/

CURRENT_HASH=$(curl -H "Accept: application/vnd.github+json" 
        https://api.github.com/repos/acidicneko/zeta/commits/main 
        | grep sha 
        | awk 'NR==1{print $2}' 
        | sed 's/[",]//g')

source "$LOC"/last_commit

if [ "$CURRENT_HASH" = "$LAST_HASH" ] ; then
    echo "Already the latest version."
    exit 1
else
    echo "Updating Zeta..."
    git clone https://github.com/acidicneko/zeta.git /tmp/zeta
    make -C /tmp/zeta/
    sudo rm /usr/bin/zeta
    sudo cp /tmp/zeta/build/zeta /usr/bin/zeta
    echo "Zeta has been updated."
    rm -rf /tmp/zeta
    echo "LAST_HASH=$CURRENT_HASH" > "$LOC"/last_commit
fi