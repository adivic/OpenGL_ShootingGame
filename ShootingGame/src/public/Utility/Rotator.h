#pragma once
#ifndef ROTATOR_H
#define ROTATOR_H

struct FRotator {
	float Yaw;
	float Pitch;
	float Roll;

	FRotator(float f1, float f2, float f3) { Yaw = f1; Pitch = f2; Roll = f3; }
	FRotator(float inF = 0.f) { Yaw = Pitch = Roll = inF; }
};
#endif // !ROTATOR_H
