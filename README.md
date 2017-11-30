# SoalShift_Modul4_E8

Repositori Dokumentasi Soal Shift Sistem Operasi - Teknik Informatika - E8

## Daftar Isi
- [1. FUSE](https://github.com/ferdinandjason/SoalShift_Modul4_E8#fuse)
- [2. Soal Shift](https://github.com/ferdinandjason/SoalShift_Modul4_E8#soal-shift)
- [3. References](https://github.com/ferdinandjason/SoalShift_Modul4_E8#references)

## FUSE

FUSE (Filesystem in Userspace) adalah sebuah interface dimana kita dapat membuat filesystem linux sendiri di userspace.

Lalu apa yang menyenangkan dari membuat filesystem sendiri di userspace? Tentu saja menyenangkan dan merupakan suatu keuntungan yang besar, kita dapat menggunakan library apapun yang tersedia untuk membuat sebuah filesystem sendiri tanpa perlu mengganti kode pada kernel dan tanpa perlu mengerti secara mendalam apa yang filesystem sebenarnya lakukan di kernelspace. hal ini dapat dilakukan karena adanya modul fuse yang menjembatani antara kode filesystem yang berada di userspace dengan filesystem yang berada di kernelspace.

Salah satu contoh yang menarik dari fuse adalah GDFS (Google Drive File System) dimana GDFS ini memungkinkan kita untuk menunggangkan (mount) Google Drive kita ke sistem linux dan menggunakannya seperti file linux biasa.

Install FUSE :
```
$ sudo apt update
$ sudo apt install libfuse*
```
Fuse memiliki struct yang dinamakan fuse_operations yang didefinisikan seperti dibawah ini:
```
static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.create         = xmp_create,
	.release	= xmp_release,
	.fsync		= xmp_fsync,
  .setxattr	= xmp_setxattr,
	.getxattr	= xmp_getxattr,
	.listxattr	= xmp_listxattr,
	.removexattr	= xmp_removexattr,
#en
```
Untuk mengcompile nya menggunakan
```
gcc -Wall `pkg-config fuse --cflags` cobafuse.c -o cobafuse `pkg-config fuse --libs`
```
## Soal Shift

```
Soal Shift Modul 4
Sistem Operasi 2017

Rain dan Cloud adalah teman baik yang sangat dekat. Karena kedekatan itu lah, timbul rasa yang berbeda di hati Cloud untuk Rain. Suatu hari Cloud ingin mengutarakan isi hatinya kepada Rain. Namun, Rain ingin melihat dahulu kesungguhan hati Cloud untuk mendapatkan hatinya. Syarat tersebut adalah Rain ingin Cloud untuk membuatkannya sebuah implementasi dari FUSE yang baru saja didapatkan dari asistensi Sistem Operasi. Sebelumnya, ketika asistensi hanya diajarkan implementasi dasar yaitu mount direktori lain dengan FUSE. Padahal ketika dimount dengan sebuah direktori Rain ingin agar implementasi FUSE memiliki kriteria sebagai berikut:
1. Pada saat membuka file dengan ekstensi *.pdf, *.doc, *.txt pada directori Documents akan muncul pesan error “Terjadi kesalahan! File berisi konten berbahaya.” dan tidak dapat membaca file tersebut. Setelah memunculkan pesan error, file tersebut diganti namanya menjadi <namafile>.<ekstensi>.ditandai
2. Setelah memunculkan pesan error dan mengganti nama file tadi, file tersebut otomatis dipindahkan ke direktori “rahasia”. Jika folder rahasia belum ada, maka secara otomatis akan membuat direktori “rahasia” sebelum dipindahkan dan file tidak bisa di read write execute.

Rain juga seorang yang pelupa, maka Rain juga menginginkan kriteria sebagai berikut:
3. Ketika semua file dalam direktori Downloads diedit dan disimpan lagi, maka secara otomatis muncul folder baru dengan nama “simpanan” yang digunakan khusus untuk menyimpan file baru hasil dari yang sudah diedit dan file asli tetap ada pada tempatnya tanpa ada perubahan pada isinya. File baru hasil editan tersebut diberi nama sesuai dengan file aslinya.
4. File hasil salinan diberi nama <namafile>.<ekstensi>.copy dan jika file yang dibuka adalah file berekstensi .copy (file hasil salin), maka akan muncul pesan error berupa “File yang anda buka adalah file hasil salinan. File tidak bisa diubah maupun disalin kembali!” Dan file tersebut tidak akan terbuka dan tidak dibuat salinannya.

```

## References
Sistem Operasi Modul 4 - Teknik Informatika
