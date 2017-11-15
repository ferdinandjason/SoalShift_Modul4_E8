#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
  
// gcc -Wall `pkg-config fuse --cflags` soal1.c -o soal1 `pkg-config fuse --libs`

static const char *dirpath = "/home/ferdinand/Documents";

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
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
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
	int i,cnt,idx=3;
	char temp[5];
	for(i=strlen(path2)-1,cnt=1;cnt<=4;i--,cnt++){
		temp[idx--]=path2[i];
	}
	
	if(strcmp(temp,".pdf")==0 || strcmp(temp,".doc")==0 || strcmp(temp,".txt")==0){
		char ch, source[1000], target[1000],command[1000];
		sprintf(source,"%s",path2);
		sprintf(target,"%s.ditandai",path2);
		int ret=rename(source,target);
		sprintf(command,"chmod 000 %s.ditandai",path2);
		system(command);
		system("zenity --error --text=\"Terjadi Kesalahan! File berisi konten berbahaya.\n\" --title=\"Warning!\"");
		return -errno;
	}
	else{
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
}

static struct fuse_operations e8_oper = {
	.getattr	= e8_getattr,
	.readdir	= e8_readdir,
	.read		= e8_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &e8_oper, NULL);
}
