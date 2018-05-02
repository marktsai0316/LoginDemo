//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/time.c $
//
// $Author: Rajashakerg $
//
// $Revision: 28 $
//
// $Date: 4/05/12 7:26a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Time.c
//
// Description:	This file contains code to handle Time control operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

TIME_METHODS gTime =
{
		(OBJECT_METHOD_CREATE)TimeCreate,
		(OBJECT_METHOD_DESTROY)TimeDestroy,
		(OBJECT_METHOD_INITIALIZE)TimeInitialize,
		(OBJECT_METHOD_DRAW)TimeDraw,
		(OBJECT_METHOD_HANDLE_ACTION)TimeHandleAction,
		(OBJECT_METHOD_SET_CALLBACK)TimeSetCallback,
		(CONTROL_METHOD_SET_FOCUS)TimeSetFocus,
		(CONTROL_METHOD_SET_POSITION)TimeSetPosition,
		(CONTROL_METHOD_SET_DIMENSIONS)TimeSetDimensions,
		(CONTROL_METHOD_SET_ATTRIBUTES)TimeSetAttributes,
		(CONTROL_METHOD_GET_CONTROL_HIGHT)TimeGetControlHeight

};

//static EFI_TIME EditTime; defined but not used
CHAR16 TimeTempNum[3];
BOOLEAN CheckKeyinHotKeysList(AMI_EFI_KEY_DATA Key);
VOID _TimeUpdateEntry(TIME_DATA *time);
EFI_STATUS _TimeHandleActionKeyMouse( TIME_DATA *time,  ACTION_DATA *Data);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeDecrease
//
// Description:	to decrease the time, i.e. Hours/Mins/Secs based on the selection
//
// Input:	TIME_DATA *time, UINT16 Selection
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeDecrease(TIME_DATA *time )
{
	EFI_TIME Tm;

	time->ControlActive =TRUE;
	//gRT->GetTime(&Tm,NULL);
	UefiGetTime(&time->ControlData, &Tm);
	

	switch(time->Sel )
	{
		case 0:
			if((Tm.Hour > 0) && (Tm.Hour > time->Min ))
				Tm.Hour--;
			else
				Tm.Hour = /*(time->Max < 23)? (UINT8)time->Max :*/ 23 ; //EIP 77070
			StrZeroPad(Tm.Hour, TimeTempNum); //Update the static time string
			break;
		case 1:
			if( (Tm.Minute > 0) && (Tm.Minute > time->Min ))
				Tm.Minute--;
			else
				Tm.Minute = /*(time->Max < 59)? (UINT8)time->Max :*/ 59; //EIP 77070 
			StrZeroPad(Tm.Minute, TimeTempNum); //Update the static time string
			break;
		case 2:
			if( (Tm.Second > 0) && (Tm.Second > time->Min ) )
				Tm.Second--;
			else
				Tm.Second =  /*(time->Max < 59)? (UINT8)time->Max :*/ 59; //EIP 77070  
			StrZeroPad(Tm.Second, TimeTempNum); //Update the static time string
			break;
	}
	
	UefiSetTime(&time->ControlData, &Tm);
	//gRT->SetTime(&Tm);
	time->ControlActive =FALSE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeIncrease
//
// Description:	to increase the time, i.e. Hours/Mins/Secs based on the selection
//
// Input:	TIME_DATA *time, UINT16 Selection
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeIncrease(TIME_DATA *time )
{
	EFI_TIME Tm;
	time->ControlActive =TRUE;
	//gRT->GetTime(&Tm,NULL);
	UefiGetTime(&time->ControlData, &Tm);

	switch(time->Sel )
	{
		case 0:
			if(Tm.Hour < 23)
				Tm.Hour++;
			else
				Tm.Hour =0;
			StrZeroPad(Tm.Hour, TimeTempNum); //Update the static time string
			break;
		case 1:
			if(Tm.Minute <59)
				Tm.Minute++;
			else
				Tm.Minute =0;
			StrZeroPad(Tm.Minute, TimeTempNum); //Update the static time string
			break;
		case 2:
			if(Tm.Second <59)
				Tm.Second++;
			else
				Tm.Second =0;
			StrZeroPad(Tm.Second, TimeTempNum); //Update the static time string
			break;
	}

	//gRT->SetTime(&Tm);
	UefiSetTime(&time->ControlData, &Tm);
	time->ControlActive =FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeCreate
//
// Description:	this function uses the create function of control
//					and creates and sets the timer
//
// Input:	TIME_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeCreate( TIME_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(TIME_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create((void**)object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gTime;
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the timer
//
// Input:	TIME_DATA *time, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeDestroy( TIME_DATA *time, BOOLEAN freeMem )
{
	if(NULL == time)
	  return EFI_SUCCESS;

	gControl.Destroy( (CONTROL_DATA *)time, FALSE );

	if ( freeMem )
	{
		MemFreePointer((VOID **)&time->EditTime);
		MemFreePointer( (VOID **)&time );
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeInitialize
//
// Description:	this function uses the Initialize function of control
//					and initializes the time
//
// Input:	TIME_DATA *time, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeInitialize( TIME_DATA *time, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( (CONTROL_DATA *)time, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	time->ControlData.ControlHelp = UefiGetHelpField(time->ControlData.ControlPtr);
	time->Interval = (UINT8)time->ControlData.ControlFlags.ControlRefresh;
	time->LabelMargin = (UINT8)gControlLeftMargin;
	time->Sel=0;
	time->ControlFocus=FALSE;
	time->ControlActive = FALSE;
	time->EditTime = EfiLibAllocateZeroPool( sizeof(EFI_TIME) );
	if ( time->EditTime == NULL )
		Status = EFI_OUT_OF_RESOURCES;

	SetControlColorsHook(NULL, NULL, 
						NULL, &(time->FGColor), 
						&(time->SelBGColor), &(time->SelFGColor),
	                    &(time->BGColor), &(time->NSelFGColor), 
						NULL, &(time->LabelFGColor),
						&(time->NSelLabelFGColor),
						NULL, NULL,
						NULL, NULL);


	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeDraw
//
// Description:	function to draw time with attributes
//
// Input:	TIME_DATA *time
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeDraw( TIME_DATA *time )
{
	CHAR16 *t,text[50];
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorTime = time->NSelFGColor ;
	UINT8 ColorLabelTime = (time->ControlFocus)?  time->LabelFGColor : time->NSelLabelFGColor ;
	CHAR16 txt[6];

	if(!(time->ControlActive))
		//Status= gRT->GetTime(&EditTime,NULL);
		UefiGetTime(&time->ControlData, time->EditTime);
		

	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if ( time->ControlData.ControlConditionalPtr != 0x0 )
	//{
		switch( CheckControlCondition( &time->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorTime = ColorLabelTime = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}
	t = HiiGetString( time->ControlData.ControlHandle, UefiGetPromptField(time->ControlData.ControlPtr));
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == t){
		t = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!t)
			return EFI_OUT_OF_RESOURCES;
		EfiStrCpy(t,L" ");
	}
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(time->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( time->Left , time->Top, 
				(UINTN)(time->LabelMargin - time->Left),(UINTN) time->Height,
				t,time->BGColor | ColorLabelTime );
	}
	else
	{
		// boundary overflow  check
		if ( EfiStrLen( t ) > (UINTN)(time->LabelMargin - time->Left  )/*21*/ )
				t[time->LabelMargin - time->Left ] = L'\0';
	
		DrawStringWithAttribute( time->Left , time->Top, (CHAR16*)t, 
				time->BGColor | ColorLabelTime  );
	}
	MemFreePointer((VOID **)&t);

	EfiStrCpy(text,L"[  :  :  ]");
	DrawStringWithAttribute( time->Left + time->LabelMargin, time->Top, (CHAR16*)text, 
			time->BGColor |  ColorTime );

	DrawStringWithAttribute( time->Left +  time->LabelMargin +1 , time->Top, 
			( (time->Sel==0) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Hour,txt), 
			(UINT8)((((time->Sel == 0) && (time->ControlFocus)) ? 
					 time->SelBGColor  | time->SelFGColor : 
					 time->BGColor | ColorTime  )) );

	DrawStringWithAttribute( time->Left +  time->LabelMargin + 4 , time->Top, 
			( (time->Sel==1) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Minute,txt), 
			(UINT8)(  (((time->Sel == 1) && (time->ControlFocus)) ? 
					   time->SelBGColor  | time->SelFGColor :
					   time->BGColor | ColorTime  )) );

	DrawStringWithAttribute( time->Left + time->LabelMargin +7 , time->Top, 
			( (time->Sel==2) && (time->ControlActive == TRUE ) ) ? TimeTempNum :StrZeroPad( time->EditTime->Second,txt), 
			(UINT8)( (((time->Sel == 2) && (time->ControlFocus)) ? 
					  time->SelBGColor  | time->SelFGColor :
					  time->BGColor |  ColorTime  )) );

	FlushLines(time->Top, time->Top);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeHandleAction
//
// Description:	function to handle the actions of time
//
// Input:	TIME_DATA *time, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeHandleAction( TIME_DATA *time, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if(time->ControlActive)
			return Status;

        if (0 == time->ControlData.ControlFlags.ControlRefresh)     //EIP61650 If control not has refresh no need of proceeding
            return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;

		if( --(time->Interval) == 0 )
		{
			// initialize the interval
			time->Interval = (UINT8)(time->ControlData.ControlFlags.ControlRefresh);
            return UefiRefershQuestionValueNvRAM(&(time->ControlData));
		}
		else
			return Status;
	} 

	if ( ! time->ControlFocus )
		return Status;

    if (( Data->Input.Type == ACTION_TYPE_KEY )||(Data->Input.Type == ACTION_TYPE_MOUSE))
        return _TimeHandleActionKeyMouse(time, Data);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeHandleActionKeyMouse
//
// Description:	function to handle the action key of time
//
// Input:	TIME_DATA *time,  ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _TimeHandleActionKeyMouse(TIME_DATA *time, ACTION_DATA *Data)
{
	CONTROL_ACTION Action = ControlActionUnknown;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_TIME Tm;
	AMI_EFI_KEY_DATA key = Data->Input.Data.AmiKey;
    if(time->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;


    //Get time
	//gRT->GetTime( &Tm, NULL );
	UefiGetTime(&time->ControlData, &Tm);
	

    //Get mapping
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
      Action = MapControlKeysHook(key);
	}
	else if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
		
			//check whether MouseTop is within the Height and Width of Time Control or not
			if((Data->Input.Data.MouseInfo.Top >= (UINT32)time->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(time->Top+time->Height)) &&
			  (Data->Input.Data.MouseInfo.Left >= (UINT32)time->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(time->Left+time->Width)))//EIP-123727
			{
				Action = ControlActionSelect;		
			}
		}
	}

    switch(Action)
    {
        case ControlActionNextLeft:
//#if !SETUP_STYLE_EZPORT
#if SETUP_STYLE_AWARD
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 0 )
				time->Sel = 2;
			else
				time->Sel--;

			Status = EFI_SUCCESS;
        break;
#endif

        case ControlActionNextRight:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

#if SETUP_STYLE_AWARD
			if ( time->Sel == 2 )
				time->Sel = 0;
			else
				time->Sel++;

			Status = EFI_SUCCESS;
#endif
        break;

        case ControlActionNextUp:
        case ControlActionNextDown:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);
        break;

        case ControlActionAbort:
			if ( time->ControlActive )
			{
				time->ControlActive = FALSE;
				Status = EFI_SUCCESS;
            }					
        break;

        case ControlActionSelect:
			if(Data->Input.Type == ACTION_TYPE_MOUSE)
			NumericSoftKbdInit();			
			_TimeUpdateEntry(time);
            _TimeUpdateHelp( time );
// for EZPORT: expressely to go to next entry in time control after hitting enter
//#if ! SETUP_STYLE_EZPORT
#if SETUP_STYLE_AWARD
		break;
#endif
        case ControlActionNextSelection:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 2 )
				time->Sel = 0;
			else
				time->Sel++;

			Status = EFI_SUCCESS; 
		break;

        case ControlActionPrevSelection:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);

			if ( time->Sel == 0 )
				time->Sel = 2;
			else
				time->Sel--;

			Status = EFI_SUCCESS; 
		break;
        case ControlActionDecreament:
			if(time->ControlActive)
            {
                _TimeUpdateEntry(time);
            }
			_TimeDecrease( time );
			time->ControlActive = TRUE; //Set control state to active, so that control string is updated with the static time string
			Status = EFI_SUCCESS;
        break;

        case ControlActionIncreament:
            if(time->ControlActive)
            {
                _TimeUpdateEntry(time);
            }
			_TimeIncrease( time );
			time->ControlActive = TRUE; //Set control state to active, so that control string is updated with the static time string
			Status = EFI_SUCCESS;
        break;

        case ControlActionNumeric:
			if( !(time->ControlActive))
			{
				time->ControlActive = TRUE;
				switch(time->Sel)
				{
					case 0: //month
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Hour);			
						break;
					case 1: // day
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Minute);			
						break;
					case 2: //year
						SPrint(TimeTempNum,sizeof(TimeTempNum),L"%d", time->EditTime->Second );			
						break;
				}
			}


			if(EfiStrLen(TimeTempNum)>1)
				TimeTempNum[0] = TimeTempNum[1];

			TimeTempNum[1] = key.Key.UnicodeChar;
			Status = gTime.Draw(time);
        break;
        default:
			if ( time->ControlActive )
				_TimeUpdateEntry(time);
        break;
    }

	if( (((!time->ControlActive)||(!IsMouseClickedonSoftkbd())) && (TSEMouseIgnoreMouseActionHook() == TRUE) )&&
		(((Data->Input.Type == ACTION_TYPE_KEY) &&
		((Action == ControlActionNextLeft) ||(Action == ControlActionNextRight) ||(Action == ControlActionNextUp) ||(Action == ControlActionNextDown) ||(Action == ControlActionPageUp) ||(Action == ControlActionPageDown) ||(Action == ControlActionAbort) ||(Action == ControlActionHome) ||(Action == ControlActionEnd) ||(CheckKeyinHotKeysList(key))) ) ||
		((Data->Input.Type == ACTION_TYPE_MOUSE)&&((!((Data->Input.Data.MouseInfo.Top >= (UINT32)time->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(time->Top+time->Height))&&(Data->Input.Data.MouseInfo.Left >= (UINT32)time->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(time->Left+time->Width))))||(Action == ControlActionAbort))))
		)
	{
		NumericSoftKbdExit();//EIP62763 : Check for softkbd presence and existing the numeric softkbd 
	}
	_TimeUpdateHelp( time );
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetCallback
//
// Description:	Function to set callback.
//
// Input:		TIME_DATA *time, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetCallback( TIME_DATA *time, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetFocus
//
// Description:	Function to set focus.
//
// Input:		TIME_DATA *time, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetFocus(TIME_DATA *time, BOOLEAN focus)
{
	if(focus != FALSE)
	{
		if ( CheckControlCondition( &time->ControlData ) )
			return EFI_UNSUPPORTED;
	}

	if( !(time->ControlFocus && focus) )
	{
		time->ControlFocus = focus;
		// set the selected field to Hour
		time->Sel = 0;
		_TimeUpdateHelp( time );
	}

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetPosition
//
// Description:	Function to set position.
//
// Input:		TIME_DATA *time, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetPosition(TIME_DATA *time, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( (CONTROL_DATA*)time, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetDimensions
//
// Description:	Function to set time dimension.
//
// Input:		TIME_DATA *time, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetDimensions(TIME_DATA *time, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions((CONTROL_DATA*) time, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeSetAttributes
//
// Description:	Function to set time attributes.
//
// Input:		TIME_DATA *time, UINT8 FGColor, UINT8 BGColor 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeSetAttributes(TIME_DATA *time, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( (CONTROL_DATA*)time, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeGetControlHeight
//
// Description:	Function to set time height.
//
// Input:		TIME_DATA *time, frame, UINT16 *height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimeGetControlHeight(TIME_DATA *time,VOID *frame , UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		*height = 1;	
		Width = (UINT16)(time->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gControlLeftPad));
		text = HiiGetString( time->ControlData.ControlHandle, UefiGetPromptField(time->ControlData.ControlPtr));
	
		newText = StringWrapText( text, Width, height );
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeUpdateHelp
//
// Description:	function to update the help of time
//
// Input:		TIME_DATA *time
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeUpdateHelp( TIME_DATA *time )
{
	UINT16	helpToken = time->ControlData.ControlHelp;

	switch ( time->Sel )
	{
		case 0:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_HOUR,&helpToken,&time->Min,&time->Max);
			break;

		case 1:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_MIN,&helpToken,&time->Min,&time->Max);
			break;

		case 2:
			UefiGetDateTimeDetails(time->ControlData.ControlPtr,AMI_TIME_SEC,&helpToken,&time->Min,&time->Max);
			break;
		default:
			break;
	}

	time->ControlData.ControlHelp = helpToken;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_TimeUpdateEntry
