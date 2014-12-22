#include <math.h>
#include <stdio.h>
#include <ctime>

float eps = 0.01;

#define GAMMA 2.0

class vector
{
public:
	float x, y, vx, vy;
	vector()
	{
		x = 0;
		y = 0;
	}
	vector(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	void out()
	{
		printf("x=%f\t", x);
		printf("y=%f\n", y);
	}
};
vector operator +(vector a, vector b)
{
	vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return(c);
}
vector operator -(vector a, vector b)
{
	vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return(c);
}
vector operator *(float a, vector b)
{
	vector c;
	c.x = a * b.x;
	c.y = a * b.y;
	return(c);
}
vector operator *(vector b, float a)
{
	vector c;
	c.x = a * b.x;
	c.y = a * b.y;
	return(c);
}

float gamma(float t)
{
	return t*GAMMA;
}

vector f(vector u, float t)
{
	vector res;
	float g = gamma(t);
	res.x = pow(u.x, 3) + 10 * u.x + 3 * u.y - 1 - 15;
	res.y = pow(u.y, 7) - 3 * u.x + 7 * u.y - 5 - 10;
	return(res*(-g));
}


int main()
{
	vector k1, k2, k3, k4, k5;
	vector R;
	float dt = 0.01;
	float t = 0.0;
	vector u(0, 0);
	int countIter = 0;

	unsigned int start_time =  clock(); 

	while (t<1)
	{
		//if (countIter < 268)
			u.out();

		countIter += 1;

		k1 = f(u, t)*dt;
		k2 = (1.0 / 3.0) * f(u + k1, t + dt * (1.0 / 3.0))*dt;
		k3 = (1.0 / 3.0) * f(u + k1 * (1.0 / 2.0) + k2 * (1.0 / 2.0), t + dt * (1.0 / 3.0))*dt;
		k4 = (1.0 / 3.0) * f(u + (3.0 / 8.0) * k1 + (9.0 / 8.0) * k3, t + dt * (1.0 / 2.0))*dt;
		k5 = (1.0 / 3.0) * f(u + (3.0 / 2.0) * k1 - (9.0 / 2.0) * k3 + 6 * k4, t + dt)*dt;

		u = u + 1.0 / 2.0 * (k1 + 4 * k4 + k5);

		R = (k1 - (9.0 / 2.0) * k3 + 4 * k4 - (1.0 / 2.0) * k5);

		
		if ((fabs(R.x) > 5 * eps) || (fabs(R.y) > 5 * eps))
		{
			dt = dt / 2.0;
		}

		if ((fabs(R.x)< (5.0 / 32.0) * eps) || (fabs(R.y)< (5.0 / 32.0) * eps))
		{
			dt = dt *2.0;
		}
		t += dt;
	}

	unsigned int end_time = clock();


	printf( "Number of iterations: %d\nPrecision: %lf\n, Time(ms): %d", countIter, eps, end_time - start_time);

	return 0;
}