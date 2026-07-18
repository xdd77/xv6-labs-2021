#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h" 
#include "kernel/fs.h"
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), 0, DIRSIZ-strlen(p));
  return buf;
}
void find(char *path, char *target)
{
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512];
    if((fd = open(path,0)) < 0)
    {
        fprintf(2,"find: cannot open %s\n",path);
        return;
    }
    if(fstat(fd,&st) < 0)
    {
        fprintf(2,"find: cannot stat %s\n",path);
        close(fd);
        return;
    }

    switch(st.type){
        case T_FILE:
            if(strcmp(fmtname(path),target)==0)
            {
                printf("%s\n",path);
            }
            break;

        case T_DIR:
            while(read(fd,&de,sizeof(de)) == sizeof(de))
            {
                if(de.inum ==0)
                {
                    continue;
                }
                if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0)
                {
                    continue;
                }
                strcpy(buf,path);
                char *p = buf + strlen(buf);
                *p ++ = '/';
                strcpy(p,de.name);
                // memmove(p,de.name,DIRSIZ);
                // p[DIRSIZ] = 0;
                find(buf,target);
            }
            break;
            }
            close(fd);
}
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(2,"Usage: find <path> <target>\n");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}