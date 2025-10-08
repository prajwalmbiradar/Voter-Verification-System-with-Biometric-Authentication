//#include <Blynk.h>
#include <SoftwareSerial.h>

// Define the pins for SoftwareSerial
//SoftwareSerial espSerial(A1, A0); // RX, TX (change pins as needed)

#include <Keypad.h>
#include <stdlib.h>
#include <stdio.h>
#include <Wire.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>

String cname;
char lc;
char ck;
int id1 = 436;
const byte ROWS = 4;  // four rows
int i = 0;
bool scan = true;
int buzz = 12;
String hello = "Hi ";
int der[6] = { 2,4365,4568, 6937, 4789, 1234};
String names[6] = {" ","Prajwal, 20 M" ,"Praveen, 19 M" ,"shreya, 20 W" ,"nithin, 19 M" ,"Aishwarya, 19 W" };
String temp = "";
String adhaar = "";
char enter = 'D';
char back = 'B';
char clear = 'C';
char scankey = 'A';
const byte COLS = 4;  // four columns
LiquidCrystal_I2C lcd(0x27, 16, 2);
// define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 11, 10, 9, 8 };  // Row pinouts of the keypad
byte colPins[COLS] = { 7, 6, 5, 4 };    // Column pinouts of the keypad
// fingerprint scanner
#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
// initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String deleteLastChar(String str) {
  return str.substring(0, str.length() - 1);
}
void setup() {
  //mySerial.begin(9600);  // Initialize software serial communication on the chosen pins
  pinMode(buzz, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Welcome");
  lcd.setCursor(6, 1);
  lcd.print("ECI");
  Serial.begin(9600);
  // fingerprint scanner things
  Serial.println("\n\nAdafruit finger detect test");

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    // while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x"));
  Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x"));
  Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: "));
  Serial.println(finger.capacity);
  Serial.print(F("Security level: "));
  Serial.println(finger.security_level);
  Serial.print(F("Device address: "));
  Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: "));
  Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: "));
  Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  } else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains ");
    Serial.print(finger.templateCount);
    Serial.println(" templates");
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter UID :");
}
uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (!Serial.available())
      ;
    num = Serial.parseInt();
  }
  return num;
}
void restart() {
  adhaar = "";
  temp = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter UID :");
}
void loop() {
  if (scan == true) {
    Serial.println("please scanbarcode p");
    adhaar = "";
    //Serial.println(adhaar);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("scanning");
    lcd.setCursor(0, 1);
    lcd.print("barcode....");
    String incoming = "";
Serial.println("going to read string");
//while (true) {
  incoming = "";
  while (Serial.available() <= 0){

  }
      
        if (Serial.available() > 0) {
          // Read the incoming byte from the serial port
          incoming += Serial.readString();
        }
        Serial.println(incoming);
        
 /* if (Serial.available()>0) {
    incoming += Serial.readString();
    Serial.println(incoming);
    // Check if the last character is '\n'
    if (incoming.endsWith("\n")) {
      break;
    }
  }*/
//}

Serial.println("end of code");

  adhaar = incoming;
  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("your ID :-");
    lcd.setCursor(0, 1);
    lcd.print(adhaar);
    delay(1000);
    scan = true;
    ck = enter;
  } else {
    ck = customKeypad.getKey();
  }

  if (ck) {

    if (ck == enter) {
      int index = -1;

      Serial.println("yes");
      for (int i = 0; i < sizeof(der) / sizeof(der[0]); i++) {
        temp = der[i];
        //Serial.print(temp);
        if (temp == adhaar) {
          index = i;
          break;
        }
      }

      if (index == -1) {
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        lcd.print("no id found");
        delay(2000);
        //scan = false;
        restart();
        return;
      } else {
       
      

        Serial.println(names[index]);
        cname = names[index];
        Serial.println(cname);
        lc = cname[cname.length() - 1];
        Serial.println(lc);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(hello);
        lcd.print(names[index]);
        lcd.setCursor(0, 1);
        lcd.print("scanning.....");
        int fid = getFingerprintID();
        Serial.println("fid");
        Serial.println(fid);
        Serial.println(adhaar);
        delay(200);
        int bb = fid == 1 || fid == 2 || fid == 3 || fid == 4 || fid == 5 || fid == 6 || fid == 7 || fid == 8 || fid == 9 || fid == 10;
        Serial.println(bb);
        if ((fid == 1) || (fid == 2) || (fid == 3) || (fid == 4) || (fid == 5) || (fid == 6) || (fid == 7) || (fid == 8) || (fid == 9) || (fid == 10)) {

          temp = der[fid];
          Serial.println(temp);
          Serial.println(adhaar);

          if (temp.equals(adhaar)) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("success");
            lcd.setCursor(0, 1);
            lcd.print("you can vote :)");
            Serial.println("success");

            Serial.println("success x77yyert give");
            
            String myString = "countvote: ";
            myString += lc;  // Concatenate char to string

           Serial.println(myString);  // Send via Serial
            digitalWrite(buzz, HIGH);
            delay(1000);
            digitalWrite(buzz, LOW);
           /* String ind;
            int in = -1;
            //int inde = ind.length();

            while (in == -1) {
              //int inde = ind.length();
              in = ind.indexOf("voted");

              while (Serial.available() <= 0) {

              }
              Serial.println(ind);
              if (Serial.available() > 0) {
                // Read the incoming byte from the serial port
                ind += Serial.readString();
                 Serial.println(ind);

              }
            }*/
            String incoming = "";
             int in = -1;
  while (Serial.available() <= 0){

  }
      

        if (Serial.available() > 0) {
          // Read the incoming byte from the serial port
          incoming += Serial.readString();

        }
         in = incoming.indexOf("s");
       

        Serial.println(incoming);
        Serial.println(in);
            scan = true;
            restart();
            return;

          } else {
            Serial.println("failed");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("failed");
            delay(2000);
           // scan = false;
            restart();
            return;
          }
        } else {
          lcd.setCursor(0, 1);
          lcd.print("Wrong finger!");
          delay(2000);
          //scan = false;
          restart();
          return;
        }
      }
      //scan = false;
    } else if (ck == clear) {
      adhaar = "";
      Serial.println(adhaar);
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } else if (ck == scan) {
      Serial.println("please scanbarcode p");
      adhaar = "";
      //Serial.println(adhaar);
      lcd.setCursor(0, 0);
      lcd.print("scanning");
      lcd.setCursor(0, 1);
      lcd.print("barcode....");
      String ind;
      while (!Serial) {}
      if (Serial.available() > 0) {

        ind += Serial.readString();
      }
      Serial.println(ind);
      adhaar = ind;
      lcd.setCursor(0, 0);
      lcd.print("your ID :-");
      lcd.setCursor(0, 1);
      lcd.print(adhaar);
      scan = true;
    } else if (ck == back) {
      // adhaar = "";
      adhaar = deleteLastChar(adhaar);
      Serial.println(adhaar);
      lcd.setCursor(0, 1);
      String toprint;
      toprint = adhaar + "               ";
      lcd.print(toprint);
    } else {
      Serial.println(ck);
      adhaar += ck;
      lcd.setCursor(0, 1);
      lcd.print(adhaar);
      // lcd.print(ck);
      i++;
    }
  }
}

// fingerprint functions
uint8_t getFingerprintID() {

  uint8_t p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
    return -1;

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);
  return finger.fingerID;
}
uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");
  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID ");
  Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  return true;
}
