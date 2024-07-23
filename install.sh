echo Starting Zeta installer...
sleep 2

echo "Installing Zeta..."
git clone https://github.com/acidicneko/zeta.git
make -C zeta/
sudo cp zeta/build/zeta /usr/bin/zeta
mkdir -p ~/.config/zeta
cp -r zeta/assets/* ~/.config/zeta/
rm -rf zeta
echo "Zeta has been installed"
