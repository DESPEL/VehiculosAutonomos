#include <iostream>
#include <array>
#include <random>
#include <algorithm>
#include <type_traits>

template <typename T, size_t Rows, size_t Columns>
class Matrix {

	using Representation = std::array<std::array<T, Columns>, Rows>;
	using Table = Matrix<T, Rows, Columns>;
	Representation data;
public:
	using type = T;

	static Table zeros() {
		Table result;
		for (auto& column: result)
			for (auto& value: column)
				value = T();
		return result;
	}

	typename Representation::iterator begin() {
		return data.begin();
	}
	
	typename Representation::iterator end() {
		return data.end();
	}

	std::array<T, Columns>& operator[](size_t row) {
		return data[row];
	}

	Matrix<T, Rows, Columns> operator+(Table& rhs) {
		Matrix<T, Rows, Columns> result;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Columns; ++j)
				result[i][j] = data[i][j] + rhs[i][j];
		return result;
	}

	Matrix<T, Rows, Columns> operator-(Table& rhs) {
		Matrix<T, Rows, Columns> result;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Columns; ++j)
				result[i][j] = data[i][j] - rhs[i][j];
		return result;
	}

	template<typename Ty, size_t R, size_t C>
	Matrix<T, Columns, Columns> operator*(Matrix<Ty, R, C>& rhs) {
        static_assert(Columns == R);

		Matrix<T, Columns, Columns> result;
		for (int i = 0; i < Rows; ++i) 
			for (int j = 0; j < C; ++j) 
				for (int k = 0; k < R; ++k) 
					result[i][0] += data[i][k] * rhs[k][j];
		return result;
	}

};



	//% Particle Swarm Optimization

	//clear
	//a = [1 2 3 4 5 6];

// Arreglo	



	//% ff = 'testfunctions';% Objective Function
	//ff = 3;

// Definicion de funcion objetivo


	//% Initializing variables
	//popsize = 10;% Size of the swarm
	//npar = 2;% Dimension of the problem
	//maxit = 10; % 100;% Maximum number of iterations
	//c1 = 1;% cognitive parameter
	//c2 = 4 - c1;% social parameter
	//C = 1;% constriction factor

int populationSize;
int dimension;
int maxIterations;
int cognitiveParamater;
int socialParameter;
int constrictionFactor;


	//% Initializing swarmand velocities
	//par = rand(popsize, npar);% random population of continuous values

// Generar random matrix, valores iniciales(cuantas filas, cuantas dimensiones)

	//% par = [1.9804 2.3333;
	//% -1.1176 0.9216;
	//% -1.4314    2.9216;
	//% 3.5490 - 2.8431;
	//% -0.4510    3.8235;
	//% 0.1765 - 1.5882;
	//% 3.5490    3.1961;
	//% 0.8039    0.4902;
	//% -2.7647    0.0980;
	//% -0.2157 - 4.6863];

	//vel = rand(popsize, npar);% random velocities

// Generar matriz random de velocities para cada valor inicial
// cuantas filas, cuantas dimensiones

	//% Evaluate initial population
	//% cost = feval(ff, par);% calculates population cost using ff

// Evaluar la poblacion inicial, segun la funcion objetivo

	
	//minc(1) = min(cost);

// Obtener mínimo

	//meanc(1) = mean(cost);% mean cost

// Obtener promedio

	//globalmin = minc(1);% initialize global minimum

// Minimo global

	//% Initialize local minimum for each particle
	//localpar = par;% location of local minima
	//localcost = cost;% cost of local minima

// Guardar el valor x del minimo para las particulas
// Guardar el valor y del minimo para las particulas

	//% Finding best particle in initial population
	//[globalcost, indx] = min(cost);
	//globalpar = par(indx, :);

// Identificar la partícula con el mínimo
// Guardar

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	//% Start iterations
	//iter = 0;% counter


void prueba() {
	int iterator = 0;

	//while iter < maxit
	//	iter = iter + 1;

	while (iterator < maxIterations) {
		
		//% update velocity = vel
		//w = (maxit - iter) / maxit;% inertia weiindxht
		
		float inertia = (maxIterations - iterator) / maxIterations;
		
		// r1 = rand(popsize, npar);% random numbers
		// r2 = rand(popsize, npar);% random numbers
		
	// Numeros aleatorios, que apoyan en la modificacion de la velocidad

		//vel = C * (w * vel + c1 * r1.*(localpar - par) + c2 * r2.*(ones(popsize, 1) * globalpar - par));

	// Recalcular la velocidad
		
		//% update particle positions
		//par = par + vel;% updates particle position
		
	// Aplica la velocidad a la posicion de las particulas
		
		//overlimit = par <= 1;
		//underlimit = par >= 0;
		//par = par.*overlimit + not(overlimit);
		//par = par.*underlimit;

	// Verificar que las particulas esten en el rango

		//% Evaluate the new swarm
		//% cost = feval(ff, par);% evaluates cost of swarm
		//cost = testfunctions(ff, par);

	// Re evalua el nuevo 

		//% Updating the best local position for each particle
		//bettercost = cost < localcost;
		//localcost = localcost.*not(bettercost)+cost.*bettercost;
		//localpar(find(bettercost), :) = par(find(bettercost), :);

		//% Updating index g
		//[temp, t] = min(localcost);
		//if temp < globalcost
		//	globalpar = par(t, :); indx = t; globalcost = temp;
		//end
		//[iter globalpar globalcost] % print output each
		//% iteration
		//minc(iter + 1) = min(cost);% min for this
		//% iteration
		//globalmin(iter + 1) = globalcost;% best min so far
		//meanc(iter + 1) = mean(cost);% avg.cost for
		//% this iteration

		//end% while

		//figure(24)
		//iters = 0:length(minc) - 1;
		//plot(iters, minc, iters, meanc, '�', iters, globalmin, ':');
		//xlabel('generation'); ylabel('cost');
		//text(0, minc(1), 'best'); text(1, minc(2), 'population average')
	}
}

int main() {
	return 0;
}