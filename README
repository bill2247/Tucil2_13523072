# Quadtree Image Compressor

## 📌 Deskripsi Program

Program ini mengimplementasikan **kompresi gambar** menggunakan struktur data **Quadtree** dengan pendekatan **Divide and Conquer**.

### 🎯 Fitur Utama:
- Kompresi berdasarkan **keseragaman warna piksel**
- 4 metode pengukuran error:
  1. Variance
  2. Mean Absolute Deviation (MAD)
  3. Max Pixel Difference
  4. Entropy
- Output:
  - Gambar terkompresi
  - Waktu eksekusi
  - Kedalaman pohon
  - Jumlah node

---

## ⚙️ Requirements

### 🖥️ Sistem Operasi
- Ubuntu (direkomendasikan)
- Windows (menggunakan WSL2 atau MinGW)

### 📦 Dependensi
- C++ Compiler (**minimal C++20**)
- Library **STB Image** (sudah termasuk dalam source code)
- CMake (opsional, untuk build otomatis)

---

## 🔧 Instalasi

### Untuk Ubuntu

1. Install compiler dan tools:
   ```bash
   sudo apt update && sudo apt install g++-11 cmake
   ```
2. Clone Repository: 
    ```bash
    git clone https://github.com/SabilulHuda/Tucil2_13523072.git
    cd Tucil2_13523072/src
    ```

### Untuk Windows

- Install MinGW atau gunakan WSL (Ubuntu)
- Jika menggunakan WSL, ikuti langkah instalasi Ubuntu

---

## 🏗️ Kompilasi Program

### Metode Manual
    ```bash
    g++ -std=c++20 -I../header main.cpp ImagePixel.cpp ErrorCalculator.cpp QuadTreeNode.cpp stb_implementation.cpp -o quadtree_compressor
    ```

### Menggunakan MakeFile
    ```bash
    make run
    ```

---

## ▶️ Cara Menjalankan Program

1. **Pindah ke direktori `bin`:**
   ```bash
   cd ../bin
   ```

2. **Jalankan program:**
    ```bash
    ./quadtree+compressor
    ```

3. **Masukkan parameter sesuai kebutuhan:**
    ```bash
    input path: test/input.png
    error method
    1. Variance
    2. Mean Absolute Deviation
    3. Max Pixel Difference
    4. Entropy
    Enter method number (1-4): 1
    input threshold (0.0-1.0): 0.3
    input minimum block size: 2
    output path: test/output.png
    ```

4. **Output yang dihasilkan:**
    ```bash
    Execution time: 106 ms
    Tree depth: 9
    Node count: 521
    ```

---

## 🧾 Penjelasan Parameter
- **input path**: Path ke gambar input (PNG/JPG)
- **error method**: Pilih metode error (1–4)
- **threshold**: Nilai ambang batas (0.0–1.0). Semakin kecil = kualitas lebih baik
- **minimum block size**: Ukuran blok terkecil, contoh: 2 = blok 2×2
- **output path**: Lokasi hasil kompresi

---

## 📁 Struktur Direktori
```bash
Tucil2_13523072/
├── src/               # Source code utama
│   ├── main.cpp
│   ├── ImagePixel.cpp
│   └── ...
├── header/            # File header (.hpp)
├── test/              # Contoh gambar input/output
├── bin/               # File executable setelah kompilasi
└── README.md          # Dokumentasi proyek ini
```

---

## ⚠️ Catatan Penting

- Pastikan file gambar input berada di path yang benar sebelum menjalankan program.
- Untuk pengguna Windows, gunakan format path: C:/path/to/image.png (hindari backslash \).
- Format hasil kompresi akan mengikuti format gambar input (PNG atau JPG).

---

## Identitas Pembuat

- Nama: Sabilul Huda
- NIM: 13523072
- Email: sabilulhuda060106@gmail.com