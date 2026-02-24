---
layout: default
---

# Armory

The Armory is a powerful feature that allows you to preview all armor pieces, weapons and costumes in the game in all colors on your character. This tool is useful for planning your character's appearance or simply exploring the vast array of appearance options available in Guild Wars.

## Notes

- The Armory only changes the appearance of your character in your Guild Wars client. Other players will still see your actual equipped armor.
- Some special armors or costumes may not be available for preview.
- There is currently no way to keep the applied armor appearance permanently. However, you can automatically reapply it every time you zone by using the Hotkeys module. See the [Tips](#tips) section below.

## Settings

{% include settings_intro.html %}

The top left of the window shows your current character's primary profession, which restricts the armor choices offered by the Armory. If you want to try out armor pieces of another profession, you will need to log in with a character of that primary profession. Costumes and weapons are not restricted this way.

<ul>
<li>{% include off.html %} <strong>Use the same colour for all pieces:</strong> When this is selected, all armour pieces will be coloured this way.</li>
</ul>

A campaign selector dropdown lets you narrow the skin options by campaign.

A **Reset** button in the top right corner lets you restore your character's real appearance.

Your currently selected skin is highlighted with green in each section. (By default these are your actually equipped skins.) Click on any other piece to switch to that. The **None** button imitates an empty equipment slot.

If you right click a piece, you can click the **Copy chat command** to use with the Hotkeys module, or click **Guild Wars Wiki** to look up the piece on the wiki, if you want to actually acquire it.

The four squares next to the equipment slot name show the currently selected dyes and lets you change them. You can choose from Guild Wars's 12 dye options for each slot. You can find more information about the usage and mixing of dyes on the [official wiki](https://wiki.guildwars.com/wiki/Dye).

## Tips

Every selection can also be applied by using a [chat command](chat_commands). The correct command format is shown when you hover over or right click an item in the Armory window. For example: `/armory "Imposing Mask" 3 3 3 3`. The text in quotes is the internal armor identifier, and the four numbers after it are the dye channels applied to that piece, which together apply the selected item to your character using the specified dye color values. Right click an item and press **Copy chat command** to copy the command. The **None** selector can also be used via chat. The chat command `/armory reset` will reset to the original character outfit.

### Reapply armor every time you rezone
There is currently no built-in way to keep your previewed armor applied permanently. However, you can use the [Hotkeys](hotkeys) module to automatically reapply your chosen outfit whenever you enter an outpost or explorable area.

#### To set this up:

1. Collect all the chat commands for the outfit you want to use by hovering over the items in the Armory Window.  Right click the item and press **Copy chat command** to copy the command. For example, as a Mesmer:
```
/armory "Imposing Mask" 3 3 3 3
/armory "Obsidian Attire" 3 3 12 12
/armory "Luxon Gloves" 3 3 12 12
/armory "Elite Noble Hose" 3 3 12 12
/armory "Vabbian Footwear" 3 3 12 12
```
2. Open the [Hotkeys](hotkeys) module and create a new hotkey. Set the method to `Send Chat` and the channel to `/Commands`.
3. In the message box, paste the first command *without* the leading slash. Example: `armory "Imposing Mask" 3 3 3 3`
4. Enable the following options: {% include on.html %} **Trigger hotkey when entering explorable area** and {% include on.html %} **Trigger hotkey when entering outpost**
5. Under Character Names, enter the name of the character you want this outfit applied to (press Enter to add it). This prevents the hotkey from affecting all characters and triggering errors because of profession mismatch.
6. Close the Hotkeys window and fast-travel to another outpost to test whether the hotkey is triggering. If set up correctly, the appearance should be applied automatically.
7. Repeat steps 2–6 for each additional `armory` command in your outfit.

#### Hotkey notes

* The game window must be in focus for the trigger to activate.
* You can also group hotkeys to keep your Hotkeys window organized. Refer to the Hotkeys module documentation for details.
* The appearance will be reset to the original for cutscenes.

{% include settings_general_window.html %}

[🡠 back](index)
