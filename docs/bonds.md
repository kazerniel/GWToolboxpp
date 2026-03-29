---
layout: default
title: Bonds
---

Shows the party's currently active bonds and enchantments near the party window.

You need to equip a maintainable enchantment or refrain to show the bonds widget on-screen.

## Settings

{% include settings_intro.html %}

* {% include off.html %} **Show in main window**
* {% include off.html %} **Hide in outpost**
* {% include off.html %} **Show on top of health bars:** Untick to show this widget to the left (or right) of the party window. Tick to show this widget over the top of the party health bars inside the party window.
* **Party window offset**: Sets the horizontal distance of the Bonds widget from the party window. Negative values place it on the right side of the party window.
  * (Default: 64)

Skills enabled for bond monitor:

<ul class="multi-column-list">
  <li>{% include on.html %} <strong>Balthazar's Spirit</strong></li>
  <li>{% include on.html %} <strong>Essence Bond</strong></li>
  <li>{% include on.html %} <strong>Holy Veil</strong></li>
  <li>{% include on.html %} <strong>Life Attunement</strong></li>
  <li>{% include on.html %} <strong>Life Barrier</strong></li>
  <li>{% include on.html %} <strong>Life Bond</strong></li>
  <li>{% include on.html %} <strong>Live Vicariously</strong></li>
  <li>{% include on.html %} <strong>Mending</strong></li>
  <li>{% include on.html %} <strong>Protective Bond</strong></li>
  <li>{% include on.html %} <strong>Purifying Veil</strong></li>
  <li>{% include on.html %} <strong>Retribution</strong></li>
  <li>{% include on.html %} <strong>Strength of Honor</strong></li>
  <li>{% include on.html %} <strong>Succor</strong></li>
  <li>{% include on.html %} <strong>Vital Blessing</strong></li>
  <li>{% include on.html %} <strong>Watchful Spirit</strong></li>
  <li>{% include off.html %} <strong>Watchful Intervention</strong></li>
  <li>{% include on.html %} <strong>Heroic Refrain</strong></li>
  <li>{% include on.html %} <strong>Burning Refrain</strong></li>
  <li>{% include on.html %} <strong>Mending Refrain</strong></li>
  <li>{% include on.html %} <strong>Bladeturn Refrain</strong></li>
  <li>{% include on.html %} <strong>Hasty Refrain</strong></li>
  <li>{% include off.html %} <strong>Aggressive Refrain</strong></li>
</ul>

**Background:** The background colour of the bonds widget.

The four number fields correspond to:
* Red, Green, Blue, Alpha (opacity)
  * (Default: 0, 0, 0, 76)

If you click on the color swatch, a color picker opens with the default color of <span class="color-swatch" style="color: #0000004C"></span> `#0000004C`. See more information about how Toolbox's color pickers work on the [Theme](theme#Colors) page.

* {% include on.html %} **Click to cast bond**
* {% include on.html %} **Click to cancel bond**
* {% include on.html %} **Show bonds for Allies:** 'Allies' meaning the ones that show in party window, such as summoning stones
* {% include off.html %} **Flip bond order (left/right):** Bond order is based on your build. Check this to flip them left <-> right

**Low Attribute Overlay:** Overlays effects casted with less than current attribute level. Only works for yourself and your heroes and doesn't include bonds.

The four number fields correspond to:
* Alpha (opacity), Red, Green, Blue
  * (Default: 7, 0, 0, 0)

[🡠 back](index)
