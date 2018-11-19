壹：许可证按照模块划分：

0.         : 完全功能
1. vdi     : 桌面接入（SPICE/VMware/Citrix)
2. terminal: 终端管理（含课堂监控和引导切换等）
3. pxe     : PVF转换
4. usb     : USB还原
5. usbredir: USB共享
6. windows : Windows终端管理


贰：USB模块许可证生成方式：

python make-license-usb.py >./license-usb.txt
输入USB设备系列号USN
然后回车


叁：其他模块许可证生成方式：

将要生成许可证的云终端UUID（展示在云终端软件主界面上）保存在macs.txt中，每行一个
python make-license.py
输入许可证天数
输入模块号
然后回车
生成的许可证在对应的文件中。


肆：检查许可证文件是否有效

python check-license.py LICENSE-FILE-GOES-HERE
显示许可证文件的原始内容

license.txt
UUID,days

license-module.txt
UUID,days,module

license-usb.txt
USN
