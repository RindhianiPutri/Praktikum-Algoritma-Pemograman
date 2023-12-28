#include <iostream>
#include <cstdlib>
#include <algorithm> // library untuk fungsi swap
#define MAXPELANGGAN 20 //konstanta ini menetapkan batas maksimum jumlah pelanggan yang dapat ditangani oleh program.
#define MAXPEMBELIAN 10 //Konstanta ini menetapkan batas maksimum jumlah pembelian yang dapat dilakukan oleh setiap pelanggan.

using namespace std;

int index = -1;
int HargaGamis = 150000;
int HargaJilbab = 40000;
int HargaMukenah = 100000;

void TampilkanJudulProgram(){
    cout << "\t\t ====================================================" << endl;
    cout << "\t\t | SELAMAT DATANG DI TOKO BUSANA MUSLIMAH AISYAH    |" << endl;
    cout << "\t\t | Create by : Rindhiani Putri                      |" << endl;
    cout << "\t\t | Departemen Teknik Elektronika                    |" << endl;
    cout << "\t\t ====================================================" << endl;
}

typedef struct {
    int JenisBusana;
    int Jumlah;
    int TotalBiaya;
} Pembelian;

typedef struct {
    char NamaPelanggan[MAXPELANGGAN]; //menggunakan array dengan indeks MAXPELANGGAN
    int NomorTransaksi;
    float Diskon;
    char StatusPembelian;
    Pembelian Pembeli[MAXPEMBELIAN]; 
} Pelanggan;

// Fungsi Untuk Sorting Nomor Transaksi Dari Terkecil Ke Terbesar
void BubbleSort(Pelanggan data[], int n){ //
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (data[j].NomorTransaksi > data[j + 1].NomorTransaksi){
                // Tukar data jika tidak dalam urutan
                swap(data[j], data[j + 1]);
            }
        }
    }
}

//Fungsi untuk menghasilkan nomor transaksi
int generateNomorTransaksi(){ //Fungsi ini tidak menerima parameter dan mengembalikan nilai bertipe int
    return rand() % 1000;
}

// Fungsi Untuk Menampilkan Menu
void PilihData(int *Pilihan){
    cout << "MENU: " << endl;
    cout << "1. Tambahkan Pelanggan  " << endl;
    cout << "2. Tampilkan Pelanggan " << endl;
    cout << "3. Proses Pengemasan Pembelian" << endl;
    cout << "4. Daftar Pelanggan Dan Status Transaksi  " << endl;
    cout << "5. Keluar " << endl;

    cout << "Pilihan : ";
    cin >> *Pilihan;
}

// Fungsi Untuk Menambahkan Pelanggan
void TambahkanPelanggan(Pelanggan data[]){
    if (index < MAXPELANGGAN){
        ++index;
        cout << "Masukkan Nama Pelanggan : ";
        cin.ignore();
        cin.getline(data[index].NamaPelanggan, MAXPELANGGAN);

        data[index].NomorTransaksi = generateNomorTransaksi();

        char konfirmasi;
        int i = 0;
        do{
            cout << "Jenis Pembelian : " << endl;
            cout << "1. Gamis\n";
            cout << "2. Jilbab\n";
            cout << "3. Mukenah\n"
                 << endl;

            cout << "Masukkan Jenis Pembelian : ";
            cin >> data[index].Pembeli[i].JenisBusana;

            int JenisBusana = data[index].Pembeli[i].JenisBusana;
            cout << "Masukkan Jumlah Pembelian (pcs) : ";
            cin >> data[index].Pembeli[i].Jumlah;

            int Jumlah = data[index].Pembeli[i].Jumlah;
            switch (data[index].Pembeli[i].JenisBusana) {
            case 1:
                data[index].Pembeli[i].TotalBiaya = HargaGamis * Jumlah;
                break;
            case 2:
                data[index].Pembeli[i].TotalBiaya = HargaJilbab * Jumlah;
                break;
            case 3:
                data[index].Pembeli[i].TotalBiaya = HargaMukenah * Jumlah;
                break;
            }
            i++;

            if (i >= MAXPEMBELIAN) {
                cout << "Jumlah Pembelian Telah Mencapai Batas Maksimum" << endl;
                break;
            }

            cout << "Ingin Menambah Pembelian Jenis Busana? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == 'n' || konfirmasi == 'N')
                break;

        } while (true);

        data[index].StatusPembelian = false;
    }
    else {
        cout << "Jumlah Pelanggan Telah Mencapai Batas Maksimum" << endl;
    }
    cout << "===============================================" << endl;
}

