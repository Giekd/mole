#include "main.h"

using namespace std;

int main() 
{
    HostScan host_scan;
    host_scan.ScanNetInfo();
    host_scan.ScanServiceInfo();
    cout << "hello world!" << endl;
    return 0;
}
