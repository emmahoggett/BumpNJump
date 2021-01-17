# Microprogrammed embedded systems 2020

## Description

The course's aim is to understand the architectures of microprogrammed embedded systems, the architectures of microprocessors, memory hierarchy and the different I/O devices included, using the Nintendo DS portable platform as a case study.
This project's aim is to develop a full solution on Nintendo DS.
The developped game is a Bump'n'Jump.


## Gameplay
Bump 'n' Jump is an overhead-view vehicular combat game. The goal is to drive while bumping enemy vehicles into the sides of the track and jumping over large obstacles such as bodies of water.
Because of the bird's eye view, players cannot see the large obstacles until it is too late to jump, so the game displays a flashing exclamation point when the large obstacles are about to appear.
The enemy vehicles are cars, that can be jumped upon and destroyed. Players get points for bumping other cars and causing the other cars to crash. 
Players lose if they crash against the roadside, or if they miss the jump.

## Getting Started
The Eclipse software environment was used to write and compile this program for the Nintendo DS (NDS). This software environment was provided during the course, as well as an NDS architecture simulator called DeSmuME, in a virtual machine (VM) that can be downloaded, installed and used in any computer.
This virtual machine runs on an open source virtualization software called VirtualBox. The software is available in different platforms and it can be freely run on most of the popular operating systems (OSs).

## Command
* _RIGHT_ : go right.
* _LEFT_: go left.
* _UP_ : speed up the car.
* _DOWN_ : slow down the car.
* _A_ or _Double Touch_ : jump.
* _START_ : Bring back to start menu.

## Code
* ``` P_Gameplay ``` : Handle the gameplay.
* ```P_Graphics``` : Enables the corresponding VRAM bank to be used.
* ```P_Map16x16``` : Initialize engines' background and sprites.
* ```P_Controls``` : Handle the keys pressed by the player.
* ```P_Audio``` : Initialize and load the sound library.
* ```P_Initializer``` : Initialize the engines, background, timers and audio.
* ```P_Score``` : Update and display the score and the highest score.
* ```P_Timer``` : Initialize the timers (warning, jump and enemy animations).


## Authors
Hoggett Emma,
Durand Mathilde

## Project Status
The project was submitted on the 18 January 2021, as part of the Microprogrammed embedded systems course.
