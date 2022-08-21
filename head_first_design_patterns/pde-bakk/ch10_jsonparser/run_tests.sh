set -e

for arg in "$@"
do
  if [[ -$arg == -"--help" ]]; then
    echo "Run me without arguments to run all the tests,"
    echo "Or specify one or more of the following to run their specific tests"
    echo "boolean, foat, integer, list, nulltype, object, string"
    exit 0
  fi
done


if [[ ! -d cmake-build-debug ]]; then
  cmake -B cmake-build-debug
fi
cd cmake-build-debug
cmake --build . --target test.out

if [[ $# -eq 0 ]]; then
  ./test.out -d yes --order lex
else
  for arg in "$@"
  do
    ./test.out -d yes --order lex -# ["#test_${arg}"]
  done
fi
