*** Fatal System Error: 0x000000d5
                       (0xFAB22C50,0x00000000,0x911DB830,0x00000000)

Driver at fault: 
***    win32k.sys - Address 911DB830 base at 91110000, DateStamp 4ce7900f
.
Break instruction exception - code 80000003 (first chance)

A fatal system error has occurred.
Debugger entered on first try; Bugcheck callbacks have not been invoked.

A fatal system error has occurred.

Connected to Windows 7 7601 x86 compatible target at (Sat Feb 13 16:48:29.650 2016 (UTC + 0:00)), ptr64 FALSE
Loading Kernel Symbols
...........

Press ctrl-c (cdb, kd, ntsd) or ctrl-break (windbg) to abort symbol loads that take too long.
Run !sym noisy before .reload to track down problems loading symbols.

....................................................
................................................................
.......
Loading User Symbols
.............

Press ctrl-c (cdb, kd, ntsd) or ctrl-break (windbg) to abort symbol loads that take too long.
Run !sym noisy before .reload to track down problems loading symbols.

........................
Loading unloaded module list
............
*******************************************************************************
*                                                                             *
*                        Bugcheck Analysis                                    *
*                                                                             *
*******************************************************************************

Use !analyze -v to get detailed debugging information.

BugCheck D5, {fab22c50, 0, 911db830, 0}

*** WARNING: Unable to verify checksum for Trigger.exe
*** ERROR: Module load completed but symbols could not be loaded for Trigger.exe
Probably caused by : win32k.sys ( win32k!hbmSelectBitmap+ca )

Followup: MachineOwner
---------

nt!RtlpBreakWithStatusInstruction:
82864d00 cc              int     3
kd> !analyze -v
*******************************************************************************
*                                                                             *
*                        Bugcheck Analysis                                    *
*                                                                             *
*******************************************************************************

DRIVER_PAGE_FAULT_IN_FREED_SPECIAL_POOL (d5)
Memory was referenced after it was freed.
This cannot be protected by try-except.
When possible, the guilty driver's name (Unicode string) is printed on
the bugcheck screen and saved in KiBugCheckDriver.
Arguments:
Arg1: fab22c50, memory referenced
Arg2: 00000000, value 0 = read operation, 1 = write operation
Arg3: 911db830, if non-zero, the address which referenced memory.
Arg4: 00000000, (reserved)

Debugging Details:
------------------


READ_ADDRESS:  fab22c50 Special pool

FAULTING_IP: 
win32k!hbmSelectBitmap+ca
911db830 854748          test    dword ptr [edi+48h],eax

MM_INTERNAL_CODE:  0

IMAGE_NAME:  win32k.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  4ce7900f

MODULE_NAME: win32k

FAULTING_MODULE: 91110000 win32k

DEFAULT_BUCKET_ID:  INTEL_CPU_MICROCODE_ZERO

BUGCHECK_STR:  0xD5

PROCESS_NAME:  Trigger.exe

CURRENT_IRQL:  2

ANALYSIS_VERSION: 6.3.9600.17336 (debuggers(dbg).150226-1500) amd64fre

TRAP_FRAME:  88f9197c -- (.trap 0xffffffff88f9197c)
ErrCode = 00000000
eax=04000000 ebx=00000001 ecx=00000000 edx=faa1e728 esi=ff80ada8 edi=fab22c08
eip=911db830 esp=88f919f0 ebp=88f91a20 iopl=0         nv up ei ng nz na po nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010282
win32k!hbmSelectBitmap+0xca:
911db830 854748          test    dword ptr [edi+48h],eax ds:0023:fab22c50=????????
Resetting default scope

LAST_CONTROL_TRANSFER:  from 828de589 to 82864d00

