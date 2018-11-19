cd ..
make
cd release
/Applications/ffmpeg -i Tile.png -f rawvideo -pix_fmt rgb565 tile.raw
~/Documents/GitHub/odroid-go-firmware/tools/mkfw/mkfw Duke3D tile.raw 0 16 1048576 app ../build/Duke3D.bin
rm Duke3D.fw
mv firmware.fw Duke3D.fw
