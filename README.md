# mSelection
This version is modified by Giapp

- Same to mSelection but new UI and custom text
- Support [open.mp](https://github.com/openmultiplayer/open.mp)
- Support [samp-textdraw-streamer](https://github.com/nexquery/samp-textdraw-streamer)

## Images
![Image](https://i.imgur.com/qR4qREp.png)

## Installation
Include in your code and begin using the library:

```pawn
#include <mSelection>
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

## Usage
- [ModelID] = "ID: 1"...
- [VehicleName] = "NRG-500"...

SkinsList.txt

`modelid text[] Float:RotationX Float:RotationY Float:RotationZ Float:Zoom`
```txt
1 [ModelID]
2 [ModelID]
5 CustomText
```

VehList.txt

`modelid text[] Float:RotationX Float:RotationY Float:RotationZ Float:Zoom`
```txt
400 [VehicleName] 1.000000 1.000000 1.000000 1.0
401 _ 2.000000 2.000000 2.000000 1.0
```

gamemode.pwn
```pawn
#include <a_samp>
#include <textdraw-streamer>
#include <mSelection>
#include <Pawn.CMD>

new SkinsList, VehList;
public OnGameModeInit()	{
	SkinsList = LoadModelSelectionMenu("SkinsList.txt"); // (scriptfiles/SkinsList.txt)
	VehList = LoadModelSelectionMenu("VehList.txt");
	return 1;
}

cmd:skinlist(playerid, params[]) {
	ShowModelSelectionMenu(playerid, SkinsList, "Skins list title");
	return 1;
}

cmd:vehlist(playerid, params[]) {
	ShowModelSelectionMenu(playerid, VehList, "Vehicles list title");
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid) {
	if(listid == SkinsList) {
		if(response) {
			// set player skin or something
			// or your work
		}
	}
	if(listid == VehList) {
		if(response) {
                        // create a vehicle or something
			// or your work
		}
	}
}
```
