// #include <stdlib.h>
#include <stdlib.h>
// #include <stdio.h>
#include <stdio.h>
// #include <Solution.h>
#include <Solution.h>


void printMatrix(char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol) {
       for(terrainSize_t row = 0; row < terrainRow; row++)  {
         for(terrainSize_t col = 0; col < terrainCol; col++) {
           printf("%c", terrain[terrainCol*row + col]);
         }
         printf("\n");
    }

}


// int main(int argc, char**argv) {
int main(int argc, char** argv) { 
//  size_t terrainRow;
    terrainSize_t terrainRow;
//  size_t terrainCol;
    terrainSize_t terrainCol;
//  size_t buildRow;
    terrainSize_t buildRow;
//  size_t buildCol;
    terrainSize_t buildCol;
//  char* terrain;
    char* terrain;

//  if(argc > 1) {
    if(argc > 1) {
//      FILE* txtDoc
        FILE* txtDoc;
//      txtDoc = fopen(argv[1], "r");
        txtDoc = fopen(argv[1], "r");
//      if (txtDoc == NULL) {
        if(txtDoc == NULL) {
//          return ERR;
            puts("File not found");
            return ERR;
//      }
        }
//      if(fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1 && fread(&terrainRow,txtDoc, 1) == 1) {
        if(fscanf(txtDoc,"%llu %llu %llu %llu", &terrainRow, &terrainCol, &buildRow, &buildCol )) {
//          terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));
            terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));
        
//      for (int counter = 0; counter < terrainRow * terrainCol; counter++) {
        for (terrainSize_t counter = 0; counter < terrainRow * terrainCol; counter++) {
//          fread(&terrain[counter], txtDoc, 1);
            fscanf(txtDoc, " %c", &terrain[counter]);
//      }
        }
//          searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
            searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
            printMatrix(terrain, terrainRow, terrainCol);
//          free(terrain);
            free(terrain);
            fclose(txtDoc);
//      }
        }
        
//     } else {
    }   else {
//          if(scanf("%llu %llu %llu %llu", &terrainRow, &terrainCol, &buildRow, &buildCol) == 4) {
            if(scanf("%llu %llu %llu %llu", &terrainRow, &terrainCol, &buildRow, &buildCol) == 4) {
//              terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));
                terrain = (char*) malloc(sizeof(char) * (terrainRow*terrainCol) + sizeof(char));
//              // falta leer chars
                for (terrainSize_t counter = 0; counter < terrainRow * terrainCol; counter++) {
//              fread(&terrain[counter], txtDoc, 1);
                    scanf(" %c", &terrain[counter]);
//          }
                }
//              searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
                searchBestArea(terrain, terrainRow, terrainCol, buildRow, buildCol);
                printMatrix(terrain, terrainRow, terrainCol);
//              free(terrain);
                free(terrain);
//          } else {
            } else {
//              return ERR;
                return ERR;
//         }    
            }

//     }
    }
// }
}

//  void searchBestArea(char* terrain, int terrainRow, int terrainCol, int buildRow, int buildCol) {
    void searchBestArea(char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, terrainSize_t buildRow, terrainSize_t buildCol) {
//      int* zoneCounter = searchZoneAreaByChar(terrain, terrainRow, terrainCol);
        int* zoneCounter = (int*) malloc(sizeof(int) * 27);
        searchZoneAreaByChar(terrain, terrainRow, terrainCol, zoneCounter);  
//      affectedArea_t** affectedAreaArr = searchAffectedAreaByBuild(terrain, terrainRow, terrainCol, buildRow, buildCol, zoneCounter);
        affectedArea_t** affectedAreaArr = (affectedArea_t**) malloc(sizeof(affectedArea_t) * (terrainRow * terrainCol));
        for(int counter = 0; counter < terrainRow * terrainCol; counter++) {
            affectedAreaArr[counter] = NULL;
        } 
        searchAffectedAreaByBuild(terrain, terrainRow, terrainCol, buildRow, buildCol, zoneCounter, affectedAreaArr);
        puts("finished");
//      affectedArea_t* bestArea = filterBestArea(affectedAreaArr);
        terrainSize_t bestAreaIndex = filterBestArea(affectedAreaArr, buildRow, buildCol, terrainRow, terrainCol);
        affectedArea_t* bestArea = affectedAreaArr[bestAreaIndex];
//     markBestArea(bestArea, terrain, terrainRow, terrainCol);
        markBestArea(bestArea, terrain, buildRow, buildCol, terrainCol);
//     printResults(bestArea, terrain, terrainRow, terrainCol);
        free(affectedAreaArr);
        free(zoneCounter);
//  }
    }

// int* searchZoneAreaByChar(char* terrain, int terrainRow, int terrainCol) {
    void searchZoneAreaByChar(char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, int* zoneCounter) {
        if (zoneCounter == NULL) puts("null");
//      int* zoneCounter[26];
//      for(int letter = 97; letter < 124; letter++) {
        for (int letter = 97; letter < 124; letter++) {
//          size_t counter = 0;
            terrainSize_t counter = 0; 
//         for (size_t index = 0; index < terrainRow * terrainCol; index++) {
            for (terrainSize_t index = 0; index < terrainRow * terrainCol; index++) {
//              if (terrain[index] == letter) {
                if (terrain[index] == letter) {
//                  counter++;
                    counter++;
//              }   
                }
//          }
            }
//          zoneCounter[letter - 97] = counter;
            zoneCounter[letter - 97] = counter;
//      }
        }
//      return zoneCounter;
// }
}

