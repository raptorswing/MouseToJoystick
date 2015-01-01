MouseToJoystick
===============

A simple vJoy (virtual joystick) feeder program which converts mouse to joystick. Written in C++/Qt5. Requires windows because it uses vJoy.

vJoy is a virtual joystick driver for Windows (see http://vjoystick.sourceforge.net). This program reads data from the mouse and feeds it to vJoy, which simulated a joystick.

I wrote this so that I could play the 1998 win32 of Tie Fighter without a joystick. Side to side movement of the mouse is mapped to the joystick's X axis. Up/down movement of the mouse is mapped to the joystick's Y axis. Left click is joystick button 1, right click is joystick button 2.

How to use it
===============
1. Compile from source or download the binary.
2. Install the vJoy virtual joystick driver (http://vjoystick.sourceforge.net)
3. Run MouseToJoystick
4. Double right-click to enable "joystick mode". Your mouse cursor will be centered and deviations from the center when you move the mouse taken as joystick inputs.
5. Enjoy using your mouse as a joystick by playing a game (e.g. Tie Fighter).
6. Double right-click again to disable "joystick mode" when you need your mouse again.

Note: You may want to minimize the MouseToJoystick window while playing a game since the GUI can sometimes "bleed" through the game (at least this seems to to be the case with Tie Fighter).
