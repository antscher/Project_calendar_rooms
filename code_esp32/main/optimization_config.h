/*
 * ESP32-S2 Optimization Configuration
 * This file contains compile-time optimizations for memory and performance
 */

#ifndef OPTIMIZATION_CONFIG_H
#define OPTIMIZATION_CONFIG_H

// Memory optimization directives
#define OPTIMIZE_FOR_SPEED __attribute__((optimize("O2")))
#define OPTIMIZE_FOR_SIZE __attribute__((optimize("Os")))
#define FORCE_INLINE __attribute__((always_inline)) inline
#define NO_INLINE __attribute__((noinline))
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

// Memory pool sizes (optimized for ESP32-S2)
#define MAX_CALENDAR_EVENTS 5
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_ROOM_NAME_LENGTH 64
#define MQTT_BUFFER_SIZE 512
#define DISPLAY_BUFFER_SIZE_KB 32

// Stack size optimizations
#define DEFAULT_STACK_SIZE 4096
#define MQTT_TASK_STACK_SIZE 8192
#define DISPLAY_TASK_STACK_SIZE 6144


#endif // OPTIMIZATION_CONFIG_H
