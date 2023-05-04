enum EXIT_ERR {
    ERR, SUCCESS, INVALID_DATA, FILE_NOT_FOUND
};

typedef long long size_t;

typedef struct AffectedArea {
    size_t row;
    size_t col;
    int affectedBuilds;
    int afffectedBuildsSize;
} affectedArea_t;

void searchBestArea(char* terrain, int terrainRow, int terrainCol, int buildRow, int buildCol);
int* searchZoneAreaByChar(char* terrain, int terrainRow, int terrainCol);
affectedArea_t** searchAffectedAreaByBuild( char* terrain, size_t terrainRow, size_t terrainCol, size_t buildRow, size_t buildCol, int* zoneCounter);
affectedArea_t* filterBestArea(affectedArea_t** affectedAreaArr);
void printResults(affectedArea_t* bestArea, char* terrain, size_t terrainRow, size_t terrainCol);