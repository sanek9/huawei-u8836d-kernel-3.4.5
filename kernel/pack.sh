
../boot/repack-MT65xx.pl -boot ../build_result/kernel_.bin ../boot/boot.img-ramdisk ../build_result/boot.img

let "v=`cat ../boot/v`+1"
echo $v > ../boot/v

cp ../boot/boot.zip ../release/boot_3.4.5_$v.zip
cp -r ../build_result/system ./
cp ../build_result/boot.img ./
find ./system -type f -name '*.ko' | xargs -n 1 ../4.6.3/bin/arm-linux-androideabi-strip --strip-unneeded
zip -g -r ../release/boot_3.4.5_$v.zip system boot.img
rm -r ./system
rm boot.img
