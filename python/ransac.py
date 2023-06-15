import numpy as np
import math

C = 0.50              # The percent of close data points (inliers) required to assert that the model fits well to the data.
E = 8.0               # A threshold value to determine data points that are fit well by the model (inlier).
T = 100

class Line:
  def __init__(self, a, b):
    self.a = a
    self.b = b

class RansacResult:
  def __init__(self, model = Line(0.0, 0.0)):
    self.bestModel = model
    self.bestFit = math.inf
    self.bestQty = 0

rs = RansacResult()

def coefficientOfDetermination(data, model, avg_y):
  ss_res = 0
  ss_tot = 0
  for i in range(len(data)):
    f = model.a * data[i][0] + model.b
    y_f = (data[i][1] - f)
    y_y = (data[i][1] - avg_y)
    ss_res += y_f * y_f
    ss_tot += y_y * y_y
  # r = 1 - (ss_res / ss_tot)  # original coefficient
  r = (ss_res / ss_tot)  # modified coefficient (lower is better)
  return r

def leastSquare(data):
  sx = 0
  sy = 0
  sxy = 0
  sx2 = 0
  n = len(data)
  if(n == 0):
    return Line(math.inf, 0), math.inf
  for i in range(n):
    sx += data[i][0]
    sy += data[i][1]
    sxy += data[i][0] * data[i][1]
    sx2 += data[i][0] * data[i][0]
  avg_y = sy / n
  den = (n * sx2 - sx * sx)
  if(den == 0):
    return Line(math.inf, 0), avg_y
  a = (n * sxy - sx * sy) / den
  b = (sy / n) - a * (sx / n)
  return Line(a, b), avg_y

def inliersOutliers(data, model):
  inliers = []
  outliers = []
  square2 = E * E * (model.a * model.a + 1.0)
  for k in range(len(data)):
    dist = (model.a * data[k][0] - data[k][1] + model.b)
    if (dist * dist <= square2):
      inliers.append(data[k])
    else:
      outliers.append(data[k])
  return inliers, outliers

def nearestOutliers(data, model):
  nearest_outliers = list(map(lambda x: np.array([np.abs(model.a * x[0] - x[1] + model.b), x[0], x[1]]), data))
  nearest_outliers = np.array(nearest_outliers)
  sorted_outliers = nearest_outliers[nearest_outliers[:, 0].argsort()][:,1:]
  return sorted_outliers

def checkModel(data, temp):
  global rs
  model, _ = leastSquare(temp)

  inliers, _ = inliersOutliers(data, model)

  if (len(inliers) >= rs.bestQty and len(inliers) >= int(len(data) * C)):
    inliersModel, inlinersAvg_y = leastSquare(inliers)
    inliersFit = coefficientOfDetermination(data, inliersModel, inlinersAvg_y)
    if (inliersFit < rs.bestFit):
      rs.bestModel = inliersModel
      rs.bestFit = inliersFit
      rs.bestQty = len(inliers)

def RANSAC(data, view_range):
  global rs
  np.seterr(divide='ignore', invalid='ignore')

  rs = RansacResult()

  initial_model = Line(0.0, view_range)

  _, outliers = inliersOutliers(data, initial_model)

  if(len(outliers) == 0):
    return RansacResult(initial_model)

  nearest_outliers = nearestOutliers(outliers, initial_model)

  loopCounter = 0

  for i in range(len(nearest_outliers)):
    for j in range(len(nearest_outliers)-1, 0, -1):
      checkModel(outliers, [nearest_outliers[i], nearest_outliers[j]])
      # print([nearest_outliers[i], nearest_outliers[j]])
      loopCounter += 1
      if(loopCounter >= T): break
    if(loopCounter >= T): break
  return rs