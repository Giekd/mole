//
// Created by Gorilla on 2021/6/27.
//

#include "host_scan.h"

void HostScan::ScanNetInfo()
{
    cout << "[* INFO *] Scanning network information\n" << endl;

    PIP_ADAPTER_INFO pIpAdapterInfo;
    pIpAdapterInfo = new IP_ADAPTER_INFO();    // PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);             // �õ��ṹ���С������GetAdapterInfo����
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);        // �õ���������Ϣ��stSize��Ϊ��������Ҳ�������
    int netCardNum = 0;                                         // ��¼��������
    int IPNumPerNetCard = 0;                                    // ��¼ÿ��������IP����

    if(ERROR_BUFFER_OVERFLOW == nRel)
    {
        // �������ERROR_BUFFER_OVERFLOW��˵��GetAdaptersInfo()�������ݵ��ڴ治����
        // ͬʱ������stSize����ʾ��Ҫ�Ŀռ�Ĵ�С
        delete pIpAdapterInfo;                                  // �ͷ�ԭ�����ڴ�ռ�
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];    // ���������ڴ�ռ������洢����������Ϣ
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);        // ���»�ȡ��������Ϣ
    }

    if(ERROR_SUCCESS == nRel)                                   // ���������Ϣ
    {
        while (pIpAdapterInfo)
        {
            cout << "����������" << ++netCardNum << endl;
            cout << "�������ƣ�" << pIpAdapterInfo->AdapterName << endl;
            cout << "����������" << pIpAdapterInfo->Description << endl;
            switch (pIpAdapterInfo->Type) {
                case MIB_IF_TYPE_OTHER:
                    cout << "�������ͣ�" << "OTHER" << endl;
                    break;
                case MIB_IF_TYPE_ETHERNET:
                    cout << "�������ͣ�" << "ETHERNET" << endl;
                    break;
                case MIB_IF_TYPE_TOKENRING:
                    cout << "�������ͣ�" << "TOKENRING" << endl;
                    break;
                case MIB_IF_TYPE_FDDI:
                    cout << "�������ͣ�" << "FDDI" << endl;
                    break;
                case MIB_IF_TYPE_PPP:
                    printf("PP\n");
                    cout << "�������ͣ�" << "PPP" << endl;
                    break;
                case MIB_IF_TYPE_LOOPBACK:
                    cout << "�������ͣ�" << "LOOPBACK" << endl;
                    break;
                case MIB_IF_TYPE_SLIP:
                    cout << "�������ͣ�" << "SLIP" << endl;
                    break;
                default:
                    break;
            }
            cout<<"����MAC��ַ��";
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
                if (i < pIpAdapterInfo->AddressLength-1)
                {
                    printf("%02X-", pIpAdapterInfo->Address[i]);
                }
                else
                {
                    printf("%02X\n", pIpAdapterInfo->Address[i]);
                }
            cout << "����IP��ַ���£�" << endl;
            //���������ж�IP,���ͨ��ѭ��ȥ�ж�
            IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
            do
            {
                cout<<"�������ϵ�IP������"<<++IPNumPerNetCard<<endl;
                cout<<"IP ��ַ��"<<pIpAddrString->IpAddress.String<<endl;
                cout<<"������ַ��"<<pIpAddrString->IpMask.String<<endl;
                cout<<"���ص�ַ��"<<pIpAdapterInfo->GatewayList.IpAddress.String<<endl;
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
        // ���� SCMan ������򿪱���E�������SERVICES_ACTIV_DATABASE ���ݿ�
        SC_HANDLE SCMan = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
        if(SCMan == nullptr)
        {
            cout << "OpenSCManager failed" << endl;
            break;
        }

        LPENUM_SERVICE_STATUS serviceStatus;                    //
        DWORD cbBytesNeeded = 0;
        DWORD servicesReturned = 0;                             // ���񷵻�
        DWORD resumeHandle = 0;                                 // �ָ�����

        // �Ӷ��з���MAX_SERVICE_SIZE��С�ڴ棬�����ڴ�����ָ�룬�����ڴ����ݳ�ʼ��Ϊ��
        serviceStatus = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, MAX_SERVICE_SIZE);

        BOOL ESS = EnumServicesStatus(
                SCMan,                                          // ���
                SERVICE_WIN32,                                  // ��������
                SERVICE_STATE_ALL,                              // ����״̬
                (LPENUM_SERVICE_STATUS)serviceStatus,           // ���������ϵͳ����Ľṹ
                MAX_SERVICE_SIZE,                               // �ṹ�Ĵ�С
                &cbBytesNeeded,                                 // ������������շ�������ķ���
                &servicesReturned,                              // ������������շ��ط��������
                &resumeHandle                                   // ���������������һ�ε��ñ���Ϊ0
                );

        if(ESS == 0)                                            // ���ڴ����
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

            LPQUERY_SERVICE_CONFIG lpServiceConfig = nullptr;      // ������ϸ��Ϣ�ṹ
            SC_HANDLE serviceCurren = nullptr;                     // ��ǰ�ķ�����
            // �����з���
            serviceCurren = OpenService(SCMan,                  // ������ƹ��������ݿ���
                                        serviceStatus[i].lpServiceName, // ���������
                                        SERVICE_QUERY_CONFIG);  // �Է���ķ���
            // �Ӷ��з���MAX_QUERY_SIZE�ֽڡ�����ָ���ڴ�����ָ�룬�ҽ��ڴ����ݳ�ʼ��Ϊ��
            lpServiceConfig = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, MAX_QUERY_SIZE);

            if(0 == QueryServiceConfig(serviceCurren,
                                          lpServiceConfig,
                                          MAX_QUERY_SIZE,
                                          &resumeHandle))
            {
                cout << "QueryServiceConfig Failed." << endl;
                CloseServiceHandle(serviceCurren);              // �رշ�����
            }
        }
    }while(FALSE);
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
