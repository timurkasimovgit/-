//
// Created by Timur on 18.04.2021.
//
#ifndef KURSACH_READER_H
#define KURSACH_READER_H

int headReader(FILE* pFile, BITMAPFILEHEADER* header, BITMAPINFOHEADER* bmiHeader) {
    header->bfType = read_u16(pFile);
    if (header->bfType != 0x4d42) {
        fclose(pFile);
        error(1);
        return 1;
    }
    header->bfSize = read_u32(pFile);
    header->bfReserved1 = read_u16(pFile);
    header->bfReserved2 = read_u16(pFile);
    header->bfOffBits = read_u32(pFile);

    bmiHeader->biSize = read_u32(pFile);
    bmiHeader->biWidth = read_s32(pFile);
    bmiHeader->biHeight = read_s32(pFile);
    bmiHeader->biPlanes = read_u16(pFile);
    bmiHeader->biBitCount = read_u16(pFile);
    bmiHeader->biCompression = read_u32(pFile);
    bmiHeader->biSizeImage = read_u32(pFile);
    bmiHeader->biXPelsPerMeter = read_s32(pFile);
    bmiHeader->biYPelsPerMeter = read_s32(pFile);
    bmiHeader->biClrUsed = read_u32(pFile);
    bmiHeader->biClrImportant = read_u32(pFile);
    return 0;
}

void reader(FILE* in, uc** canvas, int padding) {
    // каждый пискель представляется 3 байтами
    // запись идет в формате BGR
    uc tempBlue;
    uc tempGreen;
    uc tempRed;

    // ввиду особенности хранения файлов .bmp запись в высоту идет в обратном порядке
    for (int i = H - 1; i >= 0; i--) {
        for (int j = 0; j < W; j++) {
            tempBlue = getc(in);
            tempGreen = getc(in);
            tempRed = getc(in);
            if (tempBlue == tempGreen && tempGreen == tempRed && tempRed == 255) {
                canvas[i][j] = 0;
            }
            else {
                canvas[i][j] = 1;
            }
        }
        //         пропускаем последний байт в строке
        int skipBytes = padding;
        while (skipBytes) {
            getc(in);
            skipBytes--;
        }
    }
}

void headWriter(FILE* out, BITMAPFILEHEADER* header, BITMAPINFOHEADER* bmiHeader) {
    fwrite(&header->bfType, 2, 1, out);
    fwrite(&header->bfSize, 4, 1, out);
    fwrite(&header->bfReserved1, 2, 1, out);
    fwrite(&header->bfReserved2, 2, 1, out);
    fwrite(&header->bfOffBits, 4, 1, out);

    fwrite(&bmiHeader->biSize, 4, 1, out);
    fwrite(&bmiHeader->biWidth, 4, 1, out);
    fwrite(&bmiHeader->biHeight, 4, 1, out);
    fwrite(&bmiHeader->biPlanes, 2, 1, out);
    fwrite(&bmiHeader->biBitCount, 2, 1, out);
    fwrite(&bmiHeader->biCompression, 4, 1, out);
    fwrite(&bmiHeader->biSizeImage, 4, 1, out);
    fwrite(&bmiHeader->biXPelsPerMeter, 4, 1, out);
    fwrite(&bmiHeader->biYPelsPerMeter, 4, 1, out);
    fwrite(&bmiHeader->biClrUsed, 4, 1, out);
    fwrite(&bmiHeader->biClrImportant, 4, 1, out);
}


void writer(FILE* out, uc** img, int padding) {
    const int printColor[5][3] = {
            {0,   0,   0},
            {234, 141, 247},
            {255, 77,  0},
            {0,  255, 255},
            {206, 255, 29}
    };
    for (int i = H - 1; i >= 0; --i) {
        for (int j = 0; j < W; ++j) {
            if (H * W > 40 && (H - i) * j % (H * W / 40) == 0) {
                printf("\r%d%%", 60 + (int)((40 * (H - i) * j) / (H * W)));
            }
            int c = img[i][j];
            if (c == 0) {
                fputc(printColor[0][0], out);
                fputc(printColor[0][1], out);
                fputc(printColor[0][2], out);
            }
            else if (c == 1) {
                fputc(printColor[1][0], out);
                fputc(printColor[1][1], out);
                fputc(printColor[1][2], out);
            }
            else if (c == 2) {
                fputc(printColor[2][0], out);
                fputc(printColor[2][1], out);
                fputc(printColor[2][2], out);
            }
            else if (c == 3) {
                fputc(printColor[3][0], out);
                fputc(printColor[3][1], out);
                fputc(printColor[3][2], out);
            }
            else if (c == 4) {
                fputc(printColor[4][0], out);
                fputc(printColor[4][1], out);
                fputc(printColor[4][2], out);
            }
            else {
                fputc(255, out);
                fputc(255, out);
                fputc(255, out);
            }
        }
        int copyPad = padding;
        while (copyPad) {
            fputc(0, out);
            copyPad--;
        }
    }
}

#endif //KURSACH_READER_H
