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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/minisetupext.c $
//
// $Author: Arunsb $
//
// $Revision: 50 $
//
// $Date: 5/25/12 1:14a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MINISETUP.C
//
// Description:	This file contains code for entrypoint and setup loop
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include "Setup.h" // ZA0035

//Internal function definitions
VOID		MainSetupLoopInitHook(VOID);
VOID		InitGlobalPointers( VOID );
UINT16		_BootSetBootNowCount(VOID);
BOOLEAN		IsSoftKbdSupported(VOID);
CHAR16		*ReadPlatformLang( UINTN *Size );
BOOLEAN   	IsDisableESCinBBSMenu (VOID);
BOOLEAN SingleClickActivation (VOID); //EIP-139608 
extern BOOLEAN   		IsSupportDefaultForStringControl (VOID);
POSTMENU_TEMPLATE *gPostMenuData = NULL ;

UINT16 gPostMenuLevel = 0 ;
UINT16 gDynamicParentPage=0;

//EIP: 58925 Start
//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
BOOLEAN bSelectionChanged = FALSE;
UINT32 gPageNavCount = 0;
UINT32 gNavStartPage = 0;
static UINT16 gDisplayPageId = 0; //PageId which is currently displaying

#define MAX_NAVIGATION_DEPTH              20 //for breadcrumb trail
//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
typedef struct _NAV_PAGE_STACK{
	VOID *PageHandle;         		//Varies, HII Handle to the formset that contains this control
	UINT32 PageFormID;        	//Varies, Form ID within the formset for this page
	VOID *ParentPageHandle;  	//Varies, HII Handle to the formset that contains Parent Page control
	UINT32 PageParentFormID;	//Varies, Pagent Form ID within the formset for this page
} NAV_PAGE_STACK;

NAV_PAGE_STACK *NavPageStack = (NAV_PAGE_STACK *)NULL;
UINT32 NavPageStackSize = 0;
EFI_STATUS GetParentFormID(UINT16 ChildID, UINT16 *ParentID, UINT32 *StackIndex);
extern CHAR16  gPlatformLang [20];			//EIP97951

extern EFI_CONSOLE_CONTROL_PROTOCOL	*gConsoleControl;

//EIP: 58925 End
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupEntry
//
// Description:	This function prepares system so that setup can be
//              launched. Preparation mainly includes Setup data
//              fixup and variable details gathering.
//
// Input:		VOID
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MiniSetupEntry(VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;
    AMITSESETUP *pSetupVariable = (AMITSESETUP *)NULL;
	UINTN size = 0;

	RUNTIME_DEBUG( L"nvram" );

	// Update application data information to match that of HII
	Status = HiiFixupData( );
    if(EFI_ERROR(Status)){
        goto DONE;//EIP 76381 : Reset to read the variable from NVRAM
    }

   UEFICallSetupFormCallBack(AMI_CALLBACK_FORM_OPEN);//EIP-53480: Calling the Wraper function with action AMI_CALLBACK_FORM_OPEN
  
	Status = VarBuildDefaults();
    if(EFI_ERROR(Status)){
        goto DONE;//EIP 76381 : Reset to read the variable from NVRAM
    }

	Status = VarLoadVariables( (VOID **)&gVariableList, gOptimalDefaults );
    if(EFI_ERROR(Status)){
        goto DONE;//EIP 76381 : Reset to read the variable from NVRAM
    }

   //EIP-71351 Call Retrive callback after loading Current values to variable Cache.
   UEFICallSetupFormCallBack(AMI_CALLBACK_RETRIEVE);//EIP-53480: Calling the Wraper function with action AMI_CALLBACK_RETRIEVE

	if(!NoVarStoreSupport())
	{
		VarGetNvram( VARIABLE_ID_AMITSESETUP, &size );
		if(size < sizeof(AMITSESETUP))
		{
			pSetupVariable = (AMITSESETUP *) EfiLibAllocateZeroPool(sizeof(AMITSESETUP));
			if(gVariableList[VARIABLE_ID_AMITSESETUP].Buffer)
				MemCopy( pSetupVariable, gVariableList[VARIABLE_ID_AMITSESETUP].Buffer, gVariableList[VARIABLE_ID_AMITSESETUP].Size );
			VarSetNvram( VARIABLE_ID_AMITSESETUP, pSetupVariable, sizeof(AMITSESETUP));
			VarUpdateDefaults(VARIABLE_ID_AMITSESETUP);
		}
	}

    Status = EFI_SUCCESS;

DONE:
    CleanTempNvramVariableList();//EIP 76381 : Reset to read the variable from NVRAM
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainSetupLoop
//
// Description:	This function runs the loop for setup execution. This
//              function is responsible for creating the application
//              hierarchy. It also gathers actions and passes them
//              thru application hierarchy and initiates draw
//              sequence.
//
// Input:		VOID
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS MainSetupLoop( VOID )
{
	EFI_STATUS Status;
	ACTION_DATA *action = NULL;
	BOOLEAN refresh = TRUE;
	UINT32 ii;
	UINT32 page,previouspage=1;
	PAGE_DATA *thisPage;
	UINT32 SaveStateVarNum;
	UINT16 SaveState=SETUP_RESET_NOT_REQUIRED;
	CHAR16  *Language = NULL;
	UINTN 	Size = 0;
	EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;

	// Close the Image related events before loading the setup pages
	gPostStatus = TSE_POST_STATUS_ENTERING_TSE;					//Hooking MainSetupLoop for special case leads to not setting the gPostStatus properly
//  	MouseStop ();              //Stopping before clearing the screen
//	CleanUpLogo();
//	MouseRefresh ();           //Refreshing after clearing the screen
	
	gEnterSetup = FALSE;
	MainSetupLoopInitHook();
//	StopClickEvent();//EIP 86253 : Invoking the StopClickEvent function in the mainsetuploophook function

#if APTIO_4_00
	gMaxRows = MAX_ROWS;
	gMaxCols = MAX_COLS;
#endif
//	SetDesiredTextMode();		//EIP94702 - StyleInit will set the desired text mode
    
	//EIP:47939 - Style initialization before screen clear
	
	Status = MiniSetupEntry();
	if ( EFI_ERROR( Status ) )
		return MiniSetupExit( Status );

	MouseStop ();		//Stopping before clearing the screen
	CleanUpLogo();
	MouseRefresh ();
#ifndef STANDALONE_APPLICATION
	if ( gConsoleControl != NULL )
	{
		gConsoleControl->GetMode(gConsoleControl, &ScreenMode, NULL, NULL);
		if(EfiConsoleControlScreenGraphics == ScreenMode)
		{
			gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
		}
	}
#endif
	StyleInit();
	MouseStop ();		//Stopping before clearing the screen
	ClearScreen (STYLE_CLEAR_SCREEN_COLOR);
	MouseRefresh ();           //Refreshing after clearing the screen

	//EIP-38089: Hook after pressing F2 key and before showing setup menu.
	ProcessUIInitHookHook();

	MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);
	
	Status = gApplication.Create((void**) &gApp );
	if ( EFI_ERROR( Status ) )
		return MiniSetupExit( Status );

	RUNTIME_DEBUG( L"init" );
	Status = gApplication.Initialize( gApp, gApplicationData );
	if (EFI_ERROR(Status))
		return MiniSetupExit( Status );

    gMsgBoxAction = gApp->Action;

	// add boot manager and language pages
    StyleAddExtraPagesData();

	//Let's create the SaveState Variable 
	if(VarGetVariableInfoId( SETUP_SAVE_STATE_INFO_KEY_ID, &SaveStateVarNum ))
		VarSetValue(SaveStateVarNum,0,sizeof(UINT16),&SaveState);

	action = gApp->Action;

	if ( gApp->PageList == NULL )
		gApp->Quit = TRUE;

	gApp->CurrentPage = gStartPage;
	if ( gStartPage == 0 )
		StyleSelectFirstDisplayPage();
// EIP62185: Not to show the pages with PageVisible = TRUE as root page
    thisPage = gApp->PageList[gApp->CurrentPage];
    // Check current page is workable.
    if (thisPage->PageData.PageFlags.PageVisible == TRUE)
    {
        // Find first workable page.
		for ( ii = 0; ii < gApp->PageCount; ii++ )
		{
            thisPage = gApp->PageList[ii];
			if(thisPage == NULL)
				continue;
            if ((thisPage->PageData.PageID != 0) && (thisPage->PageData.PageParentID == 0))
            {
                if (thisPage->PageData.PageFlags.PageVisible != TRUE)
                {
                    gApp->CurrentPage = ii;
                    break;
                }
            }
		}
    }
// EIP62185
	if ( gApp->PageList != NULL )//EIP-75384 Static code
	{
		if ( gApp->PageList[gApp->CurrentPage] == NULL )
		{
			for ( ii = 0; ii < gApp->PageCount; ii++ )
			{
				if ( gApp->PageList[ii] != NULL )
				{
					gApp->CurrentPage = ii;
					break;
				}
			}
		}
	}

	page = gApp->CurrentPage;
    
	// Report the Status code DXE_SETUP_INPUT_WAIT
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_SETUP_INPUT_WAIT,0,NULL,NULL);
	gPostStatus = TSE_POST_STATUS_IN_TSE;

    if (IsLinkHistorySupport ())							//EIP75028 Pressing esc from Main menu which has sub menu is entering into sub menu instead of poping the exit msgbox
        SetParentFormID (0, (UINT16)gApp->CurrentPage);

	while ( ! gApp->Quit )
	{
		if ( page != gApp->CurrentPage )
		{
			if ( gApp->PageList[gApp->CurrentPage] == NULL )
				gApp->CurrentPage = page;
			else
			{
				if(((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[page]))->PageHandle != NULL) //EIP 83105 When the page is removed, don't check for inconsistency
				{
					if( CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[page])) )
					{
						//There is inconsistence so do not move from this page
						gApp->CurrentPage = page;
					}
					else
					{
						page = gApp->CurrentPage;
					}
				}
				else
				{
					page = gApp->CurrentPage;
				}
			}
		}

		thisPage = gApp->PageList[page];

		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		if ( gApp->CompleteRedraw )    
			refresh = TRUE ;		//EIP101564: Do refresh in case Refresh Id Group requires redraw

		if ( refresh )
		{
		//EIP97951-Start
			if (NULL != Language)
			{
		   		MemFreePointer ((VOID **)&Language);
			}
			Size = 0;
//			Language = VarGetNvramName (L"PlatformLang", &gEfiGlobalVariableGuid, NULL, &Size);
			Language = ReadPlatformLang(&Size);
			if (NULL != Language)//EIP-75351 Suppress the warnings from static code analyzer
			{
	 	      EfiZeroMem (gPlatformLang, sizeof (gPlatformLang));	
			   EfiCopyMem (gPlatformLang, Language, Size);
			}
		//EIP97951-End			
			if(page == previouspage)
				MouseFreeze();
			else
				MouseStop();

			if ( gApp->ClearScreen )
			{
				gApp->CompleteRedraw = TRUE;
				MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);
				ClearScreen( STYLE_CLEAR_SCREEN_COLOR );
				gApp->ClearScreen = FALSE;
			}

			if ( gApp->CompleteRedraw )
			{
				StyleDrawPageBorder( page );
				SpecialUpdatePageControls( page );
				gPage.Draw( thisPage );
				gApp->CompleteRedraw = FALSE;
			}else
				gPage.Draw( thisPage );
			DoRealFlushLines();

			previouspage = page; 
            MouseRefresh();

			refresh = FALSE;
		}

		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		if ( gPage.HandleAction( thisPage, action ) != EFI_SUCCESS )
		{
			if ( action->Input.Type == ACTION_TYPE_KEY )
			{
				if ( (ControlActionAbort != MapControlKeysHook(action->Input.Data.AmiKey)) && ( thisPage->PageData.PageFlags.PageDisableHotKeys ) )
				{
					gAction.ClearAction( action );
					continue;
				}
			}

			if ( gApplication.HandleAction( gApp, action ) == EFI_SUCCESS )
			{
				refresh = TRUE;
			}
			else if ( action->Input.Type == ACTION_TYPE_KEY )
			{
				InvalidActionHookHook();			
			}
		}
		else
			refresh = TRUE;

	}
	StyleExit();

