# Debug configuration
ifndef DEBUG
BUILD_DIR := target
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release
else
BUILD_DIR := debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug
endif

TEST_EXECUTABLE := ${BUILD_DIR}/test/test.out

build: ${BUILD_DIR}
	echo ${BUILD_DIR}
	cmake --build ${BUILD_DIR}

${BUILD_DIR}:
	cmake ${CMAKE_FLAGS} -B ${BUILD_DIR} -S .

# No executable so run is just running tests
run: test

test: build
	${TEST_EXECUTABLE}

ifndef DEBUG
debug:
	$(MAKE) DEBUG=1
endif

clean:
	$(RM) -r ${BUILD_DIR}

.PHONY: clean run build test
