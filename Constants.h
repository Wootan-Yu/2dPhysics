#pragma once


const int FPS = 60;
const int PIXEL_PER_METER = 50; //50 pixel = 1 meter (in actual screen)

const float GRAVITY = 9.8f;

//add the additional forces here (in progress)
enum SIMULATION
{
	impulse_and_friction, //0
	drag,                 //1
	weight_and_wind       //2
};