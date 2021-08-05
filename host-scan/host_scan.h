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
#include <tchar.h>
#include <stdio.h>
#include <processenv.h>
#include <vector>

#pragma comment(lib, "Iphlpapi.lib")
#pragma once

#define MAX_SERVICE_SIZE        1024 * 64
#define MAX_QUERY_SIZE          1024 * 8
#define INFO_BUFFER_SIZE        32767
#define ENV_VAR_STRING_COUNT    (sizeof(envVarStrings)/sizeof(TCHAR*))
// #define ENV_VAR_STRING_COUNT    4                           //(sizeof(envVarStrings)/sizeof(TCHAR*))

using namespace std;

extern TCHAR envVarStrings[][30];

class HostScan 
{
public:
    static void ScanNetInfo();
    static void ScanServiceInfo();
    static void ScanUserInfo();
    static void ScanSystemInfo();
    void ScanDefenseInfo();
    void printError( TCHAR* msg );
};


#endif //PROJECT_HOST_SCAN_H
