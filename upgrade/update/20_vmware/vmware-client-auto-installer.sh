#!/usr/bin/expect
set timeout 2 
spawn ./VMware-Horizon-Client-4.6.0-6617224.x64.bundle --eulas-agreed --console
expect "Client Drive Redirection(The Client Drive Redirection component enables folder redirection from your local computer to the remote desktop.)"
send "yes\r"
expect "Multimedia Redirection (MMR)(With multimedia redirection (MMR), the multimedia stream is processed on the client system.)"
send "yes\r"
expect "Smart Card(The Smart Card component enables Smart Card device redirection from your local computer to the remote desktop.)"
send "yes\r"
expect "Real-Time Audio-Video(The Real-Time Audio-Video component allows you to use local computer's webcam or microphone on the remote desktop.)"
send "yes\r"
expect "VMware Horizon(R) Virtualization Pack for Skype for Business(VMware Horizon(R) Virtualization Pack for Skype for Business enables Skype for business on linux view client.)"
send "yes\r"
expect "USB Redirection(The USB component enables USB device redirection from your local computer to the remote desktop.)"
send "yes\r"
expect "Virtual Printing(The Virtual Printing component allows you to use local or network printers from a remote desktop without requiring that additional print drivers be installed in the remote desktop.)"
send "yes\r"
expect "Press Enter to begin installation or Ctrl-C to cancel."
send "\r"
expect "Register and start installed services(s) after installation(Select yes, the Installer will create necessary entries in your system autostart or generate a launching script, so that the installed service(s) can be ready before the Horizon Client starts)"
send "no\r"
expect "Do you want to check your system compatibilities for Horizon Client, this Scan will NOT collect any of your data?"
send "no\r"

interact
