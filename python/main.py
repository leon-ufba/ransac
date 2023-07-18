import numpy as np
from rotCoords import viewedCoords, rotate
from ransac import RANSAC
from mapViewer import MapViewer
from fpgaIntegration import FPGAintegration


STOPINGMODE = False
#Se o STOPINGMODE estiver ligado, espera o enter do usuario a cada ciclo para continuar

def printRansac(rs):
  print("\n------------------------")
  print("bestFit:\t\t%f" % rs.bestFit)
  print("bestQty:\t\t%f" % rs.bestQty)
  print("bestModel:\t%f\t%f" % (rs.bestModel.a, rs.bestModel.b))
  print("------------------------\n")
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
  
  # Inicializa a visao que tem como input o ransac calculado via software
  view = MapViewer("Software", dataset,4) 
  view.startViewer()

  # Inicializa a visao que tem como input o ransac calculado via hardware (txt do fpga)
  viewFPGA= MapViewer("Hardware", dataset,4)
  viewFPGA.startViewer()

  

  # Inicializa a integracao txt com o fpga
  fpga = FPGAintegration('FPGAin', 'FPGAout', view_range)

  #Loop iterativo da movimentaco do robo
  while run == True:
    oldBot_coords = bot_coords
    viewed_coordinates = viewedCoords(dataset, origin=bot_coords, angle=angle, view_range=view_range)
    initial_view_coord = np.array([0,view_range])
    translated_coords = viewed_coordinates - (np.array(bot_coords) - initial_view_coord)

    #Atualiza a vista atual 
    view.updateView(translated_coords, bot_coords, np.rad2deg(angle), view_range) 
    
    #Exporta os dados para o FPGA
    fpga.exportData(step, bot_coords, len(translated_coords), translated_coords) 

    ransacRes = RANSAC(translated_coords, view_range) #Calcula o ransac
    
    model = ransacRes.bestModel
    if(model.a < 0.1 and model.a > -0.1):
      delta = 2 * view_range
    else:
      delta = (view_range - model.b) / model.a
    rotated_delta = np.array([delta * np.cos(angle), delta * np.sin(-angle)])
    angle += -np.arctan(model.a)

    bot_coords = bot_coords + rotated_delta #Atualiza as coordenadas com o novo delta

    #Imprime os dados
    print('Step ' + str(step))
    print(delta, angle)
    print(rotated_delta)
    print(bot_coords)
    printRansac(ransacRes) #Imprime os parametros do ransac


    #Exporta os dados para simular a presenca de um hardware FPGA enviando os dados.
    FPGAangle = np.arctan(ransacRes.bestModel.a)
    fpga.exportData2(step, [ransacRes.bestModel.a, ransacRes.bestModel.b], ransacRes.bestFit, ransacRes.bestQty, FPGAangle, delta, rotated_delta.tolist(), bot_coords.tolist())
    #Comentar a linha acima quando estiver com um FPGA gerando os txts

    #Importa os dados do fpga
    fpga.importData()


    #Atualiza a vista via hardware
    receivedAngle = np.rad2deg(fpga.receivedData.orientation[len(fpga.receivedData.steps)-1])
    viewFPGA.updateView(translated_coords, fpga.receivedData.new_bot_coords[len(fpga.receivedData.steps)-1], receivedAngle, view_range) 

    if STOPINGMODE == True: #Se o STOPINGMODE estiver ligado, espera o enter do usuario a cada ciclo para continuar
      if input("Pressione enter para continuar ou digite x para parar:\n") == "x":
        run = False
        break
    

    #Checa as condicoes de parada
    walkedDistance += delta
    breakCondition, reason = checkBreakConditions(view_range, delta, bot_coords, walkedDistance)
    if breakCondition == True:
      print("Condicoes de parada encontradas")
      print(reason)
      view.updateView([], oldBot_coords, np.rad2deg(angle), view_range) #Vista preta para indicar parada
      view.saveFigure()
      input("Pressione enter para encerrar...")
      break
    
    step +=1
  return


main()