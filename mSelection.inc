
/*
	Upgraded Model Selection include

	Model Selection using previews. For SA-MP 0.3x and above.
	- D0erfler 2013
	- Kye 2013
	Version 1.1 - Modified by Giapp
*/

#tryinclude <YSI_Coding\y_hooks>

static mS_VehicleName[212][] = {
   "Landstalker",  "Bravura",  "Buffalo", "Linerunner", "Perennial", "Sentinel",
   "Dumper",  "Firetruck" ,  "Trashmaster" ,  "Stretch",  "Manana",  "Infernus",
   "Voodoo", "Pony",  "Mule", "Cheetah", "Ambulance",  "Leviathan",  "Moonbeam",
   "Esperanto", "Taxi",  "Washington",  "Bobcat",  "Mr Whoopee", "BF Injection",
   "Hunter", "Premier",  "Enforcer",  "Securicar", "Banshee", "Predator", "Bus",
   "Rhino",  "Barracks",  "Hotknife",  "Trailer",  "Previon", "Coach", "Cabbie",
   "Stallion", "Rumpo", "RC Bandit",  "Romero", "Packer", "Monster",  "Admiral",
   "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer",  "Turismo", "Speeder",
   "Reefer", "Tropic", "Flatbed","Yankee", "Caddy", "Solair","Berkley's RC Van",
   "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron","RC Raider","Glendale",
   "Oceanic", "Sanchez", "Sparrow",  "Patriot", "Quad",  "Coastguard", "Dinghy",
   "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",  "Regina",  "Comet", "BMX",
   "Burrito", "Camper", "Marquis", "Baggage", "Dozer","Maverick","News Chopper",
   "Rancher", "FBI Rancher", "Virgo", "Greenwood","Jetmax","Hotring","Sandking",
   "Blista Compact", "Police Maverick", "Boxville", "Benson","Mesa","RC Goblin",
   "Hotring Racer", "Hotring Racer", "Bloodring Banger", "Rancher",  "Super GT",
   "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropdust", "Stunt",
   "Tanker", "RoadTrain", "Nebula", "Majestic", "Buccaneer", "Shamal",  "Hydra",
   "FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona",
   "FBI Truck", "Willard", "Forklift","Tractor","Combine","Feltzer","Remington",
   "Slamvan", "Blade", "Freight", "Streak","Vortex","Vincent","Bullet","Clover",
   "Sadler",  "Firetruck", "Hustler", "Intruder", "Primo", "Cargobob",  "Tampa",
   "Sunrise","Merit","Utility Truck","Nevada", "Yosemite", "Windsor", "Monster",
   "Monster","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RCTiger",
   "Flash","Tahoma","Savanna", "Bandito", "Freight", "Trailer", "Kart", "Mower",
   "Dune",  "Sweeper", "Broadway",  "Tornado",  "AT-400",  "DFT-30",  "Huntley",
   "Stafford", "BF-400", "Newsvan","Tug","Trailer","Emperor","Wayfarer","Euros",
   "Hotdog", "Club", "Trailer", "Trailer","Andromada","Dodo","RC Cam", "Launch",
   "Police Car (LSPD)", "Police Car (SFPD)","Police Car (LVPD)","Police Ranger",
   "Picador",   "S.W.A.T. Van",  "Alpha",   "Phoenix",   "Glendale",   "Sadler",
   "Luggage Trailer","Luggage Trailer","Stair Trailer", "Boxville", "Farm Plow",
   "Utility Trailer"
};

// Callbacks
forward OnPlayerModelSelection(playerid, response, listid, modelid);
forward OnPlayerModelSelectionEx(playerid, response, extraid, modelid, extralist_id);

// settings static lists
#define mS_TOTAL_ITEMS         	1000 // Max amount of items from all lists
#define mS_TOTAL_LISTS			20 // Max amount of lists
#define mS_TOTAL_ROT_ZOOM		100 // Max amount of items using extra information like zoom or rotations

// settings dynamic per player lists
#define mS_CUSTOM_MAX_ITEMS		20
new gCustomList[MAX_PLAYERS][mS_CUSTOM_MAX_ITEMS];
new gCustomExtraList[MAX_PLAYERS][mS_CUSTOM_MAX_ITEMS];

