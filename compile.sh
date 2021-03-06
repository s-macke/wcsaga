set -e

export CFLAGS="-g -O0"
export CXXFLAGS="-g -O0 -Wno-variadic-macros -Wno-class-memaccess -Wno-unused-but-set-variable -Wno-shadow -Wno-unused-value -Wno-format-overflow -Wno-format-security -Wno-parentheses -Wno-implicit-fallthrough -Wno-unused-variable -std=c++11"
export PNG_CFLAGS="-I$PWD/libpng"
export PNG_LIBS="../libpng/libpng.a ../zlib/libz.a"
export LUA_CFLAGS=" "
export LUA_LIBS=" "

cd libjpeg
rm -f *.a
rm -f *.o
gcc $CFLAGS -DSCP_UNIX -c *.c
ar r libjpeg.a *.o
cd ..

cd libpng
rm -f *.a
rm -f *.o
gcc $CFLAGS -c *.c
ar r libpng.a *.o
cd ..

cd lua
rm -f *.a
rm -f *.o
gcc $CFLAGS -DLUA_ANSI -c *.c
ar r liblua.a *.o
cd ..

cd zlib
rm -f *.a
rm -f *.o
gcc $CFLAGS -c *.c
ar r libz.a *.o
cd ..

#cd libogg
#cd src
#rm -f *.a
#rm -f *.o
#gcc $CFLAGS -c *.c
#ar r libogg.a *.o
#cd ..
#cd ..

make clean
./configure --with-static-jpeg=$PWD/libjpeg --enable-debug
make j=4


#readelf -d ./fs2_open_r
#./fs2_open_d -wcsaga -window
