import numpy as np
from PIL import Image
from rotCoords import viewedCoords, rotate
from ransac import RANSAC

def printRansac(rs):
  print("\n------------------------")
  print("bestFit:\t\t%f" % rs.bestFit)
  print("bestQty:\t\t%f" % rs.bestQty)
  print("bestModel:\t%f\t%f" % (rs.bestModel.a, rs.bestModel.b))
  print("------------------------\n")
  return


def testRansac():
  dataX = [
    2,3,4,5,2,3,4,5
    # -0.848, -0.800, -0.704, -0.632, -0.488, -0.472, -0.368, -0.336, -0.280, -0.200,
    # -0.008, -0.084,  0.024,  0.100,  0.124,  0.148,  0.232,  0.236,  0.324,  0.356,
    #  0.368,  0.440,  0.512,  0.548,  0.660,  0.640,  0.712,  0.752,  0.776,  0.880,
    #  0.920,  0.944, -0.108, -0.168, -0.720, -0.784, -0.224, -0.604, -0.740, -0.044,
    #  0.388, -0.020,  0.752,  0.416, -0.080, -0.348,  0.988,  0.776,  0.680,  0.880,
    # -0.816, -0.424, -0.932,  0.272, -0.556, -0.568, -0.600, -0.716, -0.796, -0.880,
    # -0.972, -0.916,  0.816,  0.892,  0.956,  0.980,  0.988,  0.992,  0.004,  0.111
  ]
  dataY = [
    2,4,6,8,8,6,4,2
    # -0.917, -0.833, -0.801, -0.665, -0.605, -0.545, -0.509, -0.433, -0.397, -0.281,
    # -0.205, -0.169, -0.053, -0.065,  0.035,  0.083,  0.059,  0.175,  0.179,  0.191,
    #  0.259,  0.287,  0.359,  0.395,  0.483,  0.539,  0.543,  0.603,  0.667,  0.679,
    #  0.751,  0.803, -0.265, -0.341,  0.111, -0.113,  0.547,  0.791,  0.551,  0.347,
    #  0.975,  0.943, -0.249, -0.769, -0.625, -0.861, -0.749, -0.945, -0.493,  0.163,
    # -0.469,  0.067,  0.891,  0.623, -0.609, -0.677, -0.721, -0.745, -0.885, -0.897,
    # -0.969, -0.949,  0.707,  0.783,  0.859,  0.979,  0.811,  0.891, -0.137,  0.111
  ]

  data = np.column_stack([dataX, dataY])
  ransacRes = RANSAC(data)
  printRansac(ransacRes)
  return

def plotView(view_coords, origin, view_range):
  height, width = (view_range * 2, view_range * 2)
  new_img = np.ones((height, width), dtype='int') * 127
  rounded_coords = (np.rint(view_coords)).astype(int)
  for c in rounded_coords:
    if(0 <= c[0] and c[0] < width and 0 <= c[1] and c[1] < height):
      new_img[c[1]][c[0]] = 0 # Note: SCREEN COORDS ARE INVERTED (y, x)
  im = Image.fromarray(new_img)
  im.show()
  # im.convert('RGB').save("out_test.bmp")
  return


def main():
  dataset = 'dataset_test_2'
  view_range = 500
  bot_coords = np.array([0,view_range])
  angle = 0
  delta = 0

  for i in range(10):
    viewed_coordinates = viewedCoords(dataset, origin=bot_coords, angle=angle, view_range=view_range)
    
    data = viewed_coordinates;

    initial_view_coord = np.array([0,view_range])
    translated_coords = viewed_coordinates - (np.array(bot_coords) - initial_view_coord)
    plotView(translated_coords, bot_coords, view_range)
    print(translated_coords)

    with open('.\coords\data'+str(i)+'.txt', 'w') as file:
     file.write(f"{len(translated_coords)} 0\n")
     for pair in translated_coords:
       file.write(f"{int(pair[0])} {int(pair[1])}\n")
    ransacRes = RANSAC(translated_coords, view_range)
    model = ransacRes.bestModel
    if(model.a == 0):
      delta = 2 * view_range
    else:
      delta = (view_range - model.b) / model.a
    rotated_delta = np.array([delta * np.cos(angle), delta * np.sin(-angle)])
    angle += -np.arctan(model.a)
    print(delta, angle)
    bot_coords = bot_coords + rotated_delta

    print(rotated_delta)
    print(bot_coords)

    # input()

  return


main()