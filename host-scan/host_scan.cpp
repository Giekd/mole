//
// Created by Gorilla on 2021/6/27.
//

#include "host_scan.h"

void HostScan::ScanNetInfo()
{
    cout << "[* INFO *] Scanning network information\n" << endl;

    PIP_ADAPTER_INFO pIpAdapterInfo;
    pIpAdapterInfo = new IP_ADAPTER_INFO();    // PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);             // 得到结构体大小，用于GetAdapterInfo参数
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);        // 得到适配器信息，stSize作为输入量，也是输出量
    int netCardNum = 0;                                         // 记录网卡数量
    int IPNumPerNetCard = 0;                                    // 记录每张网卡的IP数量

    if(ERROR_BUFFER_OVERFLOW == nRel)
    {
        // 如果返回ERROR_BUFFER_OVERFLOW，说明GetAdaptersInfo()参数传递的内存不够，
        // 同时传出的stSize，表示需要的空间的大小
        delete pIpAdapterInfo;                                  // 释放原来的内存空间
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];    // 重新申请内存空间用来存储所有网卡信息
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);        // 重新获取适配器信息
    }

    if(ERROR_SUCCESS == nRel)                                   // 输出网卡信息
    {
        while (pIpAdapterInfo)
        {
            cout << "网卡数量：" << ++netCardNum << endl;
            cout << "网卡名称：" << pIpAdapterInfo->AdapterName << endl;
            cout << "网卡描述：" << pIpAdapterInfo->Description << endl;
            switch (pIpAdapterInfo->Type) {
                case MIB_IF_TYPE_OTHER:
                    cout << "网卡类型：" << "OTHER" << endl;
                    break;
                case MIB_IF_TYPE_ETHERNET:
                    cout << "网卡类型：" << "ETHERNET" << endl;
                    break;
                case MIB_IF_TYPE_TOKENRING:
                    cout << "网卡类型：" << "TOKENRING" << endl;
                    break;
                case MIB_IF_TYPE_FDDI:
                    cout << "网卡类型：" << "FDDI" << endl;
                    break;
                case MIB_IF_TYPE_PPP:
                    printf("PP\n");
                    cout << "网卡类型：" << "PPP" << endl;
                    break;
                case MIB_IF_TYPE_LOOPBACK:
                    cout << "网卡类型：" << "LOOPBACK" << endl;
                    break;
                case MIB_IF_TYPE_SLIP:
                    cout << "网卡类型：" << "SLIP" << endl;
                    break;
                default:
                    break;
            }
            cout<<"网卡MAC地址：";
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
                if (i < pIpAdapterInfo->AddressLength-1)
                {
                    printf("%02X-", pIpAdapterInfo->Address[i]);
                }
                else
                {
                    printf("%02X\n", pIpAdapterInfo->Address[i]);
                }
            cout << "网卡IP地址如下：" << endl;
            //可能网卡有多IP,因此通过循环去判断
            IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
            do
            {
                cout<<"该网卡上的IP数量："<<++IPNumPerNetCard<<endl;
                cout<<"IP 地址："<<pIpAddrString->IpAddress.String<<endl;
                cout<<"子网地址："<<pIpAddrString->IpMask.String<<endl;
                cout<<"网关地址："<<pIpAdapterInfo->GatewayList.IpAddress.String<<endl;
                pIpAddrString=pIpAddrString->Next;
            } while (pIpAddrString);
            pIpAdapterInfo = pIpAdapterInfo->Next;
        }
    }
    if(pIpAdapterInfo)
    {
        delete pIpAdapterInfo;
    }
    cout << "[* INFO *] The end of scanning\n" << endl;
}

