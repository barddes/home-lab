String templatePlant(Plant plant) {
    // Create a String object to build the HTML template
    String page = "<!DOCTYPE html>\n";
    page += "<html>\n";
    page += "<head>\n";
    page += "<title>Plant Status</title>\n";
    page += "<style>\n";
    page += "table { width: 50%; border-collapse: collapse; }\n";
    page += "th, td { border: 1px solid black; padding: 8px; text-align: left; }\n";
    page += "th { background-color: #f2f2f2; }\n";
    page += "button {\n";
    page += "    padding: 10px 20px;\n";
    page += "    font-size: 16px;\n";
    page += "    cursor: pointer;\n";
    page += "    margin: 5px;\n";
    page += "}\n";
    page += "img {\n";
    page += "    width: 24px;\n";
    page += "    height: 24px;\n";
    page += "}\n";
    page += "#status {\n";
    page += "    margin-top: 20px;\n";
    page += "}\n";
    page += "#active_loop {\n";
    page += "    font-size: 0.5em\n";
    page += "    color: darkred\n";
    page += "}\n";
    page += "</style>\n";
    page += "</head>\n";
    page += "<body>\n";
    page += "<h1>Plant "+ plant.name + " Status";
    if(state.loop_active) page += " <span id=\"active_loop\">(active loop)</span>";
    page += "</h1>\n";
    page += "now = " + String(millis()/1000.0f) + " s\n";
    page += "<table>\n";
    page += "<tr>\n";
    page += "<th>Attribute</th>\n";
    page += "<th>Value</th>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Name</td>\n";
    page += "<td>" + plant.name + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Active</td>\n";
    page += "<td>" + String(plant.active ? "True" : "False") + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Last Checked</td>\n";
    page += "<td>" + String(plant.last_checked) + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Pump Active</td>\n";
    page += "<td>" + String(plant.pump ? "ON" : "OFF") + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Pump Active Until</td>\n";
    page += "<td>" + String(plant.pump_active_until/1000.0f) + " s</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Sensor Active</td>\n";
    page += "<td>" + String(plant.sensor ? "ON" : "OFF") + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Sensor Active Until</td>\n";
    page += "<td>" + String(plant.sensor_active_until/1000.0f) + " s</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Last sensor reading</td>\n";
    page += "<td>" + String(plant.sensor_last_reading) + "</td>\n";
    page += "</tr>\n";
    page += "<tr>\n";
    page += "<td>Last sensor computed voltage</td>\n";
    page += "<td>" + String(plant.sensor_last_computed_voltage) + " mV</td>\n";
    page += "</tr>\n";
    page += "</table>\n";
    page += "<br/>\n";
    page += "<br/>\n";
    
    // Add buttons with icons
    page += "<button id=\"check\">CHECK</button>\n";
    page += "<button id=\"pump-on\">PUMP ON</button>\n";
    page += "<button id=\"pump-iff\">PUMP OFF</button>\n";
    page += "<button id=\"sensor-on\">SENSOR ON</button>\n";
    page += "<button id=\"sensor-off\">SENSOR OFF</button>\n";
    
    page += "<div id=\"status\"></div>\n";

    page += "<script>\n";
    page += "document.getElementById('check').addEventListener('click', async function() {\n";
    page += "    fetch('/check?id=0');\n";
    page += "    location.reload();\n";
    page += "});\n";
    page += "document.getElementById('pump-on').addEventListener('click', async function() {\n";
    page += "    await fetch('/pump?id=0', {method: \"POST\"});\n";
    page += "    location.reload();\n";
    page += "});\n";
    page += "document.getElementById('pump-off').addEventListener('click', async function() {\n";
    page += "    await fetch('/pump?id=0', {method: \"DELETE\"});\n";
    page += "    location.reload();\n";
    page += "});\n";
    page += "document.getElementById('sensor-on').addEventListener('click', async function() {\n";
    page += "    await fetch('/sensor?id=0', {method: \"POST\"});\n";
    page += "    location.reload();\n";
    page += "});\n";
    page += "document.getElementById('sensor-off').addEventListener('click', async function() {\n";
    page += "    await fetch('/sensor?id=0', {method: \"DELETE\"});\n";
    page += "    location.reload();\n";
    page += "});\n";

    page += "</script>\n";
    
    page += "</body>\n";
    page += "</html>\n";

    // Return the complete HTML page as a String
    return page;
}