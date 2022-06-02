#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

typedef struct tagBITMAPHEADER {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    RGBQUAD hRGB[256];
}BITMAPHEADER;

class Image
{
public:
    BYTE* image;
    LONG width, height;
    Image(const char* filename)
    {
        BITMAPHEADER header;
        FILE* fp;
        if (fopen_s(&fp, filename, "rb") != 0)
            exit(EXIT_FAILURE);
        fread_s(&header.bf, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, fp);
        fread_s(&header.bi, sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER), 1, fp);
        fread_s(&header.hRGB, sizeof(RGBQUAD) * 256, sizeof(RGBQUAD), 256, fp);
        width = header.bi.biWidth;
        height = header.bi.biHeight;
        int imageSize = width * height;
        image = (BYTE*)malloc(sizeof(BYTE) * imageSize);
        if (image == 0)
            exit(EXIT_FAILURE);
        fread_s(image, sizeof(BYTE) * imageSize, sizeof(BYTE), imageSize, fp);
        fclose(fp);
        if (image == NULL)
            exit(EXIT_FAILURE);
    }
    ~Image()
    {
        free(image);
    }
};