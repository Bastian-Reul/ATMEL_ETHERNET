/*
 * ATMEL_ETHERNET.cpp
 *
 * Created: 21.11.2018 13:19:21
 * Author : BastianReul
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL				// CPU Takt
#endif

// UART Defines
#define BAUD 57600                                  // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
#define MYUBRR F_CPU/16/BAUD-1


#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>


#include "Pin_ATMEGA328.h"
#include "SPI_ATMEGA328.h"
#include "UART_ATMEGA328.h"

// MQTT subscribe Example.... W5500 + STM32F103(IoT board)
//Include: Board configuration
//#include "IoTEVB.h"

//Include: MCU peripheral Library
//#include "stm32f10x_rcc.h"
//#include "stm32f10x.h"

//Include: W5500 iolibrary
#include "w5100.h"
#include "wizchip_conf.h"
//#include "misc.h"

//Include: Internet iolibrary
#include "MQTTClient.h"

//Include: MCU Specific W5500 driver
//#include "W5500HardwareDriver.h"

//Include: Standard IO Library
#include <stdio.h>

//Socket number defines
#define TCP_SOCKET	0

//Receive Buffer Size define
#define BUFFER_SIZE	1024

//Username and Password for the MQTT Server
#define USERNAME "XXXXXX"
#define PASSWORD "XXXXXX"

//Global variables
unsigned char targetIP[4] = {000, 000, 000, 000}; // mqtt server IP
unsigned int targetPort = 1883; // mqtt server port
uint8_t mac_address[6] = {};
wiz_NetInfo gWIZNETINFO = { .mac = {0xDE, 0xAD, 0x77, 0xE8, 0x3E, 0xED}, //user MAC (von irgendwoher kopiert)
							.ip = {192,168,79,177}, //user IP
							.sn = {255,255,255,224},
							.gw = {192,168,79,161},
							.dns = {194,94,127,196},
							.dhcp = NETINFO_STATIC};

unsigned char tempBuffer[BUFFER_SIZE] = {};
char Ausgabebuffer[100] = {};


struct opts_struct
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	enum QoS qos;
	char* username;
	char* password;
	unsigned char* host;
	int port;
	int showtopics;
} opts ={ (char*)"stdout-subscriber", 0, (char*)"\n", QOS0, USERNAME, PASSWORD, targetIP, targetPort, 0 };

// @brief messageArrived callback function
void messageArrived(MessageData* md)
{
	unsigned char testbuffer[100];
	MQTTMessage* message = md->message;

	if (opts.showtopics)
	{
		memcpy(testbuffer,(char*)message->payload,(int)message->payloadlen);
		*(testbuffer + (int)message->payloadlen + 1) = '\n';
		//printf("%s\r\n",testbuffer);
		sprintf(Ausgabebuffer, "%s\r\n",testbuffer);
		uart_transmit_string(Ausgabebuffer);
	}

	if (opts.nodelimiter)
		{//printf("%.*s", (int)message->payloadlen, (char*)message->payload);
		sprintf(Ausgabebuffer, "%.*s", (int)message->payloadlen, (char*)message->payload);
		uart_transmit_string(Ausgabebuffer);
		}
	else
	{
		sprintf(Ausgabebuffer, "%.*s%s", (int)message->payloadlen, (char*)message->payload, opts.delimiter);
		uart_transmit_string(Ausgabebuffer);
	}
}


// @brief 1 millisecond Tick Timer setting
void NVIC_configuration(void)
{
	//NVIC_InitTypeDef NVIC_InitStructure;
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//SysTick_Config(72000);
	//NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Highest priority
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);
}

// @brief 1 millisecond Tick Timer Handler setting
void SysTick_Handler(void)
{
	_delay_ms(1);
}

int main(void)
{
	//Einstellungen für den Timer
	TCCR0A |= (1 << COM0A1);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	OCR0A = 125-1;
	TIMSK0 |= (1<<OCIE0A);
	sei();
	
	//led_ctrl led1,led2;
	Pin Led1('C', 5, false);
	Pin Led2('C', 2, false);
	int i;
	int rc = 0;
	unsigned char buf[100];
	//Usart initialization for Debug.
	//USART1Initialze();
	uart_init(MYUBRR);
	uart_transmit_string("USART initialized.\n");
	spi_init_master();
	//spi_transmit_string("test");
	//	printf("USART initialized.\n\r");

	//I2C1Initialize();
		//printf("I2C initialized.\n\r");

		/*MACEEP_Read kann nicht gefunden werden
	MACEEP_Read(mac_address,0xfa,6);

	printf("Mac address\n\r");
	for(i = 0 ; i < 6 ; i++)
	{
		printf("%02x ",mac_address[i]);
	}
	printf("\n\r");*/

	//LED initialization.
	Led1.setze_Status(false);
	Led2.setze_Status(false);
	uart_transmit_string("Leds gesetzt.\n");

	//W5500 initialization.
//	W5500HardwareInitilize();
//		printf("W5500 hardware interface initialized.\n\r");

//	W5500Initialze();
//		printf("W5500 IC initialized.\n\r");

	//Hier hing es


	//Set network informations
	Led1.setze_Status(true);
	wizchip_setnetinfo(&gWIZNETINFO);
	uart_transmit_string("wizchip_setnetinfo\n");

	setSHAR(mac_address);
    uart_transmit_string("MAC Adresse gesetzt\n"); 
	//print_network_information();

	Network n;
	MQTTClient c;
	uart_transmit_string("Neues Netzwerk erstellt.\n"); 

	NewNetwork(&n, TCP_SOCKET);
	uart_transmit_string("NewNetwork\n");
	ConnectNetwork(&n, targetIP, targetPort);
	uart_transmit_string("ConnectNetwork\n");
	MQTTClientInit(&c,&n,1000,buf,100,tempBuffer,2048);

	uart_transmit_string("MQTT Client initialisiert\n");   

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = opts.clientid;
	data.username.cstring = opts.username;
	data.password.cstring = opts.password;

	uart_transmit_string("MQTT Username und PW gesetzt\n");

	data.keepAliveInterval = 60;
	data.cleansession = 1;

	rc = MQTTConnect(&c, &data);
	uart_transmit_string("Connected to MQTT\n");
	char buffer [10];
	itoa(rc, buffer, 10);

	//string str = string(intStr);
	//uart_transmit_string(buffer);
	opts.showtopics = 1;

	uart_transmit_string("Subscribing to \n");
	uart_transmit_string( "hello/wiznet \n");
	rc = MQTTSubscribe(&c, "hello/wiznet", opts.qos, messageArrived);
	uart_transmit_string("Subscribed to hello/wiznet \n");
	//itoa(rc, buffer, 10);
	//uart_transmit_string(buffer);
	
	MQTTMessage pubmsg;
	char payload[30];
	sprintf(payload, "Hello from Atmel");
	pubmsg.payload = payload;
	pubmsg.payloadlen = strlen(payload) + 1;
	pubmsg.qos = QOS0;
	pubmsg.retained = 0;
	char* topic = "hello/wiznet"; 
	rc = MQTTPublish(&c, topic, &pubmsg);
	//int counter = 0;

    while(true)
    {
		//counter++;
    	MQTTYield(&c, data.keepAliveInterval);
    }
	uart_transmit_string("Es wird disconnected \n");
	MQTTDisconnect(&c);
	n.disconnect(&n);
}



ISR (TIMER0_COMPA_vect)
{
	MilliTimer_Handler();
}