#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
// 1 - box
// 2 - monster
// 3 - key
// 4 - lock
// 5 - trap
// 6 - star
// 7 - wall
int main() {
    char *filename = "level2";
    int strPosition = 8;
    int colPosition = 3;
    int widthTileQuant = 12;
    int heightTileQuant = 12;
    int step = 33;
    int level[12][12][3] = {
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 6}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 0}, {1, 0}, {1, 0}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 1}, {1, 4}, {1, 1}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 1}, {1, 7}, {1, 1}, {1, 0}, {1, 0}, {1, 7}, {1, 0}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 3}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 0}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
        {{1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}, {1, 7}},
    };
//    int level[12][12] = {
//        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
//        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
//    };
    ofstream in(filename,ios::binary|ios::out);//подключение текстового файла для записи в бинарном режиме
    in.write((char*)&widthTileQuant, sizeof(int));
    in.write((char*)&heightTileQuant, sizeof(int));
    in.write((char*)&step, sizeof(int));
    in.write((char*)&strPosition, sizeof(int));
    in.write((char*)&colPosition, sizeof(int));
    for (int i = 0;i < widthTileQuant; i++) {
        for (int j = 0;j < heightTileQuant; j++) {
            for (int k = 0; k < level[i][j][0] + 1; k++) {
                in.write((char*)&level[i][j][k],sizeof(int));//запись в файл поэлементно
            }
        }
    }
    in.close();//закрываем файл
//    ifstream out(filename, ios::binary|ios::in);
//    out.read((char*)&widthTileQuant, sizeof(int));
//    out.read((char*)&heightTileQuant, sizeof(int));
//    out.read((char*)&step, sizeof(int));
//    level = new int*[widthTileQuant];
//    for (int i = 0; i < widthTileQuant;i++) {
//        level[i] = new int[heightTileQuant];
//        for (int j = 0;j < heightTileQuant; j++) {
//            out.read((char*)&level[i][j],sizeof(int));//чтение каждого элемента файла в массив поэлементно
//        }
//    }
//    out.close();
//    cout << widthTileQuant << endl;
//    cout << heightTileQuant << endl;
//    cout << step << endl;
//    for (int i = 0; i < widthTileQuant; i++) {
//        for (int j = 0; j < heightTileQuant; j++) {
//            cout << level[i][j] << " ";
//        }
//        cout << endl;
//    }
    return 0;
}