void HostScan::ScanServiceInfo()
{
    cout << "[* INFO *] Scanning service information\n" << endl;
    do
    {
        // 定义 SCMan 句柄，打开本地E计算机的SERVICES_ACTIV_DATABASE 数据库
        SC_HANDLE SCMan = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
        if(SCMan == nullptr)
        {
            cout << "OpenSCManager failed" << endl;
            break;
        }

        LPENUM_SERVICE_STATUS serviceStatus;                    //
        DWORD cbBytesNeeded = 0;
        DWORD servicesReturned = 0;                             // 服务返回
        DWORD resumeHandle = 0;                                 // 恢复处理

        // 从堆中分配MAX_SERVICE_SIZE大小内存，返回内存对象的指针，并将内存内容初始化为零
        serviceStatus = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, MAX_SERVICE_SIZE);

        BOOL ESS = EnumServicesStatus(
                SCMan,                                          // 句柄
                SERVICE_WIN32,                                  // 服务类型
                SERVICE_STATE_ALL,                              // 服务状态
                (LPENUM_SERVICE_STATUS)serviceStatus,           // 输出参数，系统服务的结构
                MAX_SERVICE_SIZE,                               // 结构的大小
                &cbBytesNeeded,                                 // 输出参数，接收返回所需的服务
                &servicesReturned,                              // 输出参数，接收返回服务的数量
                &resumeHandle                                   // 输入输出参数，第一次调用必须为0
                );

        if(ESS == 0)                                            // 无内存对象
        {
            cout << "EnumServicesStatus Failed." << endl;
            break;
        }

        for(int i = 0; i < static_cast<int>(servicesReturned); i++ )
        {
            cout << "Service Name is :" << serviceStatus[i].lpDisplayName << "\t";
            switch (serviceStatus[i].ServiceStatus.dwCurrentState)
            {
                case SERVICE_CONTINUE_PENDING:
                    cout << "CONTINUE PENDING" << endl;
                    break;
                case SERVICE_PAUSE_PENDING:
                    cout << "PAUSE PENDING" << endl;
                    break;
                case SERVICE_PAUSED:
                    cout << "PAUSED" << endl;
                    break;
                case SERVICE_RUNNING:
                    cout << "RUNNING" << endl;
                    break;
                case SERVICE_START_PENDING:
                    cout << "START PENDING" << endl;
                    break;
                case SERVICE_STOPPED:
                    cout << "STOPPED" << endl;
                    break;
                default:
                    cout << "UNKNOWN" << endl;
                    break;
            }

            LPQUERY_SERVICE_CONFIG lpServiceConfig = nullptr;   // 服务详细信息结构
            SC_HANDLE serviceCurren = nullptr;                  // 当前的服务句柄
            // 打开现有服务
            serviceCurren = OpenService(SCMan,                  // 服务控制管理器数据库句柄
                                        serviceStatus[i].lpServiceName, // 服务的名称
                                        SERVICE_QUERY_CONFIG);  // 对服务的访问
            // 从堆中分配MAX_QUERY_SIZE字节。返回指向内存对象的指针，且将内存内容初始化为零
            lpServiceConfig = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, MAX_QUERY_SIZE);

            if(0 == QueryServiceConfig(serviceCurren,
                                          lpServiceConfig,
                                          MAX_QUERY_SIZE,
                                          &resumeHandle))
            {
                cout << "QueryServiceConfig Failed." << endl;
                CloseServiceHandle(serviceCurren);              // 关闭服务句柄
            }
        }
    }while(FALSE);
    cout << "[* INFO *] The end of scanning\n" << endl;
}

void HostScan::ScanUserInfo()
{
    cout << "[* INFO *] Scanning user information\n" << endl;

    DWORD i;
    TCHAR infoBuf[INFO_BUFFER_SIZE];                            // 保存
    DWORD bufCharCount = INFO_BUFFER_SIZE;                      // 保存
    bool returnValue;                                           // 保存返回值

    returnValue = GetUserName(infoBuf, &bufCharCount);
    if(returnValue == 0)                                        // 获取当前用户名
    {
        cout << "Description Failed to obtain user information" << endl;
    }
    else if(returnValue == 1)
    {
        cout << "user : " << infoBuf << endl;
    }
    

    cout << "[* INFO *] The end of scanning\n" << endl;
}

void HostScan::ScanSystemInfo()
{
    cout << "[* INFO *] Scanning system information\n" << endl;

    DWORD i;
    TCHAR infoBuf[INFO_BUFFER_SIZE];                            // 保存
    DWORD bufCharCount = INFO_BUFFER_SIZE;                      // 保存
    bool returnValue;                                           // 保存返回值

    returnValue = GetUserName(infoBuf, &bufCharCount);
    if(returnValue == 0)                                        // 获取当前用户名
    {
        cout << "Description Failed to obtain user information" << endl;
    }
    else if(returnValue == 1)
    {
        cout << "user : " << infoBuf << endl;
    }

    cout << "[* INFO *] The end of scanning\n" << endl;

}

void HostScan::ScanDefenseInfo()
{

}
