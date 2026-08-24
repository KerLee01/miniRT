#include "main.h"

int main(void)
{
    // Create our standard test vectors
    t_coor a = create_new_coor(1.0, 2.0, 3.0);
    t_coor b = create_new_coor(4.0, 5.0, 6.0);
    double scalar = 2.0;

    printf("\n========================================\n");
    printf("         MINIRT MATH SANDBOX\n");
    printf("========================================\n\n");

    printf("Vector A: (%f, %f, %f)\n", a.x, a.y, a.z);
    printf("Vector B: (%f, %f, %f)\n\n", b.x, b.y, b.z);

    // 1. Test Addition
    t_coor result_add = addition(a, b);
    printf("--- ADDITION ---\n");
    printf("Expected: (5.000000, 7.000000, 9.000000)\n");
    printf("Result  : (%f, %f, %f)\n\n", result_add.x, result_add.y, result_add.z);

    // 2. Test Subtraction
    t_coor result_sub = subtract(a, b);
    printf("--- SUBTRACTION ---\n");
    printf("Expected: (-3.000000, -3.000000, -3.000000)\n");
    printf("Result  : (%f, %f, %f)\n\n", result_sub.x, result_sub.y, result_sub.z);

    // 3. Test Multiplication
    t_coor result_mult = multiply(a, scalar);
    printf("--- MULTIPLICATION (A * 2.0) ---\n");
    printf("Expected: (2.000000, 4.000000, 6.000000)\n");
    printf("Result  : (%f, %f, %f)\n\n", result_mult.x, result_mult.y, result_mult.z);

    // 4. Test Division
    t_coor result_div = divide(a, scalar);
    printf("--- DIVISION (A / 2.0) ---\n");
    printf("Expected: (0.500000, 1.000000, 1.500000)\n");
    printf("Result  : (%f, %f, %f)\n\n", result_div.x, result_div.y, result_div.z);

    // 5. Test Magnitude
    double result_mag = magnitude(a);
    printf("--- MAGNITUDE (Length of A) ---\n");
    printf("Expected: 3.741657\n");
    printf("Result  : %f\n\n", result_mag);

    // 6. Test Dot Product
    double result_dot = dot_product(a, b);
    printf("--- DOT PRODUCT (A . B) ---\n");
    printf("Expected: 32.000000\n");
    printf("Result  : %f\n\n", result_dot);

    // 7. Test Normalization
    t_coor result_norm = normalization(a);
    printf("--- NORMALIZATION (A) ---\n");
    printf("Expected: (0.267261, 0.534522, 0.801784)\n");
    printf("Result  : (%f, %f, %f)\n\n", result_norm.x, result_norm.y, result_norm.z);

    // Let's test crossing the X axis with the Y axis
    t_coor x_axis = create_new_coor(1.0, 0.0, 0.0);
    t_coor y_axis = create_new_coor(0.0, 1.0, 0.0);
    
    t_coor result_cross = cross_product(x_axis, y_axis);
    
    printf("--- CROSS PRODUCT (X-axis x Y-axis) ---\n");
    printf("Expected: (0.000000, 0.000000, 1.000000)\n"); // It should give you the Z-axis!
    printf("Result  : (%f, %f, %f)\n\n", result_cross.x, result_cross.y, result_cross.z);
    return (0);
}
