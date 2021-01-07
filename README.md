# [NCKU Data Mining project](http://class-qry.acad.ncku.edu.tw/syllabus/online_display.php?syear=0109&sem=1&co_no=P764600&class_code=)

Implementation of hits, pagerank and simrank using c++.

## requirement

* cmake3
* c++ compiler with c++17 support
* python3

## install

```bash
git clone https://github.com/StoneLin0708/LinkAnalysis.git
```

If you don't have cmake

```bash
pip install cmake
```

## build

```bash
git submodule update --init
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## run

```bash
python script/gen_result.py
```