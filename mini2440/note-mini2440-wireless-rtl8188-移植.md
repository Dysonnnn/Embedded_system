
20190225
考虑 编译个无线网卡驱动



[root@FriendlyARM /dev]# uname -a
Linux FriendlyARM 2.6.32.2-FriendlyARM #11 Tue Dec 23 15:08:12 CST 2014 armv4tl unknown




无线 网卡信息
	Realtek RTL8188EU 无线 LAN 802.11n USB 2.0 网络适配器

rtl8188eu-master驱动源码地址：
	https://github.com/lwfinger/rtl8188eu
	**这个源码的makefile 好像不适配 arm的**

rtl8188eu_USB_linux.tar.gz
	https://www.xpgod.com/soft/35637.html
	**这份源码好像可以用**

	>rtl8188eus linux驱动安装说明：
		1. 下载驱动
		2.解压源码：
		$tar xvzf  rtl8188eu_USB_linux.tar.gz 
		3. 编译安装
		$cd 8188eu_USB_linux/driver/rtl8188eu/ 
		$make 
		$sudo make install 
		若make命令错误，可能是没有安装对应内核的编译环境，可以用sudo apt-get install linux-headers-$(uname -r) build-essentials安装
		4. 加载模块：
		$sudo insmod 8188eu.ko 
		5.可能需要重启：

打开驱动目录下的linux/rtl8188.../Makefile文件。（可能需要解压linux目录下的压缩包）

修改33行的CONFIG_POWER_SAVING = n， 去掉节能模式
修改下面的CONFIG_PLATFORM_I386_PC = n， 
在下面选择合适的平台，CONFIG_PLATFORM_ARM_S3C2K4 = y              //修改芯片架构 --参考 https://blog.csdn.net/zlw1005/article/details/8752796

```
ifeq ($(CONFIG_PLATFORM_ARM_S3C2K4), y)
EXTRA_CFLAGS += -DCONFIG_LITTLE_ENDIAN
ARCH := arm
CROSS_COMPILE := arm-linux-
KVER  := 2.6.32.2
KSRC := /linux-$(KVER)
endif
```

然后执行 make

其中的8188eu.ko就为我们编译得到的驱动

# 将8192cu.ko文件 加载到开发板应用。
在开发板中 进入到/lib/modules/2.6.32.2-FriendlyARM
执行：modpromod 8188eu
（如果不行：先 depmod后 modpromod 8188eu）就行了

