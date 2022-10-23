echo Starting Zeta installation...
sleep 3
git clone https://github.com/acidicneko/zeta.git
make -C zeta/
cp zeta/build/zeta /usr/bin/zeta
mkdir -p ~/.config/zeta
cp -r zeta/assets/templates ~/.config/zeta/
echo Zeta has been installed.