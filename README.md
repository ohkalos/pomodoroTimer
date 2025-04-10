# Arduino Pomodoro Timer

A custom-built Pomodoro Timer using an Arduino Uno, designed for productivity and focus. Includes LED indicators, sound chimes, pause/resume functionality, and a physical startup/shutdown toggle.

## Features

- **25-minute work sessions** and **5-minute breaks** (adjustable)
- **LED indicators** for work (red) and break (blue) states
- **Pause/Resume button** to temporarily stop a session
- **Startup/Shutdown button** to toggle power and reset session state
- **Audio chimes** for session transitions, startup, shutdown, pause, and resume
- **Clean state reset** on startup for consistent behavior

## How It Works

- Red LED blinks during work sessions  
- Blue LED blinks during breaks  
- Buzzer plays different chimes based on events (start, end, break, resume, pause)  
- The timer pauses cleanly, preserving time elapsed
- Powering off stops all processes and LEDs, and powering on resets everything

##  Components Used

- Arduino Uno R3
- 1x Buzzer
- 2x LEDs (Red & Blue)
- 2x Push buttons
- Resistors (220Ω for LEDs, 10kΩ for buttons if not using `INPUT_PULLUP`)
- Jumper wires & Breadboard

## Code Overview

The code is written in Arduino C++ and uses `millis()` for non-blocking timing control. A `reset()` function ensures the timer starts fresh each time it’s powered on.

### Core Functions:
- `reset()` — Resets all state variables to default
- `startChime()` / `endChime()` — Audio feedback for power transitions
- `workChime()` / `breakChime()` — Audio feedback for session switching
- `pauseChime()` / `resumeChime()` — Feedback for pause/resume
- `allOn()` / `allOff()` — Turns both LEDs on or off

## Social

Check it out on Instagram: @austrigs
Project by **Austin Ridge**

---
