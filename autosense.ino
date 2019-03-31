#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AMMUANJU"; // WiFi SSID
const char* password = "bolt123456"; //WiFi Password
const char* mqtt_server = "192.168.43.185"; //MQTT server IP Address

int potHole_id = 0; 
String var, var2, var3, var4, var5; 
int codeLen =17; 
char charac[18]; 
double pitch, roll;

// MPU6050 Slave Device Address
const uint8_t MPU6050SlaveAddress = 0x68;

const uint8_t scl = D6;
const uint8_t sda = D7;

 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

//String post = "";

const uint8_t MPU6050_REGISTER_SMPLRT_DIV = 0x19; 
const uint8_t MPU6050_REGISTER_USER_CTRL = 0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1 = 0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2 = 0x6C;
const uint8_t MPU6050_REGISTER_CONFIG = 0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG = 0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG = 0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN = 0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE = 0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H = 0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ; 

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0; 
char msg[50]; //
int value = 0;
//mock latitude data 
double lat[]={12.79,12.80,12.81,12.82,12.83,12.84,12.85,12.86,12.87,12.88,12.89,12.90,12.91,12.8187,12.8202,12.8215,12.8227,12.8237,12.8255,12.8264,12.8277,12.8295,12.83,12.8304,12.8314,12.8324,12.8344,12.8357,12.8367,12.8382,12.8393,12.8409,12.8421,12.8424,12.8439,12.8443,12.8451,12.8457,12.8463,12.8469,12.8474,12.8479,12.8483};
//mock longitude data
double lon[]={80.02,80.03,80.04,80.05,80.06,80.07,80.08,80.09,80.10,80.11,80.12,80.13,80.14,80.0359,80.0371,80.038,80.0388,80.0393,80.0404,80.0412,80.0435,80.044,80.0454,80.0464,80.0471,80.0478,80.0503,80.0519,80.0531,80.0545,80.0562,80.0569,80.0575,80.0589,80.0594,80.0603,80.061,80.0616,80.0622,80.0626,80.0631,80.0633,80.0636};

void setup_wifi() {

 delay(10);
 
 Serial.println();
 Serial.print("");
 Serial.println(ssid);

 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }

 randomSeed(micros());

 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}

//The MQTT message that was recieved is printed
void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic); //MQTT topic to be subscribed
 Serial.print("] ");
 for (int i = 0; i < length; i++) {
 Serial.print((char)payload[i]); //the message which is recieved
 }
 Serial.println();

 // Switch on the LED if an 1 was received as first character
 if ((char)payload[0] == '1') {
 digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
 // but actually the LED is on; this is because
 // it is active low on the ESP-01)
 } else {
 digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
 }

}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Create a random client ID
 String clientId = "ESP8266Client-";
 clientId += String(random(0xffff), HEX);
 // Attempt to connect
 if (client.connect(clientId.c_str())) {
 Serial.println("connected");
 // Once connected, publish an announcement...
 client.publish("event", "hello world"); //"event" is the topic, prints hello world when connects to the MQTT connection""
 // ... and resubscribe
 client.subscribe("event"); //"event" is the topic to which we are subscribing
 } else {
 Serial.print("failed, rc=");
 Serial.print(client.state());
 Serial.println(" try again in 5 seconds");
 // Wait 5 seconds before retrying
 delay(5000); //sometimes it may not connect to the MQTT server, restart the NodeMCU, i.e remove the MicroUSB then reconnect
 }
 }
}


void setup() {
 Serial.begin(9600);
 Wire.begin(sda, scl);
 pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 //client.setCallback(callback);
 MPU6050_Init();
}

void loop() {
 if (!client.connected()) {
 reconnect();
 }
 client.loop();
 
 String post = "";
 int Device_id = 1; 


 

 double Ax, Ay, Az, T, Gx, Gy, Gz, Az1, d2; //variables for accelerometer and Gyroscope data
 
 Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
 Az1=Az;
 //divide each with their sensitivity scale factor
 Ax = (double)AccelX/AccelScaleFactor;
 Ay = (double)AccelY/AccelScaleFactor;
 Az = (double)AccelZ/AccelScaleFactor;
 T = (double)Temperature/340+36.53; //temperature formula
 Gx = (double)GyroX/GyroScaleFactor;
 Gy = (double)GyroY/GyroScaleFactor;
 Gz = (double)GyroZ/GyroScaleFactor;

 Serial.print("Ax: "); Serial.print(Ax);
 Serial.print(" Ay: "); Serial.print(Ay);
 Serial.print(" Az: "); Serial.print(Az);
 Serial.print(" T: "); Serial.print(T);
 Serial.print(" Gx: "); Serial.print(Gx);
 Serial.print(" Gy: "); Serial.print(Gy);
 Serial.print(" Gz: "); Serial.println(Gz);

 d2=Az1-Az; //delta of change in accelerometer reading in z-axis

 if(d2>0.2) //if delta is greater than 0.4, then it is classified as pothole
 {
 Serial.print("Pothole Detected");
 delay(1000);
   getAngle(Ax,Ay,Az);

 var = String(Device_id); //the temp variables which stores the datas which are merged into one array to be sent
       Serial.println(String(var).c_str());
 var2 = String(lat[potHole_id]);
       Serial.println(String(var2).c_str());
 var5 = ","; 
 var3 = String(lon[potHole_id]);
        Serial.println(String(var3).c_str());
 var4 = String(d2);
        Serial.println(String(var4).c_str());
 //post = var+","var2+","var3+","var4;
 post.concat(var);
//concat the datas into a single array
 post.concat(var5);
 post.concat(var2);
 post.concat(var5);
 post.concat(var3);
 post.concat(var5);  
 post.concat(var4);
  
 post.toCharArray(charac, codeLen+4); //the data is sent to charac
 Serial.println(String(charac).c_str());
 
 client.publish("message", charac); //the data stored in charac is sent 
 
 potHole_id+=1; //goes to the next pot-hole ID



 }

 delay(200);
}

//I2C communication initialisation ignore
void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
 Wire.beginTransmission(deviceAddress);
 Wire.write(regAddress);
 Wire.write(data);
 Wire.endTransmission();
}

// read all 14 register
void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
 Wire.beginTransmission(deviceAddress);
 Wire.write(regAddress);
 Wire.endTransmission();
 Wire.requestFrom(deviceAddress, (uint8_t)14);
 AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
 AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
 AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
 Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
 GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
 GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
 GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MPU6050_Init(){
 delay(1000);
 

 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
 I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}

void getAngle(int Ax1, int Ay1, int Az1)
{
  double x = float (Ax1);
  double y = float (Ay1);
  double z = float (Az1);

  double pitch = atan2((-x),sqrt(y*y+z*z));
  double roll = atan2(y,z);

  pitch = pitch * (180.0 / 3.14);
  roll = roll * (180.0 / 3.14);
  Serial.println(" Pitch - ");
  Serial.print(pitch);
  Serial.println(" Roll - ");
  Serial.print(roll);
 client.publish("p",String(pitch).c_str(),true);
 client.publish("r",String(roll).c_str(),true);
 if(roll>150||pitch>20)
 {
 Serial.println("CONTACTING EMERGENCY SERVICES");
 client.publish("emergency","CONTACTING EMERGENCY SERVICES");
 }
}



    




