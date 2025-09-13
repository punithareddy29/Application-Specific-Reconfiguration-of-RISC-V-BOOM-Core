#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hpm.h"

#define INPUT_SIZE 128
#define HIDDEN_SIZE 64
#define OUTPUT_SIZE 32
#define LEARNING_RATE 0.01f
#define EPOCHS 30

// Randomly initialize weights and biases
void init_weights(float *weights, int size) {
    for (int i = 0; i < size; i++) {
        weights[i] = ((float) rand() / (float) RAND_MAX) - 0.5f;
    }
}

// Perform matrix-vector multiplication
void matvec_mul(float *matrix, float *vector, float *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0.0f;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

// Apply ReLU activation function
void relu(float *vector, int size) {
    for (int i = 0; i < size; i++) {
        if (vector[i] < 0) {
            vector[i] = 0;
        }
    }
}

// Compute the derivative of ReLU
void relu_derivative(float *vector, float *derivative, int size) {
    for (int i = 0; i < size; i++) {
        derivative[i] = vector[i] > 0 ? 1.0f : 0.0f;
    }
}

// Perform element-wise subtraction
void vector_sub(float *a, float *b, float *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] - b[i];
    }
}

// Perform backpropagation to compute gradients and update weights
void backpropagation(
    float *weights, float *input, float *output_grad, float *input_grad, int rows, int cols
) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            weights[i * cols + j] -= LEARNING_RATE * output_grad[i] * input[j];
            input_grad[j] += output_grad[i] * weights[i * cols + j];
        }
    }
}

int main() {
    /* Enable performance counters */
    hpm_init();

    // Input, hidden, and output layers
    float input[INPUT_SIZE];
    float hidden[HIDDEN_SIZE];
    float hidden_grad[HIDDEN_SIZE];
    float output[OUTPUT_SIZE];
    float output_grad[OUTPUT_SIZE];

    // Weights and biases
    float input_to_hidden_weights[INPUT_SIZE * HIDDEN_SIZE];
    float hidden_to_output_weights[HIDDEN_SIZE * OUTPUT_SIZE];

    // Ground truth (target output)
    float target[OUTPUT_SIZE];

    // Initialize weights
    init_weights(input_to_hidden_weights, INPUT_SIZE * HIDDEN_SIZE);
    init_weights(hidden_to_output_weights, HIDDEN_SIZE * OUTPUT_SIZE);

    // Initialize input and target with random values
    for (int i = 0; i < INPUT_SIZE; i++) {
        input[i] = ((float) rand() / (float) RAND_MAX) - 0.5f;
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        target[i] = ((float) rand() / (float) RAND_MAX); // Target values between 0 and 1
    }

    // Training loop
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        // Forward pass: Input to Hidden
        matvec_mul(input_to_hidden_weights, input, hidden, HIDDEN_SIZE, INPUT_SIZE);
        relu(hidden, HIDDEN_SIZE);

        // Forward pass: Hidden to Output
        matvec_mul(hidden_to_output_weights, hidden, output, OUTPUT_SIZE, HIDDEN_SIZE);
        relu(output, OUTPUT_SIZE);

        // Compute output gradient (mean squared error loss)
        for (int i = 0; i < OUTPUT_SIZE; i++) {
            output_grad[i] = 2.0f * (output[i] - target[i]);
        }

        // Backpropagation: Hidden to Output
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            hidden_grad[i] = 0.0f;
        }
        backpropagation(hidden_to_output_weights, hidden, output_grad, hidden_grad, OUTPUT_SIZE, HIDDEN_SIZE);

        // Backpropagation: Input to Hidden
        float input_grad[INPUT_SIZE] = {0};
        backpropagation(input_to_hidden_weights, input, hidden_grad, input_grad, HIDDEN_SIZE, INPUT_SIZE);

        // Print loss every 10 epochs
        if (epoch % 10 == 0) {
            float loss = 0.0f;
            for (int i = 0; i < OUTPUT_SIZE; i++) {
                float diff = output[i] - target[i];
                loss += diff * diff;
            }
            loss /= OUTPUT_SIZE;
            printf("Epoch %d, Loss: %f\n", epoch, loss);
        }
    }

    /* Print performance counter data */
    hpm_print();

    return 0;
}
