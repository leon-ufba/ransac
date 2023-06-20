from PIL import Image
import numpy as np
import os

dirname = os.path.dirname(__file__)

Image.MAX_IMAGE_PIXELS = None

def genCoords(dataset):
  dataset_path = 'imgsDatasets/' + dataset + '.bmp'
  dataset_path = os.path.join(dirname, dataset_path)

  img = Image.open(dataset_path).convert('L')
  width, height = img.size

  print(width, height)

  np_img = np.array(img).clip(max = 1)

  print(np_img)

  coordinates = np.argwhere(np_img == 0)
  size = np.array([len(coordinates), 0])
  coordinates = np.append([size], coordinates, axis=0)
  print(coordinates)
  
  coords_path = 'coords/' + dataset + '.txt'
  coords_path = os.path.join(dirname, coords_path)

  np.savetxt(coords_path, coordinates, fmt='%d')

dataset = 'dataset_test_2'
genCoords(dataset)


