if [[ "$1" == "debug" ]]; then
	BUILD_TYPE=Debug
else
	if [[ "$1" == "release" ]]; then
		BUILD_TYPE=Release
	else
		BUILD_TYPE=""
	fi
fi

echo "Building in ${BUILD_TYPE} Mode..."

cd build/"$BUILD_TYPE"
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../..
make VERBOSE=1

mv build/${BUILD_TYPE}/PongClone bin/${BUILD_TYPE}

