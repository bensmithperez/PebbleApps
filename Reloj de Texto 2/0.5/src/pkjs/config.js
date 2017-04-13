module.exports = [
  {
    "type": "heading",
    "defaultValue": "Configuración"
  },
  {
    "type": "text",
	  "defaultValue": "Elige el color de fondo y texto:"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colores"
      },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000000",
        "label": "Color de fondo"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Color de texto"
      }
    ]
  },	
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Otros",
		"capabilities": ["RECT"]
      },
      {
      "type": "toggle",
      "messageKey": "TextCentered",
      "label": "Texto centrado",
	  "capabilities": ["RECT"]
      }
	]
  },
  {
    "type": "submit",
    "defaultValue": "Aceptar"
  }
];