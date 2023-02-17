/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <main.h>
#include <html.h>

// Replace with your network credentials
const char* ssid = "TP-LINK_8D8B26";
const char* password = "15394255";

Settings_t settings;
State_t state;
Control_t control;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


#define DRIVER_DIR D0
#define DRIVER_PULSE D1
#define SENSOR_HOME D2
#define SENSOR_UP D3

AccelStepper stepper(AccelStepper::DRIVER, DRIVER_DIR, DRIVER_PULSE);
Stepper_t step;

WifiSettings_t AccesPoint;
#define EEPROM_LENGTH 59
#define BYTE_LENGTH 1
#define WORD_LENGTH 2

#define SSID_LOC 0
#define SSID_LENGTH 24
#define PASS_LOC 24
#define PASS_LENGTH 24

#define TIME_LOC 48
#define MAX_SPEED_LOC 49
#define LENGTH_LOC 50
#define AUTOHOME_LOC 51
#define DIR_LOC 52
#define REVO_LOC 53
#define MAXPOS_LOC 55
#define MINPOS_LOC 57

void validateSettings(){
  if(control.workTime > 15) control.workTime = 15;
  if((settings.maxSpeed > 75) | (settings.maxSpeed == 0) ) settings.maxSpeed = 20;
  if((settings.length > 20) | (settings.length == 0) ) settings.length = 5;
  if(settings.revolution > 2500) settings.revolution = 400;
  if(settings.maxPosition > 3000) settings.maxPosition = 2000;
  if(settings.minPosition > 3000) settings.minPosition = 1;

  yield();
}
void initFlags(){
  control.workSpeed = 50;
  control.start = false;
  state.isHomed = false;
  state.isHomeProcess = false;
  state.isOnHomeSensor = false;
  state.isOnUpSensor = false;
  state.isHoming = false;
}

void readEEPROM() {
  EEPROM.begin(EEPROM_LENGTH);
  for(uint8_t i=0;i<SSID_LENGTH;i++){ 
    AccesPoint.ssid[i] = EEPROM.read(SSID_LOC+i);
    yield();
  }
  for(uint8_t i=0;i<PASS_LENGTH;i++){ 
    AccesPoint.password[i] = EEPROM.read(PASS_LOC+i);
    yield();
  }
  control.workTime = EEPROM.read(TIME_LOC);
  settings.maxSpeed = EEPROM.read(MAX_SPEED_LOC);
  settings.length = EEPROM.read(LENGTH_LOC);
  settings.autoHome = EEPROM.read(AUTOHOME_LOC);
  settings.direction = EEPROM.read(DIR_LOC);
  uint16_t h = EEPROM.read(REVO_LOC);
  settings.revolution = ((h<<8) & 0xFF00) | EEPROM.read(REVO_LOC+1);
  h = EEPROM.read(MAXPOS_LOC);
  settings.maxPosition = ((h<<8) & 0xFF00) | EEPROM.read(MAXPOS_LOC+1);
  h = EEPROM.read(MINPOS_LOC);
  settings.minPosition = ((h<<8) & 0xFF00) | EEPROM.read(MINPOS_LOC+1);
  EEPROM.end();
  validateSettings();
}

void saveSettings(){
  validateSettings();
  EEPROM.begin(EEPROM_LENGTH);
  for(uint8_t i=0;i<SSID_LENGTH;i++){ 
    EEPROM.write(SSID_LOC+i, AccesPoint.ssid[i]);
    yield();
  }
  for(uint8_t i=0;i<PASS_LENGTH;i++){ 
    EEPROM.write(PASS_LOC+i, AccesPoint.password[i]);
    yield();
  }  
  EEPROM.write(TIME_LOC, control.workTime);
  EEPROM.write(MAX_SPEED_LOC, settings.maxSpeed);
  EEPROM.write(LENGTH_LOC, settings.length);
  EEPROM.write(AUTOHOME_LOC, settings.autoHome);
  EEPROM.write(DIR_LOC, settings.direction);
  EEPROM.write(REVO_LOC, settings.revolution>>8);
  EEPROM.write(REVO_LOC+1, settings.revolution & 0x00FF);
  EEPROM.write(MAXPOS_LOC, settings.maxPosition>>8);
  EEPROM.write(MAXPOS_LOC+1, settings.maxPosition & 0x00FF);
  EEPROM.write(MINPOS_LOC, settings.minPosition>>8);
  EEPROM.write(MINPOS_LOC+1, settings.minPosition & 0x00FF);
  EEPROM.end();
}

String sendSettings() {
  char json_string[512];
  DynamicJsonDocument doc(512);
  JsonObject root  = doc.to<JsonObject>();
  root["dataType"] = 1;
  root["revolution"] = settings.revolution;
  root["direction"] = settings.direction;
  root["maxPosition"] = settings.maxPosition;
  root["minPosition"] = settings.minPosition;
  root["maxSpeed"] = settings.maxSpeed;
  root["autoHome"] = settings.autoHome;
  root["length"] = settings.length;
  root["workTime"] = control.workTime;
  serializeJson(root, json_string);
  ws.textAll(String(json_string));
  return String(json_string);
}

