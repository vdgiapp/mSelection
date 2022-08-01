# Upgraded mSelection 
- New UI
- Same to mSelection
- Support dynamic player textdraw
- Custom text above model sprite

## Images
![Image](https://i.imgur.com/qR4qREp.png)

## Include
Include UmSelection in your gamemode and easily using it:

```pawn
#include <UmSelection>
```

## Functions

```pawn
  LoadModelSelectionMenu(f_name[]);
  HideModelSelectionMenu(playerid);
  ShowModelSelectionMenu(playerid, ListID, header_text[], dialogBGcolor, previewBGcolor, tdSelectionColor);
  ShowModelSelectionMenuEx(playerid, items_array[], item_amount, header_text[], extraid, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, tdSelectionColor);
```

## Callbacks

```pawn
  OnPlayerModelSelection(playerid, response, listid, modelid);
  OnPlayerModelSelectionEx(playerid, response, extraid, modelid, extralist_id);
```

## Example:

SkinsList.txt

`modelid text[] Float:RotationX Float:RotationY Float:RotationZ Float:Room`
```txt
1 [ModelID]
2 [ModelID]
5 CustomText
```

VehList.txt

`modelid text[] Float:RotationX Float:RotationY Float:RotationZ Float:Room`
```txt
400 [VehicleName] 1.000000 1.000000 1.000000 1.0
401 [VehicleName] 2.000000 2.000000 2.000000 1.0
```

gamemode.pwn
```pawn
#include <a_samp>
#include <UmSelection>
#include <Pawn.CMD>

new SkinsList, VehList;
public OnGameModeInit()	{
	SkinsList = LoadModelSelectionMenu("SkinsList.txt"); // (scriptfiles/SkinsList.txt)
	VehList = LoadModelSelectionMenu("VehList.txt");
	return 1;
}

cmd:skinlist(playerid, params[]) {
	ShowModelSelectionMenu(playerid, SkinsList, "Danh sach skin");
	return 1;
}

cmd:vehlist(playerid, params[]) {
	ShowModelSelectionMenu(playerid, VehList, "Danh sach phuong tien");
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid) {
	if(listid == SkinsList) {
		if(response) {
			SetPlayerSkin(playerid, modelid);
			// code
		}
	}
	if(listid == VehList) {
		if(response) {
			// code
		}
	}
}
```
