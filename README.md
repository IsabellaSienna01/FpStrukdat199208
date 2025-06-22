# Final Project Struktur Data (E)

**Kelompok 11**
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241199 | Isabella Sienna Sulisthio |
| 5025241208 | Ja`far Abdurrahman Shidiq|

## Pengelolaan database mahasiswa dengan data:
* NRP (String 10 digit)
* Nama (String 25 digit)
* Gender (numerik, bilangan bulat)
* IPK (numerik, bilangan pecahan)

## Fitur menu yang tersedia:
1. Menambah data
2. Mengubah data
3. Menampilkan semua data dengan index (berurutan sesuai NRP)
4. Menampilkan semua data tanpa index
5. Hapus data

## Cara Kompilasi Program:
```
gcc main.c src/menu.c src/action.c -Iinclude -o programdb.exe
```
