/* Ponto de entrada */
ENTRY(Reset_Handler)

/* Mapa de memória do STM32F411CE */
MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 96K
}

SECTIONS
{
    /* Vetores de interrupção e código na Flash */
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) 
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* Dados inicializados (vão para RAM, guardados na Flash) */
    .data : 
    {
        . = ALIGN(4);
        _sdata = .;        /* Início da seção .data na RAM */
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;        /* Fim da seção .data na RAM */
    } > RAM AT > FLASH

    /* Dados não inicializados */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;         /* Início da seção .bss */
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* Fim da seção .bss */
    } > RAM

    /* Definição do topo da pilha */
    _estack = ORIGIN(RAM) + LENGTH(RAM);
}