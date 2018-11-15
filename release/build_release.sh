cd ..
make
cd release
~/Documents/GitHub/odroid-go-firmware/tools/mkfw/mkfw Duke3D Tile.data 0 16 1048576 app ../build/Duke3D.bin
rm Duke3D.fw
mv firmware.fw Duke3D.fw
