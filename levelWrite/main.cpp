#include <iostream>
#include <fstream>
using namespace std;

int main() {
    char *filename = "level1";
    int widthTileQuant;
    int heightTileQuant;
    int step;
    int **level;
//    ofstream in(filename,ios::binary|ios::out);//подключение текстового файла для записи в бинарном режиме
//    in.write((char*)&widthTileQuant, sizeof(int));
//    in.write((char*)&heightTileQuant, sizeof(int));
//    in.write((char*)&step, sizeof(int));
//    for (int i = 0;i < widthTileQuant; i++) {
//        for (int j = 0;j < heightTileQuant; j++) {
//            in.write((char*)&level[i][j],sizeof(int));//запись в файл поэлементно
//        }
//    }
//    in.close();//закрываем файл
    ifstream out(filename, ios::binary|ios::in);
    out.read((char*)&widthTileQuant, sizeof(int));
    out.read((char*)&heightTileQuant, sizeof(int));
    out.read((char*)&step, sizeof(int));
    level = new int*[widthTileQuant];
    for (int i = 0; i < widthTileQuant;i++) {
        level[i] = new int[heightTileQuant];
        for (int j = 0;j < heightTileQuant; j++) {
            out.read((char*)&level[i][j],sizeof(int));//чтение каждого элемента файла в массив поэлементно
        }
    }
    out.close();
    cout << widthTileQuant << endl;
    cout << heightTileQuant << endl;
    cout << step << endl;
    for (int i = 0; i < widthTileQuant; i++) {
        for (int j = 0; j < heightTileQuant; j++) {
            cout << level[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
