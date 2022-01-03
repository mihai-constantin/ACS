from flask import Flask, Response, request, jsonify

app = Flask(__name__)

@app.route("/ruta1", methods=["GET"])
def hello():
    return "Hello, World!"

@app.route("/ruta2")
def salut():
    return "Salut, Lume!"

@app.route("/salut/<int:numar>")
def salut_n(numar):
    return "Hello " + str(numar)

@app.route('/call_me')
def call_me():
    payload = request.get_json(silent=True)
    if not payload:
        # Error handling
        return Response(status='400')
    else:
        # more code here
        return payload

    return jsonify({'status': 'not found'}), 404

if __name__ == '__main__':
    app.run('0.0.0.0', debug=True)
