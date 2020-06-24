# Elevator-One-Key
This is an elevator for 2 floors. One-button control
----------------------------------------------------
atmega 328p (arduino nano) provided as is
```
KEY            D2     One button 0.5 seconds between clicks
MAIN RELAY     D4     main relay timeout 5 minutes
RELAY UP       D5     relay move up
RELAY DOWN     D6     relay move down
SWITH TOP      D8     switch up
SWITH BOTTOM   D9     switch bottom
```

used library Arduino FreeRTOS ver.10.3.0-9 <https://github.com/feilipu/Arduino_FreeRTOS_Library.git>
