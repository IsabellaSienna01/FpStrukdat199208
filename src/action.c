#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "action.h"
#include <conio.h>

db data = {0, NULL};
mhs * head = NULL;

int nrpvalid(const char * nrp){
    if (strlen(nrp) != 10){
        return 0;
    }
    for (int i = 0; i<10; i++){
        if (nrp[i] < '0' || nrp[i] > '9'){
            return 0;
        }
    }
    return 1;
}
int gendervalid(int gender){
    return gender == 0 || gender == 1;
}
int ipkvalid(float ipk){
    return ipk >= 0.00 && ipk <= 4.00;
}
int nrpexist(const char *nrp){
    mhs * curr = head;
    while (curr != NULL){
        if(strcmp(curr->NRP, nrp) == 0){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
int comparenrp(const void * a, const void * b){
    mhs *ma = *(mhs**)a;
    mhs *mb = *(mhs**)b;
    return strcmp(ma->NRP, mb->NRP);
}
void savefile(const char * file){
    FILE *fp = fopen(file, "wb");
    if (!fp){
        return;
    }
    mhs * curr = head;
    while (curr != NULL){
        mhsrecord temp;
        strcpy(temp.NRP, curr->NRP);
        strcpy(temp.Nama, curr->Nama);
        temp.gender = curr->gender;
        temp.IPK = curr->IPK;

        fwrite(&temp, sizeof(mhsrecord), 1, fp);
        curr = curr->next;
    }
    fclose(fp);
}
void loadfile(const char * file){
    FILE * fp = fopen(file, "rb");
    if (!fp){
        return;
    }
    head = NULL;
    data.count = 0;
    mhsrecord temp;
    while (fread(&temp, sizeof(mhsrecord), 1, fp) == 1){
        mhs * baru = (mhs*)malloc(sizeof(mhs));
        strcpy(baru->NRP, temp.NRP);
        strcpy(baru->Nama,temp.Nama);
        baru->gender = temp.gender;
        baru->IPK = temp.IPK;
        baru->next = NULL;
        baru->prev = NULL;

        if (head == NULL){
            head = baru;
        }
        else{
            mhs * curr = head;
            while (curr->next != NULL){
                curr = curr->next;
            }
            curr->next = baru;
            baru->prev = curr;
        }
        data.count++;
    }
    fclose(fp);
}
void AddData(){
    mhs * baru = (mhs *) malloc(sizeof(mhs));
    if (!baru){
        printf("Gagal alokasi memori\n");
        printf("Tekan tombol apa saja untuk kembali ke menu...\n");
        _getch();
        return;
    }
    printf("-----------------------------------------------------------\n");
    printf("Masukkan Data: \n");
    
    do{
    printf("NRP (10 Digit): ");
    scanf("%10s", baru->NRP);
    if (!nrpvalid(baru->NRP)){
        printf("NRP tidak valid! Harus terdiri dari 10 digit angka\n");
    }
    else if(nrpexist(baru->NRP)){
        printf("NRP tidak valid! NRP ini sudah ada di database!\n");
    }
    } while (!nrpvalid(baru->NRP) || nrpexist(baru->NRP));
    getchar();

    printf("Nama: ");
    fgets(baru->Nama, 26, stdin);
    baru->Nama[strcspn(baru->Nama, "\n")] = 0;

    do {
    printf("Gender (P = 0, L = 1): ");
    scanf("%d", &baru->gender);
    if (!gendervalid(baru->gender)){
        printf("Gender tidak valid!\n");
    }
    } while (!gendervalid(baru->gender));

    do{
    printf("IPK: ");
    scanf("%f", &baru->IPK);
    if (!ipkvalid(baru->IPK)){
        printf("IPK tidak valid!\n");
    }
    } while (!ipkvalid(baru->IPK));

    baru->next = baru->prev = NULL;

    if (!head){
        head = baru;
    }
    else{
        mhs * curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = baru;
        baru->prev = curr;
    }
    data.count++;
    savefile("dbmhs.dat");
    printf("Data berhasil ditambahkan\n");
    printf("Tekan tombol apa saja untuk kembali ke menu...\n");
   _getch();
}
void ChangeData(){
    mhs * curr = head;
    printf("-----------------------------------------------------------\n");
    
    char nrp[11];
    
    do{
        printf("Masukkan NRP: ");
        scanf("%10s", nrp);
        if (!nrpvalid(nrp)){
            printf("NRP tidak valid! Harus terdiri dari 10 digit angka\n");
        }
    } while (!nrpvalid(nrp));

    while (curr != NULL){
        int input;
        int flag = 0;
        if (strcmp(curr->NRP, nrp) == 0){
            printf("\nData yang ingin diubah (1-3): \n");
            printf("-------------------------------------\n");
            printf("1. Nama\n");
            printf("2. Gender\n");
            printf("3. IPK\n");
            printf("4. Keluar\n");
            printf("-------------------------------------\n");

            scanf("%d", &input);
            getchar();
            if (input == 1){ //ubah nama
            printf("Ubah nama: ");
            fgets(curr->Nama,26, stdin);
            curr->Nama[strcspn(curr->Nama, "\n")] = 0;
            printf("Data nama berhasil diubah!\n");
            flag = 1;
            }
            else if (input == 2){ //ubah gender
                do{
                printf("Ubah gender (P = 0, L = 1): ");
                scanf("%d", &curr->gender);
                getchar();

                if (!gendervalid(curr->gender)){
                    printf("Gender tidak valid!\n");
                }
                else{
                    printf("Data gender berhasil diubah!\n");
                    flag = 1;
                }
                } while (!gendervalid(curr->gender));
            }
            else if (input == 3){ //ubah ipk
                do{
                printf("Ubah IPK: ");
                scanf("%f", &curr->IPK);
                getchar();

                if (!ipkvalid(curr->IPK)){
                    printf("IPK tidak valid!\n");
                }
                else{
                    printf("Data IPK berhasil diubah!\n");
                    flag = 1;
                }
                }while (!ipkvalid(curr->IPK));
            }
            else if (input == 4){
                printf("Tidak ada perubahan yang dilakukan\n");
                printf("Tekan tombol apa saja untuk kembali ke menu...\n");
                _getch();
                return;
            }
            else{
                printf("Data yang ingin diubah tidak valid!\n");
                printf("Tekan tombol apa saja untuk kembali ke menu...\n");
                _getch();
                return;
            }

            if (flag){
            savefile("dbmhs.dat");
            printf("Tekan tombol apa saja untuk kembali ke menu...\n");
            _getch();
            }
            return;
        }
        curr = curr->next;
    }
    printf("NRP tidak ditemukan!\n");
    printf("Tekan tombol apa saja untuk kembali ke menu...\n");
   _getch();
}
void PrintDataIdx(){ 
    printf("-----------------------------------------------------------\n");
    if (head == NULL || data.count == 0){
        printf("Tidak ada data\n");
        printf("Tekan tombol apa saja untuk kembali ke menu...\n");
        _getch();
        return;
    }
    mhs ** list = (mhs **) malloc(data.count * sizeof(mhs *));

    if (!list){
        printf("Gagal alokasi memori\n");
        printf("Tekan tombol apa saja untuk kembali ke menu...\n");
        _getch();
        return;
    }

    mhs * curr = head;
    int idx = 0; 
    float total = 0;
    while (curr != NULL && idx < data.count){
        list[idx++] = curr;
        curr = curr->next;
    }

    qsort(list, data.count, sizeof(mhs *), comparenrp);

    printf("Data mahasiswa: \n");
    for (int j = 0; j<data.count; j++){
        printf("%2d. NRP: %s\n", j+1, list[j]->NRP);
        printf("    Nama : %s\n", list[j]->Nama);
        printf("    Gender: %s\n", list[j]->gender ? "Laki-laki" : "Perempuan");
        printf("    IPK: %.2f\n\n", list[j]->IPK);
        total += list[j]->IPK;
    }

    printf("Rata-rata IPK: %.2f\n", total/data.count);
    free(list);
    printf("Tekan tombol apa saja untuk kembali ke menu...\n");
   _getch();
}
void PrintData(){ 
    printf("-----------------------------------------------------------\n");
    mhs * curr = head;
    float total = 0;
    int idx = 1;
    if (curr == NULL){
        printf("Tidak ada data\n");
        printf("Tekan tombol apa saja untuk kembali ke menu...\n");
        _getch();
        return;
    }
    while (curr != NULL){
        printf("Data Mahasiswa %d:\n", idx++);
        printf("    NRP: %s\n", curr->NRP);
        printf("    Nama: %s\n", curr->Nama);
        printf("    Gender: %s\n", curr->gender ? "Laki-laki": "Perempuan");
        printf("    IPK: %.2f", curr->IPK);
        total += curr->IPK;
        curr = curr->next;
        printf("\n\n");
    }
    printf("Rata-rata IPK: %.2f\n", total/data.count);
    
    printf("Tekan tombol apa saja untuk kembali ke menu...\n");
   _getch();
}
void DeleteData(){
    printf("-----------------------------------------------------------\n");
    if (head == NULL || data.count == 0){
        printf("Tidak ada data untuk dihapus\n");
        printf("Tekan tombol apa saja untuk kembali ke menu...\n");
        _getch();
        return;
    }
    char nrp[11];

    do{
        printf("Masukkan NRP yang ingin dihapus: ");
        scanf("%10s", nrp);
        if (!nrpvalid(nrp)){
            printf("NRP tidak valid! Harus terdiri dari 10 digit angka\n");
        }
    } while(!nrpvalid(nrp));

    mhs * curr = head;
    while (curr != NULL){
        if (strcmp(curr->NRP, nrp) == 0){
            if (curr == head){
                head = curr->next;
                if (head != NULL){
                    head->prev = NULL;
                }
            }
            else{
                if (curr->prev != NULL){
                    curr->prev->next = curr->next;
                }
                if (curr->next != NULL){
                    curr->next->prev = curr->prev;
                }
            }
            free(curr);
            data.count--;

            savefile("dbmhs.dat");
            printf("Data dengan NRP %s berhasil dihapus!\n", nrp);
             printf("Tekan tombol apa saja untuk kembali ke menu...\n");
            _getch();
            return;
        }
        curr = curr->next;
    }
    printf("NRP tidak ditemukan!\n");
    printf("Tekan tombol apa saja untuk kembali ke menu...\n");
   _getch();
}
