//
// Created by Gorilla on 2021/6/27.
//

#ifndef PROJECT_HOST_SCAN_H
#define PROJECT_HOST_SCAN_H

#include <iostream>
#include <winsock2.h>                               // socket通信，系统头文件
#include <iphlpapi.h>

#pragma comment(lib, "Iphlpapi.lib")

using namespace std;

class HostScan {
public:
    void ScanNetInfo();
    void ScanServiceInfo();
    void ScanUserInfo();
    void ScanSystemInfo();
    void ScanDefenseInfo();
};


#endif //PROJECT_HOST_SCAN_H
