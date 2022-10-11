# Math

## Gaussian elimination
```cpp

#define SIZE 10

/**
* @brief Performs Gaussian elimination on matrix
* @param a input matrix
* @param n number of unknowns
* @parma b output array with solution
*/
void GaussianElimination(float a[SIZE][SIZE] float n) {
	/* Applying Gauss Elimination */
	for(int i = 1; i <= n - 1; i++) {
		if(a[i][i] == 0.0) {
			cout<<"ERROR: Array at [" << i << "][" << i << "]is empty" ;
			exit(0);
		}
		for(int j = i + 1; j <= n; j++) {
			float ratio = a[j][i] / a[i][i];
			for(int k = 1; k <= n + 1; k++) {
				a[j][k] = a[j][k] - ratio * a[i][k];
			}
		}
	}
	 
	/* Obtaining Solution by Back Substitution Method */
	int x[SIZE];
	x[n] = a[n][n+1] / a[n][n];
	for(int i = n - 1; i >= 1; i--) {
		x[i] = a[i][n+1];
		for(j = i + 1; j <= n; j++) {
			x[i] = x[i] - a[i][j] * x[j];
		}
		x[i] = x[i] / a[i][i];
	}
}
```