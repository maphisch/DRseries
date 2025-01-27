/*
 * Copyright (C) 2007, 2008, 2010
 * Nobuhiro Iwamatsu <iwamatsu@nigauri.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <version.h>
#include <watchdog.h>
#include <net.h>
#include <mmc.h>
#include <environment.h>

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern int cpu_init(void);
extern int board_init(void);
extern int dram_init(void);
extern int timer_init(void);

unsigned long monitor_flash_len = CONFIG_SYS_MONITOR_LEN;

#ifndef CONFIG_SYS_NO_FLASH
static int sh_flash_init(void)
{
	gd->bd->bi_flashsize = flash_init();

	if (gd->bd->bi_flashsize >= (1024 * 1024))
		printf("Flash: %ldMB\n", gd->bd->bi_flashsize / (1024*1024));
	else
		printf("Flash: %ldKB\n", gd->bd->bi_flashsize / 1024);

	return 0;
}
#endif /* CONFIG_SYS_NO_FLASH */

#if defined(CONFIG_CMD_NAND)
# include <nand.h>
static int sh_nand_init(void)
{
	printf("NAND:  ");

	nand_init();	/* go init the NAND */
	return 0;
}
# define INIT_FUNC_NAND_INIT sh_nand_init, 
#else
# define INIT_FUNC_NAND_INIT
#endif /* CONFIG_CMD_NAND */

#if defined(CONFIG_WATCHDOG)
extern int watchdog_init(void);
extern int watchdog_disable(void);
# undef INIT_FUNC_WATCHDOG_INIT
# define INIT_FUNC_WATCHDOG_INIT	watchdog_init,
# define WATCHDOG_DISABLE       	watchdog_disable
#else
# define INIT_FUNC_WATCHDOG_INIT
# define WATCHDOG_DISABLE
#endif /* CONFIG_WATCHDOG */

#if defined(CONFIG_CMD_IDE)
# include <ide.h>
# define INIT_FUNC_IDE_INIT	ide_init,
#else
# define INIT_FUNC_IDE_INIT
#endif /* CONFIG_CMD_IDE */

#if defined(CONFIG_PCI)
#include <pci.h>
static int sh_pci_init(void)
{
	pci_init();
	return 0;
}
# define INIT_FUNC_PCI_INIT sh_pci_init,
#else
# define INIT_FUNC_PCI_INIT
#endif /* CONFIG_PCI */

static int sh_mem_env_init(void)
{
	mem_malloc_init(CONFIG_SYS_TEXT_BASE - CONFIG_SYS_GBL_DATA_SIZE -
			CONFIG_SYS_MALLOC_LEN, CONFIG_SYS_MALLOC_LEN - 16);
	env_relocate();
	jumptable_init();
	return 0;
}

#if defined(CONFIG_CMD_MMC)
static int sh_mmc_init(void)
{
	puts("MMC:   ");
	mmc_initialize(gd->bd);
	return 0;
}
#endif

#ifdef CONFIG_SYS_ICACHE_ENABLE
static int icache_enable_init( void ) {
        icache_enable();

        return 0;
}
#endif
#ifdef CONFIG_SYS_DCACHE_ENABLE
static int dcache_enable_init( void ) {
        dcache_enable();

        return 0;
}
#endif


typedef int (init_fnc_t) (void);

init_fnc_t *init_sequence[] =
{
#ifdef CONFIG_SYS_ICACHE_ENABLE
        icache_enable_init,
#endif
#ifdef CONFIG_SYS_DCACHE_ENABLE
        dcache_enable_init,
#endif
	cpu_init,		/* basic cpu dependent setup */
	board_init,		/* basic board dependent setup */
	interrupt_init,	/* set up exceptions */
#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,
#endif
	env_init,		/* event init */
	serial_init,	/* SCIF init */
	INIT_FUNC_WATCHDOG_INIT	/* watchdog init */
	console_init_f,
	display_options,
	checkcpu,
	checkboard,		/* Check support board */
	dram_init,		/* SDRAM init */
	timer_init,		/* SuperH Timer (TCNT0 only) init */
	sh_mem_env_init,
#ifndef CONFIG_SYS_NO_FLASH
	sh_flash_init,	/* Flash memory init*/
#endif
	INIT_FUNC_NAND_INIT/* Flash memory (NAND) init */
	INIT_FUNC_PCI_INIT	/* PCI init */
	stdio_init,
	console_init_r,
	interrupt_init,
#ifdef CONFIG_BOARD_LATE_INIT
	board_late_init,
#endif
#if defined(CONFIG_CMD_MMC)
	sh_mmc_init,
#endif
	NULL			/* Terminate this list */
};

void sh_generic_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	bd_t *bd;
	init_fnc_t **init_fnc_ptr;

	memset(gd, 0, CONFIG_SYS_GBL_DATA_SIZE);

	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */

	gd->bd = (bd_t *)(gd + 1);	/* At end of global data */
	gd->baudrate = CONFIG_BAUDRATE;

	gd->cpu_clk = CONFIG_SYS_CLK_FREQ;

	bd = gd->bd;
	bd->bi_memstart	= CONFIG_SYS_SDRAM_BASE;
	bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;
#ifndef CONFIG_SYS_NO_FLASH
	bd->bi_flashstart = CONFIG_SYS_FLASH_BASE;
#endif
#if defined(CONFIG_SYS_SRAM_BASE) && defined(CONFIG_SYS_SRAM_SIZE)
	bd->bi_sramstart = CONFIG_SYS_SRAM_BASE;
	bd->bi_sramsize	= CONFIG_SYS_SRAM_SIZE;
#endif

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		WATCHDOG_RESET();
		if ((*init_fnc_ptr) () != 0)
			hang();
	}

#ifdef CONFIG_WATCHDOG
	/* disable watchdog if environment is set */
	{
		char *s = getenv("watchdog");
		if (s != NULL)
			if (strncmp(s, "off", 3) == 0)
				WATCHDOG_DISABLE();
	}
#endif /* CONFIG_WATCHDOG*/


#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif
#if defined(CONFIG_CMD_NET)
	puts("Net:   ");
	eth_initialize();
#endif /* CONFIG_CMD_NET */

	while (1) {
		WATCHDOG_RESET();
		main_loop();
	}
}