// affectedArea_t** searchAffectedAreaByBuild( char* terrain, size_t terrainRow, size_t terrainCol, size_t buildRow, size_t buildCol, int* zoneCounter) {
    void searchAffectedAreaByBuild( char* terrain, terrainSize_t terrainRow, terrainSize_t terrainCol, terrainSize_t buildRow, terrainSize_t buildCol, int* zoneCounter, affectedArea_t** affectedAreaArr) {
//      int pushedAreas = 0;
        terrainSize_t pushedAreas = 0;
//      affectedArea_t** affectedAreaArr[26];
//      int* checkedChar[26];
//      for(int rowCount = 0; rowCount < terrainRow; rowCount++)  {
        for (terrainSize_t rowCount = 0; rowCount < terrainRow; rowCount++) {
//          for(int colCount = 0; colCount < terrainCol; colCount++) {
            for (terrainSize_t colCount = 0; colCount < terrainCol; colCount++) {            
//              affectedArea_t* affected;

                affectedAreaArr[pushedAreas] = (affectedArea_t*) malloc(sizeof(affectedArea_t));
                affectedAreaArr[pushedAreas] -> affectedBuilds = 0;
                affectedAreaArr[pushedAreas] -> affectedBuildsSize = 0;
                 affectedAreaArr[pushedAreas] -> cellsAmount = 0;  
                affectedAreaArr[pushedAreas] -> row = rowCount;
                affectedAreaArr[pushedAreas] -> col = colCount;
                int checkedChar[27] = {0};
//              for (int row = 0; row < row + buildRow; row++) {
                for (terrainSize_t row = rowCount; row < rowCount + buildRow; row++) {
//                  for (int col = 0; col < col + buildCol; col++) {
                    for (terrainSize_t col = colCount; col < colCount + buildCol; col++) {
//                      if (col < terrainCol && row < terrainRow) {
                        if( (col < terrainCol  && row < terrainRow )) {
//                          if(terrain[terrainCol + row + col] != '-' && checkedChar[ 97 - terrain[terrainCol + row + col]] != 0) {
                            if (terrain[terrainCol * row + col] != '-' && (!checkedChar[terrain[terrainCol * row + col] - 97] == 1)){
//                              affected ->affectedBuilds++;
                                affectedAreaArr[pushedAreas] -> affectedBuilds += 1;
//                              affected ->afffectedBuildsSize += zoneCounter[97 - terrain[terrainCol + row + col]];
                                affectedAreaArr[pushedAreas] -> affectedBuildsSize += zoneCounter[terrain[terrainCol * row + col] - 97];
//                              affectedAreaArr[pushedAreas] = affected;
//                              checkedChar[97 - terrain[terrainCol + row + col]] = 1;
                                checkedChar[terrain[terrainCol * row + col] - 97] = 1;
//                              pushedAreas ++;
                              
//                         }
                            }
//                     }     
                         affectedAreaArr[pushedAreas] -> cellsAmount++;
                        }
//                  }
                    }
//             }
                }
                pushedAreas ++;

//          }
            }
//      }
        }
// } 
    }

//  affectedArea_t* filterBestArea(affectedArea_t** affectedAreaArr) {
terrainSize_t filterBestArea (affectedArea_t** affectedAreaArr,  terrainSize_t buildRow, terrainSize_t buildCol, terrainSize_t terrainRow, terrainSize_t terrainCol) {
//  affectedArea_t* bestArea = affectedAreaArr[0];
    terrainSize_t bestArea = 0;
//     for(int counter = 0; counter < terrainRow * terrainCol; counter++) {
    for (terrainSize_t counter = 0; counter < terrainRow * terrainCol; counter++) {
//         if(affectedAreaArr[counter] != NULL) {
        if (affectedAreaArr[counter] != NULL && affectedAreaArr[counter] -> cellsAmount == buildRow * buildCol) {
//             if (affectedAreaArr[counter] -> afffectedBuildsSize < bestArea -> affectedBuildsSize) {
            if (affectedAreaArr[counter] -> affectedBuildsSize < affectedAreaArr[bestArea] -> affectedBuildsSize) {
                    bestArea = counter;
//             }
//         }
            }
        }
//     }
    }
//     return bestArea;
    return bestArea;
// }
}

// void markBestArea(affectedArea_t* bestArea, char* terrain, size_t buildRow, size_t buildCol) {
void markBestArea(affectedArea_t* bestArea, char* terrain, terrainSize_t buildRow, terrainSize_t buildCol, terrainSize_t terrainCol) {
//         for(int row = bestArea -> row; row < row + buildRow; row++) {
    for (terrainSize_t row = bestArea -> row; row < bestArea ->row + buildRow; row++) {
//              for(int col = bestArea -> col; col < col + buildCol; col++) {
        for (terrainSize_t col = bestArea -> col; col < bestArea -> col + buildCol; col++) {
//                 terrain[terrainCol + row + col] = '*';
        puts("listo");
                    terrain[terrainCol * row + col] = '*';
//              }
//         }
        }
    }
// }
}

// void printResults(affectedArea_t* bestArea, char* terrain, size_t terrainRow, size_t terrainCol) {
void printResults(affectedArea_t* bestArea, char* terrain, size_t terrainRow, size_t terrainCol) {
    //     printf("%d\n", bestArea->affectedBuilds);
    printf("%d\n", bestArea->affectedBuilds);
        // or(int row = 0; row < terrainRow; row++)  {
       for(int row = 0; row < terrainRow; row++)  {
        // for(int col = 0; col < terrainCol; col++) {
         for(int col = 0; col < terrainCol; col++) {
            // printf("%c", terrain[terrainCol*row + col]);
           printf("%c", terrain[terrainCol*row + col]);
        //}
         }
         // printf("\n");
         printf("\n");
    //}
    }
// }
}



