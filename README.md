# Flux Capacitor Mini

### WHAT IS IT?
A miniature version of Flux Capacitor from the movie trilogy Back to the Future. Measuring at only 48mm x 38mm (1.89in x 1.5in), it can be easily pocketable . It is constructed with high quality 3D printed frame, sandwiched between stacked Gold Plated PCBs. Featuring 24 LEDs, diffused through bare FR4 material, that animate to create the “fluxxing” effect. It’s 100% decorative, it doesn’t actually let you travel through time. But let's not lose hope. Maybe in the future.

![LED Numbers](/Images/Renders/FC_Exploded_View.png)

This mini Flux Capacitor is controlled by a Microchip ATtiny816 microcontroller. By using PWM (Pulse Width Modulation) pins for 8 channels of 3 paralleled LEDs, different animation patterns are generated for the fluxxxing effect. In settings mode, users are able change the animation type, speed, and LED brightness. There are 8 animations, 4 animation speeds, 4 LED brightness levels (100%, 75%, 50% and 25%).

### DEVICE SETTINGS
To set your desired animation, speed and LED brightness, you have to start flux condenser in Settings Mode. In order to do that, first you have to turn off your Flux Capacitor (if it's on) by holding "On/Off" button for 3 seconds **(you always have to hold the "On/Off" button for 3 seconds to turn it on or off)**. While holding the “Start/Set” button on the back turn the Flux Capacitor on by holing "On/Off" button for 3 seconds. You can release both buttons when you see all the LEDs start to light up one by one. Now you're in Settings Mode. Some of the LEDs should be on at full brightness and some very dimly lit (so you can see them through FR4 diffuser) according to the configuration it was set. LEDs on each row of all columns, starting from outer to inner are paralleled. LEDs are numbered as shown in the photo below to represent a setting for each LED.

![Settings](/Images/Featured/Flux_Capacitor_Mini_Front_Settings.png)

The LEDs display the settings in binary. If it's fully lit then it is shows "on state or in binary 1" and if it's very dimly lit then it is shows "off state or 0 in binary". 
Now the combinations of the LEDs numbered 3, 2, and 1 sets your main animation. If you set those LEDs to different on/off states, you get 8 total combinations and on each set combination LEDs animate in different patterns.
LED number 4 displays setting for flashing animation which animates when you press "Start/Set" button in normal operation. With one LED you get only 2 combination either on or off.
LEDs numbered 5 and 6 displays the setting for animation speed. 2 LEDs make 4 total combinations. For each combination LEDs animate very slow, slow, fast or very fast.
LEDs numbered 7 and 8 displays the setting for LED brightness. For each of the 4 combinations LEDs light up at 25%, 50%, 75% or 100%.
All of the combinations, and setting examğles are shown in the tables below.

![Settings](/Images/Settings.png)

You don't have to remember these. There is a QR code on the interior side of back cover PCB. Scan it and it will take you to this page.
To change the LED state, while in Settings Mode, hold the "Start/Set" button. All the LEDs should be turned on very dimly and second after that, starting from LED1 each individual LED gets fully lit. Hold the "Start/Set" button until the fully lit LED reaches the one you want to change. When you change the LED state, if the LED is already set on, it turns off (or dimly lit). If it's at off state (or dimly lit) then it turns on at full brightness. 
If all of this feels complicated to you then I can program the Flux Capacitor with older much simpler version of the firmware by your request. But the older firmware has less functionality. Check it **[HERE](https://www.youtube.com/watch?v=2X2gqoI-mSA)**

Below, all of the LED animations and their LED setting combinations are shown. Also animation patterns might seem different when you run them at different speeds.

https://user-images.githubusercontent.com/43648325/163351795-e4758084-3ac4-411a-833b-632b1832e1c3.mov

https://user-images.githubusercontent.com/43648325/163351857-c6b9a43f-3085-4918-af22-fd343d08b809.mov

https://user-images.githubusercontent.com/43648325/163352711-5db71f97-86e2-47c3-9c65-f71232630f72.mov

https://user-images.githubusercontent.com/43648325/163353298-47ecd2d0-05f4-4908-87b2-38960816e004.mov

### POWER REQUIREMENT
Device requires 1.21 Gigawatts ("Jigowatts") of power to operate. That amount of power is no match for an ordinary power supply. Luckily we've developed a miniature nuclear reactor named LIR2032 that needs to be placed inside the device. LIR2032 also encapsulates a small pellet of Plutonium to be used as fuel to generate enough power. This miniature reactor is able to supply all the power required for the Flux Capacitor. Ok, joke aside this entire paragraph is totally not true.

To really power it, you only need a non-rechargeable CR2032 or rechargeable LIR2032 coin cell battery. Power consumption is drastically lowered. At full brightness, it draws 3.7mA and at 25% brightness it draws 1.8mA of current from the battery. 

CR2032 (Non-Rechargeable) with average of 210mAh battery capacity.

- 100% LED Brightness :  57 Hours
- 25%  LED Brightness :  110 Hours

LIR2032 (Rechargeable) with average of 40mAh battery capacity.

- 100% LED Brightness :  11 Hours
- 25%  LED Brightness :  21 Hours

### WHAT MAKES THIS DEVICE SPECIAL?
First of all, the gold plating on the PCB makes it look luxurious. You can wear it around your neck with an ID card strap, hang it on your keychain or... you can place it on your car's dashboard and try and see if the time travel is possible while you're driving at 88mph. Time travel at your own RISK! If you stuck in unknown territories of time, try turning on the SOS mode of the Flux Capacitor (Animation 5 or 101 LED combination). Help may or may not arrive. NO GUARANTEES. 

### WHAT IS INCLUDED IN YOUR PURCHASE?
- 1x Front Panel. 3 Stacked PCB, with 24 LEDs and All the Electronics Soldered on
- 1x 3D Printed Frame of Your Selection
- 4x M2.5x4mm Screws
- 1x Back Cover PCB

![Teardown](/Images/Featured/Flux_Capacitor_Mini_Teardown.png)

<a href="https://www.tindie.com/stores/curiousdesignlabs/?ref=offsite_badges&utm_source=sellers_Hojadurdy&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>
