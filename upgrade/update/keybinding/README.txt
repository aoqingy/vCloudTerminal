通过快捷键打开终端窗口的逻辑

1. 按下CTRL-ALT-SHIFT-\启用或禁用终端打开功能
使用文件/root/.terminal来判断终端打开功能被启用或禁用。如果文件存在，则被启用；否则被禁用。
因此，切换终端打开功能的逻辑是：如果/root/.terminal文件存在，则删除之；否则创建之。

2. 按下CTRL-ALT-SHIFT-T来打开终端，在该功能被启用的状态下
因此，打开终端的逻辑是：如果/root/.terminal文件存在，则执行gnome-terminal。
