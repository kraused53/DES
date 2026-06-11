
To build and run DES
```bash
cmake -S . -B build
cmake --build build
.\build\Debug\DES.exe
```

To build and run tests
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```