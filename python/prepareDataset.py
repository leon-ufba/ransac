from PIL import Image
import os
import numpy as np
import pickle
import math

dirname = os.path.dirname(__file__)
Image.MAX_IMAGE_PIXELS = None

def calculate_distance(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

def reduce_coordinates(input_file, output_file, radius):
    with open(input_file, 'rb') as file:
        coordinates = pickle.load(file)

    simplified_coordinates = [coordinates[0]]  # Start with the first coordinate

    for coord in coordinates[1:]:
        distance = np.linalg.norm(coord - simplified_coordinates[-1])

        if distance >= radius:
            simplified_coordinates.append(coord)
    
    simplified_coordinates = np.array(simplified_coordinates)

    with open(output_file, 'wb') as file:
        pickle.dump(simplified_coordinates, file)

    print(f"Coordenadas do dataset reduzidas. Salvas no arquivo '{output_file}'.")

def genCoords(dataset):
  dataset_path = 'imgsDatasets/' + dataset + '.bmp'
  dataset_path = os.path.join(dirname, dataset_path)

  img = Image.open(dataset_path).convert('L')

  np_img = np.array(img)
  coordinates = np.argwhere(np_img != 255)
  coordinates = np.flip(coordinates, axis=1)

  coords_path = 'coords/' + dataset + '.pickle'
  coords_path = os.path.join(dirname, coords_path)


  with open(coords_path, 'wb') as file:
    pickle.dump(coordinates, file)


dataset = input("Digite o nome do dataset: ")
simplify = input("Deseja simplificar o dataset? (Y/N)\n")
if simplify == "Y":
    simplify = True
else:
    simplify = False


try:  
    image_path = 'imgsDatasets/' + dataset + '.bmp'
    image_path = os.path.join(dirname, image_path)
    # Open the image
    image = Image.open(image_path)

    # Convert the image to grayscale
    grayscale_image = image.convert("L")

    # Create a new image with the same size as the original
    bw_image = Image.new("L", image.size)

    # Iterate over each pixel in the grayscale image
    for x in range(grayscale_image.width):
        for y in range(grayscale_image.height):
            pixel = grayscale_image.getpixel((x, y))

            # Convert pixel to black or white
            if pixel < 128:
                bw_image.putpixel((x, y), 0)  # Black pixel
            else:
                bw_image.putpixel((x, y), 255)  # White pixel

    # Save the black and white image

    colored_image = bw_image.convert('RGB')

    output = 'imgsDatasets/' + dataset + '.bmp'
    output_path = os.path.join(dirname, output)
    colored_image.save(output_path)

except:
    print("Erro ao converter o dataset " + dataset + '.')
else:
    print("Convertido o dataset " + dataset + " para cores binarias e exportado para o arquivo " + output + ".")

try:
    genCoords(dataset)  
except:
     print("Erro ao gerar coordenadas para o dataset.")
else:
    print("Coordenadas geradas com sucesso para o dataset.")
    
    if simplify == True:
        pickle_path = os.path.join(dirname, 'coords/' + dataset + '.pickle')
        pickle_path2 = os.path.join(dirname, 'coords/' + dataset + 'SIMP.pickle')
        reduce_coordinates(pickle_path, pickle_path2, 5.0) 