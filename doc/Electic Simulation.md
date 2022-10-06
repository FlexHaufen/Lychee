# Simulation
[Article 1](https://electronics.stackexchange.com/questions/91416/how-do-circuit-simulators-actually-work)


## SPICE
The electronic simulation is done by using the [SPICE](https://en.wikipedia.org/wiki/SPICE)*(Simulation Program with Integrated Circuit Emphasis*) algorithm.

Links:
- [The SPICE algorythem](http://www.ecircuitcenter.com/SpiceTopics/Overview/Overview.htm)
- [SPICE overview](https://www.seas.upenn.edu/~jan/spice/spice.overview.html)
### Nodal Analysis


### DC Analysis
- Gaussian Elimination.
-  Liniar Systems
	- [Nodal Analysis](http://www.ecircuitcenter.com/SpiceTopics/Nodal%20Analysis/Nodal%20Analysis.htm)
-  Non Liniar
	- 
### AC Analysis
### Transient


### Components
#### Resistor
The value of a Resistor will not be stored in electrical resistance $R\;[\Omega]$, but in
electrical conductance $G\;[S]$
This gives the formula:
$$I = G * U$$$$U = G^{-1}* I$$
#### Capacitor


Matrix System:
$$\begin{bmatrix}
\frac{1}{R1}+\frac{1}{R2} - \frac{1}{R3}\\
-\frac{1}{R2} \frac{1}{R2} + \frac{1}{R3} 
\end{bmatrix}
$$

[Altium article](https://resources.altium.com/de/p/what-spice-simulation-electronics-design)

**Nodal Voltage Analysis**

$\sum_{i\neq j} C_{ij}(V_{i} - V_{j}) = F\{V_{in,\, k}\}$
$\downarrow$
$[C] [V] = [V_{in}]$
