import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib import pyplot as plt, patches
import os


class MapViewer:
    global fig, axes
    global viewArray
    global dataset

    def __init__(self, mode, dataset, columns):
        self.mode = mode
        self.dataset = dataset
        self.columns = columns
        self.viewArray = []
        #white_image = np.ones((50, 50), dtype=np.uint8) * 255
        #viewArray = [white_image, white_image, white_image]

    #Inicializa o visualizador de mapa + visoes
    def startViewer(self):
        plt.ion()
        self.fig, self.axes = plt.subplots(1, self.columns, figsize=(15, 8))
        self.fig.suptitle(self.mode)
        return
    
    #Salva a janela atual do visualizador
    def saveFigure(self):
        self.fig.savefig('MapViewer - ' + self.mode + '.png')
        return

    
    #Atualiza a janela do visualizador com um novo conjunto de dados
    def updateView(self, view_coords, origin, angle, view_range):
        def img_is_color(img):

            if len(img.shape) == 3:
                # Check the color channels to see if they're all the same.
                c1, c2, c3 = img[:, : , 0], img[:, :, 1], img[:, :, 2]
                if (c1 == c2).all() and (c2 == c3).all():
                    return True

            return False
        
        def show_image_list(list_images, list_titles=None, list_cmaps=None, grid=True, num_cols=2, figsize=(20, 10), title_fontsize=30, origin=[0,0], angle=0, view_range=25):

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

           
            #fig, axes = plt.subplots(num_rows, num_cols, figsize=figsize)



            # Create list of axes for easy iteration.
            if isinstance(self.axes, np.ndarray):
                list_axes = list(self.axes.flat)
            else:
                list_axes = [self.axes]

            self.fig.clear()
            self.fig.suptitle(self.mode)
            for ax in self.axes.flatten():
                ax.clear()

            imgpos = 1
            jumps = 0
            for i in range(num_images):    
                axis = self.fig.add_subplot(num_rows, num_cols+1, imgpos)
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
            
            axis = self.fig.add_subplot(1, num_cols+1, num_cols+1)
            image_path = 'imgsDatasets/'+ self.dataset + '.bmp'
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

            self.fig.tight_layout()
            #plt.draw() 
            plt.pause(0.5) #is necessary for the plot to update for some reason

        height, width = (view_range * 2, view_range * 2)
        new_img = np.ones((height, width), dtype='int') * 127
        rounded_coords = (np.rint(view_coords)).astype(int)
        for c in rounded_coords:
            if(0 <= c[0] and c[0] < width and 0 <= c[1] and c[1] < height):
                new_img[c[1]][c[0]] = 0 # Note: SCREEN COORDS ARE INVERTED (y, x)
        im = Image.fromarray(new_img)
        self.viewArray.append(new_img)
        labels = []
        for i in range(len(self.viewArray)):
            labels.append("Step " + str(i))
        show_image_list(list_images=self.viewArray, list_titles=labels , num_cols=3, figsize=(20, 10), grid=False, title_fontsize=20, origin=origin, angle=angle, view_range=view_range)

        #im.show()
        # im.convert('RGB').save("out_test.bmp")
        return

    

