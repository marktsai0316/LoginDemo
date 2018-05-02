//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG/EMpTcmDxe.c 4     5/09/12 6:40p Fredericko $
//
// $Revision: 4 $
//
// $Date: 5/09/12 6:40p $
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  EMpTpmDxe.c
//
// Description:
//        Contains function that help with making legacy TCG calls
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include "AmiTcg\TcgTpm12.h"
#include <AmiTcg\TpmLib.h>
#include "Protocol\TpmDevice.h"
#include "AmiTcg\TcgMisc.h"
#include<Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include<Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include "token.h"

#define _CR( Record, TYPE,\
     Field )((TYPE*) ((CHAR8*) (Record)- (CHAR8*) &(((TYPE*) 0)->Field)))

#define TPM_DXE_PRIVATE_DATA_FROM_THIS( this )\
    _CR( this, TPM_DXE_PRIVATE_DATA, TpmInterface )

typedef struct _TPM_DXE_PRIVATE_DATA
{
    EFI_TPM_DEVICE_PROTOCOL TpmInterface;
} TPM_DXE_PRIVATE_DATA;

static UINTN                  FuncID;
static TPMTransmitEntryStruct EmptyBuf;
static UINT32                 Ret;
UINT8                         *SHA_ARRAY;


GLOBAL_REMOVE_IF_UNREFERENCED IA32_SEGMENT_DESCRIPTOR mGdtEntries[] = {
/* selector { Global Segment Descriptor                              } */
/* 0x00 */  {{0,      0,  0,  0,    0,  0,  0,  0,    0,  0, 0,  0,  0}}, //null descriptor
/* 0x08 */  {{0xffff, 0,  0,  0x3,  1,  0,  1,  0xf,  0,  0, 1,  1,  0}}, //linear data segment descriptor
/* 0x10 */  {{0xffff, 0,  0,  0xf,  1,  0,  1,  0xf,  0,  0, 1,  1,  0}}, //linear code segment descriptor
/* 0x18 */  {{0xffff, 0,  0,  0x3,  1,  0,  1,  0xf,  0,  0, 1,  1,  0}}, //system data segment descriptor
/* 0x20 */  {{0xffff, 0,  0,  0xb,  1,  0,  1,  0xf,  0,  0, 1,  1,  0}}, //system code segment descriptor
/* 0x28 */  {{0,      0,  0,  0,    0,  0,  0,  0,    0,  0, 0,  0,  0}}, //spare segment descriptor
/* 0x30 */  {{0xffff, 0,  0,  0x3,  1,  0,  1,  0xf,  0,  0, 1,  1,  0}}, //system data segment descriptor
/* 0x38 */  {{0xffff, 0,  0,  0xb,  1,  0,  1,  0xf,  0,  1, 0,  1,  0}}, //system code segment descriptor
/* 0x40 */  {{0,      0,  0,  0,    0,  0,  0,  0,    0,  0, 0,  0,  0}}, //spare segment descriptor
};

GLOBAL_REMOVE_IF_UNREFERENCED CONST IA32_DESCRIPTOR mGdt = {
  sizeof (mGdtEntries) - 1,
  (UINTN) mGdtEntries
  };





