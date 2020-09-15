#include <iostream>
#include "sensorserver.h"

using namespace std;

int main()
{
    cout << "Sensor server 0.1 !" << endl;
    uv_loop_t * loop = uv_default_loop();
    SensorServer c(loop);
    uv_run(loop,UV_RUN_DEFAULT);
    return 0;
}

