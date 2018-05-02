
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
//typedef struct _AMI_SDL_SIO_DATA
//    AMI_SDL_TBL_HEADER          Header; //Signature ="$SIODATA"
//    UINT64                      GlobalSioFlags; //TBD 
//    UINTN                       SioCount;    
//    AMI_SIO_DEV_INFO            SioDev[SioCount];
//} AMI_SDL_SIO_DATA;
unsigned char SioSdlData[] = {
	//AMI_SDL_TABLE_HEADER

	0x24, 0x53, 0x49, 0x4f, 0x44, 0x41, 0x54, 0x41, 	//TblSignature
	0x24, 0x1, 0x0, 0x0, 	//TblLength
	0x5c, 	//TblChecksum
	0x0, 0x0, 0x0, 	//Reserved
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	//GlobalSioFlags
	0x1, 0x0, 0x0, 0x0, 	//SioCount
//SIODevice - AST2400
	0x7, 0x0, 0x0, 0x0, 	//LpcBridgeIndex
	0x1, 	//StdSioType
	0x0, 	//IsaLpcBridgeBusNumber
	0x0, 	//IsaLpcBridgeDeviceNumber
	0x0, 	//IsaLpcBridgeFunctionNumber
	0x4e, 0x0, 	//IndexPort
	0x4f, 0x0, 	//DataPort
	0x7, 	//DevSelReg
	0x30, 	//ActivateReg
	0x1, 	//ActivateVal
	0x0, 	//DeActivateVal
	0x60, 	//BaseHiReg1
	0x61, 	//BaseLoReg1
	0x62, 	//BaseHiReg2
	0x63, 	//BaseLoReg2
	0x70, 	//Irq1Reg
	0x72, 	//Irq2Reg
	0x74, 	//Dma1Reg
	0x75, 	//Dma2Reg
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //GlobalRegFlag
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, //LocalRegFlag

//EnterConfig

	0x1,	//OpType
	0x2, 	//InstrCount
	0x1,	0x1,	
	0xa5, 	//Instruction
	0x1,	0x1,	
	0xa5, 	//Instruction
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	//Padding

//ExitConfig

	0x1,	//OpType
	0x1, 	//InstrCount
	0x1,	0x1,	
	0xaa, 	//Instruction
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	//Padding
	0x54, 0x65, 0x73, 0x74, 0x20, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x0, 0x0, 0x0, 0x0, 0x0, 	//SmbiosInfo
	0x4, 0x0, 0x0, 0x0, 	//LogicalDevCount

//AMI_SDL_LOGICAL_DEV_INFO - Com1

	0x6, 0x0, 0x0, 0x0, 	//SIO_DEV_TYPE
	0x2, 	//Logical Device Number
	0x0, 	//Unique ID 
	0x1, 0x5, 	//Pnp ID
	0x1, 	//Implemented
	0x1, 	//Has Setup
	0x0, 	//SIO_RES_Flag
	0x55, 0x41, 0x52, 0x31, 0x0, 	//AslName
	0x0, 0x0, 	//ResBaseAddr1
	0x0, 0x0, 	//ResBaseAddr2
	0x0, 	//ResLength1
	0x0, 	//ResLength2
	0x0, 0x0, 	//IRQLink1
	0x0, 0x0, 	//IRQLink2
	0x0, 	//DMALink1
	0x0, 	//DMALink2
	0x1, 0x0, 0x0, 0x0, 	//InitRoutine

//AMI_SDL_LOGICAL_DEV_INFO - Com2

	0x6, 0x0, 0x0, 0x0, 	//SIO_DEV_TYPE
	0x3, 	//Logical Device Number
	0x1, 	//Unique ID 
	0x1, 0x5, 	//Pnp ID
	0x1, 	//Implemented
	0x1, 	//Has Setup
	0x0, 	//SIO_RES_Flag
	0x55, 0x41, 0x52, 0x32, 0x0, 	//AslName
	0x0, 0x0, 	//ResBaseAddr1
	0x0, 0x0, 	//ResBaseAddr2
	0x0, 	//ResLength1
	0x0, 	//ResLength2
	0x0, 0x0, 	//IRQLink1
	0x0, 0x0, 	//IRQLink2
	0x0, 	//DMALink1
	0x0, 	//DMALink2
	0x1, 0x0, 0x0, 0x0, 	//InitRoutine

//AMI_SDL_LOGICAL_DEV_INFO - Lpc2Ahb

	0x0, 0x0, 0x0, 0x0, 	//SIO_DEV_TYPE
	0xd, 	//Logical Device Number
	0x2, 	//Unique ID 
	0x8, 0xc, 	//Pnp ID
	0x1, 	//Implemented
	0x0, 	//Has Setup
	0x80, 	//SIO_RES_Flag
	0x4c, 0x50, 0x43, 0x32, 0x0, 	//AslName
	0x0, 0x0, 	//ResBaseAddr1
	0x0, 0x0, 	//ResBaseAddr2
	0x0, 	//ResLength1
	0x0, 	//ResLength2
	0x0, 0x0, 	//IRQLink1
	0x0, 0x0, 	//IRQLink2
	0x0, 	//DMALink1
	0x0, 	//DMALink2
	0x2, 0x0, 0x0, 0x0, 	//InitRoutine

//AMI_SDL_LOGICAL_DEV_INFO - Mailbox

	0x0, 0x0, 0x0, 0x0, 	//SIO_DEV_TYPE
	0xe, 	//Logical Device Number
	0x3, 	//Unique ID 
	0x8, 0xc, 	//Pnp ID
	0x1, 	//Implemented
	0x0, 	//Has Setup
	0x0, 	//SIO_RES_Flag
	0x4d, 0x41, 0x49, 0x4c, 0x0, 	//AslName
	0x40, 0xa, 	//ResBaseAddr1
	0x0, 0x0, 	//ResBaseAddr2
	0x10, 	//ResLength1
	0x0, 	//ResLength2
	0x0, 0x0, 	//IRQLink1
	0x0, 0x0, 	//IRQLink2
	0x0, 	//DMALink1
	0x0, 	//DMALink2
	0x3, 0x0, 0x0, 0x0, 	//InitRoutine
};

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
