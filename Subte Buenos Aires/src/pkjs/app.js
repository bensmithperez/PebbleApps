function HTTPGET(url) {
    var req = new XMLHttpRequest();
    req.open("GET", url, false);
    req.send(null);
    return req.responseText;
}

var getInfoLineas = function() {
  //por ahora esta es la dirección :D
  var response = HTTPGET("http://www.metrovias.com.ar/Subterraneos/Estado?site=Subterraneos");

  //lo convierto a JSON
  var json = JSON.parse(response);

  //saco los datos
  var lineaA = json[0].LineStatus;
  var lineaB = json[1].LineStatus;
  var lineaC = json[2].LineStatus;
  var lineaD = json[3].LineStatus;
  var lineaE = json[4].LineStatus;
  var lineaH = json[5].LineStatus;
  var lineaP = json[6].LineStatus;
  var lineaU = json[7].LineStatus;
 
  /*  //pruebo...
  console.log("LINEAA: " + lineaA + 
              "* LINEAB: " + lineaB + 
              "* LINEAC: " + lineaC + 
              "* LINEAD: " + lineaD + 
              "* LINEAE: " + lineaE + 
              "* LINEAH: " + lineaH + 
              "* LINEAP: " + lineaP + 
              "* LINEAU: " + lineaU);
 */
  //mis keys para el dictionary
  var dict = {KEY_LINEAA : lineaA, 
              KEY_LINEAB : lineaB, 
              KEY_LINEAC : lineaC, 
              KEY_LINEAD : lineaD, 
              KEY_LINEAE : lineaE, 
              KEY_LINEAH : lineaH, 
              KEY_LINEAP : lineaP, 
              KEY_LINEAU : lineaU};
    //envio los datos
    Pebble.sendAppMessage(dict);
};
 
Pebble.addEventListener("ready",
  function(e) {
    //ya está lista para recibir JS
    getInfoLineas();
  }
);