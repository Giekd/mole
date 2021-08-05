---
typora-copy-images-to: image
typora-root-url: image
---

---

#### 工作时间：2021-06-10

- 工作内容：
  - 确定项目目标功能：
    1. 扫描主机、域内信息
       - 主机信息
         1. 网络信息
            - 适配器名
            - IP地址
            - MAC地址
            - 网关地址
            - 能否出网
            
         2. 服务信息
            - 服务名称
            - 显示名称
            - 服务状态
            - 启动类型
            - 依存关系
            - 可执行文件的路径
            
         3. 用户信息
            - 用户名
            - 组名
            - 安全等级
            - 用户权限
            - 在线用户
            
         4. 系统信息

            - 命令`systeminfo`包含的内容（大部分重复了），如图：

              - <img src="E:\items\mole\image\image-20210805141456673.png" style="zoom:200%;" />

              - <img src="/image-20210805141737901.png" alt="image-20210805141737901" style="zoom:200%;" />

            - 安装的软件，及其它的版本、路径等（绿色免安装的，暂时无法获取）

            - 查询当前的进程列表、PID、

            - 查询任务计划

            - 查询本机共享列表

            - 查询路由表

            - 查询驱动情况

         5. 防御策略
       - 域内信息
         1. 判断是否有域
         2. 探测域内主机
         3. 查找域控制器
         4. 定位域管理员
    2. 开机自启（windows、linux）
    3. 情报加密发送
    4. 高隐蔽性，敏感行为免杀（扫描探测类）
    5. 模块化，可拓展，主程序可以调用其他模块
  - 确定使用c/c++作为开发语言
  - 创建工程
    
    - 提交到github
  - 学习`Port-scanner`

---

#### 工作时间：2021-06-28

- 工作内容：
  - 创建`socket_communication`分支
  - 使用socket通信的方式，将服务端的数据发送给客户端
  - 客户端执行数据（命令）并将执行的结果发送给服务端
  - 使用命令，截取客户端的屏幕

---

#### 工作时间：2021-07-30

- 工作内容：
  - 重新整理下命名方式
  - 确定扫描大概框架（主机信息、域内信息）
  - 获取主机信息的网络信息，参考文章：
    - [C++获得本机所有网卡的IP和MAC地址信息](https://www.cnblogs.com/fnlingnzb-learner/p/5942150.html)
  - 解决"this file does not belong to any project target..."警告问题
    - 参考文章：[this file does not belong to any project 解决](https://zhuanlan.zhihu.com/p/138557224)

---

#### 工作时间：2021-08-02

- 工作内容：
  - 理解参考文档代码
  - 尝试解决bug
    - 导致bug的原因是没有连接windows的库，（`#pragma comment(lib, "Iphlpapi.lib")`没有起作用）
  - 获取系统服务信息
  - 发现问题，获取系统服务信息需要权限。。获得权限的情况下可以获取系统服务信息
    - 暂时放弃低权限执行获取系统服务信息的想法，（需要提权）

---

#### 工作时间：2021-08-03

- 工作内容：
  - 解决bug：
    - vscode终端只显示mac地址的bug
      - 文件编码为：65001（UTF-8） 终端编码为：936（GBK），输出时有冲突，解决方案：设置输出终端为powershell，powershell的编码为936
    - 运行`host_scan.ScanServiceInfo()`，没有内容的bug
      - 需要提权或通过UAC的方式获取权限

---

#### 工作时间：2021-08-04

- 工作内容
  - 无

---

#### 工作时间：2021-08-05

- 工作内容

  - 获取系统目录

  - 解决警告

    - 警告内容：`ISO C++ forbids converting a string constant to 'TCHAR*' {aka 'char*'} [-Wwrite-strings]`
    - 参考文章：[warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]](https://www.programmersought.com/article/5604542845/)
    - 解决办法：将`TCHAR* enVarStrings[]`改为`TCHAR enVarStrings[][30]`

  - 解决错误

    - 错误内容：`multiple definition of xxx`
    - 参考文章：[问题解决： multiple definition of XXX](https://blog.csdn.net/liyuefeilong/article/details/44071053)

    - 解决办法：
      - 在.c中定义，在.h中加`extern`声明

  - 在注册表中获取已安装的软件

    - 参考文章：[C++ 获取已安装程序笔记](https://www.ascotbe.com/2019/11/14/C++GetInstalledProgramNotes/)
    - 参考文章：[C++访问注册表获取已安装软件信息列表示例代码](https://www.jb51.net/article/43663.htm)

