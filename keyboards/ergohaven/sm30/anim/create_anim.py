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


def find_roi(img):
    if np.count_nonzero(img) == 0:
        return 0, 0, 0, 0

    x0, y0 = 0, 0
    x1, y1 = WIDTH - 1, HEIGHT - 1
    while np.count_nonzero(img[:, x0]) == 0:
        x0 += 1
    while np.count_nonzero(img[:, x1]) == 0:
        x1 -= 1
    while np.count_nonzero(img[y0, :]) == 0:
        y0 += 1
    while np.count_nonzero(img[y1, :]) == 0:
        y1 -= 1
    return x0, y0, x1, y1


def reduce_palette(img):
    pilimg = Image.fromarray(img)
    pilimg = pilimg.quantize(colors=NCOLORS, method=Image.Quantize.FASTOCTREE)
    # put background as first color
    colors = pilimg.getcolors()
    new_colors = sorted(colors, key=lambda x: x[0], reverse=True)
    pilimg = pilimg.remap_palette([x[1] for x in new_colors])
    palette = np.array(pilimg.getpalette(), dtype=np.uint8).reshape(-1, 3)[:NCOLORS, ::]
    palette = palette.copy()
    palette.resize((NCOLORS, 3))
    return np.array(pilimg), palette


def to_lvgl_code(img, palette, name, fmt='LV_IMG_CF_USER_ENCODED_0'):
    colors = []
    for b, g, r in palette:
        colors.extend((r, g, b))
    h, w = img.shape
    x0, y0, x1, y1 = find_roi(img)
    img = img[y0:y1 + 1, x0:x1 + 1]
    rle = to_rle(img)
    data = colors + [x0, y0, img.shape[1], img.shape[0]] + rle

    template = f'''
#ifndef LV_ATTRIBUTE_IMG_{name.upper()}
#define LV_ATTRIBUTE_IMG_{name.upper()}
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_{name.upper()} uint8_t {name}_map[] = {{
{', '.join(map(str, data))}
}};

const lv_img_dsc_t {name} = {{
  .header.cf = {fmt},
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = {w},
  .header.h = {h},
  .data_size = {len(data)},
  .data = {name}_map,
}};
    '''
    return template


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
    print(i)
    img = cv.imread(f'../res/{i:02d}.png', cv.IMREAD_UNCHANGED)
    alpha = img[..., 3].copy()
    for c in range(3):
        img[..., c] = img[..., c] * (alpha / 255.0)
    img = img[..., :3]

    img_ship = img.copy()
    mask_ship = alpha > 254
    kernel = np.ones((3, 3), np.uint8)
    mask_ship = cv.dilate(mask_ship.astype(np.uint8), kernel).astype(bool)

    img_ship[~mask_ship] = (255, 0, 0)

    img_flame = img.copy()
    mask_flame = (alpha > 0) & (alpha < 255) & (img_ship[..., 0] == 255)
    img_flame[~mask_flame] = (0, 0, 0)
    img_flame = (img_flame.astype(np.float32) / img_flame.max() * 255).astype(np.uint8)

    img_ship, palette_ship = reduce_palette(img_ship)
    ship_code = to_lvgl_code(img_ship, palette_ship, f'anim_{i:02d}')
    print(ship_code, file=f)

    img_flame, palette_flame = reduce_palette(img_flame)
    flame_code = to_lvgl_code(img_flame, palette_flame, f'flame_{i:02d}')
    print(flame_code, file=f)

    combine = palette_ship[img_ship].copy()
    combine[mask_flame] = palette_flame[img_flame][mask_flame]
    cv.imshow('combine', combine)

    if cv.waitKey(0) in [27, ord('q')]:
        break
