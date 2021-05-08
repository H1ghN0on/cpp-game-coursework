#include <iostream>
#include <fstream>
#include "FileManager.h"

using namespace std;
bool FileManager :: readFile(string filename) {
    ifstream out(filename, ios::binary|ios::in);
    if (!out) {
        return false;
    }
    out.read((char*)&widthTileQuant, sizeof(int));
    out.read((char*)&heightTileQuant, sizeof(int));
    out.read((char*)&step, sizeof(int));
    out.read((char*)&strPosition, sizeof(int));
    out.read((char*)&colPosition, sizeof(int));
    level = new int*[widthTileQuant];
    for (int i = 0; i < widthTileQuant;i++) {
        level[i] = new int[heightTileQuant];
        for (int j = 0;j < heightTileQuant; j++) {
            out.read((char*)&level[i][j],sizeof(int));//чтение каждого элемента файла в массив поэлементно
        }
    }
    out.close();
    return true;
//    cout << widthTileQuant << endl;
//    cout << heightTileQuant << endl;
//    cout << step << endl;
//    for (int i = 0; i < widthTileQuant; i++) {
//        for (int j = 0; j < heightTileQuant; j++) {
//            cout << level[i][j] << " ";
//        }
//        cout << endl;
//    }
}
