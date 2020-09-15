#include <iostream>
#include "sensorclient.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#include "cmdbuilder.h"
static int gettemp()
{
    return (rand() %  (37 - 9 + 1)) + 9;
}
static int gethumid()
{
    return (rand() %  (100 - 10 + 1)) + 10;
}
static void buildfakecmd()
{
    CommandBuilder c("temp");
    time_t tt = time(NULL);
    struct tm* tm = localtime(&tt);
    for (int i=0;i < 24;i++)
    {

           tm->tm_hour += i;
           time_t time = mktime(tm);
        c.addMeasurement(1,gettemp(),gethumid(),time);


    }

    std::string input =c.buildcmd();
    //std::cin >> input;
    std::ofstream out("/home/mat/output.txt");
    out << input;
    out.close();
}
int main()
{
    srand(time(0));
    cout << "SensorClient 0.1 !" << endl;
    uv_loop_t * loop = uv_default_loop();
    SensorClient sc(loop);
    uv_run(loop,UV_RUN_DEFAULT);
    return 0;
}

