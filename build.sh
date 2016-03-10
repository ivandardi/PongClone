if [[ "$1" == "release" ]]; then
	BUILD_TYPE=Release
else
	BUILD_TYPE=Debug
fi

echo "Building in ${BUILD_TYPE} Mode..."

if [[ ! -d build/"$BUILD_TYPE" ]]; then
	echo "Build directory doesn't exist. Creating it...'"
	mkdir -p build/$BUILD_TYPE
else
	echo "Build directory already exists."
fi

echo "Calling CMake..."
cd build/$BUILD_TYPE
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../..
make

cd ../..
if [[ ! -d bin/"$BUILD_TYPE" ]]; then
	mkdir -p bin/$BUILD_TYPE
fi

mv -v -u build/${BUILD_TYPE}/PongClone bin/${BUILD_TYPE}
