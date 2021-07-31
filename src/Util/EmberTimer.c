/*
 * Created by Aaron Helton on 7/31/21.
 */

#include <EmberLib/Util/EmberTimer.h>

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
    #include <sys/resource.h>
#endif

double get_time()
{
#ifdef WIN32
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
#else
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return (double)t.tv_sec + t.tv_usec*1e-6;
#endif
}