#define mS_INVALID_LISTID		mS_TOTAL_LISTS
#define mS_CUSTOM_LISTID		(mS_TOTAL_LISTS+1)

#define mS_NEXT_TEXT   ">>>"
#define mS_PREV_TEXT   "<<<"
#define mS_CANCEL_TEXT   "X"

#define mS_SELECTION_ITEMS 		21
#define mS_ITEMS_PER_LINE  		7
#define mS_DIALOG_BASE_X   	75.0
#define mS_DIALOG_BASE_Y   	130.0
#define mS_DIALOG_WIDTH    	550.0
#define mS_DIALOG_HEIGHT   	180.0
#define mS_SPRITE_DIM_X    	60.0
#define mS_SPRITE_DIM_Y    	70.0

new PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS];
new PlayerText:gHeaderTextDrawId[MAX_PLAYERS];
new PlayerText:gBackgroundTextDrawId[MAX_PLAYERS];
new PlayerText:gNextButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gCancelButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gSelectionItems[MAX_PLAYERS][mS_SELECTION_ITEMS];
new PlayerText:gSelectionItemName[MAX_PLAYERS][mS_SELECTION_ITEMS];
new gSelectionItemsTag[MAX_PLAYERS][mS_SELECTION_ITEMS];
new gSelectionItemsExtra[MAX_PLAYERS][mS_SELECTION_ITEMS];
new gItemAt[MAX_PLAYERS];

#define mS_LIST_START			0
#define mS_LIST_END				1
new gLists[mS_TOTAL_LISTS][2]; // list information start/end index

#define mS_ITEM_MODEL			0
#define mS_ITEM_ROT_ZOOM_ID 	1
new gItemList[mS_TOTAL_ITEMS][2];
new gItemName[mS_TOTAL_LISTS][mS_TOTAL_ITEMS][32];

new Float:gRotZoom[mS_TOTAL_ROT_ZOOM][4]; // Array for saving rotation and zoom info
new gItemAmount = 0; // Amount of items used
new gListAmount = 0; // Amount of lists used
new gRotZoomAmount = 0; // Amount of Rotation/Zoom informations used


//------------------------------------------------

stock mS_GetNumberOfPages(ListID)
{
	new ItemAmount = mS_GetAmountOfListItems(ListID);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
	{
		return (ItemAmount / mS_SELECTION_ITEMS);
	}
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetNumberOfPagesEx(playerid)
{
	new ItemAmount = mS_GetAmountOfListItemsEx(playerid);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
	{
		return (ItemAmount / mS_SELECTION_ITEMS);
	}
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetAmountOfListItems(ListID)
{
	return (gLists[ListID][mS_LIST_END] - gLists[ListID][mS_LIST_START])+1;
}

//------------------------------------------------

stock mS_GetAmountOfListItemsEx(playerid)
{
	return GetPVarInt(playerid, "mS_custom_item_amount");
}

//------------------------------------------------

stock mS_GetPlayerCurrentListID(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1) return GetPVarInt(playerid, "mS_list_id");
	else return mS_INVALID_LISTID;
}

//------------------------------------------------

stock PlayerText:mS_CreateCurrentPageTextDraw(playerid, Float:Xpos, Float:Ypos)
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, "0/0");
   	PlayerTextDrawUseBox(playerid, txtInit, false);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.5);
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColour(playerid, txtInit, 1296911871);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------
// Creates a button textdraw and returns the textdraw ID.

stock PlayerText:mS_CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, const button_text[], bColour = 0x000000FF, tColour = 0xFFFFFFFF)
{
 	new PlayerText:txtInit;
 	static btn_text[128]; format(btn_text, sizeof btn_text, "%s", button_text);
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, btn_text);
   	PlayerTextDrawUseBox(playerid, txtInit, true);
   	PlayerTextDrawBoxColour(playerid, txtInit, bColour);
   	PlayerTextDrawBackgroundColour(playerid, txtInit, bColour);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.3, 1.1);
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColour(playerid, txtInit, tColour);
    PlayerTextDrawSetSelectable(playerid, txtInit, true);
    PlayerTextDrawAlignment(playerid, txtInit, TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
 
//------------------------------------------------

stock PlayerText:mS_CreatePlayerHeaderTextDraw(playerid, Float:Xpos, Float:Ypos, const header_text[])
{
	new PlayerText:txtInit;
	static head_text[128]; format(head_text, sizeof head_text, "%s", header_text);
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, head_text);
   	PlayerTextDrawUseBox(playerid, txtInit, false);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.5);
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColour(playerid, txtInit, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, txtInit);
    PlayerTextDrawSetString(playerid, txtInit, head_text);
    return txtInit;
}

