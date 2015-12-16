## Fast segmentation of object from background in given bounding box

Code author : Tomas Vojir

________________

This is a C++ implementation of fast segmentation algorithm presented in "A graphical model for rapid obstacle 
image-map estimation from unmanned surface vehicles" paper.

It is free for research use. If you find it useful or use it in your research, please acknowledge my git repository 
and cite the original paper [1].

The code depends on OpenCV 2.4+ library and is build via cmake toolchain.

_________________
Quick start guide

for linux: open terminal in the directory with the code

$ mkdir build; cd build; cmake .. ; make

This code compiles into binary **segment**

./segment image_file_path_name x1 y1 x2 y2 apriori 
 - INPUT : image_file_path ... image file to be used for segmentatin
           (x1,y1) is top-left corner and (x2, y2) is bottom-right corner
           apriori (optional) ... >0 use pixel weights in extraction of foreground model 
           (i.e. pixels near the center of the bbox have higher probability that belong to object)
 - OUTPUT : visualize segmentation of the object

__________
References

[1] M. Kristan, J. Pers, V. Sulic, S. Kovacic, "A graphical model for rapid obstacle image-map estimation from unmanned surface vehicles", in Proc. Asian Conf. Computer Vision, 2014

_____________________________________
Copyright (c) 2014, Tomáš Vojíř

Permission to use, copy, modify, and distribute this software for research
purposes is hereby granted, provided that the above copyright notice and 
this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
