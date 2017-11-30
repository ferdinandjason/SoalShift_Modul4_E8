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

static int e8_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = lstat(fpath, stbuf);  
    if (res == -1)
        return -errno;

    return 0;
}

static int e8_getdir(const char *path, fuse_dirh_t h, fuse_dirfil_t filler)
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

static int e8_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = mknod(fpath, mode, rdev);
    if(res == -1)
        return -errno;

    return 0;
}

static int e8_chmod(const char *path, mode_t mode)
{
    int res;

    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = chmod(fpath, mode);
    if(res == -1)
        return -errno;

    return 0;
}

static int e8_open(const char *path, int flags)
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

static int e8_read(const char *path, char *buf, size_t size, off_t offset)
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

static int e8_write(const char *path, const char *buf, size_t size, off_t offset)
{
    printf("LOL\n");
    int fd;
    int res;
    int res1;
	char fpath[1000],temp1[1000],tempe[1000];

	sprintf(fpath, "%s%s", dirpath, path);
    printf("%s\n",fpath);

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

static struct fuse_operations e8_oper = {
.getattr = e8_getattr,
//.readlink = e8_readlink,
.getdir = e8_getdir,
.mknod = e8_mknod,
//.mkdir = e8_mkdir,
//.symlink = e8_symlink,
//.unlink = e8_unlink,
//.rmdir = e8_rmdir,
//.rename = e8_rename,
//.link = e8_link,
.chmod = e8_chmod,
//.chown = e8_chown,
//.truncate = e8_truncate,
//.utime = e8_utime,
.open = e8_open,
.read = e8_read,
.write = e8_write,
//.release = e8_release,
//.fsync = e8_fsync

};

int main(int argc, char *argv[])
{
    fuse_main(argc, argv, &e8_oper);
    return 0;
}
