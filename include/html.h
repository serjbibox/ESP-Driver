#ifndef INC_HTML_H_
#include <main.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ExoBed control panel</title>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8; width=device-width">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 0.8rem;
    color: white;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  .buttonStart {
    width: auto;
    padding: 10px 90px;
    font-size: 14px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }    
  .buttonLR {
    width: auto;
    padding: 10px 35px;
    font-size: 14px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }  
  .button {
    width: auto;
    padding: 5px 15px;
    font-size: 14px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   .timerText {
    width: auto;
    padding: 10px 1px;
    font-size: 14px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }   
   .buttonStart:active {
     background-color: #143642;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }     
   .buttonLR:active {
     background-color: #143642;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }   
   .button:active {
     background-color: #143642;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .labelText {
     font-size: 0.8rem;
     color:#143642;
     font-weight: bold;
   }   
   .state {
     font-size: 0.8rem;
     color:#143642;
     font-weight: bold;
   }
   .masonry-layout__panel {
    break-inside: avoid;
    padding: 5px;
  }
  .masonry-layout__panel-content {
    padding: 5px;
    border-radius: 10px;
  }   
  .btnMainLayout {
    column-count: 3;
    column-gap: 0;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
    padding-top:15px;
  }
  .btnTimeLayout {
    column-count: 4;
    column-gap: 0;
    height: auto;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
    padding-top:15px;
  }  
  .btnDirLayout {
    column-count: 2;
    column-gap: 0;
    height: auto;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
    padding-top:15px;
  }  
  .btnDiaLayout {
    column-count: 3;
    column-gap: 0;
    height: auto;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
    padding-top:15px;
  }     
  .trackBarLayout {
    column-count: 1;
    column-gap: 0;
    height: auto;
    text-align: center;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
  }  
  .btnStartLayout {
    column-gap: 0;
    height: auto;
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px #143642;
    padding-top:  3px;
    padding-bottom:3px;
  }    
#reqPosition {
  height: 30px;
  width: 270px;
}  
#reqVelocity {
  height: 30px;
  width: 270px;
} 
</style>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>ExoBed V1.0 control panel</h1>
  </div>
  <div class="masonry-layout__panel">
    <div class="masonry-layout__panel-content">
      <div class="btnMainLayout">
        <button id="btnPower" class="button"></button>
        <p><button id="btnSave" class="button">Сохранить</button></p>
        <p><button id="btnHome" class="button">Home</button></p>
      </div>
      <br>
      <div class="btnTimeLayout">
        <text class="labelText">Время работы, мин.:</text>        
        <p><input type="number" id="workTimer" class="timerText" value="10" min="1" max="15"></p>
        <p><text class="labelText">Режим работы:</text></p> 
        <p><button id="btnType" class="button">Цикл</button></p>
      </div>   
      <br>    
      <div class="btnDiaLayout">
        <p><text class="labelText">Диапазон:</text></p>
        <p><input type="number" id="posMin" class="timerText" value="0" min="0" max="2499"></p>
        <p><input type="number" id="posMax" class="timerText" value="1000" min="1" max="2500"></p>
      </div>    
      <br>   
      <div class="trackBarLayout">
        <p class="state">Скорость: <span id="velocity">%VEL%</span></p>
        <input type="range" min="1" max="100" value="50" id="reqVelocity" width="500" onchange="onChangeVelocity()">
      </div> 
      <br>
      <div class="trackBarLayout">
        <p class="state">Позиция: <span id="position">%POS%</span>мм</p>
        <input type="range" min="1" max="2500" value="100" id="reqPosition" width="500" onchange="onChangePosition()">
      </div>  
      <br>    
      <div class="btnStartLayout">
        <button id="btnStart" class="buttonStart">Старт</button>
      </div> 
      <br>    
      <div class="btnDirLayout">
        <button id="btnLeft" class="buttonLR">Влево</button>
        <p><button id="btnRight" class="buttonLR">Вправо</button></p>
      </div>  
      <br>
      <div class="topnav">
        <h1>Настройки</h1>
      </div> 
      <br>
      <div class="btnDirLayout">
        <button id="btnDir" class="button">Forward</button>
        <p><button id="btnAutoPos" class="button">AutoHome ON</button></p>
      </div>
      <br>
      <div class="btnDirLayout">
        <text class="labelText">Разрешение, имп/об:</text>        
        <p><input type="number" id="revolution" class="timerText" value="64" min="1" max="10000"></p>
        <p><text class="labelText">Макс. скорость, мм/с:</text></p> 
        <p><input type="number" id="maxSpeed" class="timerText" value="5" min="1" max="10000"></p>
      </div> 
      <br>
      <div class="trackBarLayout">
        <text class="labelText">Шаг вала, мм:</text>        
        <p><input type="number" id="length" class="timerText" value="5" min="1" max="10000"></p>
      </div> 
      <br>    
      <div class="btnDirLayout">
        <button id="btnScanWifi" class="buttonLR">Scan WiFi</button>
        <p><button id="btnConn" class="buttonLR">Connect</button></p>
      </div>       
      <br>
      <div class="trackBarLayout">
        <text class="labelText">Сеть:</text>        
        <p><select class="buttonLR" id="ssid" name="ssid">
          <option value="1">Wifi Point</option>
        </select></p>
      </div>   
      <br>    
      <div class="trackBarLayout">
        <text class="labelText">Пароль:</text>
        <p><input type="text" id="wifipass" class="timerText"></p>
      </div>           
   </div> 
  </div>
<script>
/*              <select id=\"ssid\" name=\"ssid\">";
          scannedSSID = WiFi.scanComplete();
          if(scannedSSID > 0){
            for (int i = 0; i < scannedSSID; i++) {
              out += "<option value=\"";
              out += WiFi.SSID(i);
              out += "\">";
              out += WiFi.SSID(i);
              out += "</option>";
            }
            scannedSSID = -1;
          }      
          out += "</select>\*/



  //var gateway = `ws://${window.location.hostname}/ws`;
  var gateway = `ws://192.168.0.150/ws`;
  var websocket;
let settings = {
  dataType: Number(1),
  revolution: Number(52),
  direction: false,
  length: Number(5),
  maxSpeed: Number(100),
  maxPosition: Number(2000), 
  minPosition: Number(10),
  autoHome: false
};
let control = {
  dataType: Number(2),
  workTime: Number(10),
  workSpeed: Number(40),
  destPosition: Number(1000),
  workType: false,
  start: false,
  home: false,
  save: false,
  moveLeft: false,
  moveRight: false,
  power: true
};
let state = {
  dataType: Number(3),
  isMove: true,
  isHomed: false,
  isMaxPos: false,
  isMinPos: false,
  currentPosition: Number(2),
  currentSpeed: Number(2)
}; 
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; 
  }
  function onOpen(event) {
    console.log('Connection opened');
    websocket.send("init");
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    let jsonData = JSON.parse(event.data);
    if(jsonData["dataType"] == 1){
      initSettings(jsonData);  
    }else if(jsonData["dataType"] == 3){
      getState(jsonData);
    }else if(jsonData["dataType"] == 4){
      fillWifiList(jsonData);
    }

  }
