#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <dirent.h>
#endif
#include <sys/stat.h>

#ifndef WIN32
int majick(const struct dirent* de)
{
    return 1;
}
#endif

int main(int argc, char* argv[])
{
  #ifdef WIN32
    /* Nothing to check */
  #else
    struct dirent** des;
    scandir("/", &des, &majick, &alphasort);
  #endif
    return 0;
}