String sendState() {
  char json_string[512];
  DynamicJsonDocument doc(512);
  JsonObject root  = doc.to<JsonObject>();
  root["dataType"] = 3;
  root["isMove"] = state.isMove;
  root["isHomed"] = state.isHomed;
  root["isMinPos"] = state.isMinPos;
  root["isMaxPos"] = state.isMaxPos;
  root["currentPosition"] = state.currentPosition;
  root["currentSpeed"] = state.currentSpeed;

  root["start"] = control.start;
  root["power"] = control.power;
  root["destPosition"] = control.destPosition;
  root["workSpeed"] = control.workSpeed;
  root["workTime"] = control.workTime;
  root["workType"] = control.workType;

  root["maxPosition"] = settings.maxPosition;
  root["minPosition"] = settings.minPosition;

  serializeJson(root, json_string);
  ws.textAll(String(json_string));
  return String(json_string);
}
int8_t scannedSSID = -1;

String sendPoints() {
  char json_string[512];
  DynamicJsonDocument doc(512);
  JsonObject root  = doc.to<JsonObject>();
  scannedSSID = WiFi.scanComplete();
  root["dataType"] = 4;
  root["points"] = scannedSSID;  
  if(scannedSSID > 0){
    for (int i = 0; i < scannedSSID; i++) {
      root["point"+String(i)] = WiFi.SSID(i);
    }
    scannedSSID = -1;
  } 
  serializeJson(root, json_string);
  ws.textAll(String(json_string));
  WiFi.scanNetworks(true);
  return String(json_string);
}
boolean isWifiGet = false;
void handleWifi() {
  Serial.printf("Got new wifi: %s:%s\r\n", AccesPoint.ssid, AccesPoint.password);
  WiFi.begin(AccesPoint.ssid, AccesPoint.password);
  uint8_t connCnt = 0;
  Serial.print("Try to connect");
  while ((WiFi.status() != WL_CONNECTED) & (connCnt < 10)) {
    Serial.print(".");
    delay(1000);
    connCnt++;
  }
  Serial.println("");
  if((WiFi.status() == WL_CONNECTED)){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(AccesPoint.ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());

    String ipLocal = "exo-";
    ipLocal += WiFi.localIP().toString();
    WiFi.softAP(ipLocal, "12345678", 3, 0, 4);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());    
    saveSettings();
  }else{
    Serial.println("Huynya kakaya to...");
  }
}


