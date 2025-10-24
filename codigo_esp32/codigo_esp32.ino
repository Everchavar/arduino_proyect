#include <WiFi.h>
#include <WebServer.h>

// Instancia global del servidor web en el puerto 80
WebServer server(80);

// =======================================================
// 1. CONFIGURACIÓN Y CREDENCIALES
// =======================================================
const char* ssid = "Ever";      // <<<<<<< TU SSID
const char* password = "ever27123";   // <<<<<<< TU CLAVE

// Credenciales de login
const char* login_user = "admin";
const char* login_pass = "1234";

// Pines de relés 
int relays[] = { 23, 22, 21, 19 }; 
const int NUM_RELAYS = 4;

// Función auxiliar para leer el estado de los pines (LOW = ON)
String getRelayState(int pin) {
  return (digitalRead(pin) == LOW) ? "ON" : "OFF";
}

// =======================================================
// 2. PÁGINA DE LOGIN (Diseño Claro, con UTF-8 corregido)
// =======================================================
const char LOGIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1"><title>Acceso Seguro</title><style>
body{font-family:'Arial',sans-serif;display:flex;justify-content:center;align-items:center;min-height:100vh;margin:0;background:linear-gradient(135deg,#0f2027,#203a43,#2c5364);color:#fff}
.login-card{background-color:#fff;padding:40px;border-radius:12px;box-shadow:0 4px 12px rgba(0,0,0,.3);width:100%;max-width:350px;text-align:center}
.icon{font-size:48px;color:#ffc107;margin-bottom:15px}
h2{color:#333;margin-bottom:30px;font-weight:600}
input[type=text],input[type=password]{width:100%;padding:12px 15px;margin:10px 0;display:inline-block;border:1px solid #ccc;border-radius:8px;box-sizing:border-box;font-size:16px}
button[type=submit]{width:100%;background-color:#007bff;color:#fff;padding:14px 20px;margin-top:20px;border:none;border-radius:8px;cursor:pointer;font-size:18px;transition:background-color .3s ease}
button[type=submit]:hover{background-color:#0056b3}
.error{color:#dc3545;margin-top:15px}
</style></head><body>
<div class="login-card"><div class="icon">💡</div><h2>Login de Control</h2><form method="POST" action="/login"><input type="text" name="username" placeholder="Usuario" required><input type="password" name="password" placeholder="Contraseña" required><button type="submit">Iniciar Sesión</button></form></div></body></html>
)rawliteral";

// =======================================================
// 3. PÁGINA DE CONTROL (Diseño Oscuro/Toggle, con UTF-8 corregido)
// =======================================================
const char CONTROL_HTML_HEADER[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Control Remoto</title><style>
body{font-family:'Arial',sans-serif;background-color:#2c2c2c;color:#fff;display:flex;flex-direction:column;align-items:center;padding:20px;min-height:100vh}
h2{color:#f5f5f5;margin-bottom:30px;font-weight:500}
.control-card{background-color:#3c3c3c;padding:20px;border-radius:8px;box-shadow:0 4px 8px rgba(0,0,0,.4);width:100%;max-width:300px;text-align:center}
.relay-group{background-color:#3c3c3c;padding:15px 0;margin-bottom:15px;width:100%;display:flex;justify-content:space-between;align-items:center;border-bottom:1px solid #555}
.relay-text{font-size:1.1em;font-weight:400;color:#f5f5f5;flex-grow:1;text-align:left}
label.switch{position:relative;display:inline-block;width:60px;height:34px;margin:0}
label.switch input{opacity:0;width:0;height:0}
.slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;background-color:#555;transition:.4s;border-radius:34px}
.slider:before{position:absolute;content:"";height:26px;width:26px;left:4px;bottom:4px;background-color:white;transition:.4s;border-radius:50%}
input:checked+.slider{background-color:#4CAF50}
input:checked+.slider:before{transform:translateX(26px)}
.logout-btn{margin-top:25px;background:#dc3545;color:white;padding:10px 20px;border-radius:4px;text-decoration:none;display:block;transition:background-color .3s}
.logout-btn:hover{background:#c82333}
</style><script>
function toggleRelay(id,chk){fetch('/relay?ch='+id+'&state='+(chk.checked?1:0))}
</script></head><body><div class="control-card"><h2>Control de Relés</h2>
)rawliteral";

const char CONTROL_HTML_FOOTER[] PROGMEM = R"rawliteral(
<a href="/logout" class="logout-btn">Cerrar Sesión</a></div></body></html>
)rawliteral"; // <--- Punto y coma faltante AÑADIDO aquí.


// =======================================================
// 4. DEFINICIÓN DE FUNCIONES
// (Colocada aquí para evitar el error 'not declared in this scope' en Arduino IDE)
// =======================================================

// Función para generar dinámicamente la página de control
void sendControlPage() {
  String page = CONTROL_HTML_HEADER;
  for (int i = 0; i < NUM_RELAYS; i++) {
    int channel = i + 1;
    int pin = relays[i];

    page += "<div class=\"relay-group\">";
    page += "<span class=\"relay-text\">Relé " + String(channel) + " - GPIO " + String(pin) + "</span>";
    page += "<label class=\"switch\">";
    // Inyecta 'checked' si el relé está ON (LOW)
    page += "<input type=\"checkbox\" onchange=\"toggleRelay(" + String(channel) + ", this)\" ";
    if (digitalRead(pin) == LOW) {
      page += "checked";
    }
    page += "><span class=\"slider\"></span></label>";
    page += "</div>";
  }
  page += CONTROL_HTML_FOOTER;
  server.send(200, "text/html", page);
}


void setup() {
  Serial.begin(115200);

  // Inicialización de Pines
  for (int i = 0; i < NUM_RELAYS; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH); // Estado inicial: Apagado (HIGH)
  }

  // Conexión WiFi
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  // Lógica de reintento con tiempo límite de 15 segundos
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
    delay(500); 
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // --- Rutas del Servidor ---
    server.on("/", []() {
      server.send(200, "text/html", LOGIN_HTML);
    });

    server.on("/login", HTTP_POST, []() {
      if (server.arg("username") == login_user && server.arg("password") == login_pass) {
        sendControlPage(); // Login exitoso
      } else {
        server.send(200, "text/html", LOGIN_HTML); // Fallo de login
      }
    });

    server.on("/logout", []() {
      server.send(200, "text/html", LOGIN_HTML); // Redirige al login
    });

    // RUTA CRÍTICA: Control de Relé
    server.on("/relay", []() {
      int ch = server.arg("ch").toInt(); // Canal (1-4)
      int st = server.arg("state").toInt(); // Estado (1 = ON, 0 = OFF)
      
      // La función clave que enciende/apaga el relé (Lógica invertida)
      if (ch >= 1 && ch <= NUM_RELAYS) digitalWrite(relays[ch - 1], st ? LOW : HIGH); 
      server.send(200, "text/plain", "OK");
    });
    
    server.on("/control", []() {
      sendControlPage(); // Permite acceso directo
    });

    server.begin();
    Serial.println("Servidor web iniciado.");
  } else {
    Serial.println("\nERROR: Falló la conexión WiFi.");
  }
}

void loop() {
  // Maneja las peticiones del servidor
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient(); 
  }
}