//**********************************************************************
//<AMI_PHDR_START>
//
// Name: EMpTcmDxeInit
//
// Description: Call to OEM driver to initialize TPM.
//
// Input:       IN  EFI_TPM_DEVICE_PROTOCOL   *This
//
// Returns:     EFI_STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI EMpTcmDxeInit(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    TPM_DXE_PRIVATE_DATA *Private;
    EFI_PHYSICAL_ADDRESS TPM_Base = (EFI_PHYSICAL_ADDRESS)PORT_TPM_IOMEMBASE;

    FuncID  = MA_FUNCTION_INIT;
    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );
    TcmDxeCallMPDriver( FuncID, &EmptyBuf, &Ret );

    if ( !Ret )
    {
        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  EMpTcmDxeClose
//
// Description: Close TPM connection for locality 0
//
// Input:       IN  PEI_TPM_PPI               *This,
//              IN  EFI_PEI_SERVICES          **PeiServices
//
// Output:      EFI STATUS
///
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI EMpTcmDxeClose(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    TPM_DXE_PRIVATE_DATA *Private;

    FuncID  = MP_FUNCTION_CLOSE;
    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );
    TcmDxeCallMPDriver( FuncID, &EmptyBuf, &Ret );

    if ( !Ret )
    {
        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}




//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name:  EMpTcmDxeGetStatusInfo
//
// Description: GetStatus Info from MP driver
//
// Input:       IN  PEI_TPM_PPI               *This,
//              IN  EFI_PEI_SERVICES          **PeiServices
//
// Output:      EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI  EMpTcmDxeGetStatusInfo(
    IN EFI_TPM_DEVICE_PROTOCOL   * This
    )
{
    TPM_DXE_PRIVATE_DATA *Private;

    FuncID  = MP_FUNCTION_GET_STATUS;
    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );
    TcmDxeCallMPDriver( FuncID, &EmptyBuf, &Ret );

    if ( !Ret )
    {
        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}





//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name:  EMpTcmDxeGetStatusInfo
//
// Description: GetStatus Info from MP driver
//
// Input:       IN      PEI_TPM_PPI               *This,
//              IN      EFI_PEI_SERVICES          **PeiServices
//
// Output:     EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN
EFIAPI  EMpTcmDxeSHA1Setup (
IN EFI_TPM_DEVICE_PROTOCOL *This,
IN UINTN NoInBuffers,
IN TPM_TRANSMIT_BUFFER       *InBuffers,
IN OUT void                        **Buffer
)
{

    TPM_1_2_CMD_HEADER *SHA1HeaderCheck;

    SHA1HeaderCheck = (TPM_1_2_CMD_HEADER*)InBuffers->Buffer;

    if ( SHA1HeaderCheck->Ordinal !=TPM_H2NL(TCM_ORD_SHA1CompleteExtend ) &&
         SHA1HeaderCheck->Ordinal !=TPM_H2NL( TCM_ORD_SHA1Update ))
    {
        //no need to modify buffers just pass it through
        return FALSE;
    }

    //if we get here it means the buffer needs to be modified!
    gBS->AllocatePool( EfiBootservicesData,
                       InBuffers[0].Size + InBuffers[1].Size,
                       &SHA_ARRAY );

    gBS->CopyMem( &SHA_ARRAY[0],
                  InBuffers[0].Buffer,
                  InBuffers[0].Size );

    gBS->CopyMem( &SHA_ARRAY[InBuffers[0].Size],
                  InBuffers[1].Buffer,
                  InBuffers[1].Size );
    *Buffer =  SHA_ARRAY;
    return TRUE;
}



