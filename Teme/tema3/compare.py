import argparse
from PIL import Image
def compare(first_file, second_file, eps):
    image_1 = Image.open(first_file)
    image_2 = Image.open(second_file)
    assert image_1.mode == image_2.mode, 'Images are of different type.'
    assert image_1.size == image_2.size, 'Images are of different size.'
    pairs = zip(image_1.getdata(), image_2.getdata())
    if len(image_1.getbands()) == 1:
        # for gray-scale image
        dif = list(abs(p1 - p2) for p1, p2 in pairs)
    else:
        # multi-channel image
        dif = list(abs(c1 - c2) for p1, p2 in pairs for c1, c2 in zip(p1, p2))
    assert len(list(filter(lambda x: x > eps, dif))) == 0, 'At least one pixel is different.'
    print('Images are equal.')
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('first_file')
    parser.add_argument('second_file')
    parser.add_argument('--eps', type=int, default=2, help='Diferenta maxima.')
    args = parser.parse_args()
    compare(args.first_file, args.second_file, args.eps)
if __name__ == '__main__':
    main()
