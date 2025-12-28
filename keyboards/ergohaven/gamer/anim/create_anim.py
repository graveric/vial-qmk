import cv2 as cv
import numpy as np
from PIL import Image
from itertools import groupby

NBITS = 3
NCOLORS = 1 << NBITS
WIDTH = 240
HEIGHT = 224
MAX_RUN = (1 << (8 - NBITS)) - 1
print(MAX_RUN)


def to_rle(img):
    encoded_data = []
    for key, group in groupby(img.ravel()):
        count = len(list(group))
        while count > MAX_RUN:
            encoded_data.append((MAX_RUN << NBITS) | key)
            count -= MAX_RUN
        encoded_data.append((count << NBITS) | key)
    return encoded_data


all_imgs = []
for i in range(0, 17):
    img = cv.imread(f'../res/{i:02d}.png', cv.IMREAD_UNCHANGED)
    mask = img[..., 3] > 1
    for c in range(3):
        img[..., c] = img[..., c] * (img[..., 3] / 255)
    img[~mask] = (255, 0, 0, 0)
    img = img[..., :3]
    img = img[..., ::-1]

    all_imgs.append(img)

# combine all image to create common palette
all_imgs = np.hstack(all_imgs)
pilimg = Image.fromarray(all_imgs)
pilimg = pilimg.quantize(colors=NCOLORS)

# put background as first color
colors = pilimg.getcolors()
new_colors = sorted(colors, key=lambda x: x[0], reverse=True)
pilimg = pilimg.remap_palette([x[1] for x in new_colors])
# pilimg.show()

palette = np.array(pilimg.getpalette(), dtype=np.uint8).reshape(-1, 3)[:NCOLORS, ::-1]
palette_str = []
for i, (b, g, r) in enumerate(palette):
    palette_str.append(f'{r}, {g}, {b}, // color {i}')
palette_str = '\n'.join(palette_str)

for i in range(0, 17):
    img = np.array(pilimg)[:, WIDTH * i:WIDTH * (i + 1)]
    rle = to_rle(img)
    print(len(rle))
    rle_str = ', '.join(map(str, rle))
    # print(rle)
    img = palette[img]
    template = f'''
#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_ANIM_{i:02d}
#define LV_ATTRIBUTE_IMG_ANIM_{i:02d}
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ANIM_{i:02d} uint8_t anim_{i:02d}_map[] = {{
{palette_str}
{rle_str}
}};

const lv_img_dsc_t anim_{i:02d} = {{
  .header.cf = LV_IMG_CF_USER_ENCODED_0,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = {WIDTH},
  .header.h = {HEIGHT},
  .data_size = {len(rle) + NCOLORS*3},
  .data = anim_{i:02d}_map,
}};

    '''
    # print(template)
    cv.imshow('img', img)
    if cv.waitKey(1) in [27, ord('q')]:
        break

    with open(f'anim_{i:02d}.c', 'w') as f:
        print(template, file=f)

    # print(np.unique(img))
    # img = np.asarray(pilimg)
    # cv.imshow('img', img)
    # if cv.waitKey() == 27:
    #     break

# all_imgs = reduce_palette_kmeans(all_imgs, 16)
# cv.imshow('all_imgs', all_imgs)
# cv.waitKey()

# print(np.unique(img))
# print(np.unique(img))

# cv.imshow('img', img)