//	MouseDestroy(); //EIP-84150 

	if ( gResetRequired ) {
		MiniSetupExit (Status);				//EIP90149; Invoking EFI_BROWSER_ACTION_FORM_CLOSE on reset also
		///EIP:26409 - Hook function to update setup before resetting the system
		PreSystemResetHookHook();	
		gRT->ResetSystem( EfiResetCold, EFI_SUCCESS, 0, NULL );
	}
//EIP: 58925 Start
    if(IsLinkHistorySupport())
    {
        ResetNavStack();
    }
//EIP: 58925 End
	return MiniSetupExit( Status );
}

extern int gNumOfDev ;
extern UINT16 gBBSPopupSel ;
UINT16 gQuitBBSLoop=0;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawBbsPopupMenu
//
// Description:	function for the BBS Popup menu
//
// Input:	void
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern UINT32  gBootFlow;
EFI_STATUS DrawBbsPopupMenu( VOID )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16  i=0, ItemCount=0, u16BootCount = (UINT16)gNumOfDev  ;
	CHAR16 *BootStr;
	POSTMENU_TEMPLATE *BootMenu = NULL; 
	UINT16	Title, Legend, sel = 0 ;
	EFI_GUID       AmiPostManagerProtocolGuid =  AMI_POST_MANAGER_PROTOCOL_GUID;
	AMI_POST_MANAGER_PROTOCOL    *pAmiPostMgr = NULL;
		
	 Status = gBS->LocateProtocol( (EFI_GUID *)&AmiPostManagerProtocolGuid,
		                                             (void*)NULL,
		                                             (void**)&pAmiPostMgr );

	if(Status != EFI_SUCCESS)
		return Status;
//	SetDesiredTextMode();		//EIP94702 - StyleInit will set the desired text mode
	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
	StyleInit();
	
	ItemCount = u16BootCount;

#if POPUP_MENU_ENTER_SETUP
	ItemCount++;
#endif
	BootMenu = EfiLibAllocateZeroPool( sizeof( POSTMENU_TEMPLATE ) * ItemCount);

	for ( i = 0; i < u16BootCount; i++ )
	{
///EIP - 24971
	    BootStr = BootGetBootNowName(i, gPopupMenuShowAllBbsDev, BootNowInBootOrderSupport());
///EIP - 24971
	// EIP:51671 Start 
	//Depending on the value of the token hide of the disabled boot options is done
		if((gPopupMenuHideDisableBootOptions && IsBootDeviceEnabled(i,gPopupMenuShowAllBbsDev,BootNowInBootOrderSupport(),0))||
            (gLoadOptionHidden &&(NULL == BootStr)))
		{
			
			
					BootMenu[i].ItemToken = 1;
					BootMenu[i].Callback = (VOID*)NULL ;
		    		BootMenu[i].CallbackContext = (VOID*)NULL;
				   continue;
		}

	    BootMenu[i].ItemToken = HiiAddString( gHiiHandle, BootStr );
	    BootMenu[i].Callback = (VOID*)NULL ;
	    BootMenu[i].CallbackContext = (VOID*)NULL ;
		BootMenu[i].Attribute = AMI_POSTMENU_ATTRIB_FOCUS;
		BootMenu[i].Key.Key.ScanCode = 0 ;
		BootMenu[i].Key.Key.UnicodeChar = 0 ;
		BootMenu[i].Key.KeyShiftState = 0 ;
	}

