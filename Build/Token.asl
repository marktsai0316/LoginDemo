
//-------- DO NOT EDIT THIS FILE --------
//
// FILE WAS GENERATED AUTOMATICALY USING AMISDL v7.04.0230 (���� 25 2018,16:31:29)
//
//-------- DO NOT EDIT THIS FILE --------
//****************************************************************************
//****************************************************************************
//**                                                                        **
//**         (C)Copyright 1985 - 2018, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                    5555 Oakbrook Pkwy, Norcross, GA 30092              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

Name(ENTK, 0xa5)	// ASL alias for SIO Config Mode Enter Value.
Name(EXTK, 0xaa)	// ASL alias for SIO Config Mode Exit Value.
Name(IO1B, 0xa00)	// Base Address of SWC Controller.
Name(IO1L, 0x10)	// Length of SWC Controller.
Name(IO2B, 0xa10)	// Base Address of PM1B_EVT Controller.
Name(IO2L, 0x10)	// Length of PM1B_EVT Controller.
Name(IO3B, 0xa20)	// Base Address of PM1B_CNT Controller.
Name(IO3L, 0x10)	// Length of PM1B_CNT Controller.
Name(IO4B, 0xa30)	// Base Address of GPE1_BLK Controller.
Name(IO4L, 0x10)	// Length of GPE1_BLK Controller.
Name(IO5B, 0xa40)	// Base Address of MAILBOX Controller.
Name(IO5L, 0x10)	// Length of MAILBOX Controller.
Name(SP1O, 0x4e)	// Super IO Index/Data configuration port for ASL.
Name(KBFG, 0x0)	// Keyboard wake-up flag.
Name(MSFG, 0x0)	// Mouse wake-up flag.
Name(IOES, 0x0)	// It is used similar to IOST, when Device's DCAT > 0x0F , then it will be used.
Name(IPBT, 0xe4)	// Aligned base address for  BT Control register.
Name(IBUF, 0xe5)	// Aligned base address for BT buffer.
Name(BTIM, 0xe6)	// Aligned base address for  BT interrupt mask register.
Name(IDTP, 0xca2)	// Aligned base address for IPMI KCS Data Port.
Name(ICDP, 0xca3)	// Aligned base address for IPMI KCS Command Port.
Name(SRVV, 0x200)	// IPMI Specification ASL update Variable
Name(BSMI, 0xc0)	// Start value of Data to be written to SW SMI port to invoke BMC ACPI SW SMI handler.
Name(ASSB, 0x0)	// ACPI Sleep State Buffer for BIOS Usage.
Name(AOTB, 0x0)	// ACPI OS Type Buffer for BIOS Usage.
Name(AAXB, 0x0)	// ACPI Auxiliary Buffer for BIOS Usage.
Name(PEHP, 0x1)	// _OSC: Pci Express Native Hot Plug Control
Name(PEPM, 0x1)	// _OSC: Pci Express Native Power Management Events control
Name(PEER, 0x1)	// _OSC: Pci Express Advanced Error Reporting control
Name(PECS, 0x1)	// _OSC: Pci Express Capability Structure control
Name(ITKE, 0x0)	// This will be overridden by the ITK module.
Name(MBEC, 0xffff)	// EC presence (0) or abssence (0xFFFF) in system. EC declare I/O port \ 62/66, also declared as MotherBoard Resources in rmisc.asl,\ as EC's resource. To avoid conflicts redefine \ to 0 in EC mopdule, if present
Name(PEBS, 0x80000000)	// Pci Express Base Aliase to use in PCIeAccess.ASL
Name(PELN, 0x10000000)	// 
Name(SRSI, 0xb2)	// 
Name(CSMI, 0x61)	// 
Name(DSSP, 0x0)	// It is for ASL usage related to DISABLE_SOFT_SET_PREV 
Name(FHPP, 0x0)	// It is for ASL usage related to FORCE_HDD_PASSWORD_PROMPT 
Name(SMIA, 0xb2)	// Add a name of smiport for asl using
Name(SMIB, 0xb3)	// Add a name of smiport for asl using
Name(OFST, 0x35)	// Add a name of smiport for asl using
Name(TRST, 0x2)	// Platform transition for PPI request under O.S. 0: None 1: Shutdown 2: Reboot 3: OS Vendor Specific
Name(TCMF, 0x0)	// TPM ASL update Variable
Name(TMF1, 0x0)	// TPM ASL update Variable
Name(TMF2, 0x0)	// TPM ASL update Variable
Name(TMF3, 0x0)	// TPM ASL update Variable
Name(TTPF, 0x1)	// 
Name(DTPT, 0x0)	// 
Name(TTDP, 0x0)	// 
Name(TPMB, 0xffffffff)	// 
Name(TPMC, 0xffffffff)	// 
Name(TPMM, 0xfed40000)	// 
Name(FTPM, 0xffffffff)	// 
Name(AMDT, 0x0)	// 
Name(TPMF, 0x0)	// 
Name(SRCB, 0xfed1c000)	// 
Name(SRCL, 0x4000)	// 
Name(SUSW, 0xff)	// See the 'SUS_SW_GPI' TOKEN in SB.SDL.
Name(PMBA, 0x400)	// ASL alias for ACPI I/O base address.
Name(PMLN, 0x80)	// Power Management registers block length
Name(SMIP, 0xb2)	// Token to go to ASL Name Definitions
Name(APCB, 0xfec00000)	// Default I/O APIC(s) memory start address, bytes\0x0FEC00000 - default, 0 - I/O APIC's disabled
Name(APCL, 0x100000)	// I/O APIC(s) memory decoded range, bytes\0x1000 - default,\0 - I/O APIC's not decoded 
Name(PM30, 0x430)	// SMI Control Register
Name(GPBS, 0x500)	// ASL alias for GPIO base Address
Name(GPLN, 0x80)	// GPIO Register Block length
Name(SMBS, 0x580)	// SMBus I/O Registes Base Address
Name(SMBL, 0x20)	// SMBus I/O Registes Range
Name(SHPC, 0x0)	// _OSC: Standard Hot Plug Controller (SHPC) Native Hot Plug control. Platform does not have SHPC.
//-------- DO NOT EDIT THIS FILE --------
//
// FILE WAS GENERATED AUTOMATICALY USING AMISDL v7.04.0230 (���� 25 2018,16:31:29)
//
//-------- DO NOT EDIT THIS FILE --------
//****************************************************************************
//****************************************************************************
//**                                                                        **
//**         (C)Copyright 1985 - 2018, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                    5555 Oakbrook Pkwy, Norcross, GA 30092              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
