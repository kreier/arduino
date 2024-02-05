# Overview about what to expect

```
Arduino and STM32F103        450-950kByte/s           or   0.9 MB/s
ESP32 with PSRAM (PseudoStatic RAM) - SPIRAM  90 MB/s and 20 MB/s
EPS32S3 tested myself                         90 MB/s and 45 MB/s
```

## Article 1 from May 2014:
https://forum.arduino.cc/t/fast-spi-23lc1024-ram-bank-photos-code-was-spi-eeprom-speeds-better/218908/13

## Article 2 from December 2019
https://www.esp32.com/viewtopic.php?t=13356

## My test from February 2024 - here T-Display S3

Read Speed 32bit ArraySize    1kb  time: 0.0 90.4 mb/sec  
Read Speed 32bit ArraySize    2kb  time: 0.0 90.5 mb/sec  
Read Speed 32bit ArraySize    4kb  time: 0.0 90.8 mb/sec  
Read Speed 32bit ArraySize    8kb  time: 0.0 89.1 mb/sec  
Read Speed 32bit ArraySize   16kb  time: 0.0 90.0 mb/sec  
Read Speed 32bit ArraySize   32kb  time: 0.0 89.6 mb/sec  
Read Speed 32bit ArraySize   64kb  time: 0.1 45.9 mb/sec  
Read Speed 32bit ArraySize  128kb  time: 0.1 45.7 mb/sec  
Read Speed 32bit ArraySize  256kb  time: 0.3 45.7 mb/sec  
Read Speed 32bit ArraySize  512kb  time: 0.1 45.7 mb/sec  
Read Speed 32bit ArraySize 1024kb  time: 0.2 45.7 mb/sec  
Read Speed 32bit ArraySize 2048kb  time: 0.4 45.7 mb/sec  
Read Speed 32bit ArraySize 4000kb  time: 0.9 45.7 mb/sec  

### 79 lines of code from the esp32 forum

``` C
// Profile fun! microseconds to seconds
double GetTime() { return (double)esp_timer_get_time() / 1000000; }

#define LIMIT 7

void setup(void) {
  Serial.begin(115200);
  int a = RamTest();
}


void loop(void) {
  // nothing to do here
}

int RamTest()
	{
	int rs[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4000 };
	printf("Ram Speed Test!\n\n");
	char xx = 0;
	for (int a = 0; a < LIMIT; a++)
		{
		printf("Read Speed 8bit ArraySize %4dkb ", rs[a]);
		int ramsize = rs[a] * 1024;
		char * rm = (char*)malloc(ramsize);

		int iters = 10; // Just enuff to boot the dog
		if (rs[a] < 512) iters = 50;
		double st = GetTime();
		for (int b = 0; b < iters; b++)
			for (int c = 0; c < ramsize; c++)
				xx |= rm[c];
		st = GetTime() - st;
		vTaskDelay(1); // Dog it!
		double speed = ((double)(iters*ramsize ) / (1024 * 1024)) / (st);
		printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
		free(rm);
		}
	printf("\n");
	for (int a = 0; a < LIMIT; a++)
		{
		printf("Read Speed 16bit ArraySize %4dkb ", rs[a]);
		int ramsize = rs[a] * 1024;
		short * rm = (short*)malloc(ramsize);

		int iters = 10; // Just enuff to boot the dog
		if (rs[a] < 512) iters = 50;
		double st = GetTime();
		for (int b = 0; b < iters; b++)
			for (int c = 0; c < ramsize/2; c++)
				xx |= rm[c];
		st = GetTime() - st;
		vTaskDelay(1); // Dog it!
		double speed = ((double)(iters*ramsize) / (1024 * 1024)) / (st);
		printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
		free(rm);
		}
	printf("\n");
	for (int a = 0; a < LIMIT; a++)
		{
		printf("Read Speed 32bit ArraySize %4dkb ", rs[a]);
		int ramsize = rs[a] * 1024;
		int * rm = (int*)malloc(ramsize);

		int iters = 10; // Just enuff to boot the dog
		if (rs[a] < 512) iters = 50;
		double st = GetTime();
		for (int b = 0; b < iters; b++)
			for (int c = 0; c < ramsize/4; c++)
				xx |= rm[c];
		st = GetTime() - st;
		vTaskDelay(1); // Dog it!
		double speed = ((double)(iters*ramsize) / (1024 * 1024)) / (st);
		printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
		free(rm);
		}
	printf("Test done!\n");
	return xx;
	}
```
