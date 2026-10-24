#include <stdint.h>

#include "xmc4700/led.hpp"

// Register-Definitionen
#define SCU_BASE            0x50004000UL
#define SCU_GCU_PROT        (*(volatile uint32_t*)(SCU_BASE + 0x015C))
#define SCU_PRCLR0          (*(volatile uint32_t*)(SCU_BASE + 0x0140))
#define SCU_CLKSET          (*(volatile uint32_t*)(SCU_BASE + 0x010C))

#define WDT_BASE            0x40030000UL  // Korrekte Adresse für WDT auf XMC4700
#define WDT_CTR             (*(volatile uint32_t*)(WDT_BASE + 0x0000))
#define WDT_SR              (*(volatile uint32_t*)(WDT_BASE + 0x0004))

#define PORT5_              ((XMC_GPIO_PORT *)0x48028500UL)
#define P5_OUT              (*(volatile uint32_t*)(PORT5_ + 0x0000))
#define P5_OMR              (*(volatile uint32_t*)(PORT5_ + 0x0004))
#define P5_IOCR8            (*(volatile uint32_t*)(PORT5_ + 0x0014))

#ifdef __cplusplus
extern "C" {
#endif

void _init(void) {
    // Wird von __libc_init_array aufgerufen.
    // Kann für Bare-Metal leer bleiben, da SystemInit() die Hardware initialisiert.
}

void _fini(void) {
    // Stub für eventuelle Destruktoren beim Beenden (wird bei embedded selten genutzt)
}

#ifdef __cplusplus
}
#endif

// Erzwungene volatile Warteschleife
void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

// ============================================================================
// ERZWUNGENE HARDWARE-FREISCHALTUNG
// ============================================================================
void SystemInit(void) {
    // 1. SCU-Registerschutz dauerhaft aufheben
    SCU_GCU_PROT = 0x000000C5UL;

    // 2. Watchdog-Timer (WDT) mit der exakten Sequenz abschalten
    WDT_SR = 0xABADBABEUL;
    WDT_CTR = 0x00000000UL;

    // 3. GPIO-Hardware aus dem Peripherie-Reset holen
    SCU_PRCLR0 = 0x00000001UL; // Alle Ports freischalten

    // 4. Port-Takt explizit aktivieren (Port5)
    SCU_CLKSET |= (1UL << 5);  // Bit 5 für PORT5 aktivieren
}

void __libc_init_array(void) {
    // Leer für den Linker
}

// uint32_t SysTick_Config(uint32_t ticks)
// {
//   if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
//   {
//     return (1UL);                                                   /* Reload value impossible */
//   }

//   SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
//   NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
//   SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
//   SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
//                    SysTick_CTRL_TICKINT_Msk   |
//                    SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
//   return (0UL);                                                     /* Function successful */
// }

// ============================================================================
// MAIN (Einstieg nach vollendeter Startup-Routine)
// ============================================================================
int main(void) {
       
//    SysTick_Config((uint32_t)SYSTICK_MS);


    //  // 2. CLOCK GATING FÜR DIE GPIO-PORTS DEAKTIVIEREN
    // // Im SCU (System Control Unit) muss das Clock-Gating für das PORT-Modul 
    // // aufgehoben werden, sonst sind die Port-Register gesperrt (geben nur 0 zurück).
    // // Hebt das Clock-Gating für alle GPIO-Ports direkt auf Bit-Ebene auf
    // // Richtig: Über das SCU_GENERAL-Modul auf die Taktregister zugreifen
    // // Physikalische Speicheradresse des SCU_CLK->CGATCLR0 Registers
    // *(volatile uint32_t*)(0x50004C14) |= (1UL << 0);

    // // Registerschutz zur Sicherheit nochmals aufheben
    // SCU_GCU_PROT = 0x000000C5UL;
    // SCU_CLKSET |= (1UL << 5);  // Port5-Clock sicherstellen

    led builtin_led1{5, 8};
    led builtin_led2{5, 9};

    builtin_led1.begin();
    builtin_led2.begin();

    builtin_led1.toggle();
    delay(20000000UL);

    while (1)
    {
        builtin_led1.toggle();
        builtin_led2.toggle();
        delay(20000000UL);
    }
    return 0;
}