------都不行 ，就先执行一下 insmod 8188.ko 加载到内核，就有了
```
[root@FriendlyARM mini2440-wirelessFile]# insmod 8188eu.ko 
rtl8188eu driver version=v4.1.2_4787.20120803
build time: Feb 25 2019 16:03:22
register rtw_netdev_ops to netdev_ops
CHIP TYPE: RTL8188E

usb_endpoint_descriptor(0):
bLength=7
bDescriptorType=5
bEndpointAddress=81
wMaxPacketSize=64
bInterval=0
RT_usb_endpoint_is_bulk_in = 1

usb_endpoint_descriptor(1):
bLength=7
bDescriptorType=5
bEndpointAddress=2
wMaxPacketSize=64
one_wire_status: 2
bInterval=0
RT_usb_endpoint_is_bulk_out = 2

usb_endpoint_descriptor(2):
bLength=7
bDescriptorType=5
bEndpointAddress=3
wMaxPacketSize=64
bInterval=0
RT_usb_endpoint_is_bulk_out = 3
nr_endpoint=3, in_num=1, out_num=2

one_wire_status: 4
NON USB_SPEED_HIGH
Chip Version Info: CHIP_8188E_Normal_Chip_TSMC_D_CUT_1T1R_RomVer(0)
RF_Type is 3!!
_ConfigNormalChipOutEP_8188E OutEpQueueSel(0x05), OutEpNumber(2) 
EEPROM type is E-FUSE
====> _ReadAdapterInfo8188EU
Boot from EFUSE, Autoload OK !
EEPROM ID=0x8129
VID = 0x0BDA, PID = 0x8179
Customer ID: 0x00, SubCustomer ID: 0xCD
Hal_ReadPowerSavingMode88E...bHWPwrPindetect(0)-bHWPowerdown(0) ,bSupportRemoteWakeup(0)
### PS params=>  power_mgnt(0),usbss_enable(0) ###
======= Path 0, Channel 0 =======
one_wire_status: 4
Index24G_CCK_Base[0][0] = 0x25
Index24G_BW40_Base[0][0] = 0x29
======= Path 0, Channel 1 =======
Index24G_CCK_Base[0][1] = 0x25
Index24G_BW40_Base[0][1] = 0x29
======= Path 0, Channel 2 =======
Index24G_CCK_Base[0][2] = 0x25
one_wire_status: 4
Index24G_BW40_Base[0][2] = 0x29
======= Path 0, Channel 3 =======
Index24G_CCK_Base[0][3] = 0x25
Index24G_BW40_Base[0][3] = 0x29
======= Path 0, Channel 4 =======
Index24G_CCK_Base[0][4] = 0x25
Index24G_BW40_Base[0][4] = 0x29
======= Path 0, Channel 5 =======
Index24G_CCK_Base[0][5] = 0x25
Index24G_BW40_Base[0][5] = 0x29
======= Path 0, Channel 6 =======
Index24G_CCK_Base[0][6] = 0x25
Index24G_BW40_Base[0][6] = 0x28
one_wire_status: 2
======= Path 0, Channel 7 =======
Index24G_CCK_Base[0][7] = 0x25
Index24G_BW40_Base[0][7] = 0x28
======= Path 0, Channel 8 =======
Index24G_CCK_Base[0][8] = 0x25
Index24G_BW40_Base[0][8] = 0x28
======= Path 0, Channel 9 =======
one_wire_status: 3
Index24G_CCK_Base[0][9] = 0x25
Index24G_BW40_Base[0][9] = 0x28
======= Path 0, Channel 10 =======
Index24G_CCK_Base[0][10] = 0x25
Index24G_BW40_Base[0][10] = 0x28
======= Path 0, Channel 11 =======
one_wire_status: 4
Index24G_CCK_Base[0][11] = 0x25
Index24G_BW40_Base[0][11] = 0x28
======= Path 0, Channel 12 =======
Index24G_CCK_Base[0][12] = 0x25
Index24G_BW40_Base[0][12] = 0x28
======= Path 0, Channel 13 =======
one_wire_status: 4
Index24G_CCK_Base[0][13] = 0x25
Index24G_BW40_Base[0][13] = 0x28
======= Path 0, Channel 14 =======
Index24G_CCK_Base[0][14] = 0x25
Index24G_BW40_Base[0][14] = 0x28
======= TxCount 0 =======
CCK_24G_Diff[0][0]= 0
one_wire_status: 4
OFDM_24G_Diff[0][0]= 1
BW20_24G_Diff[0][0]= -1
BW40_24G_Diff[0][0]= 0
======= TxCount 1 =======
CCK_24G_Diff[0][1]= -2
OFDM_24G_Diff[0][1]= -2
BW20_24G_Diff[0][1]= -2
BW40_24G_Diff[0][1]= -2
======= TxCount 2 =======
one_wire_status: 5
CCK_24G_Diff[0][2]= -2
OFDM_24G_Diff[0][2]= -2
BW20_24G_Diff[0][2]= -2
BW40_24G_Diff[0][2]= -2
======= TxCount 3 =======
CCK_24G_Diff[0][3]= -2
OFDM_24G_Diff[0][3]= -2
BW20_24G_Diff[0][3]= -2
BW40_24G_Diff[0][3]= -2
EEPROMRegulatory = 0x0
mlmepriv.ChannelPlan = 0x20
EEPROM Customer ID: 0x 0
EEPROM : AntDivCfg = 0, TRxAntDivType = 3
Board Type: 0x 0
ThermalMeter = 0x1a
<==== _ReadAdapterInfo8188EU in 2215 ms
one_wire_status: 2
rtw_macaddr_cfg MAC Address  = 0c:82:68:32:b6:39
MAC Address from pnetdev->dev_addr= 0c:82:68:32:b6:39
bDriverStopped:1, bSurpriseRemoved:0, bup:0, hw_init_completed:0
usbcore: registered new interface driver rtl8188eu
```




-----生成 的 .ko文件存放：

