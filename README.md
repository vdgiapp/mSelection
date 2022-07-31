# Upgraded mSelection 
- New UI
- Same to mSelection
- Support dynamic player textdraw
- Custom text above model sprite

Include UmSelection in gamemode easily using it:

```pawn
#include <UmSelection>
```

## Functions

```pawn
  LoadModelSelectionMenu(f_name[])
	HideModelSelectionMenu(playerid)
	ShowModelSelectionMenu(playerid, ListID, header_text[], dialogBGcolor, previewBGcolor, tdSelectionColor)
	ShowModelSelectionMenuEx(playerid, items_array[], item_amount, header_text[], extraid, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, tdSelectionColor)
```

## Callbacks

```pawn
  OnPlayerModelSelection(playerid, response, listid, modelid);
  OnPlayerModelSelectionEx(playerid, response, extraid, modelid, extralist_id);
```

## Example:

```pawn
new List;
	public OnGameModeInit()	{
		List = LoadModelSelectionMenu("list.txt"); // (scriptfiles/list.txt)
		return 1;
	}

	public OnPlayerConnect(playerid) {
		ShowModelSelectionMenu(playerid, List, "Danh sach blabla");
		return 1;
	}

	public OnPlayerModelSelection(playerid, response, listid, modelid) {
		if(listid == List) {
			if(response) {
				SetPlayerSkin(playerid, modelid);
			}
			else Kick(playerid);
		}
	}
```
