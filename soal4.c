#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/statfs.h>

static const char *dirpath ="/home/ferdinand/Downloads/tmp";

char readPath[1000];

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = lstat(fpath, stbuf);  
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_getdir(const char *path, fuse_dirh_t h, fuse_dirfil_t filler)
{
    DIR *dp;
    struct dirent *de;
    int res = 0;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    dp = opendir(fpath);
    if(dp == NULL)
        return -errno;

    while((de = readdir(dp)) != NULL)
    {
        res = filler(h, de->d_name, de->d_type);
        if(res != 0)
            break;
    }

    closedir(dp);
    return res;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = mknod(fpath, mode, rdev);
    if(res == -1)
        return -errno;

    return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    int res;

    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = chmod(fpath, mode);
    if(res == -1)
        return -errno;

    return 0;
}

static int xmp_open(const char *path, int flags)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = open(fpath, flags);
    if(res == -1)
        return -errno;

    close(res);
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset)
{
    int fd;
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    strcpy(readPath,path);
    fd = open(fpath, O_RDONLY);
    if(fd == -1)
        return -errno;
  
    res = pread(fd, buf, size, offset);
    if(res == -1)
        res = -errno;

    close(fd);
    return res;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset)
{
    int fd;
    int res;
    int res1;
	char fpath[1000],temp1[1000],tempe[1000];

	sprintf(fpath, "%s%s", dirpath, path);

	strncpy(tempe,fpath,strlen(fpath)-4);
	int i,count,idx=3;
	char tempeks[5];
	for(i=strlen(fpath)-1,count=1;count<=4;i--,count++){
		tempeks[idx--]=fpath[i];
	}


    fd = open(fpath, O_WRONLY);
    if(fd == -1)
		return -errno;

    res = pwrite(fd, buf, size, offset);
    if(res == -1)
        res = -errno;

	sprintf(temp1, "%s%s", dirpath, readPath);


	char command[1000];
	char rename1[1000];
	sprintf(rename1,"%s%s",tempe,tempeks);
	system(command);
	char rename2[1000];
	sprintf(rename2,"%s%s.copy",dirpath,readPath);
	rename(rename1,rename2);
	//sprintf(command,"zenity --error --text=\"%s\n%s\" --title=\"Warning!\"",rename1,rename2);

	char command2[1000];
	sprintf(command2,"chmod 000 %s",rename2);
	system(command2);

    close(fd);
    return res;
}

static struct fuse_operations xmp_oper = {
.getattr = xmp_getattr,
//.readlink = xmp_readlink,
.getdir = xmp_getdir,
.mknod = xmp_mknod,
//.mkdir = xmp_mkdir,
//.symlink = xmp_symlink,
//.unlink = xmp_unlink,
//.rmdir = xmp_rmdir,
//.rename = xmp_rename,
//.link = xmp_link,
.chmod = xmp_chmod,
//.chown = xmp_chown,
//.truncate = xmp_truncate,
//.utime = xmp_utime,
.open = xmp_open,
.read = xmp_read,
.write = xmp_write,
//.release = xmp_release,
//.fsync = xmp_fsync

};

int main(int argc, char *argv[])
{
    fuse_main(argc, argv, &xmp_oper);
    return 0;
}