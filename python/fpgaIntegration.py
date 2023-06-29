import os
import numpy as np

class ReceivedData:
    def __init__(self):
        self.steps = []
        self.coefficients = []  # best Model
        self.best_fits = []
        self.best_qtys = []
        self.angles = []
        self.deltas = []
        self.rot_deltas = []
        self.new_bot_coords = []

class FPGAintegration:

    def __init__(self, outputName, inputName):
        
        self.outputName = outputName #nome para o arquivo txt de saida do codigo e entrada no fpga
        self.inputName = inputName #nome esperado para o arquivo gerado pelo fpga, que lido pelo codigo
        
        dirname = os.path.dirname(__file__)
        self.saveDir = os.path.join(dirname, "txtIo/")
        self.outputFile = self.saveDir + self.outputName + ".txt"
        self.inputFile = self.saveDir + self.inputName + ".txt"
        with open(self.outputFile, "w") as file:
            file.truncate(0)
        with open(self.inputFile, "w") as file:
            file.truncate(0)    

        self.receivedData = ReceivedData()


    
    def exportData(self, step, bot_coords, numberOfDots, dots):
        with open(self.outputFile, "a") as file:
            

            # Append the text to the file
            file.write(str(step) + '\n')
            file.write(str(bot_coords) + '\n')
            file.write(str(numberOfDots) + '\n')

            #dots_string = np.array2string(dots, separator=',')
            #file.write(dots_string + "\n")

            for row in dots.astype(int):
                    file.write(str(row) + '\n')

            file.write("\n")
            
    def exportData2(self, step, coefficients, best_fit, best_qty, angle, delta, rot_delta, new_bot_coords):
        with open(self.inputFile, "a") as file:
            
            # Append the text to the file
            file.write(str(step) + '\n')
            file.write(str(coefficients) + '\n')
            file.write(str(best_fit) + '\n')
            file.write(str(best_qty) + '\n')
            file.write(str(angle) + '\n')
            file.write(str(delta) + '\n')
            file.write(str(rot_delta) + '\n')
            file.write(str(new_bot_coords) + '\n')
            file.write("\n")  

      
        
    def importData(self):
        with open(self.inputFile, 'r') as file:
            lines = file.readlines()



        line_index = 0
        while line_index < len(lines):
            # Read the lines and assign them to variables
            step = lines[line_index].strip()
            coefficients_str = lines[line_index + 1].strip()[1:-1]  # Remove brackets []
            best_fit = lines[line_index + 2].strip()
            best_qty = lines[line_index + 3].strip()
            angle = lines[line_index + 4].strip()
            delta_str = lines[line_index + 5].strip()
            rot_delta_str = lines[line_index + 6].strip()[1:-1]  # Remove brackets []
            new_bot_coords_str = lines[line_index + 7].strip()[1:-1]  # Remove brackets []

            # Convert string representations to desired data types
            coefficients = list(map(float, coefficients_str.split(',')))
            rot_delta = list(map(float, rot_delta_str.split(',')))
            new_bot_coords = list(map(float, new_bot_coords_str.split(',')))

            # Append the variables to respective lists
            self.receivedData.steps.append(int(step))
            self.receivedData.coefficients.append(coefficients) #best Model
            self.receivedData.best_fits.append(best_fit)
            self.receivedData.best_qtys.append(int(best_qty))
            self.receivedData.angles.append(float(angle))
            self.receivedData.deltas.append(float(delta_str))
            self.receivedData.rot_deltas.append(rot_delta)
            self.receivedData.new_bot_coords.append(new_bot_coords)

            # Move to the next set of lines
            line_index += 9