//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name:  EMpTcmDxeTransmit
//
// Description: Dxe Transmit Tcg Data
//
// Input:    IN      EFI_TPM_DEVICE_PROTOCOL   *This,
//           IN      UINTN                     NoInBuffers,
//           IN      TPM_TRANSMIT_BUFFER       *InBuffers,
//           IN      UINTN                     NoOutBuffers,
//           IN OUT  TPM_TRANSMIT_BUFFER       *OutBuffers
//
// Output:     EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI EMpTcmDxeTransmit(
    IN EFI_TPM_DEVICE_PROTOCOL *This,
    IN UINTN                   NoInBuffers,
    IN TPM_TRANSMIT_BUFFER     *InBuffers,
    IN UINTN                   NoOutBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutBuffers )
{
    TPM_DXE_PRIVATE_DATA   *Private;
    TPMTransmitEntryStruct FillESI;
    UINTN                  FuncID = (UINTN)MP_FUNCTION_TRANSMIT;
    UINT32                 Ret;
    UINT8                  *SHA_ARRAY_OUT = NULL;
    BOOLEAN                FillBuff   = FALSE;
    BOOLEAN                Other      = FALSE;
    UINTN                  i = 0, loc = 0;
    UINT8                  *Tpm_SHA_ARRAY= NULL;
    EFI_STATUS             Status;
    IA32_DESCRIPTOR        Gdtr;


    if(NoInBuffers == 0 || InBuffers == NULL || NoOutBuffers == 0 || OutBuffers == NULL)
    return EFI_INVALID_PARAMETER;

    FillESI.dwInLen = 0;
    FillESI.dwOutLen = 0;

    for (; i < NoInBuffers; i++ )
   	{
       	FillESI.dwInLen += (UINT32)InBuffers[i].Size;
   	}

	Status = gBS-> AllocatePool( EfiBootservicesData, FillESI.dwInLen, &Tpm_SHA_ARRAY);
    if(EFI_ERROR(Status))return Status;

    for (i = 0; i < NoOutBuffers; i++ )
   	{
      FillESI.dwOutLen += (UINT32)OutBuffers[i].Size;
	}

    Status = gBS-> AllocatePool( EfiBootservicesData, FillESI.dwOutLen, &SHA_ARRAY_OUT );
    if(EFI_ERROR(Status))return Status;


    for (i = 0; i < NoInBuffers; i++ )
    {
        gBS->CopyMem(Tpm_SHA_ARRAY + loc,
                     InBuffers[i].Buffer,
                     InBuffers[i].Size );

        loc += InBuffers[i].Size;
    }

    FillESI.pbInBuf  = (UINT32)(EFI_PHYSICAL_ADDRESS) Tpm_SHA_ARRAY;
    FillESI.pbOutBuf = (UINT32)(EFI_PHYSICAL_ADDRESS) SHA_ARRAY_OUT;

    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );
    AsmReadGdtr (&Gdtr);
    AsmWriteGdtr (&mGdt);
    TcmDxeCallMPDriver( FuncID, &FillESI, &Ret );
    AsmWriteGdtr (&Gdtr);

    if ( Tpm_SHA_ARRAY != NULL )
    {
        gBS->FreePool( Tpm_SHA_ARRAY );
    }

    loc = 0;

    for (i=0; i < NoOutBuffers; i++ )
    {
       gBS->CopyMem( OutBuffers[i].Buffer,
                    &SHA_ARRAY_OUT[loc],
                    OutBuffers[i].Size );
       loc += (UINTN)OutBuffers[i].Size;
    }

    if ( SHA_ARRAY_OUT != NULL )
    {
        gBS->FreePool( SHA_ARRAY_OUT );
    }

    return EFI_SUCCESS;
}




static TPM_DXE_PRIVATE_DATA mTpmPrivate = {
    {
        EMpTcmDxeInit,
        EMpTcmDxeClose,
        EMpTcmDxeGetStatusInfo,
        EMpTcmDxeTransmit
    }
};


EFI_GUID                    legTcgGuid = AMI_TCG_RESETVAR_HOB_GUID;
//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name:  TcmDxeEntry
//
// Description: TpmDxeEntry, Init TpmDxeDriver and install protocol
//
// Input:      EFI_HANDLE                ImageHandle
//             EFI_SYSTEM_TABLE          *SystemTable
//
// Output:     EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI TcmDxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS TPM_Base = (EFI_PHYSICAL_ADDRESS)PORT_TPM_IOMEMBASE;
    FAR32LOCALS     	 *TempLoc   = NULL;
    EFI_GUID        gMpDriverHobGuid = EFI_TCG_MPDriver_HOB_GUID;

    TempLoc = (FAR32LOCALS*)LocateATcgHob( gST->NumberOfTableEntries,
                                           gST->ConfigurationTable,
                                           &gMpDriverHobGuid );


    if(TempLoc->Offset == 0) return EFI_NOT_FOUND;

    Prepare2Thunkproc( TempLoc->Offset, TempLoc->Selector );
    Status = gBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiTpmDeviceProtocolGuid,
        &mTpmPrivate.TpmInterface,
        NULL
        );

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
