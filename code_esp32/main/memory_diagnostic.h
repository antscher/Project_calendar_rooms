/*
 * Memory Diagnostic Tool for ESP32-S2
 * Use this to monitor memory usage during development
 */

#ifndef MEMORY_DIAGNOSTIC_H
#define MEMORY_DIAGNOSTIC_H

#include "Arduino.h"


class MemoryDiagnostic {
public:
    static void printMemoryUsage(const char* location) {
        #if CORE_DEBUG_LEVEL == 0
        Serial.printf("[MEM] %s - Free heap: %d bytes, Min free: %d bytes\n", 
                     location, ESP.getFreeHeap(), ESP.getMinFreeHeap());
        #endif
    }
    
    static void printDetailedMemory() {
        #if CORE_DEBUG_LEVEL == 0
        Serial.println("=== Memory Status ===");
        Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
        Serial.printf("Min free heap: %d bytes\n", ESP.getMinFreeHeap());
        Serial.printf("Heap size: %d bytes\n", ESP.getHeapSize());
        Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
        Serial.printf("PSRAM size: %d bytes\n", ESP.getPsramSize());
        Serial.printf("Chip revision: %d\n", ESP.getChipRevision());
        Serial.printf("Flash size: %d bytes\n", ESP.getFlashChipSize());
        Serial.println("====================");
        #endif
    }
    
    static bool checkMemoryHealth() {
        uint32_t freeHeap = ESP.getFreeHeap();
        uint32_t minFreeHeap = ESP.getMinFreeHeap();
        
        // Warning if less than 20KB free
        if (freeHeap < 20480) {
            Serial.printf("[WARNING] Low memory: %d bytes free\n", freeHeap);
            return false;
        }
        
        // Critical if fragmentation is high
        if (minFreeHeap < (freeHeap * 0.7)) {
            Serial.printf("[WARNING] Memory fragmentation detected\n");
            return false;
        }
        
        return true;
    }
};

// Macro pour faciliter le debugging
#define MEM_CHECK(location) MemoryDiagnostic::printMemoryUsage(location)
#define MEM_HEALTH() MemoryDiagnostic::checkMemoryHealth()

#endif // MEMORY_DIAGNOSTIC_H
