#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Define XSHUT pins for the 4 sensors
#define XSHUT_PIN1 2
#define XSHUT_PIN2 3
#define XSHUT_PIN3 4
#define XSHUT_PIN4 5

// Define unique I2C addresses for each sensor
#define ADDRESS_LOX1 0x30
#define ADDRESS_LOX2 0x31
#define ADDRESS_LOX3 0x32
#define ADDRESS_LOX4 0x33

// Create 4 sensor instances
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

void setID() {
  // 1. All XSHUT pins LOW to put all sensors in shutdown/reset
  digitalWrite(XSHUT_PIN1, LOW);
  digitalWrite(XSHUT_PIN2, LOW);
  digitalWrite(XSHUT_PIN3, LOW);
  digitalWrite(XSHUT_PIN4, LOW);
  delay(10);

  // 2. Bring all XSHUT pins HIGH (sensors will respond to default address 0x29)
  digitalWrite(XSHUT_PIN1, HIGH);
  digitalWrite(XSHUT_PIN2, HIGH);
  digitalWrite(XSHUT_PIN3, HIGH);
  digitalWrite(XSHUT_PIN4, HIGH);
  delay(10);

  // -----------------------------------------------------------------
  // Activate Sensor 1 and assign new address
  // -----------------------------------------------------------------
  digitalWrite(XSHUT_PIN1, HIGH);
  digitalWrite(XSHUT_PIN2, LOW);
  digitalWrite(XSHUT_PIN3, LOW);
  digitalWrite(XSHUT_PIN4, LOW);
  delay(10);
  if(!lox1.begin(ADDRESS_LOX1)) {
    Serial.println(F("Failed to boot sensor 1"));
    while(1);
  }
  delay(10);

  // -----------------------------------------------------------------
  // Activate Sensor 2 and assign new address
  // -----------------------------------------------------------------
  digitalWrite(XSHUT_PIN2, HIGH);
  delay(10);
  if(!lox2.begin(ADDRESS_LOX2)) {
    Serial.println(F("Failed to boot sensor 2"));
    while(1);
  }
  delay(10);

  // -----------------------------------------------------------------
  // Activate Sensor 3 and assign new address
  // -----------------------------------------------------------------
  digitalWrite(XSHUT_PIN3, HIGH);
  delay(10);
  if(!lox3.begin(ADDRESS_LOX3)) {
    Serial.println(F("Failed to boot sensor 3"));
    while(1);
  }
  delay(10);

  // -----------------------------------------------------------------
  // Activate Sensor 4 and assign new address
  // -----------------------------------------------------------------
  digitalWrite(XSHUT_PIN4, HIGH);
  delay(10);
  if(!lox4.begin(ADDRESS_LOX4)) {
    Serial.println(F("Failed to boot sensor 4"));
    while(1);
  }
  delay(10);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }

  // Set XSHUT pins as outputs
  pinMode(XSHUT_PIN1, OUTPUT);
  pinMode(XSHUT_PIN2, OUTPUT);
  pinMode(XSHUT_PIN3, OUTPUT);
  pinMode(XSHUT_PIN4, OUTPUT);

  Wire.begin();

  // Initialize and assign addresses via XSHUT pins
  setID();

  Serial.println(F("All 4 VL53L0X sensors initialized!"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;
  VL53L0X_RangingMeasurementData_t measure3;
  VL53L0X_RangingMeasurementData_t measure4;

  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);
  lox4.rangingTest(&measure4, false);

  Serial.print(F("S1: "));
  if (measure1.RangeStatus != 4) {
    Serial.print(measure1.RangeMilliMeter);
    Serial.print(F(" mm | "));
  } else {
    Serial.print(F("Out of range | "));
  }

  Serial.print(F("S2: "));
  if (measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
    Serial.print(F(" mm | "));
  } else {
    Serial.print(F("Out of range | "));
  }

  Serial.print(F("S3: "));
  if (measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
    Serial.print(F(" mm | "));
  } else {
    Serial.print(F("Out of range | "));
  }

  Serial.print(F("S4: "));
  if (measure4.RangeStatus != 4) {
    Serial.println(measure4.RangeMilliMeter);
  } else {
    Serial.println(F("Out of range"));
  }

  delay(200);
}