#if POPUP_MENU_ENTER_SETUP
	BootMenu[u16BootCount].ItemToken = STRING_TOKEN(STR_POPUPMENU_ENTER_SETUP);
	BootMenu[u16BootCount].Callback = (VOID*)NULL ;
	BootMenu[u16BootCount].CallbackContext = (VOID*)NULL ;
	BootMenu[u16BootCount].Attribute = AMI_POSTMENU_ATTRIB_FOCUS;
	BootMenu[u16BootCount].Key.Key.ScanCode = 0 ;
	BootMenu[u16BootCount].Key.Key.UnicodeChar = 0 ;
	BootMenu[u16BootCount].Key.KeyShiftState = 0 ;
#endif
	
	Title = STRING_TOKEN(STR_BBS_POPUP_TITLE_STRING) ;
	Legend = STRING_TOKEN(STR_BBS_POPUP_HELP_STRING) ;

	gBBSPopupSel = 0 ;

// EIP - 46314: Check ItemCount	before displaying boot menu
	if(ItemCount)
	{

    	MouseRefresh();//Mouse is Initialized when mouse is notified so refreshing the mouse.
		Status = pAmiPostMgr->DisplayPostMenu(gHiiHandle, Title, Legend, BootMenu, ItemCount, &sel);
	    MouseStop();
		
		// EIP - 51425: Check ESC key before setting boot selection 		
		if((Status == EFI_ABORTED)||(Status != EFI_SUCCESS))
		{
			if ( EFI_ABORTED == Status )
				ProcessProceedToBootHook();//EIP 116559  : When ESC pressed in the BBS popup menu 
			gBBSPopupSel = 0 ;
			goto DONE;
		}	

#if POPUP_MENU_ENTER_SETUP
		if(BootMenu[sel].ItemToken == STRING_TOKEN(STR_POPUPMENU_ENTER_SETUP))
		{
			gEnterSetup = TRUE;
		}
		else
#endif
		   gBBSPopupSel = sel ;

	}// EIP - 46314

DONE:
	gBootFlow = BOOT_FLOW_CONDITION_NORMAL;			//EIP 136371, BBS popup flow also, should behave normally on entering into setup. Fixed for root page ordering
	Status = pRS->SetVariable (L"BootFlow", 
					&_gBootFlowGuid, 
					EFI_VARIABLE_BOOTSERVICE_ACCESS,
					sizeof (gBootFlow),
					&gBootFlow);
	StyleExit ();			//Added to clear the screen after bbs popup menu vanishes.
	return Status;
}





#ifdef RUNTIME_DEBUG_SUPPORT
BOOLEAN __RuntimeCheckDebugMode( CHAR16 *string )
{
	EFI_STATUS Status;
	EFI_GUID env = ENVIRONMENT_VARIABLE_ID;

	UINTN	size = 0;
	CHAR16	*buffer = NULL;
	INTN	result = 1;

	Status = gRT->GetVariable(
			L"debug",
			&env,
			NULL,
			&size,
			NULL);

	if ( Status == EFI_BUFFER_TOO_SMALL )
	{
		buffer = EfiLibAllocateZeroPool( size );
		if ( buffer != NULL )
		{
			Status = gRT->GetVariable(
					L"debug",
					&env,
					NULL,
					&size,
					buffer);
		}
	}

	if ( ! EFI_ERROR( Status ) )
		result = EfiStrCmp( string, buffer );

	MemFreePointer( (VOID **)&buffer );

	return (BOOLEAN)( result == 0 );
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitGlobalPointers
//
// Description:	function to Initialize all the global pointer declared.
//
// Input:	void
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitGlobalPointers( VOID )
{
	UINT8	*data;

	gSetupPkg = (SETUP_PKG *)gApplicationData;
	data = (UINT8 *)gSetupPkg;

	gScreen = (SCREEN_INFO *)(data + gSetupPkg->PackageScreen);
	gToolPages = gPages = (PAGE_LIST *)(data + gSetupPkg->PackagePageList);
	gToolControlInfo = (CONTROL_INFO *) (data + gSetupPkg->PackageControlOffset);
	gToolVariables = gVariables = (VARIABLE_LIST *)(data + gSetupPkg->PackageVariableList);
	gHpkInfo = (HPK_INFO *)(data + gSetupPkg->PackageHpkData);
    gHpkInfoLength = gSetupPkg->PackageGuidList - gSetupPkg->PackageHpkData;
	gGuidList = (GUID_LIST *)(data + gSetupPkg->PackageGuidList);
	gToolPageIdList = gPageIdList = (PAGE_ID_LIST *) (data + gSetupPkg->PackagePageIdList);
	gToolPageIdInfo = gPageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gToolPageIdList) + gToolPageIdList->PageIdList[0]);
	InitgProgress();
}



