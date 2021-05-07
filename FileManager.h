#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED
#include "Level.h"
#include "LevelInfo.h"
class FileManager : public Level, public LevelInfo{
public:
    void readFile(char *filename);
};

#endif // FILEMANAGER_H_INCLUDED
