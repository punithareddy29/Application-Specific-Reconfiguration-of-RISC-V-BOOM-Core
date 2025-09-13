#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hpm.h"

#define NX 50          // Number of spatial points
#define NT 1000        // Number of time steps
#define L 1.0          // Length of the rod
#define T 1.0          // Total simulation time
#define ALPHA 0.01     // Thermal diffusivity of the material

int main() {
    /* Enable performance counters */
    hpm_init();

    // Spatial and time step sizes
    double dx = L / (NX - 1);
    double dt = T / NT;
    double r = ALPHA * dt / (dx * dx); // Stability criterion

    if (r > 0.5) {
        printf("Stability condition not met. Reduce dt or increase dx.\n");
        return 1;
    }

    // Arrays to store temperatures
    double u[NX];     // Current time step
    double u_next[NX]; // Next time step

    // Initial condition: Temperature distribution
    for (int i = 0; i < NX; i++) {
        u[i] = sin(M_PI * i * dx); // Initial temperature profile
    }

    // Boundary conditions
    u[0] = 0.0;
    u[NX - 1] = 0.0;

    // Time stepping loop
    for (int n = 0; n < NT; n++) {
        // Compute the next time step
        for (int i = 1; i < NX - 1; i++) {
            u_next[i] = u[i] + r * (u[i + 1] - 2 * u[i] + u[i - 1]);
        }

        // Update the current state
        for (int i = 1; i < NX - 1; i++) {
            u[i] = u_next[i];
        }

        // Print the temperature at a few points for visualization
        if (n % (NT / 10) == 0) { // Print 10 snapshots
            printf("Time step %d:\n", n);
            for (int i = 0; i < NX; i++) {
                printf("%.2f ", u[i]);
            }
            printf("\n");
        }
    }

    /* Print performance counter data */
    hpm_print();

    printf("Simulation complete.\n");
    return 0;
}
