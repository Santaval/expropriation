#include <stdlib.h>
#include <stdio.h>
#include <Solution.h>



int main(int argc, char**argv) {
    size_t terrainRow;
    size_t terrainCol;
    size_t buildRow;
    size_t buildCol;
    char* terrain;

    if(argc > 1) {
        FILE *txtDoc;
        txtDoc = fopen(argv[1], "r");

        if (txtDoc == NULL) {
            return ERR;
        }

        if(fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1) {
            terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));

            for (int counter = 0; counter < terrainRow * terrainCol; counter++) {
                fread(&terrain[counter], txtDoc, 1);
            }

            searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
            free(terrain);
        }
        
    } else {
        if(scanf("%llu %llu %llu %llu", &terrainRow, &terrainCol, &buildRow, &buildCol) == 4) {
            terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));
            // falta leer chars
            searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
            free(terrain);
        } else {
            return ERR;
        }

    }
}

void searchBestArea(char* terrain, int terrainRow, int terrainCol, int buildRow, int buildCol) {
    int* zoneCounter = searchZoneAreaByChar(terrain, terrainRow, terrainCol);

    affectedArea_t** affectedAreaArr = searchAffectedAreaByBuild(terrain, terrainRow, terrainCol, buildRow, buildCol, zoneCounter);
    affectedArea_t* bestArea = filterBestArea(affectedAreaArr);
    markBestArea(bestArea, terrain, terrainRow, terrainCol);
    printResults(bestArea, terrain, terrainRow, terrainCol);
}

int* searchZoneAreaByChar(char* terrain, int terrainRow, int terrainCol) {
    int* zoneCounter[26];

    for(int letter = 97; letter < 124; letter++) {
        size_t counter = 0;

        for (size_t index = 0; index < terrainRow * terrainCol; index++) {
            if (terrain[index] == letter) {
                counter++;
            }
        }
        zoneCounter[letter - 97] = counter;
    }

    return zoneCounter;
}

affectedArea_t** searchAffectedAreaByBuild( char* terrain, size_t terrainRow, size_t terrainCol, size_t buildRow, size_t buildCol, int* zoneCounter) {
    int pushedAreas = 0;
    affectedArea_t** affectedAreaArr[26]; //cambiar a memoria dinamica
    int* checkedChar[26];

    for(int rowCount = 0; rowCount < terrainRow; rowCount++)  {
         for(int colCount = 0; colCount < terrainCol; colCount++) {
            affectedArea_t* affected;
            for (int row = 0; row < row + buildRow; row++) {
                 for (int col = 0; col < col + buildCol; col++) {
                    if (col < terrainCol && row < terrainRow) {
                        if(terrain[terrainCol + row + col] != '-' && checkedChar[ 97 - terrain[terrainCol + row + col]] != 0) {
                            affected ->affectedBuilds++;
                            affected ->afffectedBuildsSize += zoneCounter[97 - terrain[terrainCol + row + col]];
                            affectedAreaArr[pushedAreas] = affected;
                            checkedChar[97 - terrain[terrainCol + row + col]] = 1;
                            pushedAreas ++;
                        }
                    }
                 }
            }
         }
    }
    
} 

affectedArea_t* filterBestArea(affectedArea_t** affectedAreaArr) {
    affectedArea_t* bestArea = affectedAreaArr[0];
    for(int counter = 0; counter < terrainRow * terrainCol; counter++) {
        if(affectedAreaArr[counter] != NULL) {
            if (affectedAreaArr[counter] -> afffectedBuildsSize < bestArea -> afffectedBuildsSize) {
                bestArea = affectedAreaArr[counter];
            }
        }
    }

    return bestArea;
}

void markBestArea(affectedArea_t* bestArea, char* terrain, size_t buildRow, size_t buildCol) {
        for(int row = bestArea -> row; row < row + buildRow; row++) {
             for(int col = bestArea -> col; col < col + buildCol; col++) {
                terrain[terrainCol + row + col] = '*';
             }
        }
}


void printResults(affectedArea_t* bestArea, char* terrain, size_t terrainRow, size_t terrainCol) {
    printf("%d\n", bestArea->affectedBuilds);

       for(int row = 0; row < terrainRow; row++)  {
         for(int col = 0; col < terrainCol; col++) {
           printf("%c", terrain[terrainCol*row + col]);
         }
         printf("\n");
    }

}