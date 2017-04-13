module.exports = [
  {
    "type": "heading",
    "defaultValue": "Configuració"
  },
  {
    "type": "text",
	  "defaultValue": "Tria el color de fons i text:"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000000",
        "label": "Color de fons"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Color de text"
      }
    ]
  },	
  {
    "type": "section",
	  "capabilities": ["RECT"],
    "items": [
      {
        "type": "heading",
        "defaultValue": "Altres"
      },
      {
      "type": "toggle",
      "messageKey": "TextCentered",
      "label": "Text centrat"
      }
	]
  },
  {
    "type": "submit",
    "defaultValue": "Acceptar"
  }
];