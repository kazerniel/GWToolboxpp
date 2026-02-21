---
layout: default
---

# Settings
The Settings window contains configuration options for all Toolbox features, and provides access to several features that don't have their own [window](windows).

{% include settings_intro.html %}

## Basics

### Top of Settings window

Toolbox displays the current version here, and if it needs updating.

Buttons link to the settings folder and this website.

* {% include off.html %} **Unlock Move All** releases all windows and widgets to be manually re-positioned.
* {% include off.html %} **Clamp growing windows to screen bounds**
* {% include off.html %} **Hide toolbox on loading screens**
* {% include on.html %} **Send anonymous gameplay stats:** Some features of toolbox allow you to contribute to the community by sending in-game data to remote websites
    * Features that use this info:
        * Sending outpost party information to [https://party.gwtoolbox.com](https://party.gwtoolbox.com)
* {% include off.html %} **Hide Settings when entering explorable area**

<h3>Settings of the Settings window itself</h3>
  
<p>You can toggle the window's visibility with the eye icon on the right side of its <a href="settings">Settings</a> header, or in the <a href="main_window">Main Window</a> if you have enabled {% include on.html %} <strong>Show in main window</strong>.</p>

<p>The first <strong>Position</strong> number controls the window's horizontal position on the screen, the second the vertical. You need to disable {% include off.html %} <strong>Lock Position</strong> to be able to see and edit this setting.</p>

<p>The first <strong>Size</strong> number controls the window's horizontal size, the second the vertical. You need to disable {% include off.html %} <strong>Lock Size</strong> to be able to see and edit this setting.</p>

<ul>
<li>{% include off.html %} <strong>Lock Position</strong></li>
<li>{% include off.html %} <strong>Lock Size</strong></li>
<li>{% include off.html %} <strong>Auto Size</strong></li>
<li>{% include on.html %} <strong>Show titlebar</strong></li>
<li>{% include on.html %} <strong>Show close button</strong></li>
<li>{% include on.html %} <strong>Show in main window</strong></li>
</ul>

### Bottom of Settings window

Buttons for saving and loading your Toolbox settings to and from the settings folder.

## Sections

<ul class="multi-column-list">
  <li><strong>General</strong>
    <ul>
      <li><a href="help">Help</a></li>
      <li><a href="theme">Theme</a></li>
      <li><a href="toolbox_settings">Toolbox Settings</a></li>
      <ul>
        <li><a href="main_window">Main Window</a></li>
      </ul>
      <li><a href="audio_settings">Audio Settings</a></li>
      <li><a href="camera_unlock">Camera Unlock</a></li>
      <li><a href="chat_settings">Chat Settings</a>
        <ul>
          <li><a href="chat_filter">Chat Filter</a></li>
        </ul>
      </li>
      <li><a href="game_settings">Game Settings</a></li>
      <li><a href="gw_settings">Guild Wars Settings</a></li>
      <li><a href="hints">In-Game Hints</a></li>
      <li><a href="inventory_settings">Inventory Settings</a></li>
        <ul>
          <li><a href="inventory_settings#inventory-sorting">Inventory Sorting</a></li>
          <li><a href="salvage_info">Salvage Info</a></li>
        </ul>
      <li><a href="item_settings">Item Settings</a>
        <ul>
          <li><a href="item_filter">Item Filter</a></li>
        </ul>
      </li>
      <li><a href="mouse_settings">Mouse Settings</a></li>
      <li><a href="notifications">Notifications</a></li>
      <li><a href="observer_module">Observer Module</a></li>
      <li><a href="party_settings">Party Settings</a></li>
      <ul>
        <li><a href="party_window">Party Window</a></li>
      </ul>
      <li><a href="plugins">Plugins</a></li>
      <li><a href="quest_module">Quest Module</a></li>
      <li><a href="text-to-speech">Text-to-speech</a></li>
      <li>Third Party Integration
        <ul>
          <li><a href="discord">Discord</a></li>
          <li><a href="teamspeak_3">Teamspeak 3</a></li>
          <li><a href="teamspeak_5">Teamspeak 5</a></li>
          <li><a href="twitch">Twitch</a></li>
        </ul>
      </li>
    </ul>
  </li>
  <li><strong>Modules</strong>
    <ul>
      <li id="code-optimiser">Code Optimiser
        <ul>
          <li>Optimises some internal GW functions to improve in-game performance.</li>
        </ul></li>
      <li id="fps-fix">FPS Fix
        <ul>
          <li>Guild Wars limits FPS to 90 even if your monitor refresh rate is higher; this fixes it.</li>
        </ul></li>
      <li><a href="gamepad_module">Gamepad Module</a></li>
      <li><a href="keyboard_layout_fix">Keyboard Layout Fix</a></li>
      <li><a href="party_broadcast">Party Broadcast</a></li>
      <li><a href="price_checker">Price Checker</a></li>
    </ul>
  </li>
  <li><strong>Windows</strong>
    <ul>
      <li><a href="armory">Armory</a></li>
      <li><a href="builds">Builds</a></li>
      <li><a href="completion">Completion</a></li>
      <li><a href="daily_quests">Daily Quests</a></li>
      <li><a href="drop_tracker">Drop Tracker</a></li>
      <li><a href="duping">Duping</a></li>
      <li><a href="enemy_window">Enemy Window</a></li>
      <li><a href="faction_leaderboard">Faction Leaderboard</a></li>
      <li><a href="hero_builds">Hero Builds</a></li>
      <li><a href="hotkeys">Hotkeys</a></li>
      <li><a href="info">Info</a></li>
        <ul>
          <li><a href="resign_log">Resign Log</a></li>
        </ul>
      <li><a href="market_browser">Market Browser</a></li>
      <li><a href="materials">Materials</a></li>
      <li><a href="notepad">Notepad</a></li>
      <li><a href="objectives">Objectives</a></li>
      <li><a href="observer_module#observer-export">Observer Export</a></li>
      <li><a href="observer_module#observer-parties">Observer Parties</a></li>
      <li><a href="observer_module#observer-player">Observer Player</a></li>
      <li><a href="observer_module#observer-target">Observer Target</a></li>
      <li><a href="party_statistics">Party Statistics</a></li>
      <li><a href="pcons">Pcons</a></li>
      <li><a href="reroll">Reroll</a></li>
      <li><a href="target_info">Target Info</a></li>
      <li><a href="trade">Trade</a></li>
      <li><a href="travel">Travel</a></li>
    </ul>
  </li>
  <li><strong>Widgets</strong>
    <ul>
      <li><a href="active_quest_info">Active Quest Info</a></li>
      <li><a href="alcohol">Alcohol</a></li>
      <li><a href="bonds">Bonds</a></li>
      <li><a href="clock">Clock</a></li>
      <li><a href="damage">Damage</a></li>
      <li><a href="distance">Distance</a></li>
      <li><a href="effect_durations">Effect Durations</a></li>
      <li><a href="friend_list">Friend List</a></li>
      <li><a href="health">Health</a></li>
      <li><a href="latency">Latency</a></li>
      <li><a href="minimap">Minimap</a></li>
      <li><a href="mission_map">Mission Map</a></li>
      <li><a href="skill_monitor">Skill Monitor</a></li>
      <li><a href="skillbar">Skillbar</a></li>
      <li><a href="timer">Timer</a></li>
      <li><a href="title_tracker">Title Tracker</a></li>
      <li><a href="vanquish">Vanquish</a></li>
      <li><a href="world_map">World Map</a></li>
    </ul>
  </li>
</ul>

[🡠 back](index)
