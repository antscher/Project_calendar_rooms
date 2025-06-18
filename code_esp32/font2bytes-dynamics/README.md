# font2bytes (Modified Version)

Python script to create custom fonts for Waveshare e-Paper / e-Ink (ESP32 module)

---

## 📌 About This Fork

This is a modified version of the original [font2bytes](https://github.com/TheHeXstyle/font2bytes) project by [TheHeXstyle](https://github.com/TheHeXstyle), licensed under **LGPL v3.0**.

My contribution introduces **dynamic character widths**:  
🔠 Each character now has its own **individual width** depending on its actual pixel width, instead of a fixed-size grid. This allows more compact and proportional text rendering on e-paper displays.

However, you have to also modify the library of waveshare (there is an example in main in src of this repo)

---

## 🎯 Motivation

The Waveshare ESP32 library only offers a few basic fixed-width fonts (`font8`, `font12`, `font16`, `font20`, `font24`). This is very limiting for UI design or text-heavy applications.

This script helps generate **custom variable-width fonts** using any TrueType font (`.ttf`), with complete control over size and style.

---

## 🧰 Requirements

- Python 3
- [Pillow](https://pillow.readthedocs.io/en/stable/index.html)
- [numpy](https://numpy.org/install/)

> 💡 **Note:** Pillow and PIL cannot co-exist in the same environment. Please uninstall `PIL` before installing `Pillow`.

---

## 🛠️ How to Use

1. Drop any font you want to use (`.ttf`) inside the `./fonts` folder.

2. In `font2bytes.py`, configure:
   - A name for your new font output file
   - The `.ttf` font name you want to use (default: `Roboto-Regular`)
   - The desired height of characters (width is dynamic)

3. Run the script:

   ```bash
   python font2bytes.py

The python script will generate the new .cpp file within the ./output folder with the desired name

within the waveshare library source folder (Arduino\libraries\esp32-waveshare-epd\src)

4. add the new .cpp font file

5. open the fonts.h and

6. add a new "extern" line with the name of the new font

    E.g.: extern sFONT FontBold40;

7. Use the new font in your script and enjoy!

    E.g. Paint_DrawString_EN(5, 0, "waveshare Electronics", &FontBold40, BLACK, WHITE);


Examples
-------------------
within the ./output folder there are already a couple of .cpp files that can be used without running the oython code.
Just follow the instructions from the 6th step


Author
-------------------
Original version by TheHeXstyle

Modified and extended by Antscher to support dynamic character widths


License
-------------------
LGPL v3.0, see LICENSE for details.
