#pragma once
#ifndef MATH_H
#define MATH_H


class Math {
public:
	
	template<class T> 
	static inline T Clamp(const T X, const T Min, const T Max) {
		return X < Min ? Min : X < Max ? X : Max;
	}
	
	static float InterpTo(float Current, float Target, float DeltaTime, float InterpSpeed);

};
#endif // !MATH_H
