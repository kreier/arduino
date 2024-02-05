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