echo Starting Zeta installer...
sleep 2

echo "Installing Zeta..."
git clone https://github.com/acidicneko/zeta.git
make -C zeta/
sudo cp zeta/build/zeta /usr/bin/zeta
mkdir -p ~/.config/zeta
cp -r zeta/assets/* ~/.config/zeta/
chmod +x ~/.config/zeta/update.sh
rm -rf zeta
CURRENT_HASH=$(curl -H "Accept: application/vnd.github+json" \
        https://api.github.com/repos/acidicneko/zeta/commits/main \
        | grep sha \
        | awk 'NR==1{print $2}' \
        | sed 's/[",]//g')
echo "LAST_HASH=$CURRENT_HASH" > "$HOME"/.config/zeta/last_commit
echo "Zeta has been installed"