//------------------------------------------------

stock PlayerText:mS_CreatePlayerBGTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, bgColour)
{
	new PlayerText:txtBackground = CreatePlayerTextDraw(playerid, Xpos, Ypos,"                                            ~n~"); // enough space for everyone
    PlayerTextDrawUseBox(playerid, txtBackground, true);
    PlayerTextDrawBoxColour(playerid, txtBackground, bgColour);
	PlayerTextDrawLetterSize(playerid, txtBackground, 5.0, 5.0);
	PlayerTextDrawFont(playerid, txtBackground, TEXT_DRAW_FONT_0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    PlayerTextDrawColour(playerid, txtBackground,0x000000FF);
    PlayerTextDrawTextSize(playerid, txtBackground, Width, Height);
   	PlayerTextDrawBackgroundColour(playerid, txtBackground, bgColour);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}

//------------------------------------------------
// Creates a model preview sprite

stock PlayerText:mS_CreateMPTextDraw(playerid, modelindex, Float:Xpos, Float:Ypos, Float:Xrot, Float:Yrot, Float:Zrot, Float:mZoom, Float:width, Float:height, bgColour)
{
    new PlayerText:txtPlayerSprite = CreatePlayerTextDraw(playerid, Xpos, Ypos, ""); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColour(playerid, txtPlayerSprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColour(playerid, txtPlayerSprite, bgColour);
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);
    PlayerTextDrawSetPreviewRot(playerid,txtPlayerSprite, Xrot, Yrot, Zrot, mZoom);
    PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, true);
    PlayerTextDrawShow(playerid, txtPlayerSprite);
    return txtPlayerSprite;
}

//------------------------------------------------
// Creates a name above model preview sprite

stock PlayerText:mS_CreateMPNameTD(playerid, Float:Xpos, Float:Ypos, const itemname[])
{
    new PlayerText:txtPlayerItemName;
    static itemn[128]; format(itemn, sizeof itemn, "%s", itemname);
    txtPlayerItemName = CreatePlayerTextDraw(playerid, Xpos, Ypos, itemn);
    PlayerTextDrawUseBox(playerid, txtPlayerItemName, false);
	PlayerTextDrawLetterSize(playerid, txtPlayerItemName, 0.18, 0.8);
	PlayerTextDrawFont(playerid, txtPlayerItemName, TEXT_DRAW_FONT_1);
	PlayerTextDrawSetShadow(playerid, txtPlayerItemName, 0);
    PlayerTextDrawSetOutline(playerid, txtPlayerItemName, 0);
    PlayerTextDrawColour(playerid, txtPlayerItemName, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, txtPlayerItemName);
    PlayerTextDrawSetString(playerid, txtPlayerItemName, itemn);
    return txtPlayerItemName;
}

//------------------------------------------------