boolean isDataReceived = false;
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  StaticJsonDocument<300> parsed; //Пул памяти
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    DeserializationError error = deserializeJson(parsed, (char*)data);
    if (error) {
      data[len] = 0;
      if (strcmp((char*)data, "init") == 0) {
        sendSettings();
      }else if (strcmp((char*)data, "getWifi") == 0) {
        sendPoints();
      }
    } else {  
      String s = parsed["ssid"];
      String p = parsed["wifipass"];      
      uint8_t type = parsed["dataType"];
      switch(type){
        case 1:
          settings.revolution = parsed["revolution"];
          settings.direction = parsed["direction"];
          settings.maxPosition = parsed["maxPosition"];
          settings.minPosition = parsed["minPosition"];
          settings.maxSpeed = parsed["maxSpeed"];
          settings.autoHome = parsed["autoHome"];
          settings.length = parsed["length"];
          isDataReceived = true;
        break;
        case 2:
          control.start = parsed["start"];
          control.power = parsed["power"];
          control.save = parsed["save"];
          control.home = parsed["home"];
          control.moveLeft = parsed["moveLeft"];
          control.moveRight = parsed["moveRight"];
          control.destPosition = parsed["destPosition"];
          control.workSpeed = parsed["workSpeed"];
          control.workTime = parsed["workTime"];
          control.workType = parsed["workType"];
          state.currentSpeed = control.workSpeed;
          isDataReceived = true;
        break;  
        case 4:
          for(uint8_t i=0; i<30; i++) AccesPoint.ssid[i] = 0;
          for(uint8_t i=0; i<30; i++) AccesPoint.password[i] = 0; 
          for(uint8_t i=0; i<s.length(); i++) AccesPoint.ssid[i] = s[i]; 
          for(uint8_t i=0; i<p.length(); i++) AccesPoint.password[i] = p[i];
          isWifiGet = true;
          
        break;        
        default:
          data[len] = 0;
          if (strcmp((char*)data, "init") == 0) {
            sendSettings();
          }
        break;
      } 
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\r\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\r\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

boolean isStarted = false;
boolean isStoped = true;

void setStepperParams(){
  step.speed = float((settings.revolution*settings.maxSpeed/settings.length)*control.workSpeed/100);
  step.accel = step.speed*4;
}

void setStepperDest(){
  step.dest = long(control.destPosition*settings.revolution/settings.length);
  if(!settings.direction) step.dest = -step.dest;
}

void setup(){
  Serial.begin(115200);
  pinMode(DRIVER_DIR, OUTPUT);
  pinMode(DRIVER_PULSE, OUTPUT);
  pinMode(SENSOR_HOME, INPUT_PULLUP);
  pinMode(SENSOR_UP, INPUT_PULLUP);
  delay(500);
  readEEPROM();
  initFlags();
  Serial.printf("Read from EEPROM: %s:%s\r\n", AccesPoint.ssid, AccesPoint.password);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(AccesPoint.ssid, AccesPoint.password);
  //WiFi.begin(ssid, password);
  uint8_t connCnt = 0;
  while ((WiFi.status() != WL_CONNECTED) & (connCnt < 10)) {
    delay(1000);
    Serial.print(".");
    connCnt++;
  }
  if((WiFi.status() == WL_CONNECTED)){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(AccesPoint.ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
  }
  String ipLocal = "exo-";
  ipLocal += WiFi.localIP().toString();
  WiFi.softAP(ipLocal, "12345678", 3, 0, 4);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  initWebSocket();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.begin();
  Serial.println("HTTP server started");
  WiFi.scanNetworks(true);
  delay(2000);
  stepper.setMinPulseWidth(100);
  setStepperParams();
  stepper.setMaxSpeed(step.speed);
  stepper.setAcceleration(step.accel);
  control.destPosition = 2000;
  setStepperDest();
  stepper.setCurrentPosition(0);
  stepper.stop();
}

void handleControl(){
  if(isWifiGet){
    isWifiGet = false;
    handleWifi();
  }
  if(control.save){
    control.save = false;
    saveSettings();
  }  
  yield();
}

void handleStepperParams(){
      setStepperParams();
      setStepperDest();
      stepper.setAcceleration(step.accel);
      stepper.setMaxSpeed(step.speed); 
      if(control.start){
        stepper.moveTo(step.dest);
      }
      Serial.printf("target: %ld, coord: %ld\r\n", stepper.targetPosition(), stepper.currentPosition());
      yield();
}

void stopStep(){
  stepper.stop();
  while(stepper.isRunning()){
    stepper.run();
    yield();
  }   
}

void goHome(){
  if(control.start == true){
    Serial.println("Cannot to home");
    delay(300);
    return;
  } 
  if(!state.isHomeProcess){
    if(stepper.isRunning() == true){
      stepper.stop();
      stopStep();
      delay(300);
    }
    state.isHomed = false;
    state.isHomeProcess = true;
    stepper.setCurrentPosition(0);
    if(settings.direction) stepper.moveTo(-4000000);
    else stepper.moveTo(4000000);
  }
  if((digitalRead(SENSOR_HOME)==1) & (state.isOnHomeSensor == false)) stepper.run();
  else{
    if(!state.isOnHomeSensor){
      stopStep();
      state.isOnHomeSensor = true;
      delay(300);
    }else{
      if(!state.isHoming){
        if(settings.direction) stepper.moveTo(4000000);
        else stepper.moveTo(-4000000);   
        state.isHoming = true;     
      }else{
        if(digitalRead(SENSOR_HOME)==0) stepper.run();
        else{
          stopStep();
          delay(300);
          state.isHomed = true;
          state.isHomeProcess = false;
          state.isOnHomeSensor = false;
          state.isHoming = false;
          control.home = false;
          stepper.setCurrentPosition(0);
          Serial.println("Homed!");
        }
      }

    }
  }

}

boolean cykle = false;

void loop() {
  static boolean moveLeftFlag = false, moveRightFlag = false;
  ws.cleanupClients();
  handleControl();

  if(isDataReceived){
    sendState();
    handleStepperParams();
    isDataReceived = false;
  }
  if((control.home==true) | (state.isHomeProcess == true)){
    goHome();
  }
  if(control.start){
    if(!isStarted){
      setStepperParams();
      stepper.setMaxSpeed(step.speed);
      stepper.moveTo(step.dest);
      isStarted = true;  
      isStoped = false;
    }
    if(digitalRead(SENSOR_HOME)==0){
      stopStep();
      Serial.println("on home sensor!");
      delay(300);
    }else if(digitalRead(SENSOR_UP)==0){
      stopStep();
      Serial.println("on up sensor!");
      delay(300);
    }else stepper.run();
    
  }else if(!control.start & !isStoped){
    isStarted = false;
    isStoped = true;
    stopStep();
    delay(300);
  }

  if(control.moveLeft){
    if(!moveLeftFlag){
      moveLeftFlag = true;
      if(settings.direction) stepper.moveTo(-4000000);
      else stepper.moveTo(4000000);
    }
    if(digitalRead(SENSOR_HOME)==1) stepper.run();
    else stopStep();
  }else if(!control.moveLeft){
    if(moveLeftFlag){
      stopStep();
      delay(300);
      moveLeftFlag = false;
    }
  }

  if(control.moveRight){
    if(!moveRightFlag){
      moveRightFlag = true;
      if(settings.direction) stepper.moveTo(4000000);
      else stepper.moveTo(-4000000);
    }
    if(digitalRead(SENSOR_UP)==1) stepper.run();
    else stepper.stop();
  }else if(!control.moveRight){
    if(moveRightFlag){
      stopStep();
      delay(300);
      moveRightFlag = false;
    }
  }
  
 
}

