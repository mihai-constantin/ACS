from flask import Flask, render_template
import random

app = Flask(__name__)

images = [
    "https://i2.wp.com/www.libraryforsmartinvestors.com/wp-content/uploads/2017/02/aws_logo.jpg?fit=500%2C500&ssl=1",
    "https://i.pinimg.com/736x/8f/2a/30/8f2a30993c405b083ba8820ae6803b93.jpg",
    "http://isoc.ae/image/cache/catalog/courses/Google%20Cloud%20Compute%20Engine%20Essential%20Training-500x500.jpg",
    "https://images.g2crowd.com/uploads/product/image/large_detail/large_detail_1528237089/microsoft-azure-biztalk-services.jpg",
    "https://aptira.com/wp-content/uploads/2016/09/kubernetes_logo.png",
    "https://www.opsview.com/sites/default/files/docker.png"
]

@app.route('/')
def index():
    url = random.choice(images)
    return render_template('index.html', url=url)

if __name__ == "__main__":
    app.run(host="0.0.0.0")