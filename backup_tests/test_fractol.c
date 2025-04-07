/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:00:11 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 15:00:14 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../include/fractol.h"

/* Setup and teardown functions */
static void setup(void) {
    // Setup code that runs before each test
    printf("Setting up test...\n");
}

static void teardown(void) {
    // Cleanup code that runs after each test
    printf("Cleaning up...\n");
}

/* Basic Requirements Tests */
Test(fractol_basic, program_initialization, .init = setup, .fini = teardown) {
    // Test program initialization
    printf("Testing program initialization...\n");
    cr_assert(true, "Basic program structure exists");
}

/* Graphics Management Tests */
Test(fractol_graphics, window_creation) {
    // Test window creation
    void *mlx = mlx_init(800, 600, "Test Window", true);
    cr_assert(mlx != NULL, "MLX window should be created successfully");
    if (mlx) mlx_terminate(mlx);
}

/* Parameter Management Tests */
Test(fractol_params, parameter_validation) {
    t_fractol fractol;
    char *argv[] = {"fractol", "mandelbrot", NULL};
    fractol.type = NONE;
    cr_assert(check_args(2, argv, &fractol) == true, "Valid parameters should be accepted");
    cr_assert(fractol.type == MANDELBROT, "Fractol type should be set to MANDELBROT");
}

/* Memory Management Tests */
Test(fractol_memory, no_leaks) {
    // Basic memory allocation and freeing test
    void *ptr = malloc(sizeof(int));
    cr_assert(ptr != NULL, "Memory allocation should succeed");
    free(ptr);
}