//
// Description:	function to update the entries in Time
//
// Input:	TIME_DATA *time
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _TimeUpdateEntry(TIME_DATA *time)
{
	if ( time->ControlActive )
	{
		// focus stays on the selection becuase we just edited it
		switch ( time->Sel )
		{
			case 0:
				time->EditTime->Hour = (UINT8)atoi_base(TimeTempNum, 10);
				break;
			case 1:
				time->EditTime->Minute = (UINT8)atoi_base(TimeTempNum, 10);
				break;
			case 2:
				time->EditTime->Second = (UINT8)atoi_base(TimeTempNum, 10);
				break;
			}

		UefiPreControlUpdate(&(time->ControlData));	
		UefiSetTime(&time->ControlData, time->EditTime);
		//For interactive time control invoke the formcallback functions
		if(UefiIsInteractive(&time->ControlData)){//code for callback based on interactive time control
			UINT8 Flags = UefiGetFlagsField(time->ControlData.ControlPtr) ;
			
			
			if(CheckTimeFlags(Flags))
			{
				//for storage type QF_TIME_STORAGE_NORMAL generate time in EFI_HII_TIME format
				
				//Call the callbacks passing the generated input value and value size
//				Status = CallFormCallBack(&time->ControlData, UefiGetControlKey(&time->ControlData), 0, AMI_CALLBACK_CONTROL_UPDATE);
				 CallFormCallBack(&time->ControlData, UefiGetControlKey(&time->ControlData), 0, AMI_CALLBACK_CONTROL_UPDATE);
			} //else {
				//This case would be handled by UefiSetTime() outside
				//since this case is directly updated using the runtime services
			//}
		}
		//gRT->SetTime( &EditTime ); 
		time->ControlActive = FALSE;
	}
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
