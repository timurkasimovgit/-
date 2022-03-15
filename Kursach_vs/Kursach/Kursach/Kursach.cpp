#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// максимально допустимое количество вершин
#define size 500

#define Height bmiHeader.biHeight
#define Width bmiHeader.biWidth

#define uc unsigned char
//#define MAX_PATH 260
int H, W;
FILE* logs, *time_file;

void error(int errorNum) {
    const char E[10][100] = { {"Memory allocation error\n"},
                             {"It`s not a .bmp file\n"},
                             {"File open error\n"} };

    fprintf(logs, "Error: %s", E[errorNum]);
}

#include "main.h"
#include "graphs.h"
#include "reader.h"

void printAns(int colors, time_t time, time_t partTime);
void help();
//void findNeighbours(uc** canvas, uc** M, int param);
void findNeighboursHoriz(uc** canvas, uc** M);
void findNeighboursVertic(uc** canvas, uc** M);
void greeting(char* in, char* out);

int main(int argc, char* argv[]) {
    if (argc == 3) {
        greeting(argv[1], argv[2]);
    }
    else if (argc == 2 && !strcmp(argv[1], "-help")) {
        help();
    }
    else if (argc == 1) {
        printf("No arguments!\n");
        //greeting((char *)"32.bmp", (char *)"30_.bmp");
        help();
    }
    else {
        printf("Too many arguments!\n");
        help();
    }
    return 0;
}

void printAns(int colors, time_t time, time_t partTime) {
    fprintf(time_file,"\n_________________________SUCCESS_________________________\n"
        "Number of colors: %d\n"
        "Total running time: %lf\n"
        "Running time of the coloring algorithm: %lf\n"
        "_________________________________________________________\n",
        colors, (double)time / CLOCKS_PER_SEC, (double)partTime / CLOCKS_PER_SEC);
}

void help() {
    printf("|--------------Welcome to the card coloring program!---------------|\n"
        "|   Areas are colored according to two conditions:                 |\n"
        "|      1) Neighboring areas are not filled with the same color     |\n"
        "|      2) Minimum number of colors used                            |\n"
        "|   There are two arguments for program:                           |\n"
        "|      1) INPUT file name                                          |\n"
        "|      2) OUTPUT file name                                         |\n"
        "|            If you have any questions, please send an email       |\n"
        "|              to Timur Kasimov, at kasimov.ta@edu.spbstu.ru       |\n"
        "|              or Kalugina Anastasia at kalugina.ap@edu.spbstu.ru  |\n"
        "|------------------------------------------------------------------|\n");
}

