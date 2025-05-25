#include <Windows.h>

typedef struct RelativePath {
    LPCSTR pathStr;
    size_t depth;
    LPCSTR* paths;
};

typedef struct AbsolutePath {
    LPCSTR drive;
    /* 这里将绝对路径视作对于磁盘驱动器的相对路径 */
    RelativePath* relativePathToDrive;
};


AbsolutePath& AnalyseFilePath(LPCSTR filePath, LPCSTR workdir) {
    // 判断 filePath 是否为绝对路径
    AbsolutePath* absPath = new AbsolutePath();
    bool isAbsolute = false;
    
}