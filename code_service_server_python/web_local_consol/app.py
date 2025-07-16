from flask import Flask, jsonify, request, render_template, Response, send_file
import threading
import json
import os
from qr_code_generator import generate_cpp_qr
from datetime import datetime, timedelta
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Get credentials from environment
USERNAME = os.getenv('USERNAME')
PASSWORD = os.getenv('PASSWORD') 
DATA_FILE = os.getenv('DATA_FILE')

app = Flask(__name__)

#******************************************************************************
# function:    load_data
# parameter:
#    None
# return:
#    dict : JSON data from DATA_FILE or empty dictionary if file not found
#******************************************************************************
def load_data():
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, 'r') as f:
            return json.load(f)
    return {}

#******************************************************************************
# function:    save_data
# parameter:
#    data : Dictionary containing ESP device data to save to file
# return:
#    None
#******************************************************************************
def save_data(data):
    with open(DATA_FILE, 'w') as f:
        json.dump(data, f, indent=2)

#******************************************************************************
# function:    check_auth
# parameter:
#    username : String username to verify
#    password : String password to verify
# return:
#    Boolean : True if credentials match, False otherwise
#******************************************************************************
def check_auth(username, password):
    return username == USERNAME and password == PASSWORD

#******************************************************************************
# function:    authenticate
# parameter:
#    None
# return:
#    Response : HTTP 401 authentication required response
#******************************************************************************
def authenticate():
    return Response('Accès refusé\n', 401, {'WWW-Authenticate': 'Basic realm="Accès restreint"'})

#******************************************************************************
# function:    require_auth
# parameter:
#    None
# return:
#    Response : Authentication response if credentials invalid, None otherwise
#******************************************************************************
@app.before_request
def require_auth():
    auth = request.authorization
    if not auth or not check_auth(auth.username, auth.password):
        return authenticate()

#******************************************************************************
# function:    index
# parameter:
#    None
# return:
#    String : Rendered index.html template with device data
#******************************************************************************
@app.route('/')
def index():
    check_needs_replacement()
    estimated_duration = 730
    return render_template('index.html', devices=load_data(), estimated_duration=estimated_duration)


#******************************************************************************
# function:    check_needs_replacement
# parameter:
#    None
# return:
#    None – Updates the "needs_replacement" field for each ESP in the JSON data
#           based on whether the last_update is older than 3 days
#******************************************************************************

def check_needs_replacement():
    data = load_data()
    now = datetime.now()
    threshold = now - timedelta(days=3)

    for esp_id, esp_info in data.items():
        last_update_str = esp_info.get("last_update")
        try:
            if last_update_str:
                last_update = datetime.strptime(last_update_str, "%Y-%m-%dT%H:%M")
                esp_info["needs_replacement"] = last_update < threshold
            else:
                esp_info["needs_replacement"] = True
        except ValueError:
            esp_info["needs_replacement"] = True

    save_data(data)
    
#******************************************************************************
# function:    update_esp
# parameter:
#    esp_id : String ESP device identifier
# return:
#    Response : JSON response with update status or error
#******************************************************************************
@app.route('/update/<esp_id>', methods=['POST'])
def update_esp(esp_id):
    data = load_data()
    if esp_id not in data:
        return jsonify({"error": "ESP not found"}), 404

    posted = request.json
    name = posted.get("name_room", "")
    screen = posted.get("screen", "")

    if data[esp_id].get("name_room") != name:
        data[esp_id]["name_room"] = name
    elif "reset_battery" == screen :
        data[esp_id]["battery"] = 0
    elif data[esp_id].get("screen") != screen:
        data[esp_id]["screen"] = screen

    save_data(data)
    return jsonify({"status": "updated"})

#******************************************************************************
# function:    calendar
# parameter:
#    None
# return:
#    String : Rendered calendar.html template with device data
#******************************************************************************
@app.route('/calendar', methods=['GET', 'POST'])
def calendar():
    data = load_data()

    if request.method == 'POST':
        for esp_id in data:
            field = f"calendar_{esp_id}"
            new_value = request.form.get(field, "")
            if new_value:
                data[esp_id]["calendar_id"] = new_value
        save_data(data)
        return render_template('calendar.html', devices=data, message="Mise à jour réussie.")

    return render_template('calendar.html', devices=data)

#******************************************************************************
# function:    calendar_qr
# parameter:
#    None
# return:
#    Response : Generated QR code file or rendered template
#******************************************************************************
@app.route('/qr_code', methods=['GET', 'POST'])
def calendar_qr():
    if request.method == 'POST':
        url = request.form.get('calendar_url', '').strip()
        if not url:
            return "URL manquante", 400

        cpp_path = f"/var/www/html/tmp/qr_code.cpp"
        generate_cpp_qr(url, cpp_path)
        return send_file(cpp_path, mimetype="text/x-c++src", as_attachment=True)
    return render_template('qr.html')

#******************************************************************************
# function:    run_flask
# parameter:
#    None
# return:
#    None : Starts Flask server on specified host and port
#******************************************************************************
def run_flask():
    app.run(
        host=os.getenv('FLASK_HOST'),
        port=int(os.getenv('FLASK_PORT')),
        debug=False,
        use_reloader=False
    )

if __name__ == '__main__':
    # Lancer le serveur Flask dans un thread
    run_flask()
