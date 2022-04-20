#include <Password.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2); 
#include <Keypad.h> 
 
const byte numRows= 4; 
 
const byte numCols= 4; 
 
char keymap[numRows][numCols]= {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};

byte rowPins[numRows] = {9,8,7,6};
byte colPins[numCols]= {5,4,3,2}; 
 
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); 

Password passwd = Password("7355608"); 

char passwd2[6]=""; 
const int relayPin =11;
const int relayPin1 =13; 
 
void setup() { 
	Serial.begin(9600); 
	lcd.init();
  lcd.backlight();
	lcd.clear();
	lcd.setCursor(0,0);  
	lcd.print("Enter Password: ");
  pinMode(relayPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);  
} 
 
void loop() { 
char key = myKeypad.getKey(); 
   if (key != NO_KEY){ 
    digitalWrite(relayPin,HIGH);
    delay(300); 
	  digitalWrite(relayPin,LOW); 
	  Serial.print(key); 
	  delay(50);  
      switch (key){ 
      case 'D': changepasswd(); break;  
      case '*': checkpasswd(); break; 
      case '#':{ passwd.reset(); 
      lcd.clear(); 
	    lcd.setCursor(0,0);  
	    lcd.print(" Enter Password ");  
      break; 
      } 
     default: passwd.append(key); 
      } 
   } 
 
} 
void(* restFunc)(void) = 0; 
void checkpasswd() { 
   if (passwd.evaluate()){ 
    lcd.clear();
    Serial.println("OK."); 
	  lcd.setCursor(0,0);  
	  lcd.print("   SuccessfuL   ");  
	  digitalWrite(relayPin1,HIGH);
    delay(50);
    digitalWrite(relayPin1,LOW);
   } else { 
    digitalWrite(relayPin1,LOW); 
    lcd.clear();
	  lcd.setCursor(0,0);  
	  lcd.print(" Wrong Password! ");  
	  Serial.println("Wrong password!");
   }  
   restFunc();
   //passwd.reset();    
} 

void changepasswd(){ 
  
	 lcd.clear();
   lcd.setCursor(0,0);  
   lcd.print("Change Password:");  
    for(byte i=0;i<5;i++){ 
       char key = NO_KEY; 
       while(key == NO_KEY || key=='*' || key=='#' || key=='D') key = myKeypad.getKey(); 
        passwd2[i] = key; 
        delay(60); 
    } 
    passwd2[5] = '\0'; 
    passwd.set(passwd2); 
	lcd.clear(); 
  lcd.setCursor(0,0);  
  lcd.print(" PW Changed To: ");  
  lcd.setCursor(0,1);  
	lcd.print("     ");  
	lcd.print(passwd2);  
	lcd.print("     ");  
  Serial.print("Password changed to "); 
	Serial.println(passwd2); 
}
