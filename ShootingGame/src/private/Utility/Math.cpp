#include "Utility/Math.h"

float Math::InterpTo(float Current, float Target, float DeltaTime, float InterpSpeed) {
	// If no interp speed, jump to target value
	if (InterpSpeed <= 0.f) {
		return Target;
	}

	// Distance to reach
	const float Dist = Target - Current;

	// If distance is too small, just set the desired location
	if ((Dist * Dist) < 1.e-8f) {
		return Target;
	}

	// Delta Move, Clamp so we do not over shoot.
	const float DeltaMove = Dist * Clamp<float>(DeltaTime * InterpSpeed, 0.f, 1.f);

	return Current + DeltaMove;
}
