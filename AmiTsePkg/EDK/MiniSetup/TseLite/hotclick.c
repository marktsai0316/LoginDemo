//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/hotclick.c $
//
// $Author: Rajashakerg $
//
// $Revision: 1 $
//
// $Date: 6/29/11 5:01a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hotclick.c
//
// Description:	This file contains code to handle hotclick operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
extern BOOLEAN IsPageModal(UINT32 PgIndex);

HOTCLICK_METHODS gHotClick =
{
	(OBJECT_METHOD_CREATE)HotClickCreate,
	(OBJECT_METHOD_DESTROY)HotClickDestroy,
	(OBJECT_METHOD_INITIALIZE)HotClickInitialize,
	(OBJECT_METHOD_DRAW)HotClickEmptyMethod,
	(OBJECT_METHOD_HANDLE_ACTION)HotClickHandleAction,
	(OBJECT_METHOD_SET_CALLBACK)HotClickSetCallback
};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotClickCreate
//
// Description:	Function create a HotClick, which uses the Object functions.
//
// Input:		HOTCLICK_DATA **object
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HotClickCreate( HOTCLICK_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(HOTCLICK_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gObject.Create((void**) object );

	if (EFI_ERROR(Status))
	{
		MemFreePointer( (VOID **)object );
		return Status;
	}

	(*object)->Methods = &gHotClick;

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotClickDestroy
//
// Description:	Function destroy a HotClick, which uses the Object functions.
//
// Input:		HOTCLICK_DATA *hotkey, BOOLEAN freeMem
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HotClickDestroy( HOTCLICK_DATA *hotclick, BOOLEAN freeMem )
{

	gObject.Destroy( hotclick, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&hotclick );

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotClickInitialize
//
// Description:	Function Initialize a Hotclick, which uses the Object functions.
//
// Input:		HOTCLICK_DATA *hotkey, VOID *data
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HotClickInitialize( HOTCLICK_DATA *hotclick, VOID *data )
{
	HOTCLICK_TEMPLATE *template = (HOTCLICK_TEMPLATE *)data;

//	MemCopy( &hotclick->HotClickData.MouseInfo, &(template->MouseInfo), sizeof(MOUSE_INFO) );
	hotclick->HotClickData.Xo = template->Xo;
	hotclick->HotClickData.Yo = template->Yo;
	hotclick->HotClickData.Xn = template->Xn;
	hotclick->HotClickData.Yn = template->Yn;

	hotclick->BasePage = template->BasePage;

	return EFI_SUCCESS;
}

EFI_STATUS HotClickEmptyMethod( HOTCLICK_DATA *hotclick )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotClickHandleAction
//
// Description:	Function to handle the HotClick actions.
//
// Input:		HOTCLICK_DATA *hotkey, ACTION_DATA *action
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HotClickHandleAction( HOTCLICK_DATA *hotclick, ACTION_DATA *action )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	PAGE_DATA *page=NULL;
	
	if ( action->Input.Type != ACTION_TYPE_MOUSE )
		return Status;
    
    page = gApp->PageList[gApp->CurrentPage];
    if(!page)
       return Status;

    if(IsPageModal(page->PageData.PageID)){
       return Status;
    }
	if  (
		((action->Input.Data.MouseInfo.Left >= hotclick->HotClickData.Xo) && (action->Input.Data.MouseInfo.Left <= hotclick->HotClickData.Xn)) &&
		((action->Input.Data.MouseInfo.Top >= hotclick->HotClickData.Yo) && (action->Input.Data.MouseInfo.Top <= hotclick->HotClickData.Yn))
	    )
	{
		if ( hotclick->Callback )
			hotclick->Callback( hotclick->Container, hotclick, hotclick->Cookie );

		gAction.ClearAction( action );
		Status = EFI_SUCCESS;
	}

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotClickSetCallback
//
// Description:	Function to set callback.
//
// Input:		HOTCLICK_DATA *hotkey, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HotClickSetCallback( HOTCLICK_DATA *hotclick, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gObject.SetCallback( hotclick, container, callback, cookie );
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
