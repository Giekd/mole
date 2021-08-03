//
// Created by Gorilla on 2021/6/27.
//

#ifndef PROJECT_HOST_SCAN_H
#define PROJECT_HOST_SCAN_H

#include <iostream>
#include <winsock2.h>                               // socket通信，系统头文件
#include <iphlpapi.h>
#include <windows.h>
#include <winsvc.h>
#include <errhandlingapi.h>
#include <winbase.h>

#pragma comment(lib, "Iphlpapi.lib")

#define MAX_SERVICE_SIZE 1024 * 64
#define MAX_QUERY_SIZE   1024 * 8

using namespace std;

class HostScan {
public:
    static void ScanNetInfo();
    static void ScanServiceInfo();
    void ScanUserInfo();
    void ScanSystemInfo();
    void ScanDefenseInfo();
};


#endif //PROJECT_HOST_SCAN_H