function fillWifiList(jsonData){
    var i=0;
    var n = document.getElementById('ssid').options[i].length;
    for(i=0;i<n;i++){
      document.getElementById('ssid').options[i] = null;
    }
    for(i=0;i<jsonData["points"];i++){
      var newPoint = jsonData["point"+i]
      var newOption = new Option(newPoint, newPoint);
      document.getElementById('ssid').options[i] = newOption;
    }
}  
function getState(jsonData){
  state.isMove = jsonData["isMove"];
  state.isHomed = jsonData["isHomed"];
  state.isMaxPos = jsonData["isMaxPos"];
  state.isMinPos = jsonData["isMinPos"];
  state.currentPosition = jsonData["currentPosition"];
  state.currentSpeed = jsonData["currentSpeed"];

  control.workTime = jsonData["workTime"];
  control.workSpeed = jsonData["workSpeed"];
  control.destPosition = jsonData["destPosition"];
  control.workType = jsonData["workType"];
  control.start = jsonData["start"];
  control.power = jsonData["power"];

  settings.maxPosition = jsonData["maxPosition"];
  settings.minPosition = jsonData["minPosition"];

  document.getElementById('reqVelocity').value = control.workSpeed;
  document.getElementById('velocity').innerHTML = control.workSpeed;  
  document.getElementById('workTimer').value = control.workTime;
  document.getElementById('posMin').value = settings.minPosition;
  document.getElementById('posMax').value = settings.maxPosition;  
  document.getElementById('btnPower').innerHTML = control.power ? "OFF" : "ON";
  document.getElementById('btnType').innerHTML = control.workType ? "Цикл" : "Free";
  document.getElementById('btnStart').innerHTML = control.start ? "Стоп" : "Старт";

} 
function initSettings(jsonData){
      settings.revolution = jsonData["revolution"];
      settings.direction = jsonData["direction"];
      settings.maxPosition = jsonData["maxPosition"];
      settings.minPosition = jsonData["minPosition"];
      settings.maxSpeed = jsonData["maxSpeed"];
      settings.autoHome = jsonData["autoHome"];
      settings.length = jsonData["length"];  
      control.workTime = jsonData["workTime"];  
      document.getElementById('btnDir').innerHTML = settings.direction ? "Forward" : "Backward";
      document.getElementById('btnAutoPos').innerHTML = settings.autoHome ? "AutoHome ON" : "AutoHome OFF";
      document.getElementById('maxSpeed').value = settings.maxSpeed;
      document.getElementById('length').value = settings.length;
      document.getElementById('revolution').value = settings.revolution;
      document.getElementById('posMin').value = settings.minPosition;
      document.getElementById('posMax').value = settings.maxPosition;
      document.getElementById('workTimer').value = control.workTime;
}

  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('btnScanWifi').addEventListener('click', toggleScanWifi);
    document.getElementById('btnConn').addEventListener('click', connectWifi);
    document.getElementById('btnPower').innerHTML = control.power ? "OFF" : "ON";
    document.getElementById('btnPower').addEventListener('click', togglePower);
    document.getElementById('btnSave').addEventListener('click', toggleSave);
    document.getElementById('btnHome').addEventListener('click', toggleHome);
    if (/Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) {
      document.getElementById('btnLeft').addEventListener('touchstart', focusLeft);
      document.getElementById('btnRight').addEventListener('touchstart', focusRight);
      document.getElementById('btnLeft').addEventListener('touchend', toggleLeft);
      document.getElementById('btnRight').addEventListener('touchend', toggleRight);
    } else {
      document.getElementById('btnLeft').addEventListener('focus', focusLeft);
      document.getElementById('btnRight').addEventListener('focus', focusRight);
      document.getElementById('btnLeft').addEventListener('click', toggleLeft);
      document.getElementById('btnRight').addEventListener('click', toggleRight);
    }
    document.getElementById('btnStart').addEventListener('click', toggleStart);
    document.getElementById('btnStart').innerHTML = control.start ? "Стоп" : "Старт";
    document.getElementById('btnType').addEventListener('click', toggleType);
    document.getElementById('btnType').innerHTML = control.workType ? "Цикл" : "Free";

    document.getElementById('posMin').addEventListener('change', inputPos);
    document.getElementById('posMax').addEventListener('change', inputPos);
    document.getElementById('workTimer').addEventListener('change', inputTime);

    control.workSpeed = document.getElementById('reqVelocity').value;
    document.getElementById('velocity').innerHTML = control.workSpeed;
    control.destPosition = document.getElementById('reqPosition').value;
    document.getElementById('position').innerHTML = control.destPosition;  
    
    document.getElementById('btnDir').innerHTML = settings.direction ? "Forward" : "Backward";
    document.getElementById('btnDir').addEventListener('click', toggleDir);

    document.getElementById('btnAutoPos').innerHTML = settings.autoHome ? "AutoHome ON" : "AutoHome OFF";
    document.getElementById('btnAutoPos').addEventListener('click', togglePos);

    document.getElementById('maxSpeed').addEventListener('change', inputVel);
    document.getElementById('revolution').addEventListener('change', inputVel);
    document.getElementById('length').addEventListener('change', inputVel);
    document.getElementById('btnSave').addEventListener('click', toggleSave);    

  }
  function toggleScanWifi(){
    websocket.send("getWifi");
  } 
  function connectWifi(){
    let wifiSettings = {
      dataType: Number(4),
      ssid: document.getElementById("ssid").value,
      wifipass: document.getElementById('wifipass').value
    };    
    websocket.send(JSON.stringify(wifiSettings));
  }       
  function inputTime(){
    control.workTime = Number(document.getElementById('workTimer').value);
    websocket.send(JSON.stringify(control));
  } 
  function inputPos(){
    settings.minPosition = Number(document.getElementById('posMin').value);
    settings.maxPosition = Number(document.getElementById('posMax').value);
    websocket.send(JSON.stringify(settings));
  }  
  function toggleStart(){
    control.start = !control.start;
    //document.getElementById('btnStart').innerHTML = control.start ? "Стоп" : "Старт";
    websocket.send(JSON.stringify(control));
  }   
  function togglePower(){
    control.power = !control.power;
    //document.getElementById('btnPower').innerHTML = control.power ? "OFF" : "ON";
    websocket.send(JSON.stringify(control));
  }  
  function toggleSave(){
    control.save = true;
    websocket.send(JSON.stringify(control));
    control.save = false;
  }    
  function toggleHome(){
    control.home = true;
    websocket.send(JSON.stringify(control));
    control.home = false;
  }  
    
  function focusLeft(){
    control.moveLeft = true;
    websocket.send(JSON.stringify(control));
  }  
  function focusRight(){
    control.moveRight = true;
    websocket.send(JSON.stringify(control));
  }  
  function toggleLeft(){
    control.moveLeft = false;
    websocket.send(JSON.stringify(control));
    document.activeElement.blur();
  }  
  function toggleRight(){
    control.moveRight = false;
    websocket.send(JSON.stringify(control));
    document.activeElement.blur();
  } 
  function toggleType(){
    control.workType = !control.workType;
    //document.getElementById('btnType').innerHTML = control.workType ? "Цикл" : "Free";
    websocket.send(JSON.stringify(control));
  } 
  function onChangeVelocity(){
    control.workSpeed = document.getElementById('reqVelocity').value;
    document.getElementById('velocity').innerHTML = control.workSpeed;
    websocket.send(JSON.stringify(control));
  }   
  function onChangePosition(){
    control.destPosition = document.getElementById('reqPosition').value;
    document.getElementById('position').innerHTML = control.destPosition;
    websocket.send(JSON.stringify(control));
  }   
  function toggleDir(){
    settings.direction = !settings.direction;
    document.getElementById('btnDir').innerHTML = settings.direction ? "Forward" : "Backward";
    websocket.send(JSON.stringify(settings));
  }  
  function togglePos(){
    settings.autoHome = !settings.autoHome;
    document.getElementById('btnAutoPos').innerHTML = settings.autoHome ? "AutoHome ON" : "AutoHome OFF";
    websocket.send(JSON.stringify(settings));
  }  
  function inputVel(){
    settings.revolution = Number(document.getElementById('revolution').value);
    settings.maxSpeed = Number(document.getElementById('maxSpeed').value);
    settings.length = Number(document.getElementById('length').value);
    websocket.send(JSON.stringify(settings));
  }  


</script>
</body>
</html>)rawliteral";

#endif