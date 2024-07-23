install() {
	make -j $(nproc)
	mv build/zeta "$GITMAN_BIN"/zeta
	mkdir -p ~/.config/zeta
	cp -r assets/* ~/.config/zeta/
}

uninstall() {
	rm "$GITMAN_BIN"/zeta
	rm -rf ~/.config/zeta
}

update() {
	make -j $(nproc)
	mv build/zeta "$GITMAN_BIN"/zeta
	cp -r assets/* ~/.config/zeta/
}

if [ $1 = "install" ] ; then 
	install
elif [ $1 = "uninstall" ] ; then
	uninstall
elif [ $1 = "update" ] ; then
	update
else
	echo unknown option
	exit 1
fi
