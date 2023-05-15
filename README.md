# mna-buttons
A project dedicated to a club at my school. Takes the hardware for the current eyes and trivia programs and makes it better. Interfaces the previous buttons and adds wireless button functionality, making for a theoretical max of 32 buttons allowed for trivia at once.

## Theory
The eyes and trivia programs were coded by a very dedicated member of our club a very long time ago (2011 ish?). I would assume that arduino/hobbyist coding technology wasn't as freely available back then, so they used the internals of a HORI Arcade Pro 3 game controller as a hub for the buttons. Since arduino-based microcontrollers are now widely available and popular, I thought it was about time to update the technology into something a little cooler with actual documentation in case someone wants to pick up from my work in the future. This is where this project was born, implementing wireless buttons to be used for the programs. Since getting rid of all the previous buttons would be a waste, I made it so that you could also use them along with the wireless buttons. The concept of the design involves 3 microcontrollers: 1 for the button sending the press/unpress data, 1 for receiving all the button data, and 1 for HID interfacing into the computer.

## Goals (Listed in a rough order of when to do things, probably)
- [x] Making a breadboard prototype of the wireless buttons to ensure this actually works
- [ ] Hardware-based ID selection for wireless buttons on arduino program startup
- [ ] Interfacing wired and wireless buttons on the program
- [ ] Display for cool button status checking
- [ ] Adding controls on the button receiver hub to (hopefully) make using eyes and trivia easier
- [ ] Design case for buttons, decide which buttons/switches to use for button
- [ ] Prototype pcbs, of course with cool silkscreen art
