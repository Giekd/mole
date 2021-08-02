---
typora-copy-images-to: image
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
         4. 系统信息
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

