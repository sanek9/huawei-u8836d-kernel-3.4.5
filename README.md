huawei-u8836d-kernel-3.4.5
==========================

For build:

cd /{PATH}/kernel

CROSS_COMPILE=/{PATH}/4.6.3/bin/arm-linux-androideabi- TARGET_PRODUCT=huaqin77_cu_jb2 ./build.sh release

After a few minutes kernel and modules in the folder build_result


To compress the modules:

cd build_result/system/lib/modules && find . -type f -name '*.ko' | xargs -n 1 /{PATH}/4.6.3/bin/arm-linux-androideabi-strip --strip-unneeded && cd ../../../..
