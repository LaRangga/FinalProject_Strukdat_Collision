# Collision Simulation: Brute Force vs Quadtree
Final Project Struktur Data

## Deskripsi Proyek
Proyek ini merupakan simulasi **tumbukan (collision) bola 2D** menggunakan **SFML (C++)**.
Tujuan dari project ini adalah **mengetahui performa algoritma Brute Force dan Quadtree**
dalam mendeteksi dan menangani collision antar objek.

Simulasi menampilkan:
- Bola bergerak dengan kecepatan berbeda
- Pantulan terhadap dinding window
- Tabrakan antar bola
- Perbandingan FPS antara Brute Force dan Quadtree

Fitur Utama
- Collision detection & response (elastic collision)
- HUD FPS realtime
- Klik kiri mouse untuk menambah bola
- Switch mode:
  - **B** → Brute Force
  - **Q** → Quadtree

## Kesulitan & Tantangan

Selama pengembangan, terdapat beberapa kendala, antara lain:

Logika collision tidak langsung bekerja mulus
Bola sempat menembus dinding window
Tumbukan antar bola tidak langsung memantul dengan benar
Implementasi Quadtree awalnya menghasilkan FPS yang sama dengan Brute Force

## Masalah tersebut diselesaikan dengan:

Perbaikan perhitungan normal collision
Penanganan overlap antar bola
Pengujian bertahap dengan jumlah bola kecil hingga besar
Validasi logika brute force sebelum membandingkan dengan quadtree

## Simulasi
![Demo Video](./video.gif)