stock mS_DestroyPlayerMPs(playerid)
{
	new x=0;
	while(x != mS_SELECTION_ITEMS) {
	    if(gSelectionItems[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
			PlayerTextDrawDestroy(playerid, gSelectionItems[playerid][x]);
			gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		}
		x++;
	}
}

stock mS_DestroyPlayerMPName(playerid)
{
	new x=0;
	while(x != mS_SELECTION_ITEMS) {
	    if(gSelectionItemName[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
			PlayerTextDrawDestroy(playerid, gSelectionItemName[playerid][x]);
			gSelectionItemName[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		}
		x++;
	}
}

//------------------------------------------------

stock mS_ShowPlayerMPs(playerid)
{
	new bgColour = GetPVarInt(playerid, "mS_previewBGColour");
    new x=0;
	new Float:BaseX = mS_DIALOG_BASE_X;
	new Float:BaseY = mS_DIALOG_BASE_Y - (mS_SPRITE_DIM_Y * 0.33); // down a bit
	new linetracker = 0;
	
	new mS_listID = mS_GetPlayerCurrentListID(playerid);
	if(mS_listID == mS_CUSTOM_LISTID)
	{
		new itemat = (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS);
		new Float:rotzoom[4];
		rotzoom[0] = GetPVarFloat(playerid, "mS_custom_Xrot");
		rotzoom[1] = GetPVarFloat(playerid, "mS_custom_Yrot");
		rotzoom[2] = GetPVarFloat(playerid, "mS_custom_Zrot");
		rotzoom[3] = GetPVarFloat(playerid, "mS_custom_Zoom");
		new itemamount = mS_GetAmountOfListItemsEx(playerid);
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);
		mS_DestroyPlayerMPName(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (itemamount)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gCustomList[playerid][itemat], BaseX, BaseY, rotzoom[0], rotzoom[1], rotzoom[2], rotzoom[3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgColour);
			gSelectionItemName[playerid][x] = mS_CreateMPNameTD(playerid, BaseX+2, BaseY+2, gItemName[mS_listID][itemat]);
			gSelectionItemsTag[playerid][x] = gCustomList[playerid][itemat];
			gSelectionItemsExtra[playerid][x] = gCustomExtraList[playerid][itemat];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
	else
	{
		new itemat = (gLists[mS_listID][mS_LIST_START] + (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS));
		
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);
		mS_DestroyPlayerMPName(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (gLists[mS_listID][mS_LIST_END]+1)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			new rzID = gItemList[itemat][mS_ITEM_ROT_ZOOM_ID]; // avoid long line
			if(rzID > -1) {
				gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, gRotZoom[rzID][0], gRotZoom[rzID][1], gRotZoom[rzID][2], gRotZoom[rzID][3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgColour);
				gSelectionItemName[playerid][x] = mS_CreateMPNameTD(playerid, BaseX+2, BaseY+2, gItemName[mS_listID][itemat]);
			}
			else {
				gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, 0.0, 0.0, 0.0, 1.0, mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgColour);
				gSelectionItemName[playerid][x] = mS_CreateMPNameTD(playerid, BaseX+2, BaseY+2, gItemName[mS_listID][itemat]);
			}
			gSelectionItemsTag[playerid][x] = gItemList[itemat][mS_ITEM_MODEL];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
}

//------------------------------------------------

stock mS_UpdatePageTextDraw(playerid)
{
	new PageText[64+1];
	new listID = mS_GetPlayerCurrentListID(playerid);
	if(listID == mS_CUSTOM_LISTID)
	{
		format(PageText, 64, "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPagesEx(playerid));
		PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
	}
	else
	{
		format(PageText, 64, "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPages(listID));
		PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
	}
}

//------------------------------------------------

stock ShowModelSelectionMenu(playerid, ListID, const header_text[], dialogBGColour = 0x1C2024FF, previewBGColour = 0x88888899 , tdSelectionColour = 0xFFFF00AA)
{
	if(!(0 <= ListID < mS_TOTAL_LISTS && gLists[ListID][mS_LIST_START] != gLists[ListID][mS_LIST_END])) return 0;
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_list_page", 0);
	SetPVarInt(playerid, "mS_list_id", ListID);
	SetPVarInt(playerid, "mS_list_active", 1);
	SetPVarInt(playerid, "mS_list_time", GetTickCount());

    gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X + 15.0, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH - 15.0, mS_DIALOG_HEIGHT, dialogBGColour);
    gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X + 25.0, mS_DIALOG_BASE_Y + 25.0, header_text);
    gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_BASE_X + 25.0, mS_DIALOG_BASE_Y + 267.0);
    gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 51.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT + 90.0, 50.0, 16.0, mS_NEXT_TEXT, 1296911871);
    gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 111.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT + 90.0, 50.0, 16.0, mS_PREV_TEXT, 1296911871);
    gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 51.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT - 152.0, 50.0, 16.0, mS_CANCEL_TEXT, 0xED2F21FF, 0xFFFFFFFF);

	SetPVarInt(playerid, "mS_previewBGColour", previewBGColour);
    mS_ShowPlayerMPs(playerid);
    mS_UpdatePageTextDraw(playerid);
	
	SelectTextDraw(playerid, tdSelectionColour);
	return 1;
}