// Fungsi Untuk Menampilkan Pelanggan
void TampilkanPelanggan(Pelanggan pelanggan[], bool selesai) {
    for (int i = 0; i <= index; i++) {
        if (pelanggan[i].StatusPembelian == selesai) {
            cout << "Nama Pelanggan:  " << pelanggan[i].NamaPelanggan << endl;
            cout << "Nomor Transaksi:  " << pelanggan[i].NomorTransaksi << endl;
            for (int j = 0; j <= index; j++) {
                if (pelanggan[i].Pembeli[j].JenisBusana != 0) {
                    cout << "Jenis Busana: ";
                    switch (pelanggan[i].Pembeli[j].JenisBusana) {
                    case 1:
                        cout << "Gamis";
                        break;
                    case 2:
                        cout << "Jilbab";
                        break;
                    case 3:
                        cout << "Mukenah";
                        break;
                    }
                    cout << "\tJumlah: " << pelanggan[i].Pembeli[j].Jumlah;

                    // Menambahkan kondisi untuk menampilkan Total Biaya hanya jika Jenis Busana dan Jumlah valid
                    if (pelanggan[i].Pembeli[j].JenisBusana >= 1 && pelanggan[i].Pembeli[j].JenisBusana <= 10 &&
                        pelanggan[i].Pembeli[j].Jumlah > 0){
                        cout << "\tTotal Biaya: " << pelanggan[i].Pembeli[j].TotalBiaya;
                    }
                    cout << endl;
                }
            }

            double biayaKeseluruhan = 0.0;
            for (int k = 0; k <= MAXPEMBELIAN; k++) {
                int JenisBusana = pelanggan[i].Pembeli[k].JenisBusana;
                int Jumlah = pelanggan[i].Pembeli[k].Jumlah;

                switch (JenisBusana) {
                case 1:
                    biayaKeseluruhan += HargaGamis * Jumlah;
                    break;
                case 2:
                    biayaKeseluruhan += HargaJilbab * Jumlah;
                    break;
                case 3:
                    biayaKeseluruhan += HargaMukenah * Jumlah;
                    break;
                }
            }

            float diskon = (biayaKeseluruhan > 1) ? 0.05 * biayaKeseluruhan : 0.0;

            cout << "Total Biaya Keseluruhan Sebelum Diskon:  " << biayaKeseluruhan << endl;
            cout << "Diskon: " << diskon << endl;

            // Menghitung total biaya setelah diskon
            double totalBiayaSetelahDiskon = biayaKeseluruhan - diskon;

            cout << "Total Biaya Keseluruhan Setelah Diskon: " << totalBiayaSetelahDiskon << endl;

            cout << "Status Pembelian dan Transaksi: " << (pelanggan[i].StatusPembelian ? "Sudah Selesai dan Pembayaran Lunas " : "Belum Selesai dan Belum Dibayar") << endl;
            cout << "====================================================================" << endl;
        }
    }
}

// Fungsi Untuk Mencari Pelanggan Berdasarkan Nomor Transaksi
int CariPelangganByNoTransaksi(Pelanggan pelanggan[], int NomorTransaksi) {
    for (int i = 0; i <= index; i++) {
        if (pelanggan[i].NomorTransaksi == NomorTransaksi) 
        { // Perbaiki kondisi
            return i; // Mengembalikan indeks pelanggan jika ditemukan
        }
    }
    return -1; // Mengembalikan -1 jika Nomor Transaksi tidak ditemukan
}

// Fungsi Untuk Menampilkan Proses  Pengemasan
void ProsesPengemasan(Pelanggan data[]) {
    int NomorTransaksi;
    cout << "Masukkan Nomor Transaksi Pelanggan yang Akan Diproses Pembeliannya: ";
    cin >> NomorTransaksi;

    int indeks = CariPelangganByNoTransaksi(data, NomorTransaksi);

    if (indeks != -1) {
        // Mengecek apakah pesanan pelanggan sudah selesai dikemas atau belum
        if (data[indeks].StatusPembelian) {
            cout << "Pesanan Pelanggan Sudah Selesai Dikemas" << endl;
        }
        else
        {
            cout << "Proses pengemasan untuk pelanggan " << data[indeks].NamaPelanggan
                 << " (Nomor Transaksi: " << data[indeks].NomorTransaksi << ")..." << endl;
            // Proses Pengemasan
            // ...

            // Menandai pembelian sebagai selesai
            data[indeks].StatusPembelian = true;
            cout << "Proses Pengemasan Pesanan Selesai" << endl;
        }
    }
    else
    {
        cout << "Pelanggan dengan Nomor Transaksi " << NomorTransaksi << " tidak ditemukan." << endl;
    }
}

int main()
{
    Pelanggan pelanggan[MAXPELANGGAN];
    TampilkanJudulProgram();
    int Pilihan;
    bool ulang = true;

    do {
        PilihData(&Pilihan);

        switch (Pilihan) {
        case 1:
            BubbleSort(pelanggan, index + 1); // index+1 karena index dimulai dari 0
            TambahkanPelanggan(pelanggan);
            break;
        case 2:
            TampilkanPelanggan(pelanggan, false);//Ini berarti program akan menampilkan daftar pelanggan yang belum menyelesaikan pembelian, atau dengan kata lain, pelanggan yang memiliki status pembelian false.
            break;

        case 3:
            ProsesPengemasan(pelanggan);
            break;

        case 4:
            BubbleSort(pelanggan, index + 1); // index+1 karena index dimulai dari 0
            TampilkanPelanggan(pelanggan, true); //Ini berarti program akan menampilkan daftar pelanggan yang telah menyelesaikan pembelian, atau dengan kata lain, pelanggan yang memiliki status pembelian true.
            break;

        case 5:
            ulang = false;
            break;
        }
    } while (ulang);

    return 0;
}
