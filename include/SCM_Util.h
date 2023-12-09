#ifndef SCM_UTIL_H
#define SCM_UTIL_H

unsigned char *filterData(unsigned char *pData, int columns, int rows, int cursorSize);
unsigned char *quantizeData(unsigned char *pData, int columns, int rows, int levels, int maxPixelValue);
unsigned char *computeSCM(unsigned char *Data1, unsigned char *Data2, int columns, int rows, int levels);
void fprintSCM(FILE *file, unsigned char *scmMatrix, int quantizationLevels);
void extractLabelSCM(FILE *outputFile, const char *filename);

#endif