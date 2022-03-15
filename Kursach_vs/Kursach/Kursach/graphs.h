//
// Created by Timur on 18.04.2021.
//

#ifndef KURSACH_GRAPHS_H
#define KURSACH_GRAPHS_H


// заполнение поля выбранным цветом
void defineTop(uc** img, int x, int y, vertex* v) {
    if (x > v->bottom) v->bottom = x;
    if (x < v->top) v->top = x;
    if (y > v->right) v->right = y;
    if (y < v->left) v->left = y;

    img[x][y] = v->color;
    if (x > 0 && img[x - 1][y] != v->color && img[x - 1][y] != 1) {
        defineTop(img, x - 1, y, v);
    }
    if (x < H - 1 && img[x + 1][y] != v->color && img[x + 1][y] != 1) {
        defineTop(img, x + 1, y, v);
    }
    if (y > 0 && img[x][y - 1] != v->color && img[x][y - 1] != 1L) {
        defineTop(img, x, y - 1, v);
    }
    if (y < W - 1 && img[x][y + 1] != v->color && img[x][y + 1] != 1) {
        defineTop(img, x, y + 1, v);
    }
}

// удаление ненастощих соседей
void isNeighbours(uc** M, int x, int y, vertex* v, int maxi) {
    int mid = 0; // is there neighbour between x and y

    // horizontal
    if (v[x - 2].right < v[y - 2].left) {
        for (int i = 0; i < maxi - 2; ++i) {
            if (v[x - 2].right < v[i].left && v[i].right < v[y - 2].left &&
                max(v[x - 2].top, v[y - 2].top) >= v[i].bottom &&
                v[i].top >= min(v[x - 2].bottom, v[y - 2].bottom)) {
                mid = 1;
            }
            // right x < left z && right x < left y
        }
    }
    if (v[y - 2].right < v[x - 2].left) {
        for (int i = 0; i < maxi - 2; ++i) {
            if (v[y - 2].right < v[i].left && v[i].right < v[x - 2].left &&
                max(v[x - 2].top, v[y - 2].top) >= v[i].bottom &&
                v[i].top >= min(v[x - 2].bottom, v[y - 2].bottom)) {
                mid = 1;
            }
            // right x < left z && right x < left y
        }
    }

    // vertical
    if (v[y - 2].top > v[x - 2].bottom) {
        for (int i = 0; i < maxi - 2; ++i) {
            if (v[y - 2].top > v[i].bottom && v[i].top > v[x - 2].bottom &&
                max(v[x - 2].right, v[y - 2].right) >= v[i].left &&
                v[i].right >= min(v[x - 2].left, v[y - 2].left)) {
                mid = 1;
            }
        }
    }
    if (v[x - 2].top > v[y - 2].bottom) {
        for (int i = 0; i < maxi - 2; ++i) {
            if (v[x - 2].top > v[i].bottom && v[i].top > v[y - 2].bottom &&
                max(v[x - 2].right, v[y - 2].right) >= v[i].left &&
                v[i].right >= min(v[x - 2].left, v[y - 2].left)) {
                mid = 1;
            }
        }
    }
    //    сам процесс удаления ненастоящих соседей
    if (mid != 0) {
        int t = 0;
        int toChange = 0;
        while (M[x][t] != '\0') {
            if (M[x][t] == y) {
                toChange = 1;
            }
            if (toChange) {
                M[x][t] = M[x][t + 1];
            }
            t++;
        }

        t = 0;
        toChange = 0;
        while (M[y][t] != '\0') {
            if (M[y][t] == x) {
                toChange = 1;
            }
            if (toChange) {
                M[y][t] = M[y][t + 1];
            }
            t++;
        }
    }
}

// пуст ли массив
int isEmpty(uc** M, int vQuan) {
    for (int i = 0; i < vQuan; ++i) {
        if (M[i][0] != 0) return 0;
    }
    return 1;
}

// основная функция, которая красит граф в разные цвета
int coloring(int vQuan, int* colors, uc** M, int v) {
    for (int i = 0; i < vQuan; ++i) {
        colors[i] = 0;
    }

    uc*** L;
    L = (uc***)calloc(sizeof(uc**), 2);
    if (L == NULL) return -1;
    L[0] = (uc**)calloc(sizeof(uc*), vQuan);
    L[1] = (uc**)calloc(sizeof(uc*), vQuan);
    if (L[0] == NULL || L[1] == NULL) return -1;
    for (int i = 0; i < vQuan; ++i) {
        L[0][i] = (uc*)calloc(sizeof(uc), vQuan);
        L[1][i] = (uc*)calloc(sizeof(uc), vQuan);
        if (L[0][i] == NULL || L[1][i] == NULL) return -1;
    }

    int* values;
    values = (int*)calloc(sizeof(int), vQuan);
    if (values == NULL) return -1;

    int id = 2;
    while (id + v < vQuan) {
        values[id] = id + v;
        id++;
    }
    int t = 2;
    while (id < vQuan) {
        values[id] = t;
        t++;
        id++;
    }

    for (int i = 2; i < vQuan; ++i) {
        for (int j = 0; j < vQuan && M[i][j] != 0; ++j) {
            if (M[i][j] != 0) {
                L[0][values[i]][j] = values[M[i][j]];
                L[1][i][j] = 0;
            }
        }
    }

    int curColor = 1;
    int cur = 0;
    while (!isEmpty(L[0], vQuan) || !isEmpty(L[1], vQuan)) {
        for (int i = 0; i < vQuan; ++i) {
            L[1 - cur][i][0] = 0;//???
        }
        for (int i = 2; i < vQuan; ++i) {
            if (L[cur][i][0] == 0)
                continue; // если нет соседей, значит их перенесли в другой массив, и раскрасим вершину в дальнейшем
            for (int j = 0; j < vQuan && L[cur][i][j] != 0; ++j) {
                int elem = L[cur][i][j];
                if (L[cur][elem][0] == 0) {
                    L[cur][i][j] = 0;
                    continue;
                }
                for (int k = 0; k < vQuan; ++k) {
                    L[1 - cur][elem][k] = L[cur][elem][k];
                }
                L[cur][i][j] = 0;
                L[cur][elem][0] = 0;
            }
            // если все-таки соседи были, то мы их точно перенесли в другой массив
            // и эта вершина раскрашивается в этот раз
            int id1 = i - v;
            if (id1 < 2) id1 += vQuan - 2;
            colors[id1] = curColor;
        }
        cur = !cur;
        curColor++;
        if (curColor > 4) return -1;
    }

    for (int i = 0; i < vQuan; ++i) {
        free(L[0][i]);
        free(L[1][i]);
    }
    free(L[0]);
    free(L[1]);
    free(L);
    free(values);
    return curColor;
}

#endif //KURSACH_GRAPHS_H
