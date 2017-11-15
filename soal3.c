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

static int e8_getattr(const char *path, struct stat *stbuf)
  {
   int hsl;
 	char path2[1000];
 	sprintf(path2,"%s%s",dirpath,path);
 	hsl = lstat(path2, stbuf);
 
 	if (hsl == -1)
 		return -errno;
 
 	return 0;
 }
 
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
 
 	DIR *dp;
 	struct dirent *de;
 
 	(void) offset;
 	(void) fi;
 
 	dp = opendir(path2);
 	if (dp == NULL)
 		return -errno;
 
 	while ((de = readdir(dp)) != NULL) {
 		struct stat st;
 		memset(&st, 0, sizeof(st));
 		st.st_ino = de->d_ino;
 		st.st_mode = de->d_type << 12;
 		hsl = (filler(buf, de->d_name, &st, 0));
 			if(hsl!=0) break;
 	}
 
 	closedir(dp);
 	return 0;
 }
 
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
     char ffrom[1000];
     char tto[1000];
     system("mkdir /home/ferdinand/Downloads/tmp/simpanan -p");
     char direk[] = "/home/ferdinand/Downloads/tmp/simpanan";
     sprintf(ffrom,"%s%s",dirpath,from);
     sprintf(tto,"%s%s",direk,to);
	 hsl = rename(ffrom, tto);
	 char command[1000];
	 sprintf(command,"cp %s %s",ffrom,tto);
	 system(command);
     if(hsl == -1)
     	return -errno;
 
     return 0;
	}
	
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

	close(fd);
	return hsl;
}

static int e8_truncate(const char *path, off_t size)
{
    int hsl;
     char path2[1000];
 	sprintf(path2,"%s%s", dirpath, path);

    hsl = truncate(path2, size);
    if(hsl == -1)
        return -errno;

    return 0;
}

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


static int e8_utimens(const char *path, const struct timespec ts[2])
{
        int hsl;
        /* don't use utime/utimes since they follow symlinks */
        hsl = utimensat(0, path, ts, AT_SYMLINK_NOFOLLOW);
        if (hsl == -1)
                return -errno;
        return 0;
}

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
  };

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &hsl_oper, NULL);
}