STACK_TEXT:  
88f914dc 828de589 00000003 96ad31c1 00000065 nt!RtlpBreakWithStatusInstruction
88f9152c 828df085 00000003 8b693a58 0000001f nt!KiBugCheckDebugBreak+0x1c
88f918f0 8286ad67 00000050 fab22c50 00000000 nt!KeBugCheck2+0x68b
88f91964 82844aa8 00000000 fab22c50 00000000 nt!MmAccessFault+0xbf
88f91964 911db830 00000000 fab22c50 00000000 nt!KiTrap0E+0xdc
88f91a20 911dbddf ff806f68 0185000f 00000001 win32k!hbmSelectBitmap+0xca
88f91aa4 911dc710 00000000 19c86aac 00000000 win32k!XDCOBJ::bCleanDC+0xaa
88f91ae0 911dc6ba 88f91b00 00000001 00000001 win32k!bDeleteDCInternalWorker+0x1b
88f91b0c 911de746 50010908 00000001 00000001 win32k!bDeleteDCInternal+0x30
88f91b28 911de942 00000bdc 00000bdc fa846e38 win32k!vCleanupDCs+0x2a
88f91b44 911db19a fa846e38 00000000 00000000 win32k!NtGdiCloseProcess+0x3f
88f91b64 911daee1 fa846e38 00000000 8b9ff720 win32k!GdiProcessCallout+0x151
88f91b80 82a1d7a5 8b693d40 00000000 96ad3f11 win32k!W32pProcessCallout+0x5d
88f91bfc 82a254b6 00000000 ffffffff 0024fe18 nt!PspExitThread+0x46f
88f91c24 828418ba ffffffff 00000000 0024fe24 nt!NtTerminateProcess+0x1fa
88f91c24 773d70b4 ffffffff 00000000 0024fe24 nt!KiFastCallEntry+0x12a
0024fe04 773d68d4 773ee1a7 ffffffff 00000000 ntdll!KiFastSystemCallRet
0024fe08 773ee1a7 ffffffff 00000000 00000000 ntdll!NtTerminateProcess+0xc
0024fe24 75932163 00000000 77e8f3b0 ffffffff ntdll!RtlExitUserProcess+0x85
0024fe38 5a7ee619 00000000 0024fe94 5a7eee79 kernel32!ExitProcessStub+0x12
0024fe44 5a7eee79 00000000 b92120f6 00000000 MSVCR120D!__crtExitProcess+0x19 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 776]
0024fe94 5a7eeea0 00000000 00000000 00000000 MSVCR120D!doexit+0x1a9 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 678]
0024fea8 000b1ee6 00000000 b80b8480 00000000 MSVCR120D!exit+0x10 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 417]
WARNING: Stack unwind information not available. Following frames may be wrong.
0024fef0 000b20bd 0024ff04 75933c45 7ffdf000 Trigger+0x11ee6
0024fef8 75933c45 7ffdf000 0024ff44 773f37f5 Trigger+0x120bd
0024ff04 773f37f5 7ffdf000 766cc07a 00000000 kernel32!BaseThreadInitThunk+0xe
0024ff44 773f37c8 000b1087 7ffdf000 00000000 ntdll!__RtlUserThreadStart+0x70
0024ff5c 00000000 000b1087 7ffdf000 00000000 ntdll!_RtlUserThreadStart+0x1b


STACK_COMMAND:  kb

FOLLOWUP_IP: 
win32k!hbmSelectBitmap+ca
911db830 854748          test    dword ptr [edi+48h],eax

SYMBOL_STACK_INDEX:  5

SYMBOL_NAME:  win32k!hbmSelectBitmap+ca

FOLLOWUP_NAME:  MachineOwner

IMAGE_VERSION:  6.1.7601.17514

FAILURE_BUCKET_ID:  0xD5_VRF_win32k!hbmSelectBitmap+ca

BUCKET_ID:  0xD5_VRF_win32k!hbmSelectBitmap+ca

ANALYSIS_SOURCE:  KM

FAILURE_ID_HASH_STRING:  km:0xd5_vrf_win32k!hbmselectbitmap+ca

FAILURE_ID_HASH:  {c18afd13-ae34-094e-a35a-2fa69da06b7c}

Followup: MachineOwner
---------

kd> r
eax=00000003 ebx=00000000 ecx=1e5424ed edx=00000060 esi=fffffffe edi=00000065
eip=82864d00 esp=88f914e0 ebp=88f9152c iopl=0         nv up ei pl zr na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00000246
nt!RtlpBreakWithStatusInstruction:
82864d00 cc              int     3
kd> k
ChildEBP RetAddr  
88f914dc 828de589 nt!RtlpBreakWithStatusInstruction
88f9152c 828df085 nt!KiBugCheckDebugBreak+0x1c
88f918f0 8286ad67 nt!KeBugCheck2+0x68b
88f91964 82844aa8 nt!MmAccessFault+0xbf
88f91964 911db830 nt!KiTrap0E+0xdc
88f91a20 911dbddf win32k!hbmSelectBitmap+0xca
88f91aa4 911dc710 win32k!XDCOBJ::bCleanDC+0xaa
88f91ae0 911dc6ba win32k!bDeleteDCInternalWorker+0x1b
88f91b0c 911de746 win32k!bDeleteDCInternal+0x30
88f91b28 911de942 win32k!vCleanupDCs+0x2a
88f91b44 911db19a win32k!NtGdiCloseProcess+0x3f
88f91b64 911daee1 win32k!GdiProcessCallout+0x151
88f91b80 82a1d7a5 win32k!W32pProcessCallout+0x5d
88f91bfc 82a254b6 nt!PspExitThread+0x46f
88f91c24 828418ba nt!NtTerminateProcess+0x1fa
88f91c24 773d70b4 nt!KiFastCallEntry+0x12a
0024fe04 773d68d4 ntdll!KiFastSystemCallRet
0024fe08 773ee1a7 ntdll!NtTerminateProcess+0xc
0024fe24 75932163 ntdll!RtlExitUserProcess+0x85
0024fe38 5a7ee619 kernel32!ExitProcessStub+0x12
0024fe44 5a7eee79 MSVCR120D!__crtExitProcess+0x19 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 776]
0024fe94 5a7eeea0 MSVCR120D!doexit+0x1a9 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 678]
0024fea8 000b1ee6 MSVCR120D!exit+0x10 [f:\dd\vctools\crt\crtw32\startup\crt0dat.c @ 417]
WARNING: Stack unwind information not available. Following frames may be wrong.
0024fef0 000b20bd Trigger+0x11ee6
0024fef8 75933c45 Trigger+0x120bd
0024ff04 773f37f5 kernel32!BaseThreadInitThunk+0xe
0024ff44 773f37c8 ntdll!__RtlUserThreadStart+0x70
0024ff5c 00000000 ntdll!_RtlUserThreadStart+0x1b
