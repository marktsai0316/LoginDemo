/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/*++

Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  SpsDcmi.h

Abstract:

  SPS DCMI Protocol

--*/
#ifndef _EFI_DCMI_H_
#define _EFI_DCMI_H_

#define EFI_DCMI_PROTOCOL_GUID \
{ \
    0x856f8ca6, 0x2fe, 0x45f5, {0x8a, 0xbe, 0x80, 0x74, 0x92, 0x5b, 0x1a, 0x8d} \
}

typedef struct
{
  UINT8     DcmiEnable;
} EFI_DCMI_PROTOCOL;

extern EFI_GUID gEfiDcmiProtocolGuid;

#endif // _EFI_SPS_DCMI_H_