//------------------------------------------------------------

stock ShowModelSelectionMenuEx(playerid, const items_array[], item_amount, const header_text[], extraid, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGColour = 0x4A5A6BBB, previewBGColour = 0x88888899 , tdSelectionColour = 0xFFFF00AA)
{
	mS_DestroySelectionMenu(playerid);
	if(item_amount > mS_CUSTOM_MAX_ITEMS)
	{
		item_amount = mS_CUSTOM_MAX_ITEMS;
		print("-mSelection- WARNING: Too many items given to \"ShowModelSelectionMenuEx\", increase \"mS_CUSTOM_MAX_ITEMS\" to fix this");
	}
	if(item_amount > 0)
	{
		for(new i=0;i<item_amount;i++)
		{
			gCustomList[playerid][i] = items_array[i];
		}
		SetPVarInt(playerid, "mS_list_page", 0);
		SetPVarInt(playerid, "mS_list_id", mS_CUSTOM_LISTID);
		SetPVarInt(playerid, "mS_list_active", 1);
		SetPVarInt(playerid, "mS_list_time", GetTickCount());
	
		SetPVarInt(playerid, "mS_custom_item_amount", item_amount);
		SetPVarFloat(playerid, "mS_custom_Xrot", Xrot);
		SetPVarFloat(playerid, "mS_custom_Yrot", Yrot);
		SetPVarFloat(playerid, "mS_custom_Zrot", Zrot);
		SetPVarFloat(playerid, "mS_custom_Zoom", mZoom);
		SetPVarInt(playerid, "mS_custom_extraid", extraid);
		

		gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X + 15.0, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH - 15.0, mS_DIALOG_HEIGHT, dialogBGColour);
		gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X + 25.0, mS_DIALOG_BASE_Y + 25.0, header_text);
		gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_BASE_X + 25.0, mS_DIALOG_BASE_Y + 267.0);
		gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 51.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT + 90.0, 50.0, 16.0, mS_NEXT_TEXT, 1296911871);
		gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 111.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT + 90.0, 50.0, 16.0, mS_PREV_TEXT, 1296911871);
		gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 51.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT - 152.0, 50.0, 16.0, mS_CANCEL_TEXT, 0xED2F21FF, 0xFFFFFFFF);

		SetPVarInt(playerid, "mS_previewBGColour", previewBGColour);
		mS_ShowPlayerMPs(playerid);
		mS_UpdatePageTextDraw(playerid);
		
		SelectTextDraw(playerid, tdSelectionColour);
		return 1;
	}
	return 0;
}

//------------------------------------------------

stock HideModelSelectionMenu(playerid)
{
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_ignore_next_esc", 1);
	CancelSelectTextDraw(playerid);
	return 1;
}

//------------------------------------------------

stock mS_DestroySelectionMenu(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1)
	{
		if(mS_GetPlayerCurrentListID(playerid) == mS_CUSTOM_LISTID)
		{		
			DeletePVar(playerid, "mS_custom_Xrot");
			DeletePVar(playerid, "mS_custom_Yrot");
			DeletePVar(playerid, "mS_custom_Zrot");
			DeletePVar(playerid, "mS_custom_Zoom");
			DeletePVar(playerid, "mS_custom_extraid");
			DeletePVar(playerid, "mS_custom_item_amount");
		}
		DeletePVar(playerid, "mS_list_time");
		SetPVarInt(playerid, "mS_list_active", 0);

		mS_DestroyPlayerMPs(playerid);
		mS_DestroyPlayerMPName(playerid);

		PlayerTextDrawDestroy(playerid, gHeaderTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gBackgroundTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCurrentPageTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gNextButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gPrevButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCancelButtonTextDrawId[playerid]);

		gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;	
		gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
}

//------------------------------------------------

