:: DFU 
:: set FW_PATH=..\..\..\..\X-B1.0\V04_MCU_FW_20160427
:: set BIN_PATH=%FW_PATH%\bin
:: set OUTPUT_PATH=%FW_PATH%\Output

:: %BIN_PATH%\DfuGenerate.exe 0x8003000 %OUTPUT_PATH%\TY_STM_Base_Proj_V1.bin

:: del %OUTPUT_PATH%\STM32_FW_Laser_Flash.bin
:: fsutil  file createnew %OUTPUT_PATH%\STM32_FW_Laser_Flash.bin 0x3000
:: %BIN_PATH%\cat %OUTPUT_PATH%\TY_STM_Base_Proj_V1.bin >> %OUTPUT_PATH%\STM32_FW_Laser_Flash.bin
:: %BIN_PATH%\hbin .\Obj\mcu_dfu.bin %OUTPUT_PATH%\STM32_FW_Laser_Flash.bin

set DFU_BIN_PATH=..\..\dfu\Project\usb_Device_Firmware_Upgrade\RVMDK\Obj

..\bin\DfuGenerate.exe 0x8003000 .\Output\HID_Base_Proj_V1.bin
del .\Output\STM32_FW_Flash.bin
fsutil  file createnew .\Output\STM32_FW_Flash.bin 0x3000
..\bin\cat .\Output\HID_Base_Proj_V1.bin>> .\Output\STM32_FW_Flash.bin
..\bin\hbin %DFU_BIN_PATH%\mcu_dfu.bin .\Output\STM32_FW_Flash.bin





::pause