#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
#include<time.h>
#include<softPwm.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#define M1 1 
#define M2 2
#define M3 3 
#define M4 4  
#define SW1 12
#define SW2 13
#define SW3 14
#define SW4 15

int segments[] = {31, 29, 23, 21, 30, 26, 24, 22};
int digits[] = {25, 28, 27, 11};
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int count = 0;
int fndData[10][8] = {
        {0, 0, 0, 0, 0, 0, 1, 1}, // 0
        {1, 0, 0, 1, 1, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0, 1}, // 2
        {0, 0, 0, 0, 1, 1, 0, 1}, // 3
        {1, 0, 0, 1, 1, 0, 0, 1}, // 4
        {0, 1, 0, 0, 1, 0, 0, 1}, // 5
        {0, 1, 0, 0, 0, 0, 0, 1}, // 6
        {0, 0, 0, 1, 1, 0, 1, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0, 1}, // 8
        {0, 0, 0, 0, 1, 0, 0, 1}, // 9
};
void setup(){
	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);
	pinMode(SW3, INPUT);
	pinMode(SW4, INPUT);
	softPwmCreate(M1, 0, 200);
	softPwmCreate(M2, 0, 200);
	softPwmCreate(M3, 0, 200);
	softPwmCreate(M4, 0, 200);
	
	softPwmWrite(M1, 0);
	softPwmWrite(M2, 0);
	softPwmWrite(M3, 0);
	softPwmWrite(M4, 0);
	
	for(int i=0; i<4; i++)
		pinMode(digits[i], OUTPUT);
	for(int i=0; i<8; i++)
		pinMode(segments[i], OUTPUT);
	digitalWrite(digits[0], HIGH);
	digitalWrite(digits[1], HIGH);
	digitalWrite(digits[2], HIGH);
	digitalWrite(digits[3], HIGH);
}

void fndOff(){
	for(int i=0; i<4; i++)
		digitalWrite(digits[i], LOW);
}

void targetUp(int t){
	softPwmWrite(t, 25);
	delay(400);
	softPwmWrite(t, 15);
	if(t == 1) state1 = 1;
	if(t == 2) state2 = 1;
	if(t == 3) state3 = 1;
	if(t == 4) state4 = 1;
}

void targetDown(int t){
	softPwmWrite(t, 5);
	delay(400);
	softPwmWrite(t, 15);
	if(t == 1) state1 = 0;
	if(t == 2) state2 = 0;
	if(t == 3) state3 = 0;
	if(t == 4) state4 = 0;
}
void start(){
	for(int j=3; j>0; j--){
		for(int i=0; i<8; i++)
			digitalWrite(segments[i], fndData[j][i]);
		delay(1000);
	}
	fndOff();	
}
void pickOn(int t){
	for(int i=0; i<4; i++)
		digitalWrite(digits[i], LOW);
	digitalWrite(digits[t], HIGH);
}
void number(int t){
	for(int i=0; i<8; i++)
		digitalWrite(segments[i], fndData[t][i]);
}

void *timerSet(void *num){
	int m = 0;
	int s = 3;
	int c = 0;
	int i = 60;
	while(1){
		pickOn(2);
		number(m);
		delay(4);

		pickOn(1);
		number(s);
		delay(4);

		pickOn(0);
		number(c);
		i--;
		delay(4);

		if(i == -1) { c--; i =60;}
		if(c == -1) { s--; c = 9;}
		if(s == -1) { m--; s = 5;}
		if(m == -1) break;
		delay(4);
	}
	count = 1;
}
void *timer(void *num){
	int m = 0;
	int s = 0;
	int c = 0;
	int c1 = 0;
	int i = 0;
	int j = 0;
	while(1){
		pickOn(3);
		number(m);
		delay(4);

		pickOn(2);
		number(s);
		delay(4);

		pickOn(1);
		number(c1);
		delay(4);

		pickOn(0);
		number(c);
		delay(4);
		if(j == 400) break;
		if((digitalRead(SW1) && digitalRead(SW2) && digitalRead(SW3) && digitalRead(SW4)) == HIGH) {j++; continue;}

		i++;
		if(i == 60) {c++; i=0;}
		if(c == 10) {c1++; c=0;}
		if(c1 == 10) {s++; c1=0;}
		if(s == 10) {m++; s=0;}
	}
	printf("end\n");
	fndOff();
	pthread_exit((void*) 0);
}
void showScore(int score){
	for(int i=0; i<500; i++){
		pickOn(2);
		number(score / 100);
		delay(4);

		pickOn(1);
		number(score / 10);
		delay(4);

		pickOn(0);
		number(0);
		delay(4);
	}
}
int main(void){
	if(wiringPiSetup() == -1) return -1;
	setup();
	targetDown(M1);
	targetDown(M2);
	targetDown(M3);
	targetDown(M4);
	int num;
	pthread_t pthread_A;
	printf("select Mode(1 or 2 or 3)\n");
	scanf("%d", &num);
	int score = 0;
	if(num == 1){
		fndOff();
		while(1){
			if(digitalRead(SW1) == HIGH) {targetUp(M1); score += 10;}
			if(digitalRead(SW2) == HIGH) {targetUp(M2); score += 10;}
			if(digitalRead(SW3) == HIGH) {targetUp(M3); score += 10;}
			if(digitalRead(SW4) == HIGH) {targetUp(M4); score += 10;}
			delay(500);
		}
	}else if(num == 2){
		pthread_create(&pthread_A, NULL, timerSet, NULL);
		while(1){
			srand(time(NULL));
			int random = rand() % 4 +1;		
			targetUp(random);
			delay(1500);
			if(state1 == 1 && (digitalRead(SW1) == HIGH)) score += 10;
			if(state2 == 1 && (digitalRead(SW2) == HIGH)) score += 10;
			if(state3 == 1 && (digitalRead(SW3) == HIGH)) score += 10;
			if(state4 == 1 && (digitalRead(SW4) == HIGH)) score += 10;
			if(count == 1) break;
			targetDown(random);
			delay(500);
		}
	}else if(num == 3){
		targetUp(M1);
		targetUp(M2);
		targetUp(M3);
		targetUp(M4);
		pthread_create(&pthread_A, NULL, timer, NULL);
		while(1){
			if(digitalRead(SW1) == HIGH) 
				if(digitalRead(SW2) == HIGH) 
					if(digitalRead(SW3) == HIGH) 
						if(digitalRead(SW4) == HIGH) 
							delay(8000);
			
		}
		
	}
	showScore(score);
	printf("score: %d\n", score);
	return 0;
}
