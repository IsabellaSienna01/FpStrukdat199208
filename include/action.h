#ifndef ACTION_H
#define ACTION_H

typedef struct mahasiswa{
    char NRP[11];
    char Nama[26];
    int gender;
    float IPK;
    struct mahasiswa *next;
    struct mahasiswa *prev;
} mhs;

typedef struct mhs{
    char NRP[11];
    char Nama[26];
    int gender;
    float IPK;
}mhsrecord;

typedef struct data{
    int count;
    mhs * head;
}db;

extern mhs * head;
extern db data;

void AddData();
void ChangeData();
void PrintDataIdx();
void PrintData();
void DeleteData();
void savefile(const char * file);
void loadfile(const char * file);

#endif