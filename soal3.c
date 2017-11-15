#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/ferdinand/Downloads/tmp";

<<<<<<< HEAD
static int e8_getattr(const char *path, struct stat *stbuf)
  {
   int hsl;
 	char path2[1000];
 	sprintf(path2,"%s%s",dirpath,path);
 	hsl = lstat(path2, stbuf);
 
 	if (hsl == -1)
=======
static int xmp_getattr(const char *path, struct stat *stbuf)
  {
   int res;
 	char fpath[1000];
 	sprintf(fpath,"%s%s",dirpath,path);
 	res = lstat(fpath, stbuf);
 
 	if (res == -1)
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
 		return -errno;
 
 	return 0;
 }
 
<<<<<<< HEAD
 static int e8_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
 		       off_t offset, struct fuse_file_info *fi)
 {
   char path2[1000];
 	if(strcmp(path,"/") == 0)
 	{
 		path=dirpath;
 		sprintf(path2,"%s",path);
 	}
 	else sprintf(path2, "%s%s",dirpath,path);
 	int hsl = 0;
=======
 static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
 		       off_t offset, struct fuse_file_info *fi)
 {
   char fpath[1000];
 	if(strcmp(path,"/") == 0)
 	{
 		path=dirpath;
 		sprintf(fpath,"%s",path);
 	}
 	else sprintf(fpath, "%s%s",dirpath,path);
 	int res = 0;
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
 
 	DIR *dp;
 	struct dirent *de;
 
 	(void) offset;
 	(void) fi;
 
<<<<<<< HEAD
 	dp = opendir(path2);
=======
 	dp = opendir(fpath);
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
 	if (dp == NULL)
 		return -errno;
 
 	while ((de = readdir(dp)) != NULL) {
 		struct stat st;
 		memset(&st, 0, sizeof(st));
 		st.st_ino = de->d_ino;
 		st.st_mode = de->d_type << 12;
<<<<<<< HEAD
 		hsl = (filler(buf, de->d_name, &st, 0));
 			if(hsl!=0) break;
=======
 		res = (filler(buf, de->d_name, &st, 0));
 			if(res!=0) break;
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
 	}
 
 	closedir(dp);
 	return 0;
 }
 
<<<<<<< HEAD
 static int e8_read(const char *path, char *buf, size_t size, off_t offset,
 		    struct fuse_file_info *fi)
 {
   char path2[1000];
 	if(strcmp(path,"/") == 0)
 	{
 		path=dirpath;
 		sprintf(path2,"%s",path);
 	}
 	else sprintf(path2, "%s%s",dirpath,path);
 	int hsl = 0;
   int fd = 0 ;
 
 	(void) fi;
 	fd = open(path2, O_RDONLY);
 	if (fd == -1)
 		return -errno;
 
 	hsl = pread(fd, buf, size, offset);
 	if (hsl == -1)
 		hsl = -errno;
 
 	close(fd);
  	return hsl;
  }
  
 static int e8_rename(const char *from, const char *to)
 {
     // juga digunakan untuk menyimpan / menyimpan hasil perubahan isi berkas
     int hsl;
=======
 static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
 		    struct fuse_file_info *fi)
 {
   char fpath[1000];
 	if(strcmp(path,"/") == 0)
 	{
 		path=dirpath;
 		sprintf(fpath,"%s",path);
 	}
 	else sprintf(fpath, "%s%s",dirpath,path);
 	int res = 0;
   int fd = 0 ;
 
 	(void) fi;
 	fd = open(fpath, O_RDONLY);
 	if (fd == -1)
 		return -errno;
 
 	res = pread(fd, buf, size, offset);
 	if (res == -1)
 		res = -errno;
 
 	close(fd);
  	return res;
  }
  
 static int xmp_rename(const char *from, const char *to)
 {
     // juga digunakan untuk menyimpan / menyimpan hasil perubahan isi berkas
     int res;
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
     char ffrom[1000];
     char tto[1000];
     system("mkdir /home/ferdinand/Downloads/tmp/simpanan -p");
     char direk[] = "/home/ferdinand/Downloads/tmp/simpanan";
     sprintf(ffrom,"%s%s",dirpath,from);
     sprintf(tto,"%s%s",direk,to);
<<<<<<< HEAD
	 hsl = rename(ffrom, tto);
	 char command[1000];
	 sprintf(command,"cp %s %s",ffrom,tto);
	 system(command);
     if(hsl == -1)
=======
	 res = rename(ffrom, tto);
	 char command[1000];
	 sprintf(command,"cp %s %s",ffrom,tto);
	 system(command);
     if(res == -1)
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
     	return -errno;
 
     return 0;
	}
	
