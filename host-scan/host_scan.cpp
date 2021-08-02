//
// Created by Gorilla on 2021/6/27.
//

#include "host_scan.h"

void HostScan::ScanNetInfo()
{
    cout << "[* INFO *] Scanning network information\n" << endl;

    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();    // PIP_ADAPTER_INFO结构体指针存储本机网卡信息
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
                cout<<"网卡IP地址如下："<<endl;
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
    do
    {
        // 定义 SCMan 句柄，打开本地计算机的SERVICES_ACTIVE_DATABASE 数据库
        SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 
        if(SCMan == NULL)
        {
            cout << "OpenSCManager failed" << endl;
            break;
        }

        LPENUM_SERVICE_STATUS SERVICE_STATUS;
        
    }
}

void HostScan::ScanUserInfo()
{

}

void HostScan::ScanSystemInfo()
{

}

void HostScan::ScanDefenseInfo()
{

}
