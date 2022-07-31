# Upgraded mSelection 
- New UI
- Same to mSelection
- Support dynamic player textdraw
- Custom text above model sprite

![alt text]([http://url/to/img.png](https://imgur.com/qR4qREp))

Include UmSelection in gamemode easily using it:

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

`modelid "text" Float:RotationX Float:RotationY Float:RotationZ Float:Room`
```txt
1 [ModelID]
2 [ModelID]
```

VehList.txt

`modelid "text" Float:RotationX Float:RotationY Float:RotationZ Float:Room`
```txt
400 [VehicleName] 1.000000 1.000000 1.000000
401 [VehicleName] 2.000000 2.000000 2.000000
```

gamemode.pwn
```pawn
new SkinsList, VehList;
public OnGameModeInit()	{
	SkinsList = LoadModelSelectionMenu("SkinsList.txt"); // (scriptfiles/SkinsList.txt)
	VehList = LoadModelSelectionMenu("VehList.txt");
	return 1;
}

ShowSkinsListForPlayer(playerid) {
	ShowModelSelectionMenu(playerid, SkinsList, "Danh sach skin");
	return 1;
}

ShowVehListForPlayer(playerid) {
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
