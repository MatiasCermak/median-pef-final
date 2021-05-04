export CC=$(which clang)
export CC+=$(which clang)

mkdir cmakebuild
cd cmakebuild
cmake ..
make
