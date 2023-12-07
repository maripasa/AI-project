// PGM_Operations.h

#ifndef PGM_OPERATIONS_H
#define PGM_OPERATIONS_H

struct pgm {
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);

#endif // PGM_OPERATIONS_H