//разбить на 2 функции
//canvas - раскрашенная картинка, M - матрица смежности, param - по вертикали или горизонтали поиск
void findNeighboursHoriz(uc** canvas, uc** M)
{
    int size1, size2;
    size1 = H;
    size2 = W;
    int cur;
    //запускаем цикл для прохода в ширину/глубину
    for (int i = 0; i < size1; ++i) 
    {
        cur = canvas[i][0];
        int t = 0;
        //если в ширину, то идем вниз и ищем границу
        while (t < size2 && cur == 1) 
        {
            cur = canvas[i][t];
            t++;
        }
        //в cur лежит черный цвет
        //когда нашли границу, то идем дальше и ищем, когда граница закончится
        for (int j = t; j < size2; ++j) {
            uc elem;
            elem = canvas[i][j];

            if (elem != cur && elem != 1) {
                //                && canvas[i][j - 1] != 1
                int k = 0;
                int isConnect = 0;
                //заполняем весь столбец связью
                while (M[cur][k] != 0) {
                    if (M[cur][k] == elem) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[cur][k] = elem;
                }

                k = 0;
                isConnect = 0;

                while (M[elem][k] != 0) {
                    if (M[elem][k] == cur) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[elem][k] = cur;
                }
                cur = elem;
            }
        }
    }
}
void findNeighboursVertic(uc** canvas, uc** M)
{
    int size1, size2;
    size1 = W;
    size2 = H;
    int cur;
    //запускаем цикл для прохода в ширину/глубину
    for (int i = 0; i < size1; ++i) 
    {
        cur = canvas[0][i];

        int t = 0;
        //если в ширину, то идем вниз и ищем границу
        while (t < size2 && cur == 1) 
        {
            cur = canvas[t][i];
            t++;
        }
        //в cur лежит черный цвет
        //когда нашли границу, то идем дальше и ищем, когда граница закончится
        for (int j = t; j < size2; ++j) {
            uc elem;
            elem = canvas[j][i];

            if (elem != cur && elem != 1) {
                //                && canvas[i][j - 1] != 1
                int k = 0;
                int isConnect = 0;
                //заполняем весь столбец связью
                while (M[cur][k] != 0) {
                    if (M[cur][k] == elem) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[cur][k] = elem;
                }

                k = 0;
                isConnect = 0;

                while (M[elem][k] != 0) {
                    if (M[elem][k] == cur) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[elem][k] = cur;
                }
                cur = elem;
            }
        }
    }
}
/*
void findNeighbours(uc** canvas, uc** M, int param) {
    // param = 1 - horizontal
    // param = 2 - vertical

    //смотрим как проходим
    int size1, size2;
    if (param == 1) {
        size1 = H;
        size2 = W;
    }
    if (param == 2) {
        size1 = W;
        size2 = H;
    }
    int cur;
    //запускаем цикл для прохода в ширину/глубину
    for (int i = 0; i < size1; ++i) {
        if (param == 1) {
            cur = canvas[i][0];
        }
        if (param == 2) {
            cur = canvas[0][i];
        }
        int t = 0;
        //если в ширину, то идем вниз и ищем границу
        while (t < size2 && cur == 1) {
            if (param == 1) {
                cur = canvas[i][t];
            }
            if (param == 2) {
                cur = canvas[t][i];
            }
            t++;
        }
        //в cur лежит черный цвет
        //когда нашли границу, то идем дальше и ищем, когда граница закончится
        for (int j = t; j < size2; ++j) {
            uc elem;
            if (param == 1) {
                elem = canvas[i][j];
            }
            if (param == 2) {
                elem = canvas[j][i];
            }

            if (elem != cur && elem != 1) {
                //                && canvas[i][j - 1] != 1
                int k = 0;
                int isConnect = 0;
                //заполняем весь столбец связью
                while (M[cur][k] != 0) {
                    if (M[cur][k] == elem) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[cur][k] = elem;
                }

                k = 0;
                isConnect = 0;

                while (M[elem][k] != 0) {
                    if (M[elem][k] == cur) {
                        isConnect = 1;
                    }
                    k++;
                }
                if (isConnect == 0) {
                    M[elem][k] = cur;
                }
                cur = elem;
            }
        }
    }
}*/

