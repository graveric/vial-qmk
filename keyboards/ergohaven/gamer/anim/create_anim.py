import cv2 as cv
import numpy as np
from PIL import Image
from itertools import groupby

NBITS = 4
NCOLORS = 1 << NBITS
WIDTH = 240
HEIGHT = 224
MAX_RUN = (1 << (8 - NBITS)) - 1
print(MAX_RUN)
NIMGS = 16


def to_rle(img):
    encoded_data = []
    for key, group in groupby(img.ravel()):
        count = len(list(group))
        while count > MAX_RUN:
            encoded_data.append((MAX_RUN << NBITS) | key)
            count -= MAX_RUN
        encoded_data.append((count << NBITS) | key)
    return encoded_data


f = open(f'anim.c', 'w')
header = '''
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
'''
print(header, file=f)

for i in range(0, NIMGS):
    if True:
        img = cv.imread(f'../res/{i:02d}.png', cv.IMREAD_UNCHANGED)
        mask = img[..., 3] > 1
        for c in range(3):
            img[..., c] = img[..., c] * (img[..., 3] / 255)
        img[~mask] = (255, 0, 0, 0)
        img = img[..., :3]
        img = img[..., ::-1]
        pilimg = Image.fromarray(img)
    else:
        pilimg = Image.open(f'../res/{i:02d}.png')
    print(pilimg.getpalette())
    print('pillow mode', pilimg.mode)
    pilimg = pilimg.quantize(colors=NCOLORS, method=Image.Quantize.FASTOCTREE)
    print(pilimg.getpalette())

    # put background as first color
    colors = pilimg.getcolors()
    new_colors = sorted(colors, key=lambda x: x[0], reverse=True)
    pilimg = pilimg.remap_palette([x[1] for x in new_colors])
    # pilimg.show()

    palette = np.array(pilimg.getpalette(), dtype=np.uint8).reshape(-1, 3)[:NCOLORS, ::-1]
    palette_str = []
    for j, (b, g, r) in enumerate(palette):
        palette_str.append(f'{r}, {g}, {b}, // color {j}')
    palette_str = '\n'.join(palette_str)

    img = np.array(pilimg)
    roi_x0, roi_y0 = 0, 0
    roi_x1, roi_y1 = WIDTH - 1, HEIGHT - 1
    while np.count_nonzero(img[:, roi_x0]) == 0:
        roi_x0 += 1
    while np.count_nonzero(img[:, roi_x1]) == 0:
        roi_x1 -= 1
    while np.count_nonzero(img[roi_y0, :]) == 0:
        roi_y0 += 1
    while np.count_nonzero(img[roi_y1, :]) == 0:
        roi_y1 -= 1

    img = img[roi_y0:roi_y1 + 1, roi_x0:roi_x1 + 1]
    rle = to_rle(img)
    print(len(rle))
    rle_str = ', '.join(map(str, rle))
    name = f'anim_{i:02d}'
    template = f'''
#ifndef LV_ATTRIBUTE_IMG_{name.upper()}
#define LV_ATTRIBUTE_IMG_{name.upper()}
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_{name.upper()} uint8_t {name}_map[] = {{
{palette_str}
{roi_x0}, {roi_y0}, {img.shape[1]}, {img.shape[0]}, // x0 y0 w h
{rle_str}
}};

const lv_img_dsc_t {name} = {{
  .header.cf = LV_IMG_CF_USER_ENCODED_0,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = {WIDTH},
  .header.h = {HEIGHT},
  .data_size = {len(rle) + NCOLORS*3},
  .data = {name}_map,
}};
    '''

    print(template, file=f)

    img = palette[img]
    cv.imshow('img', img)
    if cv.waitKey(1) in [27, ord('q')]:
        break
