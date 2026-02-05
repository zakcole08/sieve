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

### ToDo

- Add parsing and proper handling for max colour value
- Add support for new image formats
- Drag and drop image UI
- Image resizing
