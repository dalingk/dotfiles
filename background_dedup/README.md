# Background Image Deduplicator
## Usage
Compile and install [pHash](https://phash.org/).

```
sudo apt-get install cimg-dev
./configure --disable-video-hash --disable-audio-hash --enable-pthread --enable-openmp
make
sudo make install
sudo ldconfig
```

Compile `dedup.cpp`

```
g++ -O3 -Wall -std=c++17 -o dedup -g dedup.cpp -lpHash
```

Run

```
./dedup $HOME/Pictures
```
