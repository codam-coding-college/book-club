set -e


cd cmake-build-debug
cmake --build . --target json_parser

cd -
cd tests
if [[ ! -d cmake-build-debug ]]; then
  cmake -B cmake-build-debug
fi
cd -
cmake --build cmake-build-debug --target test.out  # I think --target test.out is optional

pwd
cd cmake-build-debug/tests
./test.out -d yes --order lex
