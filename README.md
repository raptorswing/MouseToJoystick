MouseToJoystick
===============

A simple vJoy (virtual joystick) feeder program which converts mouse to joystick. Written in C#. Runs only on Windows.

vJoy is a virtual joystick driver for Windows (see http://vjoystick.sourceforge.net). This program reads data from the mouse and feeds it to vJoy, which simulates a joystick.

I wrote this so that I could play the 1998 win32 version of Tie Fighter without a joystick. Side to side movement of the mouse is mapped to the joystick's X axis. Up/down movement of the mouse is mapped to the joystick's Y axis. Left click is joystick button 1, right click is joystick button 2.

How to use it
=============

1. Compile from source or download the binary (may require .Net Framework install/update)
1. Install the vJoy virtual joystick driver (http://vjoystick.sourceforge.net)
1. Run MouseToJoystick
1. Enjoy using your mouse as a joystick by playing a game (e.g. Tie Fighter).

Fork Changes
============

Added a master key option which lets you toggle the feeding on/off while in game. Lets you use mouse yoke like in FSX.

- The mouse position is saved when toggling off and restored when toggling on again. Avoids erratic yoke inputs.
- Changeable master key.

Seems a bit finicky in MSFS 2020. Doesn't register at first press always. Not sure whats going on. Maybe to much input handling going on in the background.
