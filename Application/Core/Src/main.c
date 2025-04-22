/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
typedef void(*ptrF)(uint32_t dlyticks);
typedef void (*pFunction)(void);

/* Bootloader Shared API Struct */
struct BootloaderAPI {
    void (*Blink)(uint32_t dlyticks);
    void (*TurnOn)(void);
    void (*TurnOff)(void);
};

/* UART handle ---------------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Section variables ---------------------------------------------------------*/
unsigned char __attribute__((section(".myBufSectionRAM"))) buf_ram[128];
const unsigned char __attribute__((section(".myBufSectionFLASH"))) buf_flash[10] = {0,1,2,3,4,5,6,7,8,9};

#define FLASH_APP_ADDR (0x8008000)

/* Function Prototypes -------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* Support printf over UART --------------------------------------------------*/
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        HAL_UART_Transmit(&huart2, (uint8_t *)ptr++, 1, 100);
    }
    return len;
}

/* RAM-resident LED toggle function ------------------------------------------*/
void __attribute__((section(".RamFunc"))) TurnOnLED(GPIO_PinState PinState) {
    if (PinState != GPIO_PIN_RESET) {
        LED_GREEN_GPIO_Port->BSRR = (uint32_t)LED_GREEN_Pin;
    } else {
        LED_GREEN_GPIO_Port->BRR = (uint32_t)LED_GREEN_Pin;
    }
}

/* Application entry ---------------------------------------------------------*/
int main(void) {
    struct BootloaderAPI *api = (struct BootloaderAPI *) 0x8018000;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    while (1) {
        printf("Application Running\r\n");
        api->Blink(200);
        HAL_Delay(1000);
    }
}

/* System Clock Configuration ------------------------------------------------*/
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

/* USART2 Initialization -----------------------------------------------------*/
static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&huart2);
    HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8);
    HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8);
    HAL_UARTEx_DisableFifoMode(&huart2);
}

/* GPIO Initialization -------------------------------------------------------*/
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {}
}
