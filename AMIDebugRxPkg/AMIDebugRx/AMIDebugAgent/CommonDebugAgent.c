//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//
// $Header: /AptioV/BIN/AMIDebugRx/AMIDebugAgent/CommonDebugAgent.c 4     1/07/15 9:43a Jekekumarg $
//
// $Revision: 4 $
//
// $Date: 1/07/15 9:43a $
//*****************************************************************
//
// Revision History
// ----------------
// $Log: /AptioV/BIN/AMIDebugRx/AMIDebugAgent/CommonDebugAgent.c $
// 
// 4     1/07/15 9:43a Jekekumarg
// Added Warning Message for SMM EXIT when SMM Read Save state resgister
// fails
// as a part of the EIP-186481
// 
//
//*****************************************************************
//*****************************************************************
#include "token.h"

#ifndef REDIRECTION_ONLY_MODE
#define REDIRECTION_ONLY_MODE 0
#endif

#ifndef PeiDebugger_SUPPORT
#define PeiDebugger_SUPPORT 0
#endif

#ifndef GENERIC_USB_CABLE_SUPPORT
#define GENERIC_USB_CABLE_SUPPORT 0
#endif

#ifndef SMM_DEBUG_SUPPORT
#define SMM_DEBUG_SUPPORT 0
#endif

UINTN	SMMExitBreakpoint = 0;
UINT8   SMMExitBPOpcode = 0;
UINT8 	PMModeEnabled = 0;
UINT8 	gSMMEntryBreak = 0;
UINT8 	gSMMExitBreak = 0;
UINT8 	gSMMRuntime = 0;
UINTN 	SMMDxeDbgDataBaseAddr = 0;
UINT8 	SMMExitMessage[] = "AMIDebugger: Unable to Get SMM Save State registers hence SMM Exit Breakpoint can't be set...\nTo set SMM Exit BreakPoint manually go to the return address and Put Breakpoint...\n";
UINTN 	mSavedDebugRegisters[6];

volatile UINTN RedirectionOnlyEnabled = REDIRECTION_ONLY_MODE;
volatile UINTN PeiDebuggerEnabled = PeiDebugger_SUPPORT;
//volatile UINTN gGenericUsbSupportEnabled = GENERIC_USB_CABLE_SUPPORT;
volatile UINTN gSmmDebuggingSupport = SMM_DEBUG_SUPPORT;

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
