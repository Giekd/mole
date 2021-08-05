#include "main.h"
 
using namespace std;

int main() 
{
    HostScan host_scan;                                         // 创建实例
    // host_scan.ScanNetInfo();                                    // 扫描主机网络信息
    // host_scan.ScanServiceInfo();                                // 扫描主机服务信息
    host_scan.ScanUserInfo();                                     // 扫描主机用户信息
    host_scan.ScanSystemInfo();                                 // 扫描主机系统信息
    system("PAUSE");                                            // 按任意键继续

    return 0;
}
 