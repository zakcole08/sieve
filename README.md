# Sieve - Image Viewer
---

### Install

```bash
# clone repo
git clone https://github.com/zakcole08/sieve.git
cd sieve
# compile
gcc sieve.c -o sieve `sdl2-config --cflags --libs`
```

### Usage

```bash
cat <filename> | ./sieve
```

### Notes

- Currently only supports .ppm image format
- Doesn't work on PPM's that have comment lines

### ToDo

- Add parsing and proper handling for max colour value and comment line
- Add functionality to pass filename as an argument
- Add support for new image formats