把生成的8192cu.ko拷到/lib/modules/2.6.32.2-FriendlyARM/路径下。
cd /lib/modules/2.6.32.2-FriendlyARM/
depmod /lib/modules/2.6.32.2-FriendlyARM/
modprobe 8192cu
（或者把8192cu.ko拷到/lib/modules/2.6.32.2-FriendlyARM/net/wireless路径下。
直接modprobe 8192cu）
(或者insmod 8192cu.ko                   
rtw driver version=v3.0.2164.20110715                                          
usbcore: registered new interface driver rtl8192cu)

---http://blog.sina.com.cn/s/blog_6701bbda0101kvjb.html


四、配置usb无线网
启动无线网卡：ifconfig wlan0 up
查看可用搞得无线网络接入点：iwlist scanning
接入无线网：start-wifi wpa2 wifiname  wifikey
设置IP：ifconfig wlan0 172.16.16.16 netmask xxx.xxx.xxx.xxx up
如：
ifconfig eth0 192.168.2.110 netmask 255.255.255.0 up
route add default gw 192.168.2.1 dev wlan0

到此，已经基本结束
--------------------- 
作者：mrjy1475726263 
来源：CSDN 
原文：https://blog.csdn.net/mrjy1475726263/article/details/8886925 
版权声明：本文为博主原创文章，转载请附上博文链接！
----



交叉编译参考：
	交叉编译和安装ARM板（RK3288）和Linux 3.10上的RTL8188无线网卡驱动
	https://www.cnblogs.com/chujian1120/p/5888629.html

	--参考 https://blog.csdn.net/zlw1005/article/details/8752796



wget http://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.32.2.tar.gz

编译内核：  内核在友善之臂的光盘文件有
	http://www.bubuko.com/infodetail-2405978.html


make distclean是把整个内核的配置全清除了！
--- 

在使用ubuntu16.4编译Linux-2.6.31内核时出现这样的错误

可以修改timeconst.pl的内容后正常编译。

以下是编译错误提示的内容：

Can't use 'defined(@array)' (Maybe you should just omit the defined()?) at kernel/timeconst.pl line 373.
/opt/ARM/mini6410/linux/linux-2.6.38/kernel/Makefile:140: recipe for target 'kernel/timeconst.h' failed
make[1]: *** [kernel/timeconst.h] Error 255
Makefile:916: recipe for target 'kernel' failed
make: *** [kernel] Error 2

将kernel/timeconst.pl中第373行的defined()去掉只留下@val就可以了	

--- https://www.cnblogs.com/zxc2man/p/6370603.html

---


----

五、为了更好的管理wifi，可以选择编译wireless_tools
进入/home/RTL8188C_8192C_USB_linux_v3.4.4_4749.20121105/wireless_tools/wireless_tools.30.rtl，修改makefile即可

>## Compiler to use (modify this for cross compile).
CC = arm-linux-gcc
>## Other tools you need to modify for cross compile (static lib only).
AR = arm-linux-ar
RANLIB = arm-linux-ranlib

再执行make，编译完成后，将生成的iwconfig，iwlist文件拷贝到开发板的根文件系统中的/bin目录下，将
libiw.so.29拷贝到/lib目录下。
--------------------- 
作者：mrjy1475726263 
来源：CSDN 
原文：https://blog.csdn.net/mrjy1475726263/article/details/8886925 
版权声明：本文为博主原创文章，转载请附上博文链接！
---


---

将wlanrtl8188.ko文件复制到开发板/home/firefly目录下，执行sudo depmod -n /home/firefly/wlanrtl8188.ko，然后执行insmod /home/firefly/wlanrtl8188.ko，即可使用无线网卡。

如果需要以后开机后也能使用无线网卡，编辑/etc/rc.local文件，加入/sbin/insmod /home/firefly/wlanrtl8188.ko即可。

本文永久更新链接地址：http://www.linuxidc.com/Linux/2016-09/135374.htm

---


修改启动项
[root@FriendlyARM /]# vi /etc/init.d/rcS      
```
# start wlan0 8188eu    

insmod wlan_rtl8188.ko >> ~/wlan.log  

echo "insmod wlan_rtl8188 over "  >> ~/wlan.log  

ifconfig wlan0 up  >> ~/wlan.log  

echo "ifconfig wlan0 up "  >> ~/wlan.log 

sleep 2                              
             
depmod wlan_rtl8188.ko >> ~/wlan.log 
```





