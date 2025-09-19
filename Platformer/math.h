#pragma once

struct Vector {float x, y;};

Vector addVectors(Vector a, Vector b) {
	return (Vector){x:a.x + b.x, y:a.y + b.y};
}

Vector subtractVectors(Vector a, Vector b) {
	return (Vector){x:a.x - b.x, y:a.y - b.y};
}

Vector scaleVector(Vector v, float scale) {
	return (Vector){x:v.x * scale, y:v.y * scale};
}

float magnitudeOfVector(Vector v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

Vector normalizeVector(Vector v) {
	if (v.x == 0 && v.y == 0) return {x:0, y:0};
	return scaleVector(v, 1/magnitudeOfVector(v));
}

float dotProductOfVectors(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

Vector inverseVector(Vector v) {
	return (Vector){x:v.x * -1, y:v.y * -1};	
}

float distanceBetweenTwoPoints(Vector a, Vector b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

Vector directionVectorBetweenTwoPoints(Vector a, Vector b) {
	return normalizeVector(subtractVectors(b, a));
}

/*
function jumpHeight(impulse, gravity) {
	var height = 0;
	var jump = impulse;
	var counter = 0;

	do {
		height += jump;
		jump -= gravity;
		counter++;
	} while (jump > 0);

	return {height: height, counter: counter};
}
*/