void greeting(char* in, char* out) {
    time_t runTime = clock();
    logs = fopen("logs.log", "a");
    if (logs == NULL) {
        printf("Open log file error\n");
        return;
    }
    time_file = fopen("time.txt", "a");
    if (time_file == NULL) {
        printf("Open log file error\n");
        return;
    }
    time_t ttime;
    ttime = time(NULL);
    fprintf(logs, "\n\nTime: %s", ctime(&ttime));

    FILE* inFile = fopen(in, "rb");
    if (inFile == NULL) return error(2);

    BITMAPFILEHEADER header; // заголовок файла
    BITMAPINFOHEADER bmiHeader; // заголовок изображения
    if (headReader(inFile, &header, &bmiHeader) == 1) return;

    fprintf(logs, "Width - %d\nHeight - %d\n", Width, Height);//считывания шапки

    H = Height;
    W = Width;

    //     картинка представляется в данном массиве
    uc** canvas;
    canvas = (uc**)calloc(sizeof(uc*), Height);
    if (canvas == NULL) return error(0);

    if (H % 2 == 1)
    {
        canvas[0] = (uc*)calloc(sizeof(uc), Width);
        if (canvas[0] == NULL) return error(0);
        for (int i = 1; i < Height; i+=2) {
            canvas[i] = (uc*)calloc(sizeof(uc), Width);
            if (canvas[i] == NULL) return error(0);
            canvas[i+1] = (uc*)calloc(sizeof(uc), Width);
            if (canvas[i+1] == NULL) return error(0);
        }
    }
    else
    {
        for (int i = 0; i < Height; i+=2) {
            canvas[i] = (uc*)calloc(sizeof(uc), Width);
            if (canvas[i] == NULL) return error(0);
            canvas[i + 1] = (uc*)calloc(sizeof(uc), Width);
            if (canvas[i + 1] == NULL) return error(0);
        }
    }

    //     отступ
    int padding = ((4 - (Width * (bmiHeader.biBitCount / 8)) % 4)) % 4;
    fprintf(logs, "padding = %d\n", padding);
    reader(inFile, canvas, padding);//заполнение матрицы 0 и 1 - 0 черный пиксель, 1 - белый

    printf("\r2%%");

    vertex* V = (vertex*)calloc(sizeof(vertex), size);
    if (V == NULL) return error(0);

    //заполнение массива вершин графа
    for (int i = 0; i < size; ++i) {
        V[i].color = 0;
        V[i].top = 0;
        V[i].bottom = 0;
        V[i].left = 0;
        V[i].right = 0;
    }

    // раскрашивание всех областей в разные цвета (цвета не повторяются)

    int id = 0;
    int color = 2;
    int del = H * W / 40;
    int del_2 = H * W;
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (canvas[i][j] == 0) {//для белых пикселей
                if ((i * j) % del == 0) {
                    printf("\r%d%%", 2 + (int)((40 * i * j) / del_2));
                }
                V[id].left = j;
                V[id].top = i;
                V[id].color = color;
                defineTop(canvas, i, j, &V[id]);
                id++;
                color++;
            }
        }
    }

    // список смежности, изначально везде 0 - смежности пока что не известны
    uc** M;
    M = (uc**)calloc(sizeof(uc*), size + 2);
    if (M == NULL) return error(0);
    int new_size = size + 2;
    for (int i = 0; i < new_size; ++i) {
        M[i] = (uc*)calloc(sizeof(uc), new_size);
        if (M[i] == NULL) return error(0);
        for (int j = 0; j < new_size; ++j) {
            M[i][j] = 0;
        }
    }

    // поиск соседних вершин. вначале по горизонтали, затем по вертикали
    //findNeighbours(canvas, M, 1);
    findNeighboursHoriz(canvas, M);
    printf("\r45%%");
    //findNeighbours(canvas, M, 2);
    findNeighboursVertic(canvas, M);
    printf("\r48%%");

    int vertexQuan = 2;
    while (M[vertexQuan][0] != 0) vertexQuan++;

    // удаление лишних соседей
    for (int i = 2; i < vertexQuan; ++i) {
        int it = 0;
        while (M[i][it] != '\0') {
            isNeighbours(M, i, M[i][it], V, vertexQuan);
            it++;
        }
    }
    printf("\r50%%");

    int* colors = (int*)calloc(sizeof(int), vertexQuan + 1);
    if (colors == NULL) return error(0);

    // матрица смежности. где цифры для удобства представляются буквами
    fprintf(logs, "There are %d neighbours:\n", vertexQuan - 2);
    for (int i = 2; i < vertexQuan; ++i) {
        if (i < 10) {
            fprintf(logs, "%d  | ", i);
        }
        else {
            fprintf(logs, "%d | ", i);
        }
        for (int j = 0; j < vertexQuan; ++j) {
            fprintf(logs, "%d ", M[i][j]);
        }
        fprintf(logs, "\n");
    }

    // поиск самой оптимальной раскраски
    time_t partTime = clock();
    int mini = size + 1;
    int miniId = 0;
    for (int i = 0; i < vertexQuan - 1; ++i) {
        if (vertexQuan > 8 && i % (vertexQuan / 8) == 0) {
            printf("\r%d%%", 50 + (int)((8 * i) / (vertexQuan)));
        }
        //добавить проверку на возвращаемое значение
        int a = coloring(vertexQuan, colors, M, i);
        if (a == -1) continue;//пропуск заведомо неверных вариантов
        if (a < mini) {
            mini = a;
            miniId = i;
        }
    }
    partTime = clock() - partTime;

    // выбор оптимальной раскраски
    coloring(vertexQuan, colors, M, miniId);

    fprintf(logs, "\nSelected color for each vertex:\nV: ");
    for (int i = 0; i < vertexQuan; ++i) {
        fprintf(logs, "%d ", i);
    }
    fprintf(logs, "\nC: ");
    for (int i = 0; i < vertexQuan; ++i) {
        fprintf(logs, "%d ", colors[i]);
        if (i > 9) fprintf(logs, " ");
    }

    // раскрашивание карты по полученным цветам

    if (vertexQuan == 2) {
        colors[2] = 2;
        mini++;
    }
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            canvas[i][j] = colors[canvas[i][j]];
        }
    }
    printf("\r60%%");

    FILE* coloredFile = fopen(out, "wb");
    if (coloredFile == NULL) return error(2);

    headWriter(coloredFile, &header, &bmiHeader);
    writer(coloredFile, canvas, padding);

    fclose(inFile);
    fclose(coloredFile);
    for (int i = 0; i < Height; ++i) {
        free(canvas[i]);
    }
    free(canvas);
    free(V);
    for (int i = 0; i < size + 2; ++i) {
        free(M[i]);
    }
    free(M);
    free(colors);
    runTime = clock() - runTime;
    printf("\rFinished!\n");
    printAns(mini - 1, runTime, partTime);
}


