enum EXIT_ERR {
    ERR, SUCCESS, INVALID_DATA, FILE_NOT_FOUND
};

typedef long long terrainSize_t;

typedef struct AffectedArea {
    terrainSize_t row;
    terrainSize_t col;
    terrainSize_t affectedBuilds;
    terrainSize_t affectedBuildsSize;
    terrainSize_t cellsAmount;
} affectedArea_t;

void searchBestArea(char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, terrainSize_t buildRow, terrainSize_t buildCol);
void searchZoneAreaByChar(char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, int* zoneCounter);
void searchAffectedAreaByBuild( char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, terrainSize_t buildRow, terrainSize_t buildCol, int* zoneCounter, affectedArea_t** affectedAreaArr);
terrainSize_t filterBestArea (affectedArea_t** affectedAreaArr, terrainSize_t buildRow, terrainSize_t buildCol, terrainSize_t terrainRow, terrainSize_t terrainCol);
void markBestArea(affectedArea_t* bestArea, char* terrain, terrainSize_t buildRow, terrainSize_t buildCol, terrainSize_t terrainCol);
void printResults(affectedArea_t* bestArea, char* terrain, size_t terrainRow, size_t terrainCol);