public OnPlayerConnect(playerid)
{
	// Init all of the textdraw related globals
    gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    
    for(new x=0; x < mS_SELECTION_ITEMS; x++) {
        gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
        gSelectionItemName[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}
	
	gItemAt[playerid] = 0;
	
	return CallLocalFunction("MP_OPC", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect MP_OPC

forward MP_OPC(playerid);

//-------------------------------------------
// Even though only Player* textdraws are used in this script,
// OnPlayerClickTextDraw is still required to handle ESC
#if defined _INC_textdraw_streamer
	hook OnClickDynamicTextDraw(playerid, Text:clickedid)
#else
	hook OnPlayerClickTextDraw(playerid, Text:clickedid)
#endif
{
   	if(GetPVarInt(playerid, "mS_ignore_next_esc") == 1) {
		SetPVarInt(playerid, "mS_ignore_next_esc", 0);
		return 1;
	}
   	if(GetPVarInt(playerid, "mS_list_active") == 0) return 1;

	// Handle: They cancelled (with ESC)
	if(clickedid == Text:INVALID_TEXT_DRAW) {
		new listid = mS_GetPlayerCurrentListID(playerid);
		if(listid == mS_CUSTOM_LISTID)
		{
			new extraid = GetPVarInt(playerid, "mS_custom_extraid");
			mS_DestroySelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 0, extraid, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		else
		{
			mS_DestroySelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelection", "dddd", playerid, 0, listid, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
        return 1;
	}
	
	return Y_HOOKS_CONTINUE_RETURN_1;
}

//------------------------------------------------

#if defined _INC_textdraw_streamer
	hook OnClickDynamicPlayerTextDraw(playerid, PlayerText:playertextid)
#else
	hook OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#endif
{
	if(GetPVarInt(playerid, "mS_list_active") == 0 || (GetTickCount()-GetPVarInt(playerid, "mS_list_time")) < 200 /* Disable instant selection */) return 1;

	new curpage = GetPVarInt(playerid, "mS_list_page");
	
	// Handle: cancel button
	if(playertextid == gCancelButtonTextDrawId[playerid]) {
		new listID = mS_GetPlayerCurrentListID(playerid);
		if(listID == mS_CUSTOM_LISTID)
		{
			new extraid = GetPVarInt(playerid, "mS_custom_extraid");
			HideModelSelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 0, extraid, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		else
		{
			HideModelSelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelection", "dddd", playerid, 0, listID, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
		
	// Handle: next button
	if(playertextid == gNextButtonTextDrawId[playerid]) {
		new listID = mS_GetPlayerCurrentListID(playerid);
		if(listID == mS_CUSTOM_LISTID)
		{			
			if(curpage < (mS_GetNumberOfPagesEx(playerid) - 1)) {
				SetPVarInt(playerid, "mS_list_page", curpage + 1);
				mS_ShowPlayerMPs(playerid);
				mS_UpdatePageTextDraw(playerid);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			} else {
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			if(curpage < (mS_GetNumberOfPages(listID) - 1)) {
				SetPVarInt(playerid, "mS_list_page", curpage + 1);
				mS_ShowPlayerMPs(playerid);
				mS_UpdatePageTextDraw(playerid);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			} else {
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			}
		}
		return 1;
	}
	
	// Handle: previous button
	if(playertextid == gPrevButtonTextDrawId[playerid]) {
	    if(curpage > 0) {
	    	SetPVarInt(playerid, "mS_list_page", curpage - 1);
	    	mS_ShowPlayerMPs(playerid);
	    	mS_UpdatePageTextDraw(playerid);
	    	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
	
	// Search in the array of textdraws used for the items
	new x=0;
	while(x != mS_SELECTION_ITEMS) {
	    if(playertextid == gSelectionItems[playerid][x]) {
			new listID = mS_GetPlayerCurrentListID(playerid);
			if(listID == mS_CUSTOM_LISTID)
			{
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				new item_id = gSelectionItemsTag[playerid][x];
				new extraid = GetPVarInt(playerid, "mS_custom_extraid");
				new extralist_id = gSelectionItemsExtra[playerid][x];
				HideModelSelectionMenu(playerid);
				CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 1, extraid, item_id, extralist_id);
				return 1;
			}
			else
			{
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				new item_id = gSelectionItemsTag[playerid][x];
				HideModelSelectionMenu(playerid);
				CallLocalFunction("OnPlayerModelSelection", "dddd", playerid, 1, listID, item_id);
				return 1;
			}
		}
		x++;
	}
	
	return Y_HOOKS_CONTINUE_RETURN_1;
}

//------------------------------------------------------------------


stock LoadModelSelectionMenu(const f_name[])
{
	new File:f, str[75];
	format(str, sizeof(str), "%s", f_name);
	f = fopen(str, io_read);
	if( !f ) {
		printf("-mSelection- WARNING: Failed to load list: \"%s\"", f_name);
		return mS_INVALID_LISTID;
	}
	
	if(gListAmount >= mS_TOTAL_LISTS)
	{
		printf("-mSelection- WARNING: Reached maximum amount of lists, increase \"mS_TOTAL_LISTS\"", f_name);
		return mS_INVALID_LISTID;
	}
	new tmp_ItemAmount = gItemAmount; // copy value if loading fails
	
	new line[128], idxx;
	while(fread(f,line,sizeof(line),false))
	{
		if(tmp_ItemAmount >= mS_TOTAL_ITEMS)
		{
			printf("-mSelection- WARNING: Reached maximum amount of items, increase \"mS_TOTAL_ITEMS\"", f_name);
			break;
		}
		idxx = 0;
		if(!line[0]) continue;
		new mID = strval(mS_strtok(line,idxx));
		if(0 <= mID < 20000)
		{
			gItemList[tmp_ItemAmount][mS_ITEM_MODEL] = mID;
		
			new tmp_mS_strtok[32];
			new Float:mRotation[3], Float:mZoom = 1.0;
			new bool:useRotation = false;

			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				if(!strcmp(tmp_mS_strtok, "[ModelID]")) {
					format(gItemName[gListAmount][tmp_ItemAmount], 32, "ID: %d", mID);
				}
				else if(!strcmp(tmp_mS_strtok, "[VehicleName]")) {
					if(400 <= mID <= 611) format(gItemName[gListAmount][tmp_ItemAmount], 32, "%s", mS_VehicleName[mID-400]);
					else format(gItemName[gListAmount][tmp_ItemAmount], 32, "ID: %d", mID);
				}
				else format(gItemName[gListAmount][tmp_ItemAmount], 32, "%s", tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[0] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[1] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[2] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mZoom = floatstr(tmp_mS_strtok);
			}
			if(useRotation)	{
				new bool:foundRotZoom = false;
				for(new i=0; i < gRotZoomAmount; i++)
				{
					if(gRotZoom[i][0] == mRotation[0] && gRotZoom[i][1] == mRotation[1] && gRotZoom[i][2] == mRotation[2] && gRotZoom[i][3] == mZoom)
					{
						foundRotZoom = true;
						gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = i;
						break;
					}
				}
				if(gRotZoomAmount < mS_TOTAL_ROT_ZOOM)
				{
					if(!foundRotZoom)
					{
						gRotZoom[gRotZoomAmount][0] = mRotation[0];
						gRotZoom[gRotZoomAmount][1] = mRotation[1];
						gRotZoom[gRotZoomAmount][2] = mRotation[2];
						gRotZoom[gRotZoomAmount][3] = mZoom;
						gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = gRotZoomAmount;
						gRotZoomAmount++;
					}
				}
				else print("-mSelection- WARNING: Not able to save rotation/zoom information. Reached maximum rotation/zoom information count. Increase '#define mS_TOTAL_ROT_ZOOM' to fix the issue"); 
			}
			if(!useRotation) gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = -1;

			tmp_ItemAmount++;
		}
	}
	if(tmp_ItemAmount > gItemAmount) // any models loaded ?
	{
		gLists[gListAmount][mS_LIST_START] = gItemAmount;
		gItemAmount = tmp_ItemAmount; // copy back
		gLists[gListAmount][mS_LIST_END] = (gItemAmount-1);
		
		gListAmount++;
		return (gListAmount-1);
	}
	printf("-mSelection- WARNING: No Items found in file: %s", f_name);
	return mS_INVALID_LISTID;
}
			
	
	
stock mS_strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
