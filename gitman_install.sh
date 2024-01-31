install() {
	make -j $(nproc)
	mv build/zeta "$GITMAN_BIN"/zeta
	mkdir -p ~/.config/zeta
	cp -r assets/* ~/.config/zeta/
	chmod +x ~/.config/zeta/update.sh
	CURRENT_HASH=$(curl -H "Accept: application/vnd.github+json" \
        	https://api.github.com/repos/acidicneko/zeta/commits/main \
        	| grep sha \
        	| awk 'NR==1{print $2}' \
        	| sed 's/[",]//g')
	echo "LAST_HASH=$CURRENT_HASH" > "$HOME"/.config/zeta/last_commit
}

uninstall() {
	rm "$GITMAN_BIN"/zeta
	rm -rf ~/.config/zeta
}

if [ $1 = "install" ] ; then 
	install
elif [ $1 = "uninstall" ] ; then
	uninstall
else
	echo unknown option
	exit 1
fi