EFI_STATUS _PostMenuUpdate( LISTBOX_DATA *ListBox)
{
  	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Index= 0, j=0 ;
	LISTBOX_BSS_POPUP_DATA *listboxBBSPopupData=NULL;
		

	listboxBBSPopupData = EfiLibAllocateZeroPool( sizeof( LISTBOX_BSS_POPUP_DATA ) );
	
	if(listboxBBSPopupData==NULL)
		return EFI_OUT_OF_RESOURCES;
	
	listboxBBSPopupData->pControlData = NULL ;
	listboxBBSPopupData->ItemCount = ListBox->ItemCount;
	listboxBBSPopupData->PtrItems = EfiLibAllocateZeroPool( sizeof(POSTMENU_TEMPLATE)* listboxBBSPopupData->ItemCount);

	if ( listboxBBSPopupData->PtrItems == NULL )
		return EFI_OUT_OF_RESOURCES;
	

	// MOVE the Hidden items to the end,
	// First copy the printable list
	for ( Index = 0,j=0; Index < listboxBBSPopupData->ItemCount; Index++ )
	{				
		if(	(gPostMenuData[Index].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
			(gPostMenuData[Index].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY))
		{
			listboxBBSPopupData->PtrItems[j] = gPostMenuData[Index] ;
			j++;
		}
	}

	listboxBBSPopupData->HiddenItemCount = Index - j;
	// copy the hidden list
	for ( Index = 0; Index < listboxBBSPopupData->ItemCount; Index++ )
	{				
		if(	(gPostMenuData[Index].Attribute == AMI_POSTMENU_ATTRIB_HIDDEN)||
			(gPostMenuData[Index].Attribute == AMI_POSTMENU_ATTRIB_EXIT_KEY))
		{
			listboxBBSPopupData->PtrItems[j] = gPostMenuData[Index] ;
			j++;
		}
	}

	MemFreePointer((VOID **)&ListBox->PtrTokens);
	MemFreePointer((VOID **)&ListBox->PtrItems);
	//RestoreScreen( ListBox->ScreenBuf );

	ListBox->Width = 0 ;
	ListBox->Height = 0 ;

	Status = gListBox.InitializeBBSPopup( ListBox, listboxBBSPopupData );
	
	// Free allocated init data
	MemFreePointer((VOID**)&listboxBBSPopupData->PtrItems);
	MemFreePointer((VOID**)&listboxBBSPopupData);

	MemCopy( gActiveBuffer, ListBox->ScreenBuf, sizeof(SCREEN_BUFFER) );


	return Status ;
}

EFI_STATUS _PostMenuItemChange( POSTMENU_TEMPLATE MenuItem, UINT16 Count )
{
  	EFI_STATUS Status = EFI_SUCCESS ; 
	UINT16 Index= 0 ;

	for ( Index = 0; Index < Count; Index++ )
	{
		if(gPostMenuData[Index].ItemToken == MenuItem.ItemToken)
		{
			if(gPostMenuData[Index].Attribute != MenuItem.Attribute)
				break;

			if(gPostMenuData[Index].Callback != MenuItem.Callback)
				break;

			if(gPostMenuData[Index].Key.Key.ScanCode != MenuItem.Key.Key.ScanCode)
				break;

			if(gPostMenuData[Index].Key.Key.UnicodeChar != MenuItem.Key.Key.UnicodeChar)
				break;

			if(gPostMenuData[Index].Key.KeyShiftState != MenuItem.Key.KeyShiftState)
				break;
			
			return EFI_UNSUPPORTED;
		}
	}
	
	return Status ;
}

EFI_STATUS _PostMenuChange( LISTBOX_DATA *PopupMenu)
{
  	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Index= 0 ;

	for ( Index = 0; Index < PopupMenu->ItemCount; Index++ )
	{
		Status = _PostMenuItemChange(PopupMenu->PtrItems[Index], PopupMenu->ItemCount) ;

		if(Status == EFI_SUCCESS)
			return 	Status ;
	}

	return Status ;
}

VOID _ProcessPostMenuChange( LISTBOX_DATA *PopupMenu)
{
	ACTION_DATA *action=NULL;
	EFI_STATUS Status = EFI_UNSUPPORTED; 
	UINT16 Sel = PopupMenu->Sel ; 	

	//Check if Menu has been dynamically changed
	if(_PostMenuChange(PopupMenu )== EFI_SUCCESS)
	{
		//Update and initialize with new menu data
		//Note: PopupMenu->Sel will be initialized to zero
		_PostMenuUpdate(PopupMenu);
		
		if(PopupMenu->PtrItems[Sel].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS)
		{
			// item has been changed to non-focus
			PopupMenu->Sel = Sel;
			
			//Create and Send Fake Action...<Down-Arrow> Key
			Status = gAction.Create( &action );
			if ( !EFI_ERROR( Status ) )
			{
				action->Input.Type = ACTION_TYPE_KEY ;
				action->Input.Data.AmiKey.Key.ScanCode = SCAN_DOWN;
				action->Input.Data.AmiKey.Key.UnicodeChar = CHAR_NULL ;
				gListBox.HandleAction(PopupMenu, action);
				
				gAction.Destroy( action, TRUE );
			}
		}
		else if( (PopupMenu->PtrItems[Sel].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
			 (PopupMenu->PtrItems[Sel].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY))
		{
			PopupMenu->Sel = Sel;
		}	
		//Exit if item callback has been changed to null
		else if(PopupMenu->PtrItems[Sel].Callback == NULL)
		{
			PopupMenu->QuitPopupLoop = 1;
		}
	}	
}

VOID _PostMenuCallback( LISTBOX_DATA *container, LISTBOX_DATA *PopupMenu, VOID *cookie )
{
  	if ( cookie != NULL )
	{
		UINT16 Sel = *(UINT16 *) cookie;
		POSTMENU_TEMPLATE *CurrentPostMenuData = NULL ;
		
		//EIP-177012: Start
		if(Sel > (PopupMenu->ItemCount - 1))
		    return ;
		
		if(PopupMenu->PtrItems[Sel].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS)
		    return ;
		//EIP-177012: End
		
						
		if(PopupMenu->PtrItems[Sel].Callback != NULL)
		{
			CurrentPostMenuData = gPostMenuData; //EIP-93639 
			PopupMenu->PtrItems[Sel].Callback(PopupMenu->PtrItems[Sel].CallbackContext);
		}
		
		if( NULL != CurrentPostMenuData ) //EIP-93639 
		 gPostMenuData = CurrentPostMenuData;
		// EIP:54517
        _ProcessPostMenuChange(PopupMenu);

		//EIP:52897, Allways check for NULL to exit properly.	
		if(PopupMenu->PtrItems[Sel].Callback == NULL)
			PopupMenu->QuitPopupLoop = 1; 
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		ShowPostMenu
//
// Description:		Function to show menu 
//				
// Input:		IN CHAR16 *Title, IN POSTMENU_TEMPLATE *MenuData, IN UINT32 menucount, OUT UINT16  *pSelection
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostMenu(
	IN VOID		*HiiHandle, 	
    	IN UINT16 	TitleToken, 
    	IN UINT16 	LegendToken,	  
    	IN POSTMENU_TEMPLATE *MenuData,
    	IN UINT16 	MenuCount,
    OUT UINT16  *pSelection)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Index= 0, j, i, EXIT_KEY_PRESENT=0;
	CONTROL_INFO	*newControlInfo=NULL;
	LISTBOX_BSS_POPUP_DATA *listboxBBSPopupData=NULL;
	LISTBOX_DATA	*ListBoxCtrl=NULL;
	ACTION_DATA *action=NULL;
//	UINT8 Color, sel = 0 ; sel not used
	UINT8 Color;
	CONTROL_ACTION Action ;

	
    // Error check the input pointers (HiiHandle is allowed to be NULL)
    if(pSelection == NULL || MenuData == NULL) return EFI_INVALID_PARAMETER;

	newControlInfo = EfiLibAllocateZeroPool( sizeof( CONTROL_INFO ) );

	if(newControlInfo==NULL) return EFI_OUT_OF_RESOURCES;
	
	newControlInfo->ControlHandle = (HiiHandle!=NULL)?HiiHandle:gHiiHandle;
	newControlInfo->ControlFlags.ControlVisible = TRUE;

	listboxBBSPopupData = EfiLibAllocateZeroPool( sizeof( LISTBOX_BSS_POPUP_DATA ) );
	
	if(listboxBBSPopupData==NULL) return EFI_OUT_OF_RESOURCES;
	
	listboxBBSPopupData->TitleToken = TitleToken;
	listboxBBSPopupData->Help1Token = LegendToken;
	listboxBBSPopupData->pControlData = newControlInfo;

	Status = gAction.Create( &action );
	if ( EFI_ERROR( Status ) )
		return Status;

	listboxBBSPopupData->ItemCount = MenuCount;
	listboxBBSPopupData->PtrItems = EfiLibAllocateZeroPool( sizeof(POSTMENU_TEMPLATE)* listboxBBSPopupData->ItemCount);

	if ( listboxBBSPopupData->PtrItems == NULL )
		return EFI_OUT_OF_RESOURCES;

	gPostMenuData = MenuData;

	// MOVE the Hidden items to the end,
	// First copy the printable list
	for ( Index = 0,j=0; Index < listboxBBSPopupData->ItemCount; Index++ )
	{				
		if(	(MenuData[Index].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
			(MenuData[Index].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY))
		{
			//EIP:51671 START
				//Depending on the value of the token hide of the disabled boot options is done
				if(gPopupMenuHideDisableBootOptions || gLoadOptionHidden)
				{
					if(MenuData[Index].ItemToken == 1)
					{
						MenuData[Index].Attribute = AMI_POSTMENU_ATTRIB_HIDDEN;
						continue;
					}
				}
         //	EIP:51671 END
			listboxBBSPopupData->PtrItems[j] = MenuData[Index] ;
			j++;
		}
	}

	listboxBBSPopupData->HiddenItemCount = Index - j;

	// Then copy the hidden list
	for ( Index = 0; Index < listboxBBSPopupData->ItemCount; Index++ )
	{				
		if(	(MenuData[Index].Attribute == AMI_POSTMENU_ATTRIB_HIDDEN)||
			(MenuData[Index].Attribute == AMI_POSTMENU_ATTRIB_EXIT_KEY))
		{
			listboxBBSPopupData->PtrItems[j] = MenuData[Index] ;
			j++;
		}
	}

    // Create the list box item
	if ( gListBox.Create( (void**)&ListBoxCtrl ) == EFI_SUCCESS )
	{
		Status = gListBox.InitializeBBSPopup( ListBoxCtrl, listboxBBSPopupData );
		// Free allocated init data
		MemFreePointer((VOID**)&newControlInfo);
		MemFreePointer((VOID**)&listboxBBSPopupData->PtrItems);
		MemFreePointer((VOID**)&listboxBBSPopupData);
		
		if(Status == EFI_SUCCESS )
		{
			//Set default selection, make sure it is not hidden or non-focused
			if(	(ListBoxCtrl->PtrItems[*pSelection].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
				(ListBoxCtrl->PtrItems[*pSelection].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY)&&
                (ListBoxCtrl->PtrItems[*pSelection].Attribute != AMI_POSTMENU_ATTRIB_NON_FOCUS))
			{
				ListBoxCtrl->Sel = *pSelection; 
			}
			else
			{
				//Find the next selectable item...
				for ( Index = 0; Index < ListBoxCtrl->ItemCount; Index++ )
				{				
					if(	(ListBoxCtrl->PtrItems[Index].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
						(ListBoxCtrl->PtrItems[Index].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY)&&
					   	(ListBoxCtrl->PtrItems[Index].Attribute != AMI_POSTMENU_ATTRIB_NON_FOCUS))
					{
						ListBoxCtrl->Sel = Index;
						break;
					}	
				}

                // if the entire menuy is hidden, get out
				if(ListBoxCtrl->HiddenItemCount == ListBoxCtrl->ItemCount)
				{
					Status = EFI_UNSUPPORTED;
					goto Done;
				}
				
				// If there are no selectable items, go out
				if(Index == ListBoxCtrl->ItemCount)
				{
					//Status = EFI_INVALID_PARAMETER;
					//goto Done;
				}

			}

			gPostMenuLevel += 1 ;			

			Color = ListBoxCtrl->FGColor | ListBoxCtrl->BGColor ;
			StyleGetWindowColor(&Color, gPostMenuLevel, TSE_WINDOW_TYPE_POSTMENU);
			ListBoxCtrl->FGColor = (Color & 0x0F) ;
			ListBoxCtrl->BGColor = (Color & 0xF0) ;
					

            // Display everything to the internal screen buffer
			ListBoxCtrl->QuitPopupLoop = 0 ;	
			gListBox.SetCallback(ListBoxCtrl, NULL, (OBJECT_CALLBACK) _PostMenuCallback, NULL);
			gListBox.Draw( ListBoxCtrl );
	
            MouseStop();
            // Display everything to the screen
			DoRealFlushLines();
			MouseRefresh();//EIP:51627 -Provided the mouse support for Add boot option with File browser support
			
//TH0037 >>>>
			while( gAction.GetAction( action ) != EFI_SUCCESS ) //Clean KBC invalid buffer value
			{ }
//TH0037 <<<<			
	
			while(!ListBoxCtrl->QuitPopupLoop)
			{
				if ( action->Input.Type != ACTION_TYPE_NULL )
					gAction.ClearAction( action );
		
				gListBox.Draw( ListBoxCtrl );
    			MouseFreeze();
				DoRealFlushLines();
				MouseRefresh();
		
				if ( gAction.GetAction( action ) != EFI_SUCCESS )
					continue;

				//EIP-123432 PrintScreen Support work only inside TSE not in post
				if( (gPostStatus == TSE_POST_STATUS_IN_TSE) && ( action->Input.Type == ACTION_TYPE_KEY ) &&
					(TsePrintScreenEventSupport(action->Input.Data.AmiKey.Key.ScanCode) ) ) 
				{
					gApplication.HandleAction( gApp, action );
					continue;
				}

				//EIP:52897, Make sure pSelection is updated before callback is handled.
				for(i=0; i < MenuCount; i++)
				{
					if( ListBoxCtrl->PtrItems[ListBoxCtrl->Sel].ItemToken == MenuData[i].ItemToken)
					{
						*pSelection = i;
						break;
					}
				}

				Status = gListBox.HandleAction( ListBoxCtrl, action );
				if ( !EFI_ERROR (Status) )//EIP-123432
				{
					if (action->Input.Type == ACTION_TYPE_KEY)
						Action = MapControlKeysHook (action->Input.Data.AmiKey);

					else if( (gPostStatus == TSE_POST_STATUS_IN_TSE) && ( //If mouse is clicked outside menu inside setup
				        (action->Input.Data.MouseInfo.Top  < (UINT32)(ListBoxCtrl->Top-2)) || //If clicked above menu title
				        (action->Input.Data.MouseInfo.Top  >= (UINT32)(ListBoxCtrl->Top + ListBoxCtrl->Height)) ||	//if clicked below menu
				        (action->Input.Data.MouseInfo.Left < (UINT32)(ListBoxCtrl->Left)) || 								//if clicked left outside of menu
				        (action->Input.Data.MouseInfo.Left > (UINT32)(ListBoxCtrl->Left + ListBoxCtrl->Width)) //if clicked right outside of menu
						 ) &&(	(SingleClickActivation() &&  (ControlActionSelect ==MapControlMouseActionHook(&action->Input.Data.MouseInfo))) || //If singleClickActivation is enabled
						 		(ControlActionAbort == MapControlMouseActionHook(&action->Input.Data.MouseInfo)) || //If right clicked outside
						 		(ControlActionChoose == MapControlMouseActionHook(&action->Input.Data.MouseInfo)) //EIP-139608 Closing postmenu when mouse action happens outside postmenu.
						 	)
				     )
					{
				        Action = ControlActionAbort;
					}
				}

																				
   				//Menu may dynamically update, so init EXIT KEY flag here...
				EXIT_KEY_PRESENT = 0 ;             
			
				//Since hidden items are moved to the end, 
				//we need to return the matching index of the caller's menu
				for(i=0; i < MenuCount; i++)
                {
                    if( ListBoxCtrl->PtrItems[ListBoxCtrl->Sel].ItemToken == MenuData[i].ItemToken)
						*pSelection = i;

					if(ListBoxCtrl->PtrItems[i].Attribute == AMI_POSTMENU_ATTRIB_EXIT_KEY)
					{
						EXIT_KEY_PRESENT = 1 ;

						if( (ListBoxCtrl->PtrItems[i].Key.Key.ScanCode == action->Input.Data.AmiKey.Key.ScanCode ) &&
	                   		(ListBoxCtrl->PtrItems[i].Key.Key.UnicodeChar == action->Input.Data.AmiKey.Key.UnicodeChar) &&
	                   		(TseCheckShiftState( action->Input.Data.AmiKey, ListBoxCtrl->PtrItems[i].Key.KeyShiftState)  ) )
	                		{
								ListBoxCtrl->QuitPopupLoop = 1;
								Status = EFI_ABORTED ;  //EIP:39415, return error status on esc key  
								
							}
					}
                }

				if(ControlActionSelect == Action)
				{
				
					//EIP:52427 Start
					if(TitleToken && ListBoxCtrl->Title != NULL)
					{
						//To avoid memory leak, free memory before updating...
						MemFreePointer((VOID **)&ListBoxCtrl->Title);

						//EIP:48417 Start
						ListBoxCtrl->Title = HiiGetString( ListBoxCtrl->ListHandle, TitleToken );	
						//EIP:48417 End				
					}
					//EIP:52427 End
					

					gPostMenuData = MenuData;
					_ProcessPostMenuChange(ListBoxCtrl) ;

				}else if(!EXIT_KEY_PRESENT && ControlActionAbort == Action)
				{
					if (gPostStatus == TSE_POST_STATUS_IN_BBS_POPUP)
					{
						if (IsDisableESCinBBSMenu ())//EIP-128526 Disable ESC behaviour in BBS menu and retain till selecting any options
							continue;
						else //Enabling ESC key in BBS menu and exit BBS menu on pressing ESC key
						{
							ListBoxCtrl->QuitPopupLoop = 1;
							Status = EFI_ABORTED ;  //EIP:39415, return error status on esc key  
						}
					}
					else //Handling ESC other than BBSMenu
					{
						ListBoxCtrl->QuitPopupLoop = 1;
						Status = EFI_ABORTED ;  
					}
				}
			}
		}
	}
		

Done:	
	
	gPostMenuLevel -= 1 ;	

	gListBox.Destroy( ListBoxCtrl,TRUE );
	ListBoxCtrl = NULL;
	
	gAction.Destroy( action, TRUE );
	MouseStop();//EIP:51627 -Provided the mouse support for Add boot option with File browser support

	FlushLines( 0, gMaxRows - 1 );
	DoRealFlushLines();		

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		_LoadPageDefaults
//
// Description:	Function to updated defaults for specific page for both Optimal and FailSafe defaults
//
// Input:			PAGE_INFO, UINT32
//
// Output:			VOID
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _LoadPageDefaults(PAGE_INFO *pageInfo, UINT32 OldVariableCount)
{
    UINT32	control;

	for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
	{
		CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

		if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE ) || ( controlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER ) || (controlInfo->ControlVariable == VARIABLE_ID_BBS_ORDER) )
			continue;

		if ( controlInfo->ControlDataWidth > 0 )
		{
			VOID *ifrData = controlInfo->ControlPtr;
			UINT8 *failValue, *optValue;
			UINT32 ControlVarOffset;

			if ( ifrData == NULL )
				continue;

			failValue = (UINT8 *)controlInfo + sizeof(CONTROL_INFO);
			optValue = failValue + controlInfo->ControlDataWidth;

			ControlVarOffset = UefiGetQuestionOffset(ifrData);

			//EIP-93340 Updating gOptimalDefaults and gFailSafeDefaults for stringType controls based on controlPtr
			if (IsSupportDefaultForStringControl() && controlInfo->ControlType == CONTROL_TYPE_POPUP_STRING)
			{
				if (*(UINT16*)(failValue))
				{
					failValue = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(failValue));
					if (NULL == failValue)
						continue;

					_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen((CHAR16*)failValue) * sizeof(CHAR16), failValue );
				}
				
				if (*(UINT16*)(optValue))
				{
					optValue = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(optValue));
					if (NULL == optValue)
						continue;

					_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen((CHAR16*)optValue) * sizeof(CHAR16), optValue );
					
					if(controlInfo->ControlVariable > OldVariableCount)
						_VarGetSetValue( VAR_COMMAND_SET_VALUE, gVariableList, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen((CHAR16*)optValue) * sizeof(CHAR16), optValue );
					
				}
				
				if (failValue)
					MemFreePointer( (VOID **)&failValue );
				
				if (optValue)
					MemFreePointer( (VOID **)&optValue );
			}
			//EIP-93340 End
			else
			{
				_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, controlInfo->ControlVariable, ControlVarOffset, controlInfo->ControlDataWidth, failValue );
				_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, ControlVarOffset, controlInfo->ControlDataWidth, optValue );
				// Dont' Update the cache of exsiting variable.
				if(controlInfo->ControlVariable > OldVariableCount)
					_VarGetSetValue( VAR_COMMAND_SET_VALUE, gVariableList, controlInfo->ControlVariable, ControlVarOffset, controlInfo->ControlDataWidth, optValue );
			}
		}
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		UIUpdateCallback
//
// Description:		UI callback function for dynamic form updates.
//				
// Input:		IN Handle of Affected page
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//static AMI_IFR_MENU gMenuData = {CONTROL_TYPE_MENU,2};
extern UINT32	gtempCurrentPage;
VOID UIUpdateCallback(VOID * Handle, UINT32 OldVariableCount)
{
	UINT32 i,j, CurrentPage,Index;
	PAGE_INFO *_gPageInfo,*_gappPageInfo,*_tmpPageInfo;
	UINT32	tmpControlCount,tmpCurrentControl,tmpFirstVisibleCtrl;
    FRAME_DATA *fdata;
	PAGE_DATA *PageData;

	if(gApp == NULL)
		return; // Application data not initilized.

	if(gVariables->VariableCount > OldVariableCount)
	{  	
		// NewVariables Added.
	    // Update the TSE catch and Defaults	
		// Reallocate
		gVariableList 		= MemReallocateZeroPool( gVariableList, sizeof(NVRAM_VARIABLE) * OldVariableCount, gVariables->VariableCount * sizeof(NVRAM_VARIABLE));
		gOptimalDefaults 	= MemReallocateZeroPool( gOptimalDefaults, sizeof(NVRAM_VARIABLE) * OldVariableCount, gVariables->VariableCount * sizeof(NVRAM_VARIABLE));
		gFailsafeDefaults 	= MemReallocateZeroPool( gFailsafeDefaults, sizeof(NVRAM_VARIABLE) * OldVariableCount, gVariables->VariableCount * sizeof(NVRAM_VARIABLE));
		ASSERT (gVariableList != NULL);
		ASSERT (gOptimalDefaults != NULL);
		ASSERT (gFailsafeDefaults != NULL);

	  	for(Index = OldVariableCount; Index< gVariables->VariableCount; Index++)
		{
			gVariableList[Index].Buffer = VarGetNvram( Index, &(gVariableList[Index].Size) );
			if (gVariableList[Index].Size)
			{
				// init std defautls 
				gOptimalDefaults[Index].Buffer = EfiLibAllocateZeroPool( gVariableList[Index].Size );
				if (NULL == gOptimalDefaults[Index].Buffer)
				{
					continue;
				}
				if (NULL == gVariableList[Index].Buffer)
				{
					gVariableList[Index].Buffer = EfiLibAllocateZeroPool( gVariableList[Index].Size );
					if (NULL == gVariableList[Index].Buffer)
					{
						continue;
					}
				}				
				MemCopy(gOptimalDefaults[Index].Buffer, gVariableList[Index].Buffer, gVariableList[Index].Size);

				// init mfg defautls 
				gFailsafeDefaults[Index].Buffer = EfiLibAllocateZeroPool( gVariableList[Index].Size );
				MemCopy(gFailsafeDefaults[Index].Buffer, gVariableList[Index].Buffer, gVariableList[Index].Size);
			}
			else
			{
				gFailsafeDefaults[Index].Buffer = NULL;
				gOptimalDefaults[Index].Buffer = NULL;
			}

			gFailsafeDefaults[Index].Size = gVariableList[Index].Size;
			gOptimalDefaults[Index].Size = gVariableList[Index].Size;
		}
	}

	CurrentPage = gApp->CurrentPage;
	fdata = ((PAGE_DATA*)gApp->PageList[gApp->CurrentPage])->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

	tmpControlCount = fdata->ControlCount;
	tmpCurrentControl = fdata->CurrentControl;
	tmpFirstVisibleCtrl = fdata->FirstVisibleCtrl;

	// Fix gApp Pages
	for ( i = 1; i < gPages->PageCount; i++ )
	{
		// Get the Setupdata's Page Info
		_gPageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);
		
		// If page is updated
		if( (_gPageInfo->PageHandle == Handle) || (_gPageInfo->PageHandle == (VOID *)(UINTN)0xFFFF)) 
		{
			for ( j = 1; j < gApp->PageCount; j++ )
			{
				_gappPageInfo = (PAGE_INFO*)&( gApp->PageList[j]->PageData);
				// If updated handle ?
				if(_gappPageInfo->PageHandle == Handle)
				{
					// Update page
					if(_gPageInfo->PageFormID == _gappPageInfo->PageFormID)
					{
						gPage.Destroy( gApp->PageList[j], FALSE );
						if(_gPageInfo->PageHandle != (VOID *)(UINTN)0xFFFF)
                        {
                            if((_gPageInfo->PageFlags.PageDynamic == TRUE) && (_gPageInfo->PageParentID == 0))
                                _gPageInfo->PageParentID = gDynamicParentPage;
							gPage.Initialize( gApp->PageList[j], _gPageInfo );
                            _LoadPageDefaults(_gPageInfo,OldVariableCount);
                        }
						else
							_gappPageInfo->PageHandle = NULL; 

						break;
					}
				}
			}
			// New Page - Add Page
		if(j == gApp->PageCount)
            {
		gtempCurrentPage = gApp->CurrentPage;
		gApp->CurrentPage = j;								//Change the current else in UefiGetQuestionOffset page handle will not be matched useful for name value
		gApplication.AddPage( gApp, _gPageInfo );
		gApp->CurrentPage = gtempCurrentPage;
                _LoadPageDefaults(_gPageInfo,OldVariableCount);
            }
		}
	}

	// If Current Page removed ????
	_gappPageInfo = (PAGE_INFO*)&( gApp->PageList[gApp->CurrentPage]->PageData);
	if(_gappPageInfo->PageHandle == NULL)
	{
		UINT32 rootPage = 0, FirstPage=0;
		for ( j = 1; j < gApp->PageCount; j++ )
		{
			_tmpPageInfo = (PAGE_INFO*)&( gApp->PageList[j]->PageData);
			if(_tmpPageInfo->PageHandle == Handle)
			{
				if(_gappPageInfo->PageFormID == _tmpPageInfo->PageFormID)
				{
					//Current Page moved
					CurrentPage = gApp->CurrentPage = j;
					break;
				}
				if(_tmpPageInfo->PageParentID == 0)
					rootPage = _tmpPageInfo->PageID;
			}
			//Make first focus to the visible page if current page is removed
			if((_tmpPageInfo->PageHandle != NULL) && (FirstPage==0) && (!_tmpPageInfo->PageFlags.PageVisible))
				FirstPage = j;
		}
		// Page permently removed.
		if(j == gApp->PageCount)
		{
			if(rootPage)
			{
				// Try to go to Root page of Current handle
				gApp->CurrentPage = rootPage;
			}
			else
			{
				if(FirstPage)
					gApp->CurrentPage = FirstPage;
				else
				{
					// NO Valid PAGE Found
					// HANDLE ERRROR!!!!
				}
			}
		}
		gApp->CompleteRedraw = TRUE;
	}

	// Update the Menu control
	i = StyleFrameIndexOf(SUBTITLE_FRAME); 
	for ( j = 1; j < gApp->PageCount; j++ )
	{
		PageData = (PAGE_DATA*)gApp->PageList[j];
		if(PageData == NULL)
			continue;
		if(PageData->PageData.PageHandle != NULL)
		{
			gFrame.Destroy( PageData->FrameList[i], FALSE );		
			StyleInitializeFrame( PageData->FrameList[i], SUBTITLE_FRAME, &PageData->PageData );
		}
	}

	// To Maintain the current control
	if(CurrentPage == gApp->CurrentPage)
	{
		fdata = ((PAGE_DATA*)gApp->PageList[gApp->CurrentPage])->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
		// Update Controls
		if(fdata->ControlCount == tmpControlCount)
		{
			fdata->CurrentControl=tmpCurrentControl;
			fdata->FirstVisibleCtrl=tmpFirstVisibleCtrl;
			_FrameSetControlFocus( fdata, tmpCurrentControl );
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		GetUpdatedControlData
//
// Description:		Try to get the updated control.
//				
// Input:		CONTROL_DATA * ControlData,UINT16 ControlType,VOID *Handle,UINT16 Key
//
// Output:		controlData. Null if not found.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CONTROL_DATA * GetUpdatedControlData(CONTROL_DATA * ControlData,UINT16 ControlType,VOID *Handle,UINT16 Key)
{
	FRAME_DATA *frame;
	UINT32 i;
	CONTROL_DATA **control;

	if ( NULL == ((PAGE_DATA*)gApp->PageList[gApp->CurrentPage]) )//Setup crashes on clicking submenu when PageList is NULL 
		 return NULL;

	frame = ((PAGE_DATA*)gApp->PageList[gApp->CurrentPage])->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

	control = frame->ControlList;
	for ( i = 0; i < frame->ControlCount; i++, control++ )
	{
		if(((*control)->ControlData.ControlHandle == Handle) && ((*control)->ControlData.ControlType == ControlType))
		{
			if(UefiGetControlKey(&((*control)->ControlData)) == Key)
				return *control;
		}
	}
	return NULL;
}

BOOLEAN IsActiveControlPresent(PAGE_DATA *page)
{
	BOOLEAN ControlActive=FALSE;
	CONTROL_DATA **control;
	FRAME_DATA * pFrame;
	UINTN i;

	for ( i = 0; i < page->FrameCount; i++ )
	{
		pFrame = page->FrameList[StyleFrameIndexOf((UINT32)i)];
		if(pFrame->CurrentControl != FRAME_NONE_FOCUSED)
		{
			control = &pFrame->ControlList[pFrame->CurrentControl];
			if((*control)->ControlActive == TRUE )
			{
				ControlActive = TRUE;
				break;
			}
		}
	}
	return ControlActive;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------
// Procedure:		UpdategScreenParams
//
// Description:		Verifies and corrects the gScreen params with the current uni strings
//				
// Input:		    VOID
//
// Output:		    VOID
//
//-----------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdategScreenParams (VOID)
{
    if (STR_MAIN_TITLE != gScreen->MainTitle)
    {
        gScreen->MainTitle = STR_MAIN_TITLE;
    }
    if (STR_MAIN_COPYRIGHT != gScreen->MainCopyright)
    {
        gScreen->MainCopyright = STR_MAIN_COPYRIGHT;
    }
    if (STR_EVAL_MSG != gScreen->MainHelpTitle)
    {
        gScreen->MainHelpTitle = STR_EVAL_MSG;
    }
}
//EIP: 58925 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetParentFormID
//
// Description: Gets the parent page ID from given child page ID
//
// Input:	UINT16 ChildID - Child page ID
//			UINT16 *ParentID - Parent page ID
//
// Output:	EFI_STATUS Status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetParentFormID(UINT16 ChildID, UINT16 *ParentID, UINT32 *StackIndex)
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    UINT32 navCount = 0, gAppPageCount = 0;

	*StackIndex = 0xFFFFFFFF;

    if(gApp->PageList[ChildID] == NULL){
		Status = EFI_ABORTED;
        goto DONE;
    }

	Status = EFI_NOT_FOUND;
    for(navCount = 0; navCount < gPageNavCount; navCount++){ //Check in the navigated page stack
        if((NavPageStack[navCount].PageFormID == gApp->PageList[ChildID]->PageData.PageFormID)
            && (NavPageStack[navCount].PageHandle == gApp->PageList[ChildID]->PageData.PageHandle))
        {
            if((NavPageStack[navCount].PageParentFormID == 0) && (NavPageStack[navCount].ParentPageHandle == NULL)){ //If the parent page and parent handle is invalid
                *StackIndex = 0;
                break;
            }
            for(gAppPageCount = gNavStartPage; gAppPageCount < gApp->PageCount; gAppPageCount++){ //Check against the application page list
                if((gApp->PageList[gAppPageCount]->PageData.PageFormID == (UINT16)NavPageStack[navCount].PageParentFormID)
                    && (gApp->PageList[gAppPageCount]->PageData.PageHandle == NavPageStack[navCount].ParentPageHandle))
                {
                    *ParentID = gApp->PageList[gAppPageCount]->PageData.PageID;
					*StackIndex = navCount;
                    Status = EFI_SUCCESS;
                    break;
                }
            }
            break;
        }
    }

DONE:
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetParentFormID
//
// Description: Updated NAV_PAGE_STACK with current page and parent page info
//
// Input:       UINT16 ParentID - Current/Parent Page ID
//				UINT16 TargetID - Target/child page ID
//
// Output:      EFI_STATUS Status - EFI_SUCCESS if successful, else EFI_ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetParentFormID(UINT16 ParentID, UINT16 TargetID)
{
    EFI_STATUS Status = EFI_SUCCESS;
	UINT32 StackIndex = 0xFFFFFFFF;
	UINT16 ParID = 0; //Temporary variable for finding the parent page ID of the target page

    if(ParentID == TargetID){
        return Status;
    }

    if(NavPageStack == NULL){
		NavPageStackSize = gApp->PageCount + MAX_NAVIGATION_DEPTH;
        NavPageStack = (NAV_PAGE_STACK *)EfiLibAllocateZeroPool(sizeof(NAV_PAGE_STACK) * (NavPageStackSize));
        if(NavPageStack == NULL){			
            Status = EFI_OUT_OF_RESOURCES;
            goto DONE;
        }
        gNavStartPage = TargetID; //Sets the start page of the formset
    }

	Status = GetParentFormID(TargetID, &ParID, &StackIndex);
	if(Status == EFI_ABORTED){
		goto DONE;
	}
	if((Status == EFI_SUCCESS) && (StackIndex < NavPageStackSize)){
		gPageNavCount = StackIndex + 1; //Decrement the total number of pages navigated
		if(gPageNavCount < NavPageStackSize){
			MemSet(&NavPageStack[gPageNavCount], (NavPageStackSize - gPageNavCount) * sizeof(NAV_PAGE_STACK), 0); //Remove the child page information from NAV_PAGE_STACK			
		}			
		goto DONE;
	} else if((Status != EFI_SUCCESS) && (StackIndex < NavPageStackSize) && (ParID == 0)){
		gPageNavCount = 1; //Because the navigation root is not found
		if(gPageNavCount < NavPageStackSize){
			MemSet(&NavPageStack[gPageNavCount], (NavPageStackSize - gPageNavCount) * sizeof(NAV_PAGE_STACK), 0); //Remove the child page information from NAV_PAGE_STACK			
		}			
		goto DONE;
	}

	//Adds the child page info in the NAV_PAGE_STACK
	if(NavPageStackSize <= gPageNavCount)
	{
		NavPageStackSize += MAX_NAVIGATION_DEPTH;
		NavPageStack = MemReallocateZeroPool( NavPageStack, NavPageStackSize-MAX_NAVIGATION_DEPTH, NavPageStackSize );
		if(NavPageStack == NULL){			
            Status = EFI_OUT_OF_RESOURCES;
			gPageNavCount=0;
            goto DONE;
        }
	}

    NavPageStack[gPageNavCount].PageHandle = gApp->PageList[TargetID]->PageData.PageHandle;
    NavPageStack[gPageNavCount].PageFormID = gApp->PageList[TargetID]->PageData.PageFormID;
    if(gPageNavCount){
        NavPageStack[gPageNavCount].ParentPageHandle = NavPageStack[gPageNavCount - 1].PageHandle;
        NavPageStack[gPageNavCount].PageParentFormID = NavPageStack[gPageNavCount - 1].PageFormID;		
    }
    gPageNavCount++; //Increment the total number of pages navigated
        

DONE:
    return Status;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   ResetNavStack
//
// Description: Resets the navigation stack
//
// Input:	None
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetNavStack()
{
    if(NavPageStack){
        MemFreePointer((VOID**)&NavPageStack);
        NavPageStack = (NAV_PAGE_STACK *)NULL; //Resets the navigated page info
    }
    gPageNavCount = 0; //Resets the navigated page count
    gNavStartPage = 0; //Resets the start page of the formset
	gDisplayPageId = 0; //Reset the displayed page ID
}
//EIP: 58925 End

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckEnableQuietBoot
//
// Description:	Function to check the quick boot enable option
//
// Input:	void
//
// Output:	void
//
// Notes		:	if NVRAM variable field AMISilentBoot = 0, then disable silent
//					mode else enable In case of error reading the Setup variable,
//					then return as silent boot disable
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckEnableQuietBoot( VOID )
{
#ifndef STANDALONE_APPLICATION
	if(ItkSupport())
	    gQuietBoot = TRUE;
	else
	{
		//ZA0035>>>
#if Foxconn_SUPPORT
		EFI_GUID	gEfiSetupGuid = SETUP_GUID;	
		SETUP_DATA	TSEVar;	
		UINTN		Size = sizeof(SETUP_DATA);
		EFI_STATUS	Status;

		Status = pRS->GetVariable ( L"Setup", \
						&gEfiSetupGuid, \
						NULL, \
						&Size, \
						&TSEVar \
						);
	
		if ( EFI_ERROR( Status ) )
			gQuietBoot = FALSE;
		else
			gQuietBoot = (BOOLEAN)TSEVar.AMISilentBoot;
#else
//ZA0035<<<
		UINT8 *setupvar=NULL;
		UINT8 *setup=NULL;
		UINTN size = 0;
		UINTN offset;
	
		GetAMITSEVariable((AMITSESETUP**)&setup,&setupvar,&size);
	
		offset = STRUCT_OFFSET( AMITSESETUP, AMISilentBoot );
		if ( ( setup == NULL ) || ( size < offset ) )
			gQuietBoot = FALSE;
		else

			gQuietBoot = (BOOLEAN)setup[offset];
	
		if(setupvar)
			MemFreePointer( (VOID **)&setupvar );
		else
			MemFreePointer( (VOID **)&setup );
#endif	//ZA0035
	}
#endif //#ifndef STANDALONE_APPLICATION
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetAMITSEVariableLocal
//
// Description: function to get the local NvRam variable
//
// Input: AMITSESETUP **mSysConf, UINT8 **setup, UINTN *VarSize
//
// Output: void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetAMITSEVariableLocal(AMITSESETUP **mSysConf, UINT8 **setup, UINTN *VarSize)
{
 *mSysConf = VarGetVariable( VARIABLE_ID_AMITSESETUP, VarSize );
 if ( ( *mSysConf == NULL ) || ( *VarSize != sizeof(AMITSESETUP) ) )
  *mSysConf = VarGetNvram( VARIABLE_ID_AMITSESETUP, VarSize );
}

EFI_STATUS ShowDriverHealthConfigForm (PAGE_INFO *pageInfo)
{
	PAGE_DATA **page;                   //To display the configuration page in advanced menu itself
	page = &gApp->PageList [pageInfo->PageID];
	gPage.Destroy (*page, FALSE);
	gPage.Initialize (*page, pageInfo);
	return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
