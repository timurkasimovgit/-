#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


typedef struct {
    unsigned int bfType; // type of file "0x4D42"
    unsigned int bfSize; // size of file. There are troubles with documentation. si we can ignore it
    unsigned int bfReserved1; // reserved. should be 0
    unsigned int bfReserved2; // reserved. should be 0
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize; // размер структур (версия)
    int biWidth; // ширина
    int biHeight; // высота от знака зависит порядок стрк
    unsigned short biPlanes; // 1
    unsigned short biBitCount; // бит на пиксель 1, 4, 8, 16, 24, 32
    unsigned int biCompression; // способ хранения
    unsigned int biSizeImage; // размер инфы для хранения пиксельных данных
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed; // size of RGBQUAD
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
    int color;
    int top;
    int bottom;
    int left;
    int right;

} vertex;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

unsigned short read_u16(FILE* fp) {
    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);
    return ((b1 << 8) | b0);
}

unsigned int read_u32(FILE* fp) {
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int read_s32(FILE* fp) {
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

#endif // MAIN_H_INCLUDEDs