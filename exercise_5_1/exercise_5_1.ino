/* ====================================
File name: Exerc_5_1.ino 
Date: 2018-02-21
Group Number: 07
Members That contributed:
Qing Lin
Qiu Shengzhi
Demonstration code: 44466

====================================== */

// Pins for light up segments on the LED display
#define A 7
#define B 6
#define C 13
#define D 3
#define E 2
#define F 4
#define G 5
// Pins for driving common anodes
#define CA1 9
#define CA2 8
// Pins for A B C D E F G
const int segs[7] = {A,B,C,D,E,F,G};
// Segments for each number
//const byte numbers[10] = {0b11110111, 0b1100000, 0b1011011, 0b1111010, 0b1101100, 
//0b0111110, 0b0111111, 0b1110000, 0b1111111, 0b1111100};

const byte numbers[10] = {0b00111111, 0b0000110, 0b01011011, 0b1001111, 0b1100110, 0b1101101,
0b1111101, 0b0000111, 0b1111111, 0b1101111 };

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
	pinMode( 10, INPUT); // digitalWrite(4,HIGH) for 2 bits dip switch
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
  	int temp = (analogRead(A0)*500.0)/1023;
  	if(temp > maxTemp) 
    	maxTemp = temp;

  	Serial.print("Temp:");
  	Serial.println(temp);
  	Serial.print("Max:");
  	Serial.println(maxTemp);
  	Serial.println(digitalRead(10));
  	unsigned long startTime = millis();
	
	if(digitalRead(10)==0){
	for (unsigned long elapsed = 0; elapsed < 600; elapsed = millis() - startTime ){
		ledDigit1(numbers[(temp%100)/10]);
		delay(5);
		ledDigit2(numbers[temp%10]);
		delay(5);
		}	
	}
	
	else{
		for(unsigned elapsed = 0; elapsed < 600; elapsed = millis() - startTime){
			ledDigit1(numbers[(maxTemp%100)/10]);
			delay(5);
			ledDigit2(numbers[maxTemp%10]);
			delay(5);
		}
	}
	
}
	
