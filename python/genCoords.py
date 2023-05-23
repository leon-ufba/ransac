from PIL import Image
import numpy as np
import pickle
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
  print(coordinates)
  
  coords_path = 'coords/' + dataset + '.pickle'
  coords_path = os.path.join(dirname, coords_path)

  with open(coords_path, 'wb') as file:
    pickle.dump(coordinates, file)

dataset = 'dataset_test'
genCoords(dataset)



