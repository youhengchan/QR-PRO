# coding:utf-8
# @Author : youhengchan@idiospace.com

import qrcode
import numpy as np

data = "http://idiospace.com"
qr = qrcode.QRCode(
    version=1,			#version二维码的格子矩阵大小，可以是1到40
    error_correction=qrcode.constants.ERROR_CORRECT_L,	#error_correction二维码错误容许率，默认ERROR_CORRECT_M，容许小于15%的错误率
    box_size=1,	#box_size二维码每个小格子包含的像素数量
    border=0,	#border二维码到图片边框的小格子数，默认值为4
)

qr.add_data(data=data)
img = qr.make_image(fill_color="black", back_color="white")
img.show()  # 以BMP的格式输出图片

img_arr = np.array(img)

print(img_arr.shape)
[rows, cols] = img_arr.shape
for i in range(rows):
    for j in range(cols):
        if img_arr[j, i]:
            print("1", end="")
        else:
            print("0", end="")
        print(", ", end="")
    print("")


