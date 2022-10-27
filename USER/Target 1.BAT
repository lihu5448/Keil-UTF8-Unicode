SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;D:\Program Files (x86)\VMware\VMware Workstation\bin\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Bandizip\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files\IDM Computer Solutions\UltraEdit;C:\Program Files\TortoiseGit\bin;C:\mingw64\bin;D:\Program Files\Calibre2\;D:\Program Files\Git\cmd;C:\Users\lihu\AppData\Local\Microsoft\WindowsApps;;D:\Users\lihu\AppData\Local\Programs\Microsoft VS Code\bin
SET CPU_TYPE=N32G031F8
SET CPU_VENDOR=Nationstech
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_n32g031.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_n32g031._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\n32g030_it.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\delay.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\led.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\modbus_slave.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\init.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\flash.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\proc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\N32G030F6S7.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\N32G030F6S7.axf" --i32combined --output ".\Objects\N32G030F6S7.hex"
