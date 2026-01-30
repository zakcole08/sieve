# Sieve
---

### Install

```bash
# clone repo
git clone https://github.com/zakcole08/sieve.git
# compile
gcc sieve.c -o sieve `sdl2-config --cflags --libs`
```

### Usage

```bash
cat <filename> | ./sieve
```

### Notes

- Currently only passes in the dimensions of the image and displays solid colour
- Currently only supports .ppm image format

### ToDo

- Read individual pixel rgb values and display to the window
- Add functionality to pass filename as an argument
- Add support for new image formats