<<<<<<< HEAD
static int e8_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int hsl;
	char path2[1000];
    sprintf(path2,"%s%s", dirpath, path);
	(void) fi;
	fd = open(path2, O_WRONLY);
	if (fd == -1)
		return -errno;

	hsl = pwrite(fd, buf, size, offset);
	if (hsl == -1)
		hsl = -errno;
=======
static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
	char fpath[1000];
    sprintf(fpath,"%s%s", dirpath, path);
	(void) fi;
	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25

	close(fd);
	return hsl;
}

static int e8_truncate(const char *path, off_t size)
{
<<<<<<< HEAD
    int hsl;
     char path2[1000];
 	sprintf(path2,"%s%s", dirpath, path);

    hsl = truncate(path2, size);
    if(hsl == -1)
=======
    int res;
     char fpath[1000];
 	sprintf(fpath,"%s%s", dirpath, path);

    res = truncate(fpath, size);
    if(res == -1)
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
        return -errno;

    return 0;
}

<<<<<<< HEAD
static int e8_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int hsl;
    char path2[1000];
    sprintf(path2,"%s%s", dirpath, path);
    hsl = mknod(path2, mode, rdev);
    if(hsl == -1)
        return -errno;

    return 0;
}

=======
static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;
    char fpath[1000];
    sprintf(fpath,"%s%s", dirpath, path);
    res = mknod(fpath, mode, rdev);
    if(res == -1)
        return -errno;
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25


static int e8_open(const char *path, struct fuse_file_info *fi)
{
    char path2[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(path2,"%s",path);
	}
	else sprintf(path2, "%s%s",dirpath,path);

        int hsl;
        hsl = open(path2, fi->flags);
        if (hsl == -1)
                return -errno;
        close(hsl);
        return 0;
}


<<<<<<< HEAD
static int e8_utimens(const char *path, const struct timespec ts[2])
{
        int hsl;
        /* don't use utime/utimes since they follow symlinks */
        hsl = utimensat(0, path, ts, AT_SYMLINK_NOFOLLOW);
        if (hsl == -1)
=======

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);

        int res;
        res = open(fpath, fi->flags);
        if (res == -1)
                return -errno;
        close(res);
        return 0;
}


static int xmp_utimens(const char *path, const struct timespec ts[2])
{
        int res;
        /* don't use utime/utimes since they follow symlinks */
        res = utimensat(0, path, ts, AT_SYMLINK_NOFOLLOW);
        if (res == -1)
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
                return -errno;
        return 0;
}

<<<<<<< HEAD
  static struct fuse_operations hsl_oper = {
  	.getattr	= e8_getattr,
	.readdir	= e8_readdir,
	.read		= e8_read,
	.rename     = e8_rename,
	.write 		= e8_write,
	.truncate	= e8_truncate,
	.mknod		= e8_mknod,
	.open		= e8_open,
	.utimens 	= e8_utimens,
=======
  static struct fuse_operations xmp_oper = {
  	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.rename     = xmp_rename,
	.write 		= xmp_write,
	.truncate	= xmp_truncate,
	.mknod		= xmp_mknod,
	.open		= xmp_open,
	.utimens 	= xmp_utimens,
>>>>>>> a57f94c0364bdd9d4f082e906817943712661a25
  };

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &hsl_oper, NULL);
}
