from flask import Flask, Response, request, jsonify, json
app = Flask(__name__)

movie_id = 0
movies = []

class Movie:
    def __init__(self, id, nume):
        self.id = id
        self.nume = nume

    def get_dict(self):
        return ({"id": self.id, "nume": self.nume})

# GET
@app.route("/movies", methods=["GET"])
def get_all_movies():
    global movies
    print("=== [GET] Movies ===")
    print(movies)
    return jsonify(movies), 200

@app.route("/movie/<int:ID>", methods=["GET"])
def get_movie_by_id(ID):
    global movies
    print("=== [GET] Movies ===")
    print(movies)
    print("id: " + str(ID))
    for idx in range(len(movies)):
        if movies[idx]['id'] == ID:
            return jsonify(movies[idx]), 200

    return Response(status='404')

# POST
@app.route("/movies", methods=["POST"])
def add_movie():
    global movies
    global movie_id
    json_data = request.json
    if json_data and "nume" in json_data:
        movie_id = movie_id + 1
        movies.append(Movie(movie_id, json_data['nume']).get_dict())
        print("=== [POST] Movies ===")
        print(movies)
        return Response(status='201')
    else:
        return Response(status='400')

# PUT
@app.route("/movie/<int:ID>", methods=["PUT"])
def update_movie(ID):
    global movies
    json_data = request.json
    if json_data and "nume" in json_data:
        print(movies)
        for idx in range(len(movies)):
            if movies[idx]['id'] == ID:
                movies[idx]['nume'] = json_data["nume"]
                return Response(status='200')
        return Response(status='404')
    else:
        return Response(status='400')

# DELETE
@app.route("/reset", methods=["DELETE"])
def delete_all_movies():
    global movies
    global movie_id
    movies.clear()
    movie_id = 0
    return Response(status='200')

@app.route("/movie/<int:ID>", methods=["DELETE"])
def delete_movie(ID):
    global movies
    for idx in range(len(movies)):
        if movies[idx]['id'] == ID:
            movies.pop(idx)
            return Response(status='200')
    
    return Response(status='404')

if __name__ == '__main__':
    app.run('0.0.0.0', debug=True)
