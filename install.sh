echo Starting Zeta installer...
sleep 2

read -p "Install or Update Zeta[i/u]: " choice
if [ "$choice" = "i" ] ; then 
    echo "Installing Zeta..."
    git clone https://github.com/acidicneko/zeta.git
    make -C zeta/
    sudo cp zeta/build/zeta /usr/bin/zeta
    mkdir -p ~/.config/zeta
    cp -r zeta/assets/templates ~/.config/zeta/
    rm -rf zeta
    echo "Zeta has been installed"
elif [ "$choice" = "u" ] ; then
    echo "Updating Zeta..."
    git clone https://github.com/acidicneko/zeta.git
    make -C zeta/
    sudo cp zeta/build/zeta /usr/bin/zeta
    echo "Zeta has been updated."
    rm -rf zeta
else
    echo "Wrong option: " "$choice"
fi
