BUILD_DIR='build'
EXECUTABLE='a.out'

if [ ! -d $BUILD_DIR ]
then
	cmake -S . -B build
fi

cmake --build build && "$BUILD_DIR/src/$EXECUTABLE"
