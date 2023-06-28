import numpy as np
from PIL import Image
from rotCoords import viewedCoords, rotate
from ransac import RANSAC
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib import pyplot as plt, patches
import os

global viewArray
viewArray = []
white_image = np.ones((50, 50), dtype=np.uint8) * 255
#viewArray = [white_image, white_image, white_image]



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

def img_is_color(img):

    if len(img.shape) == 3:
        # Check the color channels to see if they're all the same.
        c1, c2, c3 = img[:, : , 0], img[:, :, 1], img[:, :, 2]
        if (c1 == c2).all() and (c2 == c3).all():
            return True

    return False

def show_image_list(list_images, list_titles=None, list_cmaps=None, grid=True, num_cols=2, figsize=(20, 10), title_fontsize=30, origin=[0,0], angle=0, view_range=25):
    '''
    Shows a grid of images, where each image is a Numpy array. The images can be either
    RGB or grayscale.

    Parameters:
    ----------
    images: list
        List of the images to be displayed.
    list_titles: list or None
        Optional list of titles to be shown for each image.
    list_cmaps: list or None
        Optional list of cmap values for each image. If None, then cmap will be
        automatically inferred.
    grid: boolean
        If True, show a grid over each image
    num_cols: int
        Number of columns to show.
    figsize: tuple of width, height
        Value to be passed to pyplot.figure()
    title_fontsize: int
        Value to be passed to set_title().
    '''

    assert isinstance(list_images, list)
    assert len(list_images) > 0
    assert isinstance(list_images[0], np.ndarray)

    if list_titles is not None:
        assert isinstance(list_titles, list)
        assert len(list_images) == len(list_titles), '%d imgs != %d titles' % (len(list_images), len(list_titles))

    if list_cmaps is not None:
        assert isinstance(list_cmaps, list)
        assert len(list_images) == len(list_cmaps), '%d imgs != %d cmaps' % (len(list_images), len(list_cmaps))

    num_images  = len(list_images)
    num_cols    = min(num_images, num_cols)
    num_rows    = int(num_images / num_cols) + (1 if num_images % num_cols != 0 else 0)

    # Create a grid of subplots.
    
    #fig, axes = plt.subplots(num_rows, num_cols, figsize=figsize)



    # Create list of axes for easy iteration.
    if isinstance(axes, np.ndarray):
        list_axes = list(axes.flat)
    else:
        list_axes = [axes]

    fig.clear()
    for ax in axes.flatten():
        ax.clear()

    

    imgpos = 1
    jumps = 0
    for i in range(num_images):    
      axis = fig.add_subplot(num_rows, num_cols+1, imgpos)
      img    = list_images[i]
      title  = list_titles[i] if list_titles is not None else 'Image %d' % (i)
      cmap   = list_cmaps[i] if list_cmaps is not None else (None if img_is_color(img) else 'gray')
      
      axis.imshow(img, cmap=cmap)
      axis.set_title(title, fontsize=title_fontsize) 
      axis.grid(grid)   
      if (imgpos-jumps)%(num_cols) == 0:
        imgpos +=1
        jumps +=1
      imgpos +=1
    
    axis = fig.add_subplot(1, num_cols+1, num_cols+1)
    image_path = 'imgsDatasets/'+ dataset + '.bmp'
    image_path = os.path.join(os.path.dirname(__file__), image_path)
    image = mpimg.imread(image_path)
    axis.imshow(image)
    axis.set_title('Mapa', fontsize=title_fontsize) 
    axis.grid(grid)  

    viewRec = patches.Rectangle((origin[0], origin[1]),view_range*2, -view_range, edgecolor='orange',
    facecolor=(0, 1, 0, 0.3), linewidth=0, angle=-angle)
    axis.add_patch(viewRec)
    viewRec = patches.Rectangle((origin[0], origin[1]),view_range*2, view_range, edgecolor='orange',
    facecolor=(0, 1, 0, 0.3), linewidth=0, angle=-angle)
    axis.add_patch(viewRec)
    
    axis.scatter([origin[0]], [origin[1]])   

    for i in range(num_images, len(list_axes)):
        list_axes[i].set_visible(False)

    fig.tight_layout()
    #plt.draw() 
    plt.pause(0.5) #is necessary for the plot to update for some reason
