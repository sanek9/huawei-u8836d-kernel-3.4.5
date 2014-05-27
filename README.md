huawei-u8836d-kernel-3.4.5
==========================

For build:

cd /<path>/beta22
CROSS_COMPILE=/<path>/4.6.3/bin/arm-linux-androideabi- TARGET_PRODUCT=huaqin77_cu_jb2 ./build.sh release

To compress the modules:
cd build_result/system/lib/modules && find . -type f -name '*.ko' | xargs -n 1 /<path>/4.6.3/bin/arm-linux-androideabi-strip --strip-unneeded && cd ../../../..
