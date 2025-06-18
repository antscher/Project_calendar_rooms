import qrcode
from PIL import Image

# QR Code version 4 = 33x33 modules, box_size ajusté pour 100x100px
#******************************************************************************
# function:    generate_cpp_qr
# parameter:
#    url : String URL to encode in the QR code
#    cpp_path : String path where to save the C++ header file
#    png_path : Optional String path to save QR code as PNG image
# return:
#    None : Generates QR code and saves it as C++ header and optionally as PNG
#******************************************************************************
def generate_cpp_qr(url, cpp_path, png_path=None):
    qr = qrcode.QRCode(
        version=4,
        error_correction=qrcode.constants.ERROR_CORRECT_M,
        box_size=1,
        border=4
    )
    qr.add_data(url)
    img = qr.make_image(fill_color="black", back_color="white").convert("1")
    img = img.resize((120, 120), Image.NEAREST)

    if png_path:
        img.save(png_path)

    pixels = img.load()
    width, height = img.size
    byte_array = []
    for y in range(height):
        for x in range(0, width, 8):
            byte = 0
            for b in range(8):
                byte <<= 1
                if x + b < width and pixels[x + b, y] == 0:
                    byte |= 1
            byte_array.append(byte)

    with open(cpp_path, "w") as f:
        f.write('#include "ImageData.h"\n\n')
        f.write('// \'QR code\', 120x120px\n')
        f.write('const unsigned char QR_code [] = {\n')
        for i, byte in enumerate(byte_array):
            if i % 12 == 0:
                f.write('    ')
            f.write(f'0x{byte:02x}, ')
            if (i + 1) % 12 == 0:
                f.write('\n')
        f.write('\n};\n\n')
        f.write('const IMAGE qr_code = {\n')
        f.write('    QR_code,\n')
        f.write('    120,\n')
        f.write('    120\n')
        f.write('};\n')