def plotView2(view_coords, origin, angle, view_range):
  height, width = (view_range * 2, view_range * 2)
  new_img = np.ones((height, width), dtype='int') * 127
  rounded_coords = (np.rint(view_coords)).astype(int)
  for c in rounded_coords:
    if(0 <= c[0] and c[0] < width and 0 <= c[1] and c[1] < height):
      new_img[c[1]][c[0]] = 0 # Note: SCREEN COORDS ARE INVERTED (y, x)
  im = Image.fromarray(new_img)
  viewArray.append(new_img)
  labels = []
  for i in range(len(viewArray)):
     labels.append("Step " + str(i))
  show_image_list(list_images=viewArray, list_titles=labels , num_cols=3, figsize=(20, 10), grid=False, title_fontsize=20, origin=origin, angle=angle, view_range=view_range)

  #im.show()
  # im.convert('RGB').save("out_test.bmp")
  return

def checkBreakConditions(view_range, delta, bot_coords, walkedDistance):
  breakCondition = False
  reason = ""
  if walkedDistance > view_range*2*10*2:
      breakCondition = True
      reason = "Distancia andada superior a " + str(view_range*2*10*2)
  if delta <= 0:
      breakCondition = True    
      reason = "Delta igual ou inferior a zero."    
  if delta > view_range*2:
      breakCondition = True    
      reason = "Delta superior a visada."
  if bot_coords[0] > view_range*2*10 or bot_coords[1] > view_range*2*10:
      breakCondition = True  
      reason = "Andou para fora area de operacao"  
  if bot_coords[0] < 0 or bot_coords[1] < 0:
      breakCondition = True  
      reason = "Andou para fora area de operacao"    

  return breakCondition, reason

def main():
  global dataset
  dataset = 'dataset_test_3'
  view_range = 50 #Largura do quadrado de visao
  view_range = int(view_range/2)
  bot_coords = np.array([0,view_range])
  angle = 0
  delta = 0
  walkedDistance = 0
  run = True
  step = 0
  global fig, axes
  plt.ion()
  fig, axes = plt.subplots(1, 4, figsize=(15, 8))
  while run == True:
    viewed_coordinates = viewedCoords(dataset, origin=bot_coords, angle=angle, view_range=view_range)
    initial_view_coord = np.array([0,view_range])
    translated_coords = viewed_coordinates - (np.array(bot_coords) - initial_view_coord)
    plotView2(translated_coords, bot_coords, np.rad2deg(angle), view_range) 
    # print(translated_coords)
    ransacRes = RANSAC(translated_coords, view_range)
    

    model = ransacRes.bestModel
    if(model.a == 0):
      delta = 2 * view_range
    else:
      delta = (view_range - model.b) / model.a
    rotated_delta = np.array([delta * np.cos(angle), delta * np.sin(-angle)])
    angle += -np.arctan(model.a)
    print('Step ' + str(step))
    print(delta, angle)
    bot_coords = bot_coords + rotated_delta
    print(rotated_delta)
    print(bot_coords)

    printRansac(ransacRes)
    if input("Pressione enter para continuar ou digite x para parar:\n") == "x":
      run = False
      break
    
    step +=1
    # input()

    walkedDistance += delta
    breakCondition, reason = checkBreakConditions(view_range, delta, bot_coords, walkedDistance)
    if breakCondition == True:
      print("Condicoes de parada encontradas")
      print(reason)
      plt.savefig('views.png')
      input("Pressione enter para encerrar...")
      break
  return


main()