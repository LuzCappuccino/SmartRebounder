/*
 * mbed SDK
 * Copyright (c) 2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Automatically generated configuration file.
// DO NOT EDIT, content will be overwritten.

#ifndef __MBED_CONFIG_DATA__
#define __MBED_CONFIG_DATA__

// Configuration parameters
#define ATT_NUM_SIMUL_NTF                                                       1                                       // set by library:cordio
#define ATT_NUM_SIMUL_WRITE_CMD                                                 1                                       // set by library:cordio
#define BLE_FEATURE_EXTENDED_ADVERTISING                                        1                                       // set by library:ble
#define BLE_FEATURE_GATT_CLIENT                                                 1                                       // set by library:ble
#define BLE_FEATURE_GATT_SERVER                                                 1                                       // set by library:ble
#define BLE_FEATURE_PERIODIC_ADVERTISING                                        1                                       // set by library:ble
#define BLE_FEATURE_PHY_MANAGEMENT                                              1                                       // set by library:ble
#define BLE_FEATURE_PRIVACY                                                     1                                       // set by library:ble
#define BLE_FEATURE_SECURE_CONNECTIONS                                          1                                       // set by library:ble
#define BLE_FEATURE_SECURITY                                                    1                                       // set by library:ble
#define BLE_FEATURE_SIGNING                                                     1                                       // set by library:ble
#define BLE_FEATURE_WHITELIST                                                   1                                       // set by library:ble
#define BLE_GAP_HOST_BASED_PRIVATE_ADDRESS_RESOLUTION                           0                                       // set by library:ble[NUCLEO_WB55RG]
#define BLE_GAP_HOST_PRIVACY_RESOLVED_CACHE_SIZE                                16                                      // set by library:ble
#define BLE_GAP_MAX_ADVERTISING_REPORTS_PENDING_ADDRESS_RESOLUTION              16                                      // set by library:ble
#define BLE_GAP_MAX_ADVERTISING_SETS                                            15                                      // set by library:ble
#define BLE_ROLE_BROADCASTER                                                    1                                       // set by library:ble
#define BLE_ROLE_CENTRAL                                                        1                                       // set by library:ble
#define BLE_ROLE_OBSERVER                                                       1                                       // set by library:ble
#define BLE_ROLE_PERIPHERAL                                                     1                                       // set by library:ble
#define BLE_SECURITY_DATABASE_FILESYSTEM                                        1                                       // set by library:ble
#define BLE_SECURITY_DATABASE_KVSTORE                                           0                                       // set by library:ble
#define BLE_SECURITY_DATABASE_MAX_ENTRIES                                       5                                       // set by library:ble
#define DM_CONN_MAX                                                             3                                       // set by library:cordio
#define DM_NUM_ADV_SETS                                                         3                                       // set by library:cordio
#define DM_NUM_PHYS                                                             3                                       // set by library:cordio
#define DM_SYNC_MAX                                                             1                                       // set by library:cordio
#define EATT_CONN_CHAN_MAX                                                      1                                       // set by library:cordio
#define L2C_COC_CHAN_MAX                                                        1                                       // set by library:cordio
#define L2C_COC_REG_MAX                                                         1                                       // set by library:cordio
#define LPTICKER_DELAY_TICKS                                                    0                                       // set by target:MCU_STM32WB
#define MBED_CONF_BLE_API_IMPLEMENTATION_MAX_CCCD_COUNT                         20                                      // set by library:ble-api-implementation
#define MBED_CONF_BLE_API_IMPLEMENTATION_MAX_CHARACTERISTIC_AUTHORISATION_COUNT 20                                      // set by library:ble-api-implementation
#define MBED_CONF_BLE_PRESENT                                                   1                                       // set by library:ble
#define MBED_CONF_CORDIO_DESIRED_ATT_MTU                                        23                                      // set by library:cordio
#define MBED_CONF_CORDIO_MAX_PREPARED_WRITES                                    4                                       // set by library:cordio
#define MBED_CONF_CORDIO_PREFERRED_TX_POWER                                     0                                       // set by library:cordio
#define MBED_CONF_CORDIO_ROUTE_UNHANDLED_COMMAND_COMPLETE_EVENTS                1                                       // set by library:cordio
#define MBED_CONF_CORDIO_RX_ACL_BUFFER_SIZE                                     70                                      // set by library:cordio
#define MBED_CONF_DRIVERS_OSPI_CSN                                              OSPI_FLASH1_CSN                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_DQS                                              OSPI_FLASH1_DQS                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO0                                              OSPI_FLASH1_IO0                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO1                                              OSPI_FLASH1_IO1                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO2                                              OSPI_FLASH1_IO2                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO3                                              OSPI_FLASH1_IO3                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO4                                              OSPI_FLASH1_IO4                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO5                                              OSPI_FLASH1_IO5                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO6                                              OSPI_FLASH1_IO6                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_IO7                                              OSPI_FLASH1_IO7                         // set by library:drivers
#define MBED_CONF_DRIVERS_OSPI_SCK                                              OSPI_FLASH1_SCK                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_CSN                                              QSPI_FLASH1_CSN                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_IO0                                              QSPI_FLASH1_IO0                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_IO1                                              QSPI_FLASH1_IO1                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_IO2                                              QSPI_FLASH1_IO2                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_IO3                                              QSPI_FLASH1_IO3                         // set by library:drivers
#define MBED_CONF_DRIVERS_QSPI_SCK                                              QSPI_FLASH1_SCK                         // set by library:drivers
#define MBED_CONF_DRIVERS_UART_SERIAL_RXBUF_SIZE                                256                                     // set by library:drivers
#define MBED_CONF_DRIVERS_UART_SERIAL_TXBUF_SIZE                                256                                     // set by library:drivers
#define MBED_CONF_EVENTS_PRESENT                                                1                                       // set by library:events
#define MBED_CONF_EVENTS_SHARED_DISPATCH_FROM_APPLICATION                       0                                       // set by library:events
#define MBED_CONF_EVENTS_SHARED_EVENTSIZE                                       768                                     // set by library:events
#define MBED_CONF_EVENTS_SHARED_HIGHPRIO_EVENTSIZE                              256                                     // set by library:events
#define MBED_CONF_EVENTS_SHARED_HIGHPRIO_STACKSIZE                              1024                                    // set by library:events
#define MBED_CONF_EVENTS_SHARED_STACKSIZE                                       2048                                    // set by library:events
#define MBED_CONF_EVENTS_USE_LOWPOWER_TIMER_TICKER                              0                                       // set by library:events
#define MBED_CONF_PLATFORM_CALLBACK_COMPARABLE                                  1                                       // set by library:platform
#define MBED_CONF_PLATFORM_CALLBACK_NONTRIVIAL                                  0                                       // set by library:platform
#define MBED_CONF_PLATFORM_CRASH_CAPTURE_ENABLED                                0                                       // set by library:platform
#define MBED_CONF_PLATFORM_CTHUNK_COUNT_MAX                                     8                                       // set by library:platform
#define MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE                             9600                                    // set by library:platform
#define MBED_CONF_PLATFORM_ERROR_ALL_THREADS_INFO                               0                                       // set by library:platform
#define MBED_CONF_PLATFORM_ERROR_FILENAME_CAPTURE_ENABLED                       0                                       // set by library:platform
#define MBED_CONF_PLATFORM_ERROR_HIST_ENABLED                                   0                                       // set by library:platform
#define MBED_CONF_PLATFORM_ERROR_HIST_SIZE                                      4                                       // set by library:platform
#define MBED_CONF_PLATFORM_ERROR_REBOOT_MAX                                     1                                       // set by library:platform
#define MBED_CONF_PLATFORM_FATAL_ERROR_AUTO_REBOOT_ENABLED                      0                                       // set by library:platform
#define MBED_CONF_PLATFORM_MAX_ERROR_FILENAME_LEN                               16                                      // set by library:platform
#define MBED_CONF_PLATFORM_MINIMAL_PRINTF_ENABLE_64_BIT                         1                                       // set by library:platform
#define MBED_CONF_PLATFORM_MINIMAL_PRINTF_ENABLE_FLOATING_POINT                 0                                       // set by library:platform
#define MBED_CONF_PLATFORM_MINIMAL_PRINTF_SET_FLOATING_POINT_MAX_DECIMALS       6                                       // set by library:platform
#define MBED_CONF_PLATFORM_POLL_USE_LOWPOWER_TIMER                              0                                       // set by library:platform
#define MBED_CONF_PLATFORM_STDIO_BAUD_RATE                                      115200                                  // set by application[*]
#define MBED_CONF_PLATFORM_STDIO_BUFFERED_SERIAL                                0                                       // set by library:platform
#define MBED_CONF_PLATFORM_STDIO_CONVERT_NEWLINES                               1                                       // set by library:platform
#define MBED_CONF_PLATFORM_STDIO_CONVERT_TTY_NEWLINES                           1                                       // set by library:platform
#define MBED_CONF_PLATFORM_STDIO_FLUSH_AT_EXIT                                  1                                       // set by library:platform
#define MBED_CONF_PLATFORM_STDIO_MINIMAL_CONSOLE_ONLY                           0                                       // set by library:platform
#define MBED_CONF_PLATFORM_USE_MPU                                              1                                       // set by library:platform
#define MBED_CONF_RTOS_API_PRESENT                                              1                                       // set by library:rtos-api
#define MBED_CONF_RTOS_EVFLAGS_NUM                                              0                                       // set by library:rtos
#define MBED_CONF_RTOS_IDLE_THREAD_STACK_SIZE                                   512                                     // set by library:rtos
#define MBED_CONF_RTOS_IDLE_THREAD_STACK_SIZE_DEBUG_EXTRA                       128                                     // set by library:rtos[STM]
#define MBED_CONF_RTOS_IDLE_THREAD_STACK_SIZE_TICKLESS_EXTRA                    256                                     // set by library:rtos
#define MBED_CONF_RTOS_MAIN_THREAD_STACK_SIZE                                   4096                                    // set by library:rtos
#define MBED_CONF_RTOS_MSGQUEUE_DATA_SIZE                                       0                                       // set by library:rtos
#define MBED_CONF_RTOS_MSGQUEUE_NUM                                             0                                       // set by library:rtos
#define MBED_CONF_RTOS_MUTEX_NUM                                                0                                       // set by library:rtos
#define MBED_CONF_RTOS_PRESENT                                                  1                                       // set by library:rtos
#define MBED_CONF_RTOS_SEMAPHORE_NUM                                            0                                       // set by library:rtos
#define MBED_CONF_RTOS_THREAD_NUM                                               0                                       // set by library:rtos
#define MBED_CONF_RTOS_THREAD_STACK_SIZE                                        4096                                    // set by library:rtos
#define MBED_CONF_RTOS_THREAD_USER_STACK_SIZE                                   0                                       // set by library:rtos
#define MBED_CONF_RTOS_TIMER_NUM                                                0                                       // set by library:rtos
#define MBED_CONF_RTOS_TIMER_THREAD_STACK_SIZE                                  768                                     // set by library:rtos
#define MBED_CONF_SD_CMD0_IDLE_STATE_RETRIES                                    5                                       // set by library:sd
#define MBED_CONF_SD_CMD_TIMEOUT                                                10000                                   // set by library:sd
#define MBED_CONF_SD_CRC_ENABLED                                                0                                       // set by library:sd
#define MBED_CONF_SD_FSFAT_SDCARD_INSTALLED                                     1                                       // set by library:sd
#define MBED_CONF_SD_INIT_FREQUENCY                                             100000                                  // set by library:sd
#define MBED_CONF_SD_SPI_CLK                                                    SPI_SCK                                 // set by library:sd
#define MBED_CONF_SD_SPI_CS                                                     SPI_CS                                  // set by library:sd
#define MBED_CONF_SD_SPI_MISO                                                   SPI_MISO                                // set by library:sd
#define MBED_CONF_SD_SPI_MOSI                                                   SPI_MOSI                                // set by library:sd
#define MBED_CONF_SD_TEST_BUFFER                                                8192                                    // set by library:sd
#define MBED_CONF_SD_TRX_FREQUENCY                                              1000000                                 // set by library:sd
#define MBED_CONF_TARGET_BOOT_STACK_SIZE                                        0x400                                   // set by library:rtos[*]
#define MBED_CONF_TARGET_CONSOLE_UART                                           1                                       // set by target:Target
#define MBED_CONF_TARGET_DEEP_SLEEP_LATENCY                                     4                                       // set by target:MCU_STM32
#define MBED_CONF_TARGET_DEFAULT_ADC_VREF                                       NAN                                     // set by target:Target
#define MBED_CONF_TARGET_INIT_US_TICKER_AT_BOOT                                 1                                       // set by target:MCU_STM32
#define MBED_CONF_TARGET_INTERNAL_FLASH_UNIFORM_SECTORS                         1                                       // set by target:Target
#define MBED_CONF_TARGET_LPTICKER_LPTIM                                         1                                       // set by target:MCU_STM32WB
#define MBED_CONF_TARGET_LPTICKER_LPTIM_CLOCK                                   1                                       // set by target:MCU_STM32
#define MBED_CONF_TARGET_LPUART_CLOCK_SOURCE                                    USE_LPUART_CLK_LSE|USE_LPUART_CLK_PCLK1 // set by target:MCU_STM32
#define MBED_CONF_TARGET_LSE_AVAILABLE                                          1                                       // set by target:MCU_STM32
#define MBED_CONF_TARGET_MPU_ROM_END                                            0x0fffffff                              // set by target:Target
#define MBED_CONF_TARGET_TICKLESS_FROM_US_TICKER                                0                                       // set by target:Target
#define MBED_CONF_TARGET_XIP_ENABLE                                             0                                       // set by target:Target
#define MBED_CRC_TABLE_SIZE                                                     16                                      // set by library:drivers
#define MBED_STACK_DUMP_ENABLED                                                 0                                       // set by library:platform
#define MEM_ALLOC                                                               malloc                                  // set by library:mbed-trace
#define MEM_FREE                                                                free                                    // set by library:mbed-trace
#define SEC_CCM_CFG                                                             1                                       // set by library:cordio
#define SMP_DB_MAX_DEVICES                                                      3                                       // set by library:cordio
#define TARGET_LSE_DRIVE_LOAD_LEVEL                                             RCC_LSEDRIVE_LOW                        // set by target:MCU_STM32WB
// Macros
#define WSF_MS_PER_TICK                                                         1                                       // defined by library:cordio
#define _RTE_                                                                                                           // defined by library:rtos

#endif