```开机 log

<==== _ReadAdapterInfo8188EU in 3050 ms
one_wire_status: 4
rtw_macaddr_cfg MAC Address  = 0c:82:68:32:b6:39
MAC Address from pnetdev->dev_addr= 0c:82:68:32:b6:39
bDriverStopped:1, bSurpriseRemoved:0, bup:0, hw_init_completed:0
usbcore: registered new interface driver rtl8188eu
depmod: chdir(wlan_rtl8188.ko): No such file or directory
/etc/init.d/rcS: line 70: modpromod: not found


```


MINI2440提供的系统没有DHCP客户端程序，只能设置静态IP
开启dhcp：（） ---这是有线连接，无线连接的话有DHCP



-------

## 报错：
执行接入无线网：
```
start-wifi wpa2 wifiname  wifikey
```
输出log：
```
survey done event(0)
survey done event(0)
survey done event(0)
Sending discover...
Sending discover...
survey done event(0)
Sending discover...
survey done event(0)

```
输入 ctrl+c 无法停止，只能 kill 掉，具体操作如下

# ps
```
 848 root      2068 S    wpa_supplicant -B -P /var/run/wpa_wlan0_server -i wla
```
# kill -9 848  // 结束进程



- wifi密码有三种加密模式：  
>WPA‐PSK/WPA2‐PSK 
>WPA/WPA2  
>WEP





---

dhcp v1.13.3   DHCP源码 下载地址  http://ftp.isc.org/isc/dhcp/

然而，配置失败，编译失败？

---


下来执行
[root@Xtramus6410 /opt]# wpa_supplicant -Dwext -iwlan0 -c /etc/wpa_supplicant.conf -dd &
结果出来一长串的信息，以后慢慢了解！


在ubuntu16.04环境下交叉编译了一个 wireless RTL8188C_8118_USB wifi模块，然后移植到 mini2440（Samsung S3C2440为微处理器），可以加载模块，ifconfig 可以看到wlan0，但是无法连接到wifi，一直显示
Sending discover...
survey done event(0)
Sending discover...
Sending discover...
survey done event(0)
Sending discover...
这是什么原因呢？

浩哥说:
	你这个应该驱动已经起来了，但就是分配不了IP，可能里面配置文件不对还是什么的，无法获取服务器IP



```
[root@FriendlyARM /]# survey done event(2c)
(2)871x_drv - drv_close, bup=1, hw_init_completed=1
-871x_drv - drv_close, bup=1
###=> usb_read_port_complete => urb status(-75)
rtl8188e_set_FwJoinBssReport_cmd mstatus(0)
+871x_drv - drv_open, bup=1
-871x_drv - drv_open, bup=1
[rtw_wx_set_pmkid] IW_PMKSA_FLUSH!
set_mode = IW_MODE_INFRA
=>rtw_wx_set_essid
ssid=gͺF|Z.c3, len=32
Set SSID under fw_state=0x00000008
<=rtw_wx_set_essid, ret 0
hw_var_set_opmode()-3434 mode = 2
[rtw_wx_set_pmkid] IW_PMKSA_FLUSH!
survey done event(33)
rtw_select_and_join_from_scanned_queue: return _FAIL(candidate == NULL)
try_to_join, but select scanning queue fail, to_roaming:0
survey done event(2d)
==>pwr_state_check_handler .fw_state(8)
==> rtw_ps_cmd  , enqueue CMD 
survey done event(32)
set_mode = IW_MODE_INFRA	
```

启动wlan0.
>#  wpa_supplicant  -B -c /etc/wpa_supplicant/wpa_supplicant.conf  -i wlan0    自动获取IP地址 
># udhcpc -i wlan0




--- 在图形界面就可以连wifi 了？

ps 有以下进程
 827 root      2068 S    wpa_supplicant -B -P /var/run/wpa_wlan0_server -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
  849 root      3072 S    udhcpc -p /var/run/dhcp_wlan0 -i wlan0 


###  log
```
UpdateHalRAMask8188EUsb => mac_id:0, networkType:0x0b, mask:0x000fffff
         ==> rssi_level:0, rate_bitmap:0x000ff015
>### MacID(0),Set Max Tx RPT MID(1)
>### rtl8188e_set_FwMediaStatus_cmd: MStatus=1 MACID=0 
rtw_tkip_decrypt:rx bc/mc packets,but didn't install group key!!!!!!!!!!
```




产生log  survey done event(0)   的进程是 wpa_supplicant -B -P /var/run/wpa_wlan0_server -i wla