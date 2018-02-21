/* ====================================
File name: Exerc_5_1.ino 
Date: 2018-02-21
Group Number: 07
Members That contributed:
Qing Lin
Qiu Shengzhi
Demonstration code: 

====================================== */

// Pins for light up segments on the LED display
#define A 11
#define B 10
#define C 7
#define D 9
#define E 8
#define F 12
#define G 13
// Pins for driving common anodes
#define CA1 6
#define CA2 5
// Pins for A B C D E F G
const int segs[7] = {A,B,C,D,E,F,G};
// Segments for each number
const byte numbers[10] = {0b11110111, 0b1100000, 0b1011011, 0b1111010, 0b1101100, 
0b0111110, 0b0111111, 0b1110000, 0b1111111, 0b1111100}

int maxTemp = 0;

void setup(){
	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);
	pinMode(E, OUTPUT);
	pinMode(F, OUTPUT);
	pinMode(G, OUTPUT);
	
	pinMode(CA1, OUTPUT);
	pinMode(CA2, OUTPUT);
	
	pinMode(A0, INPUT); // Configuring pin A0 as input
	pinMode( 4, INPUT); // digitalWrite(4,HIGH) for 2 bits dip switch
	Serial.begin(9600);	
}

void ledDigit1(byte number){
	digitalWrite(CA1,LOW);
	digitalWrite(CA2,HIGH);
	ledSegments(number);
}

void ledDigit2(byte number){
	digitalWrite(CA1,HIGH);
	digitalWrite(CA2,LOW);
	ledSegments(number);
}

void ledSegments(byte number){
	for (int i=0; i < 7; i++){
		int bit = bitRead(number,i);
		digitalWrite(segs[i],bit);
	}
}

void loop(){
	if(digitalRead(4)=0){
		int temp = (analogRead(A0))*500.0)/1024;
		if(temp > maxTemp) 
			maxTemp = temp;

		unsigned long startTime = millis();
		for (unsigned long elapsed = 0; elapsed < 600; elapsed = millis() - startTime ){
			ledDigit1(numbers[(temp%100)/10]);
			delay(5);
			ledDigit2(numbers[temp%10]);
			delay(5);
		}	
	}
	
	else{
		unsigned long startTime = millis();
		for(unsigned elapsed = 0; elapsed < 600; elapsed = millis() - startTime){
			ledDigit1(numbers[(maxTemp%100)/10]);
			delay(5);
			ledDigit2(numbers[maxTemp%10]);
			delay(5);
		}
	}
	
}
	
